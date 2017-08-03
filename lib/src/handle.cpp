#include <ext_handle.h>
#include <vector>
#include <mutex>
#include <assert.h>

#include "handle_p.h"

namespace ext {

struct handle_internal {
  handle_type type  : 8;
  uint64_t    salt  : 24;
  uint64_t    index : 32;
};

struct object_entry {
  uint32_t salt;
  void *obj;
};

struct handle_table {
  std::mutex lock;
  pfn_deleter_t pfn_deleter;
  std::vector<object_entry> entries;
  std::vector<uint32_t> free_list;
};

static handle_table handles[handle_type_count];

static handle_internal & HandleCastToInternal(handle_t &handle) {
  return *reinterpret_cast<handle_internal *>(&handle);
}

static handle_t & HandleCastFromInternal(handle_internal &handle) {
  return *reinterpret_cast<handle_t *>(&handle);
}

void HandleRegisterDeleter(handle_type type, pfn_deleter_t pfn_deleter) {
  handles[type].pfn_deleter = pfn_deleter;
}

handle_t HandleAlloc(handle_type type, void *obj) {
  handle_internal handle;
  handle.type = type;

  handle_table &table = handles[type];
  std::lock_guard<std::mutex> lock(table.lock);

  if (!table.free_list.empty()) {
    handle.index = table.free_list.back();
    handle.salt = table.entries[handle.index].salt;
    table.entries[handle.index].obj = obj;
    table.free_list.pop_back();
  } else {
    handle.index = static_cast<uint32_t>(table.entries.size());
    table.entries.push_back(object_entry());
    handle.salt = table.entries[handle.index].salt = 0;
    table.entries[handle.index].obj = obj;
  }
  return HandleCastFromInternal(handle);
}

void *HandleGetObject(handle_t handle) {
  handle_internal &handle_p = HandleCastToInternal(handle);
  if (handle_p.type == handle_type_unknown || handle_p.type >= handle_type_count) {
    assert(false);
    return nullptr;
  }

  handle_table &table = handles[handle_p.type];
  std::lock_guard<std::mutex> lock(table.lock);

  if (handle_p.index >= table.entries.size()) {
    assert(false);
    return nullptr;
  }

  object_entry &entry = table.entries[handle_p.index];
  if (handle_p.salt != entry.salt) {
    assert(false);
    return nullptr;
  }

  return entry.obj;
}

void HandleFree(handle_t handle) {
  handle_internal &handle_p = HandleCastToInternal(handle);
  if (handle_p.type == handle_type_unknown || handle_p.type >= handle_type_count) {
    assert(false);
    return;
  }

  handle_table &table = handles[handle_p.type];
  std::lock_guard<std::mutex> lock(table.lock);

  if (handle_p.index >= table.entries.size()) {
    assert(false);
    return;
  }

  object_entry &entry = table.entries[handle_p.index];
  if (handle_p.salt != entry.salt) {
    assert(false);
    return;
  }

  if (table.pfn_deleter) {
    table.pfn_deleter(entry.obj);
  }
  
  table.free_list.push_back(handle_p.index);
  entry.salt++;
}

} // namespace ext

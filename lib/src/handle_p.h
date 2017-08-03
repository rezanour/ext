#pragma once

#include <ext_handle.h>

namespace ext {

enum handle_type {
  handle_type_unknown = 0,
  handle_type_gfx_device_gl,

  handle_type_count
};

typedef void (*pfn_deleter_t)(void *obj);

void HandleRegisterDeleter(handle_type type, pfn_deleter_t pfn_deleter);
handle_t HandleAlloc(handle_type type, void *obj);
void *HandleGetObject(handle_t handle);
void HandleFree(handle_t handle);

} // namespace ext

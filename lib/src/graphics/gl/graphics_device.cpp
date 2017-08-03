#include <graphics/graphics_device.h>
#include <OpenGL/gl.h>
#include "../../handle_p.h"

namespace ext {
namespace gl {

struct gfx_device {
  GLuint context;
};

static void GfxDeviceDeleter(void *p) {
  gfx_device *device = static_cast<gfx_device *>(p);
  delete device;
}

handle_t GraphicsDeviceCreate(GraphicsDeviceCreateParams const &create_params) {
  // in case it's not already registered, register the deleter
  HandleRegisterDeleter(handle_type_gfx_device_gl, GfxDeviceDeleter);

  gfx_device *device = new gfx_device;
  if (!device) {
    return EXT_INVALID_HANDLE;
  }

  // TODO: Initialize

  return HandleAlloc(handle_type_gfx_device_gl, device);
}

} // namespace gl
} // namespace ext

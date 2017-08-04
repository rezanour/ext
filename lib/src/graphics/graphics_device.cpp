#include <graphics/graphics_device.h>
#include "../handle_p.h"

namespace ext {

namespace gl {
  handle_t GraphicsDeviceCreate(GraphicsDeviceCreateParams const &create_params);
};

handle_t GraphicsDeviceCreate(GraphicsDeviceCreateParams const &create_params) {
  switch (create_params.API) {
    case Graphics_API_GL:
      return gl::GraphicsDeviceCreate(create_params);

    default:
      assert(false);
      return EXT_INVALID_HANDLE;
  }
}

void GraphicsDeviceDestroy(handle_t graphics_device) {
  HandleFree(graphics_device);
}

} // namespace ext

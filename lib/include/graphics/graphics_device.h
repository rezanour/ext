#pragma once

#include <ext_handle.h>

namespace ext {

enum GraphicsAPI {
  Graphics_API_Unknown = 0,
  Graphics_API_GL,
};

struct GraphicsDeviceCreateParams {
  GraphicsAPI API;
};

handle_t GraphicsDeviceCreate(GraphicsDeviceCreateParams const &create_params);
void GraphicsDeviceDestroy(handle_t graphics_device);

} // namespace ext

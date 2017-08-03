#include <stdio.h>
#include <graphics/graphics_device.h>

int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;

    ext::GraphicsDeviceCreateParams params;
    params.API = ext::Graphics_API_GL;
    ext::handle_t graphics_device = ext::GraphicsDeviceCreate(params);
    if (ext::EXT_INVALID_HANDLE == graphics_device) {
        printf("Failed to create graphics device\n");
        return -1;
    }

    ext::GraphicsDeviceDestroy(graphics_device);
    return 0;
}
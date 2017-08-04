#include <graphics/graphics_device.h>
#include "../../handle_p.h"
#include <stdio.h>

#if EXT_OS_APPLE
#include <OpenGL/gl.h>
#include <OpenGL/OpenGL.h>
#include <OpenGL/CGLTypes.h>
#include <OpenGL/CGLContext.h>
#include <OpenGL/CGLCurrent.h>
#else
#error Only Mac supported at this time
#endif

namespace ext {
namespace gl {

class GfxDevice {
public:
  GfxDevice();
  ~GfxDevice();

  bool Initialize(GraphicsDeviceCreateParams const &create_params);
  void Destroy();

  bool MakeCurrent();
  bool SwapBuffers();

private:
#if EXT_OS_APPLE
  CGLContextObj context_ = nullptr;
#endif
};

static void GfxDeviceDeleter(void *p) {
  GfxDevice *device = static_cast<GfxDevice *>(p);
  delete device;
}

handle_t GraphicsDeviceCreate(GraphicsDeviceCreateParams const &create_params) {
  // in case it's not already registered, register the deleter
  HandleRegisterDeleter(handle_type_gfx_device_gl, GfxDeviceDeleter);

  GfxDevice *device = new GfxDevice();
  if (!device) {
    return EXT_INVALID_HANDLE;
  }

  if (!device->Initialize(create_params)) {
    return EXT_INVALID_HANDLE;
  }

  return HandleAlloc(handle_type_gfx_device_gl, device);
}

GfxDevice::GfxDevice() {
}

GfxDevice::~GfxDevice() {
  Destroy();
}

bool GfxDevice::Initialize(GraphicsDeviceCreateParams const &create_params) {
  // Create surfaceless context
#if EXT_OS_APPLE
  CGLPixelFormatAttribute pixelFormatAttributes[] = {
    kCGLPFAOpenGLProfile, (CGLPixelFormatAttribute) kCGLOGLPVersion_3_2_Core,
    kCGLPFAColorSize, (CGLPixelFormatAttribute) 24,
    kCGLPFAAlphaSize, (CGLPixelFormatAttribute) 8,
    kCGLPFAAccelerated,
    kCGLPFADoubleBuffer,
    kCGLPFASampleBuffers, (CGLPixelFormatAttribute) 1,
    kCGLPFASamples, (CGLPixelFormatAttribute) 4,
    (CGLPixelFormatAttribute) 0,
  };

  CGLPixelFormatObj pixelFormat;
  GLint num_virtual_screens = 0;
  CGLError err = CGLChoosePixelFormat(pixelFormatAttributes, &pixelFormat, &num_virtual_screens);
  assert(kCGLNoError == err);

  err = CGLCreateContext(pixelFormat, 0, &context_);
  assert(kCGLNoError == err);

  CGLDestroyPixelFormat(pixelFormat);
#endif // EXT_OS_APPLE
  return true;
}

void GfxDevice::Destroy() {
#if EXT_OS_APPLE
  CGLSetCurrentContext(nullptr);
  CGLDestroyContext(context_);
  context_ = nullptr;
#endif
}

bool GfxDevice::MakeCurrent() {
#if EXT_OS_APPLE
  CGLError err = CGLSetCurrentContext(context_);
  return (kCGLNoError == err);
#endif
}

bool GfxDevice::SwapBuffers() {
  return true;
}

} // namespace gl
} // namespace ext

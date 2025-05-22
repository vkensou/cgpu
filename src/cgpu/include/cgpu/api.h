#pragma once
#include "platform.h"

#ifdef __cplusplus
CGPU_EXTERN_C_BEGIN
#endif

#include "flags.h"

#define CGPU_MAX_MRT_COUNT 8u
#define CGPU_MAX_VERTEX_ATTRIBS 15
#define CGPU_SHADER_STAGE_COUNT 6

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-const-variable"
#pragma clang diagnostic ignored "-Wunused-variable"
#endif

CGPU_UNUSED static const CGPUBufferId CGPU_BUFFER_OUT_OF_HOST_MEMORY = (CGPUBufferId)1;
CGPU_UNUSED static const CGPUBufferId CGPU_BUFFER_OUT_OF_DEVICE_MEMORY = (CGPUBufferId)3;

static const char* gCGPUBackendNames[CGPU_BACKEND_COUNT] = {
    "vulkan",
    "d3d12",
    "metal",
};

// Above APIs

// Instance APIs

// Adapter APIs

// Device APIs

// API Objects APIs

// Queue APIs

// RenderPass APIs

// Command APIs

// Shader APIs

// Buffer APIs

// Sampler APIs

// Texture/TextureView APIs

// Shared Resource APIs

// Swapchain APIs

// CMDs

// Compute Pass

// Render Pass

// Event & Markers

// EXPERIMENTAL Compiled/Linked ISA APIs

// EXPERIMENTAL StateBuffer APIs

// raster state encoder APIs

// shader state encoder APIs

// user state encoder APIs

// EXPERIMENTAL binder APIs

// cgpux

// Types

// surfaces
CGPU_API CGPUSurfaceId cgpu_surface_from_native_view(CGPUDeviceId device, void* view);
#if defined(_WIN32) || defined(_WIN64)
typedef struct HWND__* HWND;
CGPU_API CGPUSurfaceId cgpu_surface_from_hwnd(CGPUDeviceId device, HWND window);
typedef CGPUSurfaceId (*CGPUSurfaceProc_CreateFromHWND)(CGPUDeviceId device, HWND window);
#endif
#ifdef __APPLE__
// CGPU_API CGPUSurfaceId cgpu_surface_from_ui_view(CGPUDeviceId device, UIView* window);
// typedef CGPUSurfaceId (*CGPUSurfaceProc_CreateFromUIView)(CGPUDeviceId device, UIView* window);
typedef struct CGPUNSView CGPUNSView;
CGPU_API CGPUSurfaceId cgpu_surface_from_ns_view(CGPUDeviceId device, CGPUNSView* window);
typedef CGPUSurfaceId (*CGPUSurfaceProc_CreateFromNSView)(CGPUDeviceId device, CGPUNSView* window);
#endif
#ifdef __ANDROID__
typedef struct ANativeWindow ANativeWindow;
CGPU_API CGPUSurfaceId cgpu_surface_from_native_window(CGPUDeviceId device, ANativeWindow* window);
typedef CGPUSurfaceId(*CGPUSurfaceProc_CreateFromNativeWindow)(CGPUDeviceId device, ANativeWindow* window);
#endif
CGPU_API void cgpu_free_surface(CGPUDeviceId device, CGPUSurfaceId surface);
typedef void (*CGPUSurfaceProc_Free)(CGPUDeviceId device, CGPUSurfaceId surface);
typedef struct CGPUSurfacesProcTable {
#if defined(_WIN32) || defined(_WIN64)
    const CGPUSurfaceProc_CreateFromHWND from_hwnd;
#endif
#ifdef __APPLE__
    // const CGPUSurfaceProc_CreateFromUIView from_ui_view;
    const CGPUSurfaceProc_CreateFromNSView from_ns_view;
#endif
#ifdef __ANDROID__
    const CGPUSurfaceProc_CreateFromNativeWindow from_native_window;
#endif
    const CGPUSurfaceProc_Free free_surface;
} CGPUSurfacesProcTable;

// Shaders

// Descriptors (on Stack)

#ifdef __cplusplus
CGPU_EXTERN_C_END
#endif

#ifdef __clang__
#pragma clang diagnostic pop
#endif
#pragma once
#include "cgpu_vulkan.h"

#ifdef __cplusplus
extern "C" {
#endif

CGPU_API void cgpu_free_surface_vulkan(cgpu_device_id device, CGPUSurfaceId surface);

#if defined(_WIN32) || defined(_WIN64)
CGPU_API CGPUSurfaceId cgpu_surface_from_hwnd_vulkan(cgpu_device_id device, HWND window);
#elif defined(_MACOS)
CGPU_API CGPUSurfaceId cgpu_surface_from_ns_view_vulkan(cgpu_device_id device, CGPUNSView* window);
#elif defined(__ANDROID__)
CGPU_API CGPUSurfaceId cgpu_surface_from_native_window_vulkan(cgpu_device_id device, struct ANativeWindow* window);
#endif

#ifdef __cplusplus
} // end extern "C"
#endif
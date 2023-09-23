#pragma once

#define CGPU_USE_VULKAN

#ifdef _WIN32
    #define CGPU_USE_D3D12
#endif
#ifdef __APPLE__
    #define CGPU_USE_METAL
#endif

#if defined(__EMSCRIPTEN__) || defined(__wasi__)
    #ifdef CGPU_USE_VULKAN
        #undef CGPU_USE_VULKAN
    #endif
#endif

#define MAX_GPU_VENDOR_STRING_LENGTH 64
#define MAX_GPU_DEBUG_NAME_LENGTH 128
#define PSO_NAME_LENGTH 160

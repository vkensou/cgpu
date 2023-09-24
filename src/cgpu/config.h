#pragma once

#ifdef _WIN32
    #define CGPU_USE_D3D12
#endif
#ifdef __APPLE__
    #define CGPU_USE_METAL
#endif

#if UINTPTR_MAX == UINT32_MAX
#define CGPU_NAME_HASH_SEED 1610612741
#else
#define CGPU_NAME_HASH_SEED 8053064571610612741
#endif

CGPU_EXTERN_C CGPU_STATIC_API 
size_t cgpu_hash(const void* buffer, size_t size, size_t seed);

#define cgpu_name_hash(buffer, size) cgpu_hash((buffer), (size), (CGPU_NAME_HASH_SEED))

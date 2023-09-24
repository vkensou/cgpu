#pragma once

#include "cgpu/platform.h"
#include <stdlib.h>
#include <string.h>

#ifdef _DEBUG
    #include "assert.h"
    #define cgpu_assert assert
#else
    #define cgpu_assert(expr) (void)(expr);
#endif
#define cgpu_static_assert static_assert

#if UINTPTR_MAX == UINT32_MAX
    #define CGPU_NAME_HASH_SEED 1610612741
#else
    #define CGPU_NAME_HASH_SEED 8053064571610612741
#endif

size_t cgpu_hash(const void* buffer, size_t size, size_t seed);

#define cgpu_name_hash(buffer, size) cgpu_hash((buffer), (size), (CGPU_NAME_HASH_SEED))

#if defined(__cplusplus)
    #define CGPU_DECLARE_ZERO(type, var) static_assert(std::is_trivially_constructible<type>::value, "not trival, 0 init is invalid!"); type var = {};
#else
    #define CGPU_DECLARE_ZERO(type, var) type var = { 0 };
#endif

#define cgpu_trace(...)
#define cgpu_debug(...)
#define cgpu_info(...)
#define cgpu_warn(...)
#define cgpu_error(...)
#define cgpu_fatal(...)

CGPU_FORCEINLINE static void* _aligned_calloc(size_t nelem, size_t elsize, size_t alignment)
{
    void* memory = _aligned_malloc(nelem * elsize, alignment);
    if (memory != NULL) memset(memory, 0, nelem * elsize);
    return memory;
}
    #define cgpu_malloc malloc
    #define cgpu_malloc_aligned _aligned_malloc
    #define cgpu_malloc_alignedN(size, alignment, ...)  _aligned_malloc(size, alignment)
    #define cgpu_calloc calloc
    #define cgpu_callocN(count, size, ...) calloc((count), (size))
    #define cgpu_calloc_aligned _aligned_calloc
    #define cgpu_memalign _aligned_malloc
    #define cgpu_free free
    #define cgpu_freeN(ptr, ...) free(ptr)
    #define cgpu_free_aligned(ptr, alignment) _aligned_free(ptr)
    #define cgpu_free_alignedN(ptr, alignment, ...) _aligned_free((ptr), (alignment))

#ifdef __cplusplus
#include <utility>
template <typename T, typename... Args>
T* cgpu_new_placed(void* memory, Args&&... args)
{
    return new (memory) T(std::forward<Args>(args)...);
}

template <typename T, typename... Args>
T* cgpu_new(Args&&... args)
{
    void* pMemory = cgpu_malloc_aligned(sizeof(T), alignof(T));
    memset(pMemory, 0, sizeof(T));
    cgpu_assert(pMemory != nullptr);
    return new (pMemory) T{ std::forward<Args>(args)... };
}

template <typename T, typename... Args>
T* cgpu_new_sized(uint64_t size, Args&&... args)
{
    void* ptr = cgpu_calloc_aligned(1, size, alignof(T));
    return cgpu_new_placed<T>(ptr, std::forward<Args>(args)...);
}

template <typename T>
void cgpu_delete_placed(T* object)
{
    object->~T();
}

template <typename T>
void cgpu_delete(T* object)
{
    cgpu_delete_placed(object);
    cgpu_free_aligned(object, alignof(T));
}
#endif

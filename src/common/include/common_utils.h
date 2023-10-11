#pragma once

#include "cgpu/api.h"
#include "cgpu/platform.h"
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

CGPU_EXTERN_C_BEGIN

struct CGPURuntimeTable* cgpu_create_runtime_table();
void cgpu_early_free_runtime_table(struct CGPURuntimeTable* table);
void cgpu_free_runtime_table(struct CGPURuntimeTable* table);
void cgpu_runtime_table_add_queue(CGPUQueueId queue, ECGPUQueueType type, uint32_t index);
CGPUQueueId cgpu_runtime_table_try_get_queue(CGPUDeviceId device, ECGPUQueueType type, uint32_t index);

void cgpu_runtime_table_add_custom_data(struct CGPURuntimeTable* table, const char* key, void* data);
void cgpu_runtime_table_add_sweep_callback(struct CGPURuntimeTable* table, const char* key, void(pfn)(void*), void* usrdata);
void cgpu_runtime_table_add_early_sweep_callback(struct CGPURuntimeTable* table, const char* key, void(pfn)(void*), void* usrdata);
void* cgpu_runtime_table_try_get_custom_data(struct CGPURuntimeTable* table, const char* key);
bool cgpu_runtime_table_remove_custom_data(struct CGPURuntimeTable* table, const char* key);

void CGPUUtil_InitRSParamTables(CGPURootSignature* RS, const struct CGPURootSignatureDescriptor* desc);
void CGPUUtil_FreeRSParamTables(CGPURootSignature* RS);

// check for slot-overlapping and try get a signature from pool
CGPURootSignaturePoolId CGPUUtil_CreateRootSignaturePool(const CGPURootSignaturePoolDescriptor* desc);
CGPURootSignatureId CGPUUtil_TryAllocateSignature(CGPURootSignaturePoolId pool, CGPURootSignature* RSTables, const struct CGPURootSignatureDescriptor* desc);
CGPURootSignatureId CGPUUtil_AddSignature(CGPURootSignaturePoolId pool, CGPURootSignature* sig, const CGPURootSignatureDescriptor* desc);
// TODO: signature pool statics
//void CGPUUtil_AllSignatures(CGPURootSignaturePoolId pool, CGPURootSignatureId* signatures, uint32_t* count);
bool CGPUUtil_PoolFreeSignature(CGPURootSignaturePoolId pool, CGPURootSignatureId sig);
void CGPUUtil_FreeRootSignaturePool(CGPURootSignaturePoolId pool);

#define cgpu_round_up(value, multiple) ((((value) + (multiple)-1) / (multiple)) * (multiple))
#define cgpu_round_down(value, multiple) ((value) - (value) % (multiple))

CGPU_EXTERN_C_END

#ifndef cgpu_max
    #define cgpu_max(a, b) (((a) > (b)) ? (a) : (b))
#endif

#ifndef cgpu_min
    #define cgpu_min(a, b) (((a) < (b)) ? (a) : (b))
#endif

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

// VLA
#ifndef __cplusplus
    #if defined(_MSC_VER) && !defined(__clang__)
        #define CGPU_DECLARE_ZERO_VLA(type, var, num)              \
            type* var = (type*)_alloca(sizeof(type) * (num)); \
            memset((void*)(var), 0, sizeof(type) * (num));
    #else
        #define CGPU_DECLARE_ZERO_VLA(type, var, num) \
            type var[(num)];                     \
            memset((void*)(var), 0, sizeof(type) * (num));
    #endif
#else
    #define CGPU_DECLARE_ZERO_VLA(type, var, num)              \
        type* var = (type*)_alloca(sizeof(type) * (num)); \
        memset((void*)(var), 0, sizeof(type) * (num));
#endif

#define cgpu_trace(...)
#define cgpu_debug(...)
#define cgpu_info(...)
#define cgpu_warn(...)
#define cgpu_error(...)
#define cgpu_fatal(...)

#define CGPU_UNIMPLEMENTED_FUNCTION()

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
T* cgpu_new_aligned(Args&&... args)
{
    void* pMemory = cgpu_malloc_aligned(sizeof(T), alignof(T));
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

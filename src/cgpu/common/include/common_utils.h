#pragma once

#include "cgpu/api.h"
#include "cgpu/platform.h"
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <stdarg.h>
#include <stdio.h>

CGPU_EXTERN_C_BEGIN

struct CGPURuntimeTable* cgpu_create_runtime_table(const CGPUAllocator* allocator);
void cgpu_early_free_runtime_table(struct CGPURuntimeTable* table);
void cgpu_free_runtime_table(const CGPUAllocator* allocator, struct CGPURuntimeTable* table);
void cgpu_runtime_table_add_queue(CGPUQueueId queue, ECGPUQueueType type, uint32_t index);
CGPUQueueId cgpu_runtime_table_try_get_queue(CGPUDeviceId device, ECGPUQueueType type, uint32_t index);

void cgpu_runtime_table_add_custom_data(struct CGPURuntimeTable* table, const char* key, void* data);
void cgpu_runtime_table_add_sweep_callback(struct CGPURuntimeTable* table, const char* key, void(pfn)(void*), void* usrdata);
void cgpu_runtime_table_add_early_sweep_callback(struct CGPURuntimeTable* table, const char* key, void(pfn)(void*), void* usrdata);
void* cgpu_runtime_table_try_get_custom_data(struct CGPURuntimeTable* table, const char* key);
bool cgpu_runtime_table_remove_custom_data(struct CGPURuntimeTable* table, const char* key);

void CGPUUtil_InitRSParamTables(CGPURootSignature* RS, const struct CGPURootSignatureDescriptor* desc, const CGPUAllocator* allocator);
void CGPUUtil_FreeRSParamTables(CGPURootSignature* RS);

// check for slot-overlapping and try get a signature from pool
CGPURootSignaturePoolId CGPUUtil_CreateRootSignaturePool(const CGPUAllocator* allocator, const CGPURootSignaturePoolDescriptor* desc);
CGPURootSignatureId CGPUUtil_TryAllocateSignature(CGPURootSignaturePoolId pool, CGPURootSignature* RSTables, const struct CGPURootSignatureDescriptor* desc);
CGPURootSignatureId CGPUUtil_AddSignature(CGPURootSignaturePoolId pool, CGPURootSignature* sig, const CGPURootSignatureDescriptor* desc);
// TODO: signature pool statics
//void CGPUUtil_AllSignatures(CGPURootSignaturePoolId pool, CGPURootSignatureId* signatures, uint32_t* count);
bool CGPUUtil_PoolFreeSignature(CGPURootSignaturePoolId pool, CGPURootSignatureId sig);
void CGPUUtil_FreeRootSignaturePool(const CGPUAllocator* allocator, CGPURootSignaturePoolId pool);

#define cgpu_round_up(value, multiple) ((((value) + (multiple)-1) / (multiple)) * (multiple))
#define cgpu_round_down(value, multiple) ((value) - (value) % (multiple))

CGPU_EXTERN_C_END

#ifndef cgpu_max
    #define cgpu_max(a, b) (((a) > (b)) ? (a) : (b))
#endif

#ifndef cgpu_min
    #define cgpu_min(a, b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef NDEBUG
    #include "assert.h"
    #define cgpu_assert assert
#else
    #define cgpu_assert(expr) (void)(expr);
#endif
#if defined(__cplusplus)
#define cgpu_static_assert static_assert
#else
#define cgpu_static_assert _Static_assert
#endif

#if UINTPTR_MAX == UINT32_MAX
    #define CGPU_NAME_HASH_SEED 1610612741
#else
    #define CGPU_NAME_HASH_SEED 8053064571610612741
#endif

CGPU_EXTERN_C size_t cgpu_hash(const void* buffer, size_t size, size_t seed);

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

CGPU_FORCEINLINE static void logger_default(void* user_data, ECGPULogSeverity severity, const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
}

#define cgpu_trace(logger, fmt, ...) {(logger)->log_callback((logger)->log_callback_user_data, CGPU_LOG_TRACE, fmt, ##__VA_ARGS__);}
#define cgpu_debug(logger, fmt, ...) {(logger)->log_callback((logger)->log_callback_user_data, CGPU_LOG_DEBUG, fmt, ##__VA_ARGS__);}
#define cgpu_info(logger, fmt, ...) {(logger)->log_callback((logger)->log_callback_user_data, CGPU_LOG_INFO, fmt, ##__VA_ARGS__);}
#define cgpu_warn(logger, fmt, ...) {(logger)->log_callback((logger)->log_callback_user_data, CGPU_LOG_WARNING, fmt, ##__VA_ARGS__);}
#define cgpu_error(logger, fmt, ...) {(logger)->log_callback((logger)->log_callback_user_data, CGPU_LOG_ERROR, fmt, ##__VA_ARGS__);}
#define cgpu_fatal(logger, fmt, ...) {(logger)->log_callback((logger)->log_callback_user_data, CGPU_LOG_FATAL, fmt, ##__VA_ARGS__);}

#define CGPU_UNIMPLEMENTED_FUNCTION()

CGPU_FORCEINLINE static void* cgpu_malloc_default(void* user_data, size_t size, const void* pool)
{
    return malloc(size);
}

CGPU_FORCEINLINE static void* cgpu_realloc_default(void* user_data, void* ptr, size_t size, const void* pool)
{
    return realloc(ptr, size);
}

CGPU_FORCEINLINE static void* cgpu_calloc_default(void* user_data, size_t count, size_t size, const void* pool)
{
    return calloc(count, size);
}

CGPU_FORCEINLINE static void cgpu_free_default(void* user_data, void* ptr, const void* pool)
{
    free(ptr);
}

CGPU_EXTERN_C void* cgpu_malloc_aligned_default(void* user_data, size_t size, size_t alignment, const void* pool);
CGPU_EXTERN_C void* cgpu_realloc_aligned_default(void* user_data, void* ptr, size_t size, size_t alignment, const void* pool);
CGPU_EXTERN_C void* cgpu_calloc_aligned_default(void* user_data, size_t count, size_t size, size_t alignment, const void* pool);
CGPU_EXTERN_C void cgpu_free_aligned_default(void* user_data, void* ptr, const void* pool);

#define cgpu_malloc(allocator, size) (allocator)->malloc_fn((allocator)->user_data, size, 0)
#define cgpu_malloc_aligned(allocator, size, alignment) (allocator)->malloc_aligned_fn((allocator)->user_data, size, alignment, 0)
#define cgpu_malloc_alignedN(allocator, size, alignment, pool) (allocator)->malloc_aligned_fn((allocator)->user_data, size, alignment, pool)
#define cgpu_calloc(allocator, count, size) (allocator)->calloc_fn((allocator)->user_data, count, size, 0)
#define cgpu_callocN(allocator, count, size, pool) (allocator)->calloc_fn((allocator)->user_data, count, size, pool)
#define cgpu_calloc_aligned(allocator, count, size, alignment) (allocator)->calloc_aligned_fn((allocator)->user_data, count, size, alignment, 0)
#define cgpu_free(allocator, ptr) (allocator)->free_fn((allocator)->user_data, ptr, 0)
#define cgpu_freeN(allocator, ptr, pool) (allocator)->free_fn((allocator)->user_data, ptr, pool)
#define cgpu_free_aligned(allocator, ptr) (allocator)->free_aligned_fn((allocator)->user_data, ptr, 0)
#define cgpu_free_alignedN(allocator, ptr, pool) (allocator)->free_aligned_fn((allocator)->user_data, ptr, pool)

#ifdef __cplusplus
#include <utility>
template <typename T, typename... Args>
T* cgpu_new_placed(void* memory, Args&&... args)
{
    return new (memory) T(std::forward<Args>(args)...);
}

template <typename T, typename... Args>
T* cgpu_new(const CGPUAllocator* allocator, Args&&... args)
{
    void* pMemory = cgpu_malloc_aligned(allocator, sizeof(T), alignof(T));
    memset(pMemory, 0, sizeof(T));
    cgpu_assert(pMemory != nullptr);
    return new (pMemory) T{ std::forward<Args>(args)... };
}

template <typename T, typename... Args>
T* cgpu_new_aligned(const CGPUAllocator* allocator, Args&&... args)
{
    void* pMemory = cgpu_malloc_aligned(allocator, sizeof(T), alignof(T));
    cgpu_assert(pMemory != nullptr);
    return new (pMemory) T{ std::forward<Args>(args)... };
}

template <typename T, typename... Args>
T* cgpu_new_sized(const CGPUAllocator* allocator, uint64_t size, Args&&... args)
{
    void* ptr = cgpu_calloc_aligned(allocator, 1, size, alignof(T));
    return cgpu_new_placed<T>(ptr, std::forward<Args>(args)...);
}

template <typename T>
void cgpu_delete_placed(T* object)
{
    object->~T();
}

template <typename T>
void cgpu_delete(const CGPUAllocator* allocator, T* object)
{
    cgpu_delete_placed(object);
    cgpu_free_aligned(allocator, object);
}
#endif

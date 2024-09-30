#include "common_utils.h"
#include <assert.h>

#ifdef CGPU_OS_WINDOWS
void* cgpu_malloc_aligned_default(void* user_data, size_t size, size_t alignment, const void* pool)
{
    return _aligned_malloc(size, alignment);
}

void* cgpu_realloc_aligned_default(void* user_data, void* ptr, size_t size, size_t alignment, const void* pool)
{
    return _aligned_realloc(ptr, size, alignment);
}

void cgpu_free_aligned_default(void* user_data, void* ptr, size_t alignment, const void* pool)
{
    _aligned_free(ptr);
}

#else

typedef struct {
    void* raw;
    size_t size;
    size_t alignment;
} control;

static inline bool _is_power_of_2(size_t x) {
    return ((x & (x - 1)) == 0);
}

void* cgpu_malloc_aligned_default(void* user_data, size_t size, size_t alignment, const void* pool)
{
    void* raw, * ptr;
    control* ctrl;

    if (size == 0)
        return NULL;
    if (!_is_power_of_2(alignment))
        return NULL;
    if (size > (size_t)-1 - alignment)
        return NULL;
    if (size + alignment > (size_t)-1 - sizeof(control))
        return NULL;

    size_t whole_size = size + sizeof(control) + alignment;
    raw = malloc(whole_size);
    if (!raw)
        return NULL;
    ptr = (void*)(((uintptr_t)raw + alignment + sizeof(control) - 1) & ~(alignment - 1));
    ctrl = ((control*)ptr) - 1;
    ctrl->raw = raw;
    ctrl->size = size;
    ctrl->alignment = alignment;
    return ptr;
}

void cgpu_free_aligned_default(void* user_data, void* ptr, size_t alignment, const void* pool)
{
    if (!ptr)
        return;
    control* ctrl = ((control*)ptr) - 1;
    free(ctrl->raw);
}

void* cgpu_realloc_aligned_default(void* user_data, void* ptr, size_t size, size_t alignment, const void* pool)
{
    void* ptr2;
    control* ctrl;

    if (!ptr)
        return cgpu_malloc_aligned_default(user_data, size, alignment, pool);
    if (!size) {
        cgpu_free_aligned_default(user_data, ptr, 1, pool);
        return NULL;
    }
    if (!_is_power_of_2(alignment))
        return NULL;

    ctrl = ((control*)ptr) - 1;
    if (ctrl->alignment != alignment)
        return NULL;
    if (ctrl->size >= size)
        return ptr;

    if (ctrl->size > (size_t)-1 - ctrl->alignment)
        return NULL;
    if (ctrl->size + ctrl->alignment > (size_t)-1 - sizeof(control))
        return NULL;

    ptr2 = cgpu_malloc_aligned_default(user_data, size, alignment, pool);
    if (!ptr2)
        return NULL;

    memcpy(ptr2, ptr, ctrl->size);
    cgpu_free_aligned_default(user_data, ptr, alignment, pool);
    return ptr2;
}

#endif

void* cgpu_calloc_aligned_default(void* user_data, size_t count, size_t size, size_t alignment, const void* pool)
{
    void* memory = cgpu_malloc_aligned_default(user_data, count * size, alignment, pool);
    if (memory != NULL) memset(memory, 0, count * size);
    return memory;
}

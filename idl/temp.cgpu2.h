#ifndef CGPU_C99_H_HEADER_GUARD
#define CGPU_C99_H_HEADER_GUARD

#include <stdarg.h>  // va_list
#include <stdbool.h> // bool
#include <stdint.h>  // uint32_t
#include <stdlib.h>  // size_t

#define DEFINE_CGPU_OBJECT2(name) typedef const struct name* name##_id;

typedef uint32_t ECGPUFlags;
typedef uint32_t ECGPUFlags64;

$cenums

$cflags

$cids

typedef struct CGPUInstanceDescriptor CGPUInstanceDescriptor;
typedef struct CGPUInstanceFeatures CGPUInstanceFeatures;
typedef struct CGPUProcTable CGPUProcTable;
typedef struct CGPUSurfacesProcTable CGPUSurfacesProcTable;
typedef struct CGPURuntimeTable CGPURuntimeTable;
typedef struct CGPUAdapterDetail CGPUAdapterDetail;
typedef struct CGPUDeviceDescriptor CGPUDeviceDescriptor;

$cfuncptrs

$cstructs

$c99decl

#endif // CGPU_C99_H_HEADER_GUARD

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

typedef struct cgpu_instance_descriptor cgpu_instance_descriptor_t;
typedef struct cgpu_instance_features cgpu_instance_features_t;
typedef struct cgpu_proc_table cgpu_proc_table_t;
typedef struct cgpu_surfaces_proc_table cgpu_surfaces_proc_table_t;
typedef struct cgpu_runtime_table cgpu_runtime_table_t;
typedef struct cgpu_adapter_detail cgpu_adapter_detail_t;
typedef struct cgpu_device_descriptor cgpu_device_descriptor_t;

$cfuncptrs

$cstructs

$c99decl

#endif // CGPU_C99_H_HEADER_GUARD

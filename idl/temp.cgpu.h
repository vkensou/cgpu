#ifndef CGPU_C99_H_HEADER_GUARD
#define CGPU_C99_H_HEADER_GUARD

#include <stdarg.h>  // va_list
#include <stdbool.h> // bool
#include <stdint.h>  // uint32_t
#include <stdlib.h>  // size_t

#define DEFINE_CGPU_OBJECT(name) struct name##Descriptor; typedef const struct name* name##Id;

$enums

$flags

$handles

$ids

$structs

#endif // CGPU_C99_H_HEADER_GUARD

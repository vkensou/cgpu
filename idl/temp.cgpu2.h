#ifndef CGPU_C99_H_HEADER_GUARD
#define CGPU_C99_H_HEADER_GUARD

#include <stdarg.h>  // va_list
#include <stdbool.h> // bool
#include <stdint.h>  // uint32_t
#include <stdlib.h>  // size_t

#define DEFINE_CGPU_OBJECT(name) typedef const struct name* name##_id;

$cenums

$cflags

$cids

$cstructs

$c99decl

#endif // CGPU_C99_H_HEADER_GUARD

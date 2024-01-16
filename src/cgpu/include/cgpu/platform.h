#pragma once

#include <stdint.h>
#include <stdbool.h>
#ifdef __cplusplus
    #define CGPU_NULL nullptr
#else
    #define CGPU_NULL 0
#endif

#ifdef __cplusplus
    #ifndef CGPU_NULLPTR
        #define CGPU_NULLPTR nullptr
    #endif
#else
    #ifndef CGPU_NULLPTR
        #define CGPU_NULLPTR CGPU_NULL
    #endif
#endif

#define MAX_GPU_VENDOR_STRING_LENGTH 64
#define MAX_GPU_DEBUG_NAME_LENGTH 128
#define PSO_NAME_LENGTH 160

#if defined(__cplusplus)
    #define CGPU_UNUSED [[maybe_unused]]
#elif defined(__GNUC__) || defined(__clang__)
    #define CGPU_UNUSED __attribute__((unused))
#elif defined(_MSC_VER)
    #define CGPU_UNUSED 
#endif

#ifndef CGPU_STATIC_API
    #define CGPU_STATIC_API
#endif

#ifndef CGPU_API // If the build file hasn't already defined this to be dllexport...
    #ifdef RUNTIME_SHARED
        #if defined(_MSC_VER)
            #define CGPU_API __declspec(dllimport)
        #elif defined(__CYGWIN__)
            #define CGPU_API __attribute__((dllimport))
        #elif (defined(__GNUC__) && (__GNUC__ >= 4))
            #define CGPU_API __attribute__((visibility("default")))
        #else
            #define CGPU_API
        #endif
    #else
        #define CGPU_API
    #endif
#endif

#ifndef CGPU_EXTERN_C
#ifdef __cplusplus
    #define CGPU_EXTERN_C extern "C"
#else
    #define CGPU_EXTERN_C
#endif
#endif

#ifndef CGPU_EXTERN_C_BEGIN
#ifdef __cplusplus
    #define CGPU_EXTERN_C_BEGIN extern "C" {
#else
    #define CGPU_EXTERN_C_BEGIN
#endif
#endif

#ifndef CGPU_EXTERN_C_END
#ifdef __cplusplus
    #define CGPU_EXTERN_C_END }
#else
    #define CGPU_EXTERN_C_END
#endif
#endif

#if defined(_WIN32) || defined(_WIN64)
#define CGPU_OS_WINDOWS
#endif

#if defined(_MSC_VER) && !defined(__clang__)
#ifndef CGPU_FORCEINLINE
    #define CGPU_FORCEINLINE __forceinline
#endif
    #define DEFINE_ALIGNED(def, a) __declspec(align(a)) def
#else
#ifndef CGPU_FORCEINLINE
    #define CGPU_FORCEINLINE inline __attribute__((always_inline))
#endif
    #define DEFINE_ALIGNED(def, a) __attribute__((aligned(a))) def
#endif

#ifdef __cplusplus
    #define CGPU_IF_CPP(...) __VA_ARGS__
#else
    #define CGPU_IF_CPP(...)
#endif

#if defined(_MSC_VER)
    #define CGPU_ALIGNAS(x) __declspec(align(x))
#else
    #define CGPU_ALIGNAS(x) __attribute__((aligned(x)))
#endif

#if defined(__x86_64__) || defined(_M_X64) || defined(_AMD64_) || defined(_M_AMD64)
    #define CGPU_PLATFORM_X86_64
#elif defined(__i386) || defined(_M_IX86) || defined(_X86_)
    #define CGPU_PLATFORM_X86
#elif defined(__aarch64__) || defined(__AARCH64) || defined(_M_ARM64)
    #define CGPU_PLATFORM_ARM64
#elif defined(__arm__) || defined(_M_ARM)
    #define CGPU_PLATFORM_ARM32
#elif defined(__POWERPC64__) || defined(__powerpc64__)
    #define CGPU_PLATFORM_POWERPC64
#elif defined(__POWERPC__) || defined(__powerpc__)
    #define CGPU_PLATFORM_POWERPC32
#elif defined(__wasm64__)
    #define CGPU_PLATFORM_WA
    #define CGPU_PLATFORM_WA64
#elif defined(__wasm__) || defined(__EMSCRIPTEN__) || defined(__wasi__)
    #define CGPU_PLATFORM_WA
    #define CGPU_PLATFORM_WA32
#else
    #error Unrecognized CPU was used.
#endif

#if defined(CGPU_PLATFORM_WA32)
    #define size_t uint32_t;
    typedef int64_t host_ptr_t;
#endif

// PTR SIZE
#if INTPTR_MAX == 0x7FFFFFFFFFFFFFFFLL
    #define PTR_SIZE 8
#elif INTPTR_MAX == 0x7FFFFFFF
    #define PTR_SIZE 4
#else
    #error unsupported platform
#endif

#if __cplusplus >= 201100L
#define CGPU_UTF8(str) u8##str
#else
#define CGPU_UTF8(str) str
#endif

#if __cpp_char8_t
#define CHAR8_T_DEFINED
#endif

#ifndef CHAR8_T_DEFINED // If the user hasn't already defined these...
    #if defined(EA_PLATFORM_APPLE)
        #define char8_t char // The Apple debugger is too stupid to realize char8_t is typedef'd to char, so we #define it.
    #else
        typedef char char8_t;
    #endif
    #define CHAR8_T_DEFINED
#endif

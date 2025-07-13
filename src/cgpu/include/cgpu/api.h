#pragma once

#ifndef CGPU_API_HEADER_GUARD
#define CGPU_API_HEADER_GUARD

#include "platform.h"

#ifdef __cplusplus
CGPU_EXTERN_C_BEGIN
#endif

#include <stdarg.h>  // va_list
#include <stdbool.h> // bool
#include <stdint.h>  // uint32_t
#include <stdlib.h>  // size_t

#define CGPU_MAX_MRT_COUNT 8

#define CGPU_MAX_ATTACHMENT_COUNT 9

#define CGPU_MAX_VERTEX_ATTRIBUTES 15

#define CGPU_SHADER_STAGE_COUNT 6


#define DEFINE_CGPU_OBJECT(name) typedef const struct name* name##Id;

typedef uint32_t ECGPUFlags;
typedef uint32_t ECGPUFlags64;
typedef struct HWND__* HWND;
typedef struct ANativeWindow ANativeWindow;
typedef ANativeWindow* ANativeWindowPtr;

typedef enum ECGPUBackend
{
    CGPU_BACKEND_VULKAN,                      /** ( 0) Vulkan                         */
    CGPU_BACKEND_D3D12,                       /** ( 1) D3D12                          */
    CGPU_BACKEND_METAL,                       /** ( 2) Metal                          */

    CGPU_BACKEND_COUNT

} ECGPUBackend;

typedef enum ECGPUBlendFactor
{
    CGPU_BLEND_FACTOR_ZERO,                   /** ( 0)                                */
    CGPU_BLEND_FACTOR_ONE,                    /** ( 1)                                */
    CGPU_BLEND_FACTOR_SRC_COLOR,              /** ( 2)                                */
    CGPU_BLEND_FACTOR_ONE_MINUS_SRC_COLOR,    /** ( 3)                                */
    CGPU_BLEND_FACTOR_DST_COLOR,              /** ( 4)                                */
    CGPU_BLEND_FACTOR_ONE_MINUS_DST_COLOR,    /** ( 5)                                */
    CGPU_BLEND_FACTOR_SRC_ALPHA,              /** ( 6)                                */
    CGPU_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA,    /** ( 7)                                */
    CGPU_BLEND_FACTOR_DST_ALPHA,              /** ( 8)                                */
    CGPU_BLEND_FACTOR_ONE_MINUS_DST_ALPHA,    /** ( 9)                                */
    CGPU_BLEND_FACTOR_SRC_ALPHA_SATURATE,     /** (10)                                */

    CGPU_BLEND_FACTOR_COUNT

} ECGPUBlendFactor;

typedef enum ECGPUBlendOp
{
    CGPU_BLEND_OP_ADD,                        /** ( 0)                                */
    CGPU_BLEND_OP_SUBTRACT,                   /** ( 1)                                */
    CGPU_BLEND_OP_REVERSE_SUBTRACT,           /** ( 2)                                */
    CGPU_BLEND_OP_MIN,                        /** ( 3)                                */
    CGPU_BLEND_OP_MAX,                        /** ( 4)                                */

    CGPU_BLEND_OP_COUNT

} ECGPUBlendOp;

typedef enum ECGPULogSeverity
{
    CGPU_LOG_SEVERITY_TRACE,                  /** ( 0)                                */
    CGPU_LOG_SEVERITY_DEBUG,                  /** ( 1)                                */
    CGPU_LOG_SEVERITY_INFO,                   /** ( 2)                                */
    CGPU_LOG_SEVERITY_WARNING,                /** ( 3)                                */
    CGPU_LOG_SEVERITY_ERROR,                  /** ( 4)                                */
    CGPU_LOG_SEVERITY_FATAL,                  /** ( 5)                                */

    CGPU_LOG_SEVERITY_COUNT

} ECGPULogSeverity;

typedef enum ECGPUTextureFormat
{
    CGPU_TEXTURE_FORMAT_UNDEFINED,            /** ( 0)                                */
    CGPU_TEXTURE_FORMAT_R4G4_UNORM_PACK8,     /** ( 1)                                */
    CGPU_TEXTURE_FORMAT_R4G4B4A4_UNORM_PACK16, /** ( 2)                                */
    CGPU_TEXTURE_FORMAT_B4G4R4A4_UNORM_PACK16, /** ( 3)                                */
    CGPU_TEXTURE_FORMAT_R5G6B5_UNORM_PACK16,  /** ( 4)                                */
    CGPU_TEXTURE_FORMAT_B5G6R5_UNORM_PACK16,  /** ( 5)                                */
    CGPU_TEXTURE_FORMAT_R5G5B5A1_UNORM_PACK16, /** ( 6)                                */
    CGPU_TEXTURE_FORMAT_B5G5R5A1_UNORM_PACK16, /** ( 7)                                */
    CGPU_TEXTURE_FORMAT_A1R5G5B5_UNORM_PACK16, /** ( 8)                                */
    CGPU_TEXTURE_FORMAT_R8_UNORM,             /** ( 9)                                */
    CGPU_TEXTURE_FORMAT_R8_SNORM,             /** (10)                                */
    CGPU_TEXTURE_FORMAT_R8_UINT,              /** (11)                                */
    CGPU_TEXTURE_FORMAT_R8_SINT,              /** (12)                                */
    CGPU_TEXTURE_FORMAT_R8_SRGB,              /** (13)                                */
    CGPU_TEXTURE_FORMAT_R8G8_UNORM,           /** (14)                                */
    CGPU_TEXTURE_FORMAT_R8G8_SNORM,           /** (15)                                */
    CGPU_TEXTURE_FORMAT_R8G8_UINT,            /** (16)                                */
    CGPU_TEXTURE_FORMAT_R8G8_SINT,            /** (17)                                */
    CGPU_TEXTURE_FORMAT_R8G8_SRGB,            /** (18)                                */
    CGPU_TEXTURE_FORMAT_R8G8B8_UNORM,         /** (19)                                */
    CGPU_TEXTURE_FORMAT_R8G8B8_SNORM,         /** (20)                                */
    CGPU_TEXTURE_FORMAT_R8G8B8_UINT,          /** (21)                                */
    CGPU_TEXTURE_FORMAT_R8G8B8_SINT,          /** (22)                                */
    CGPU_TEXTURE_FORMAT_R8G8B8_SRGB,          /** (23)                                */
    CGPU_TEXTURE_FORMAT_B8G8R8_UNORM,         /** (24)                                */
    CGPU_TEXTURE_FORMAT_B8G8R8_SNORM,         /** (25)                                */
    CGPU_TEXTURE_FORMAT_B8G8R8_UINT,          /** (26)                                */
    CGPU_TEXTURE_FORMAT_B8G8R8_SINT,          /** (27)                                */
    CGPU_TEXTURE_FORMAT_B8G8R8_SRGB,          /** (28)                                */
    CGPU_TEXTURE_FORMAT_R8G8B8A8_UNORM,       /** (29)                                */
    CGPU_TEXTURE_FORMAT_R8G8B8A8_SNORM,       /** (30)                                */
    CGPU_TEXTURE_FORMAT_R8G8B8A8_UINT,        /** (31)                                */
    CGPU_TEXTURE_FORMAT_R8G8B8A8_SINT,        /** (32)                                */
    CGPU_TEXTURE_FORMAT_R8G8B8A8_SRGB,        /** (33)                                */
    CGPU_TEXTURE_FORMAT_B8G8R8A8_UNORM,       /** (34)                                */
    CGPU_TEXTURE_FORMAT_B8G8R8A8_SNORM,       /** (35)                                */
    CGPU_TEXTURE_FORMAT_B8G8R8A8_UINT,        /** (36)                                */
    CGPU_TEXTURE_FORMAT_B8G8R8A8_SINT,        /** (37)                                */
    CGPU_TEXTURE_FORMAT_B8G8R8A8_SRGB,        /** (38)                                */
    CGPU_TEXTURE_FORMAT_A8B8G8R8_UNORM_PACK32, /** (39)                                */
    CGPU_TEXTURE_FORMAT_A8B8G8R8_SNORM_PACK32, /** (40)                                */
    CGPU_TEXTURE_FORMAT_A8B8G8R8_UINT_PACK32, /** (41)                                */
    CGPU_TEXTURE_FORMAT_A8B8G8R8_SINT_PACK32, /** (42)                                */
    CGPU_TEXTURE_FORMAT_A8B8G8R8_SRGB_PACK32, /** (43)                                */
    CGPU_TEXTURE_FORMAT_A2R10G10B10_UNORM_PACK32, /** (44)                                */
    CGPU_TEXTURE_FORMAT_A2R10G10B10_SNORM_PACK32, /** (45)                                */
    CGPU_TEXTURE_FORMAT_A2R10G10B10_UINT_PACK32, /** (46)                                */
    CGPU_TEXTURE_FORMAT_A2R10G10B10_SINT_PACK32, /** (47)                                */
    CGPU_TEXTURE_FORMAT_A2B10G10R10_UNORM_PACK32, /** (48)                                */
    CGPU_TEXTURE_FORMAT_A2B10G10R10_SNORM_PACK32, /** (49)                                */
    CGPU_TEXTURE_FORMAT_A2B10G10R10_UINT_PACK32, /** (50)                                */
    CGPU_TEXTURE_FORMAT_A2B10G10R10_SINT_PACK32, /** (51)                                */
    CGPU_TEXTURE_FORMAT_R16_UNORM,            /** (52)                                */
    CGPU_TEXTURE_FORMAT_R16_SNORM,            /** (53)                                */
    CGPU_TEXTURE_FORMAT_R16_UINT,             /** (54)                                */
    CGPU_TEXTURE_FORMAT_R16_SINT,             /** (55)                                */
    CGPU_TEXTURE_FORMAT_R16_SFLOAT,           /** (56)                                */
    CGPU_TEXTURE_FORMAT_R16G16_UNORM,         /** (57)                                */
    CGPU_TEXTURE_FORMAT_R16G16_SNORM,         /** (58)                                */
    CGPU_TEXTURE_FORMAT_R16G16_UINT,          /** (59)                                */
    CGPU_TEXTURE_FORMAT_R16G16_SINT,          /** (60)                                */
    CGPU_TEXTURE_FORMAT_R16G16_SFLOAT,        /** (61)                                */
    CGPU_TEXTURE_FORMAT_R16G16B16_UNORM,      /** (62)                                */
    CGPU_TEXTURE_FORMAT_R16G16B16_SNORM,      /** (63)                                */
    CGPU_TEXTURE_FORMAT_R16G16B16_UINT,       /** (64)                                */
    CGPU_TEXTURE_FORMAT_R16G16B16_SINT,       /** (65)                                */
    CGPU_TEXTURE_FORMAT_R16G16B16_SFLOAT,     /** (66)                                */
    CGPU_TEXTURE_FORMAT_R16G16B16A16_UNORM,   /** (67)                                */
    CGPU_TEXTURE_FORMAT_R16G16B16A16_SNORM,   /** (68)                                */
    CGPU_TEXTURE_FORMAT_R16G16B16A16_UINT,    /** (69)                                */
    CGPU_TEXTURE_FORMAT_R16G16B16A16_SINT,    /** (70)                                */
    CGPU_TEXTURE_FORMAT_R16G16B16A16_SFLOAT,  /** (71)                                */
    CGPU_TEXTURE_FORMAT_R32_UINT,             /** (72)                                */
    CGPU_TEXTURE_FORMAT_R32_SINT,             /** (73)                                */
    CGPU_TEXTURE_FORMAT_R32_SFLOAT,           /** (74)                                */
    CGPU_TEXTURE_FORMAT_R32G32_UINT,          /** (75)                                */
    CGPU_TEXTURE_FORMAT_R32G32_SINT,          /** (76)                                */
    CGPU_TEXTURE_FORMAT_R32G32_SFLOAT,        /** (77)                                */
    CGPU_TEXTURE_FORMAT_R32G32B32_UINT,       /** (78)                                */
    CGPU_TEXTURE_FORMAT_R32G32B32_SINT,       /** (79)                                */
    CGPU_TEXTURE_FORMAT_R32G32B32_SFLOAT,     /** (80)                                */
    CGPU_TEXTURE_FORMAT_R32G32B32A32_UINT,    /** (81)                                */
    CGPU_TEXTURE_FORMAT_R32G32B32A32_SINT,    /** (82)                                */
    CGPU_TEXTURE_FORMAT_R32G32B32A32_SFLOAT,  /** (83)                                */
    CGPU_TEXTURE_FORMAT_R64_UINT,             /** (84)                                */
    CGPU_TEXTURE_FORMAT_R64_SINT,             /** (85)                                */
    CGPU_TEXTURE_FORMAT_R64_SFLOAT,           /** (86)                                */
    CGPU_TEXTURE_FORMAT_R64G64_UINT,          /** (87)                                */
    CGPU_TEXTURE_FORMAT_R64G64_SINT,          /** (88)                                */
    CGPU_TEXTURE_FORMAT_R64G64_SFLOAT,        /** (89)                                */
    CGPU_TEXTURE_FORMAT_R64G64B64_UINT,       /** (90)                                */
    CGPU_TEXTURE_FORMAT_R64G64B64_SINT,       /** (91)                                */
    CGPU_TEXTURE_FORMAT_R64G64B64_SFLOAT,     /** (92)                                */
    CGPU_TEXTURE_FORMAT_R64G64B64A64_UINT,    /** (93)                                */
    CGPU_TEXTURE_FORMAT_R64G64B64A64_SINT,    /** (94)                                */
    CGPU_TEXTURE_FORMAT_R64G64B64A64_SFLOAT,  /** (95)                                */
    CGPU_TEXTURE_FORMAT_B10G11R11_UFLOAT_PACK32, /** (96)                                */
    CGPU_TEXTURE_FORMAT_E5B9G9R9_UFLOAT_PACK32, /** (97)                                */
    CGPU_TEXTURE_FORMAT_D16_UNORM,            /** (98)                                */
    CGPU_TEXTURE_FORMAT_X8_D24_UNORM_PACK32,  /** (99)                                */
    CGPU_TEXTURE_FORMAT_D32_SFLOAT,           /** (100)                                */
    CGPU_TEXTURE_FORMAT_S8_UINT,              /** (101)                                */
    CGPU_TEXTURE_FORMAT_D16_UNORM_S8_UINT,    /** (102)                                */
    CGPU_TEXTURE_FORMAT_D24_UNORM_S8_UINT,    /** (103)                                */
    CGPU_TEXTURE_FORMAT_D32_SFLOAT_S8_UINT,   /** (104)                                */
    CGPU_TEXTURE_FORMAT_BC1_RGB_UNORM_BLOCK,  /** (105)                                */
    CGPU_TEXTURE_FORMAT_BC1_RGB_SRGB_BLOCK,   /** (106)                                */
    CGPU_TEXTURE_FORMAT_BC1_RGBA_UNORM_BLOCK, /** (107)                                */
    CGPU_TEXTURE_FORMAT_BC1_RGBA_SRGB_BLOCK,  /** (108)                                */
    CGPU_TEXTURE_FORMAT_BC2_UNORM_BLOCK,      /** (109)                                */
    CGPU_TEXTURE_FORMAT_BC2_SRGB_BLOCK,       /** (110)                                */
    CGPU_TEXTURE_FORMAT_BC3_UNORM_BLOCK,      /** (111)                                */
    CGPU_TEXTURE_FORMAT_BC3_SRGB_BLOCK,       /** (112)                                */
    CGPU_TEXTURE_FORMAT_BC4_UNORM_BLOCK,      /** (113)                                */
    CGPU_TEXTURE_FORMAT_BC4_SNORM_BLOCK,      /** (114)                                */
    CGPU_TEXTURE_FORMAT_BC5_UNORM_BLOCK,      /** (115)                                */
    CGPU_TEXTURE_FORMAT_BC5_SNORM_BLOCK,      /** (116)                                */
    CGPU_TEXTURE_FORMAT_BC6H_UFLOAT_BLOCK,    /** (117)                                */
    CGPU_TEXTURE_FORMAT_BC6H_SFLOAT_BLOCK,    /** (118)                                */
    CGPU_TEXTURE_FORMAT_BC7_UNORM_BLOCK,      /** (119)                                */
    CGPU_TEXTURE_FORMAT_BC7_SRGB_BLOCK,       /** (120)                                */
    CGPU_TEXTURE_FORMAT_PVRTC1_2BPP_UNORM_BLOCK, /** (121)                                */
    CGPU_TEXTURE_FORMAT_PVRTC1_4BPP_UNORM_BLOCK, /** (122)                                */
    CGPU_TEXTURE_FORMAT_PVRTC2_2BPP_UNORM_BLOCK, /** (123)                                */
    CGPU_TEXTURE_FORMAT_PVRTC2_4BPP_UNORM_BLOCK, /** (124)                                */
    CGPU_TEXTURE_FORMAT_PVRTC1_2BPP_SRGB_BLOCK, /** (125)                                */
    CGPU_TEXTURE_FORMAT_PVRTC1_4BPP_SRGB_BLOCK, /** (126)                                */
    CGPU_TEXTURE_FORMAT_PVRTC2_2BPP_SRGB_BLOCK, /** (127)                                */
    CGPU_TEXTURE_FORMAT_PVRTC2_4BPP_SRGB_BLOCK, /** (128)                                */
    CGPU_TEXTURE_FORMAT_ETC2_R8G8B8_UNORM_BLOCK, /** (129)                                */
    CGPU_TEXTURE_FORMAT_ETC2_R8G8B8_SRGB_BLOCK, /** (130)                                */
    CGPU_TEXTURE_FORMAT_ETC2_R8G8B8A1_UNORM_BLOCK, /** (131)                                */
    CGPU_TEXTURE_FORMAT_ETC2_R8G8B8A1_SRGB_BLOCK, /** (132)                                */
    CGPU_TEXTURE_FORMAT_ETC2_R8G8B8A8_UNORM_BLOCK, /** (133)                                */
    CGPU_TEXTURE_FORMAT_ETC2_R8G8B8A8_SRGB_BLOCK, /** (134)                                */
    CGPU_TEXTURE_FORMAT_EAC_R11_UNORM_BLOCK,  /** (135)                                */
    CGPU_TEXTURE_FORMAT_EAC_R11_SNORM_BLOCK,  /** (136)                                */
    CGPU_TEXTURE_FORMAT_EAC_R11G11_UNORM_BLOCK, /** (137)                                */
    CGPU_TEXTURE_FORMAT_EAC_R11G11_SNORM_BLOCK, /** (138)                                */
    CGPU_TEXTURE_FORMAT_ASTC_4X4_UNORM_BLOCK, /** (139)                                */
    CGPU_TEXTURE_FORMAT_ASTC_4X4_SRGB_BLOCK,  /** (140)                                */
    CGPU_TEXTURE_FORMAT_ASTC_5X4_UNORM_BLOCK, /** (141)                                */
    CGPU_TEXTURE_FORMAT_ASTC_5X4_SRGB_BLOCK,  /** (142)                                */
    CGPU_TEXTURE_FORMAT_ASTC_5X5_UNORM_BLOCK, /** (143)                                */
    CGPU_TEXTURE_FORMAT_ASTC_5X5_SRGB_BLOCK,  /** (144)                                */
    CGPU_TEXTURE_FORMAT_ASTC_6X5_UNORM_BLOCK, /** (145)                                */
    CGPU_TEXTURE_FORMAT_ASTC_6X5_SRGB_BLOCK,  /** (146)                                */
    CGPU_TEXTURE_FORMAT_ASTC_6X6_UNORM_BLOCK, /** (147)                                */
    CGPU_TEXTURE_FORMAT_ASTC_6X6_SRGB_BLOCK,  /** (148)                                */
    CGPU_TEXTURE_FORMAT_ASTC_8X5_UNORM_BLOCK, /** (149)                                */
    CGPU_TEXTURE_FORMAT_ASTC_8X5_SRGB_BLOCK,  /** (150)                                */
    CGPU_TEXTURE_FORMAT_ASTC_8X6_UNORM_BLOCK, /** (151)                                */
    CGPU_TEXTURE_FORMAT_ASTC_8X6_SRGB_BLOCK,  /** (152)                                */
    CGPU_TEXTURE_FORMAT_ASTC_8X8_UNORM_BLOCK, /** (153)                                */
    CGPU_TEXTURE_FORMAT_ASTC_8X8_SRGB_BLOCK,  /** (154)                                */
    CGPU_TEXTURE_FORMAT_ASTC_10X5_UNORM_BLOCK, /** (155)                                */
    CGPU_TEXTURE_FORMAT_ASTC_10X5_SRGB_BLOCK, /** (156)                                */
    CGPU_TEXTURE_FORMAT_ASTC_10X6_UNORM_BLOCK, /** (157)                                */
    CGPU_TEXTURE_FORMAT_ASTC_10X6_SRGB_BLOCK, /** (158)                                */
    CGPU_TEXTURE_FORMAT_ASTC_10X8_UNORM_BLOCK, /** (159)                                */
    CGPU_TEXTURE_FORMAT_ASTC_10X8_SRGB_BLOCK, /** (160)                                */
    CGPU_TEXTURE_FORMAT_ASTC_10X10_UNORM_BLOCK, /** (161)                                */
    CGPU_TEXTURE_FORMAT_ASTC_10X10_SRGB_BLOCK, /** (162)                                */
    CGPU_TEXTURE_FORMAT_ASTC_12X10_UNORM_BLOCK, /** (163)                                */
    CGPU_TEXTURE_FORMAT_ASTC_12X10_SRGB_BLOCK, /** (164)                                */
    CGPU_TEXTURE_FORMAT_ASTC_12X12_UNORM_BLOCK, /** (165)                                */
    CGPU_TEXTURE_FORMAT_ASTC_12X12_SRGB_BLOCK, /** (166)                                */
    CGPU_TEXTURE_FORMAT_ASTC_4X4_SFLOAT_BLOCK, /** (167)                                */
    CGPU_TEXTURE_FORMAT_ASTC_5X4_SFLOAT_BLOCK, /** (168)                                */
    CGPU_TEXTURE_FORMAT_ASTC_5X5_SFLOAT_BLOCK, /** (169)                                */
    CGPU_TEXTURE_FORMAT_ASTC_6X5_SFLOAT_BLOCK, /** (170)                                */
    CGPU_TEXTURE_FORMAT_ASTC_6X6_SFLOAT_BLOCK, /** (171)                                */
    CGPU_TEXTURE_FORMAT_ASTC_8X5_SFLOAT_BLOCK, /** (172)                                */
    CGPU_TEXTURE_FORMAT_ASTC_8X6_SFLOAT_BLOCK, /** (173)                                */
    CGPU_TEXTURE_FORMAT_ASTC_8X8_SFLOAT_BLOCK, /** (174)                                */
    CGPU_TEXTURE_FORMAT_ASTC_10X5_SFLOAT_BLOCK, /** (175)                                */
    CGPU_TEXTURE_FORMAT_ASTC_10X6_SFLOAT_BLOCK, /** (176)                                */
    CGPU_TEXTURE_FORMAT_ASTC_10X8_SFLOAT_BLOCK, /** (177)                                */
    CGPU_TEXTURE_FORMAT_ASTC_10X10_SFLOAT_BLOCK, /** (178)                                */
    CGPU_TEXTURE_FORMAT_ASTC_12X10_SFLOAT_BLOCK, /** (179)                                */
    CGPU_TEXTURE_FORMAT_ASTC_12X12_SFLOAT_BLOCK, /** (180)                                */

    CGPU_TEXTURE_FORMAT_COUNT

} ECGPUTextureFormat;

typedef enum ECGPUFilterType
{
    CGPU_FILTER_TYPE_NEAREST,                 /** ( 0)                                */
    CGPU_FILTER_TYPE_LINEAR,                  /** ( 1)                                */

    CGPU_FILTER_TYPE_COUNT

} ECGPUFilterType;

typedef enum ECGPUAddressMode
{
    CGPU_ADDRESS_MODE_MIRROR,                 /** ( 0)                                */
    CGPU_ADDRESS_MODE_REPEAT,                 /** ( 1)                                */
    CGPU_ADDRESS_MODE_CLAMP_TO_EDGE,          /** ( 2)                                */
    CGPU_ADDRESS_MODE_CLAMP_TO_BORDER,        /** ( 3)                                */

    CGPU_ADDRESS_MODE_COUNT

} ECGPUAddressMode;

typedef enum ECGPUMipMapMode
{
    CGPU_MIP_MAP_MODE_NEAREST,                /** ( 0)                                */
    CGPU_MIP_MAP_MODE_LINEAR,                 /** ( 1)                                */

    CGPU_MIP_MAP_MODE_COUNT

} ECGPUMipMapMode;

typedef enum ECGPULoadAction
{
    CGPU_LOAD_ACTION_DONT_CARE,               /** ( 0)                                */
    CGPU_LOAD_ACTION_LOAD,                    /** ( 1)                                */
    CGPU_LOAD_ACTION_CLEAR,                   /** ( 2)                                */

    CGPU_LOAD_ACTION_COUNT

} ECGPULoadAction;

typedef enum ECGPUStoreAction
{
    CGPU_STORE_ACTION_STORE,                  /** ( 0)                                */
    CGPU_STORE_ACTION_DISCARD,                /** ( 1)                                */

    CGPU_STORE_ACTION_COUNT

} ECGPUStoreAction;

typedef enum ECGPUPrimitiveTopology
{
    CGPU_PRIMITIVE_TOPOLOGY_POINT_LIST,       /** ( 0)                                */
    CGPU_PRIMITIVE_TOPOLOGY_LINE_LIST,        /** ( 1)                                */
    CGPU_PRIMITIVE_TOPOLOGY_LINE_STRIP,       /** ( 2)                                */
    CGPU_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,    /** ( 3)                                */
    CGPU_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP,   /** ( 4)                                */
    CGPU_PRIMITIVE_TOPOLOGY_PATCH_LIST,       /** ( 5)                                */

    CGPU_PRIMITIVE_TOPOLOGY_COUNT

} ECGPUPrimitiveTopology;

typedef enum ECGPUCompareOp
{
    CGPU_COMPARE_OP_NEVER,                    /** ( 0)                                */
    CGPU_COMPARE_OP_LESS,                     /** ( 1)                                */
    CGPU_COMPARE_OP_EQUAL,                    /** ( 2)                                */
    CGPU_COMPARE_OP_LESS_EQUAL,               /** ( 3)                                */
    CGPU_COMPARE_OP_GREATER,                  /** ( 4)                                */
    CGPU_COMPARE_OP_NOT_EQUAL,                /** ( 5)                                */
    CGPU_COMPARE_OP_GREATER_EQUAL,            /** ( 6)                                */
    CGPU_COMPARE_OP_ALWAYS,                   /** ( 7)                                */

    CGPU_COMPARE_OP_COUNT

} ECGPUCompareOp;

typedef enum ECGPUFillMode
{
    CGPU_FILL_MODE_SOLID,                     /** ( 0)                                */
    CGPU_FILL_MODE_WIRE_FRAME,                /** ( 1)                                */

    CGPU_FILL_MODE_COUNT

} ECGPUFillMode;

typedef enum ECGPUFrontFace
{
    CGPU_FRONT_FACE_COUNTER_CLOCKWISE,        /** ( 0)                                */
    CGPU_FRONT_FACE_CLOCK_WISE,               /** ( 1)                                */

    CGPU_FRONT_FACE_COUNT

} ECGPUFrontFace;

typedef enum ECGPUVertexInputRate
{
    CGPU_VERTEX_INPUT_RATE_VERTEX,            /** ( 0)                                */
    CGPU_VERTEX_INPUT_RATE_INSTANCE,          /** ( 1)                                */

    CGPU_VERTEX_INPUT_RATE_COUNT

} ECGPUVertexInputRate;

typedef enum ECGPUStencilOp
{
    CGPU_STENCIL_OP_KEEP,                     /** ( 0)                                */
    CGPU_STENCIL_OP_ZERO,                     /** ( 1)                                */
    CGPU_STENCIL_OP_REPLACE,                  /** ( 2)                                */
    CGPU_STENCIL_OP_INCREMENT_AND_CLAMP,      /** ( 3)                                */
    CGPU_STENCIL_OP_DECREMENT_AND_CLAMP,      /** ( 4)                                */
    CGPU_STENCIL_OP_INVERT,                   /** ( 5)                                */
    CGPU_STENCIL_OP_INCREMENT_AND_WRAP,       /** ( 6)                                */
    CGPU_STENCIL_OP_DECREMENT_AND_WRAP,       /** ( 7)                                */

    CGPU_STENCIL_OP_COUNT

} ECGPUStencilOp;

typedef enum ECGPUTextureDimension
{
    CGPU_TEXTURE_DIMENSION_UNDEFINED,         /** ( 0)                                */
    CGPU_TEXTURE_DIMENSION_1D,                /** ( 1)                                */
    CGPU_TEXTURE_DIMENSION_2D,                /** ( 2)                                */
    CGPU_TEXTURE_DIMENSION_2DMS,              /** ( 3)                                */
    CGPU_TEXTURE_DIMENSION_3D,                /** ( 4)                                */
    CGPU_TEXTURE_DIMENSION_CUBE,              /** ( 5)                                */
    CGPU_TEXTURE_DIMENSION_1DARRAY,           /** ( 6)                                */
    CGPU_TEXTURE_DIMENSION_2DARRAY,           /** ( 7)                                */
    CGPU_TEXTURE_DIMENSION_2DMSARRAY,         /** ( 8)                                */
    CGPU_TEXTURE_DIMENSION_CUBE_ARRAY,        /** ( 9)                                */

    CGPU_TEXTURE_DIMENSION_COUNT

} ECGPUTextureDimension;

typedef enum ECGPUShaderBytecodeType
{
    CGPU_SHADER_BYTECODE_TYPE_SPIRV,          /** ( 0)                                */
    CGPU_SHADER_BYTECODE_TYPE_DXIL,           /** ( 1)                                */
    CGPU_SHADER_BYTECODE_TYPE_MTL,            /** ( 2)                                */

    CGPU_SHADER_BYTECODE_TYPE_COUNT

} ECGPUShaderBytecodeType;

typedef enum ECGPUFenceStatus
{
    CGPU_FENCE_STATUS_COMPLETE,               /** ( 0)                                */
    CGPU_FENCE_STATUS_INCOMPLETE,             /** ( 1)                                */
    CGPU_FENCE_STATUS_NOT_SUBMITTED,          /** ( 2)                                */

    CGPU_FENCE_STATUS_COUNT

} ECGPUFenceStatus;

typedef enum ECGPUQueryType
{
    CGPU_QUERY_TYPE_TIMESTAMP,                /** ( 0)                                */
    CGPU_QUERY_TYPE_PIPELINE_STATISTICS,      /** ( 1)                                */
    CGPU_QUERY_TYPE_OCCLUSION,                /** ( 2)                                */

    CGPU_QUERY_TYPE_COUNT

} ECGPUQueryType;

typedef enum ECGPUMemoryUsage
{
    CGPU_MEMORY_USAGE_UNKNOWN,                /** ( 0)                                */
    CGPU_MEMORY_USAGE_GPU_ONLY,               /** ( 1)                                */
    CGPU_MEMORY_USAGE_CPU_ONLY,               /** ( 2)                                */
    CGPU_MEMORY_USAGE_CPU_TO_GPU,             /** ( 3)                                */
    CGPU_MEMORY_USAGE_GPU_TO_CPU,             /** ( 4)                                */

    CGPU_MEMORY_USAGE_COUNT

} ECGPUMemoryUsage;

typedef enum ECGPUMemoryPoolType
{
    CGPU_MEMORY_POOL_TYPE_AUTOMATIC,          /** ( 0)                                */
    CGPU_MEMORY_POOL_TYPE_LINEAR,             /** ( 1)                                */
    CGPU_MEMORY_POOL_TYPE_TILED,              /** ( 2)                                */

    CGPU_MEMORY_POOL_TYPE_COUNT

} ECGPUMemoryPoolType;

typedef enum ECGPUPipelineType
{
    CGPU_PIPELINE_TYPE_NONE,                  /** ( 0)                                */
    CGPU_PIPELINE_TYPE_COMPUTE,               /** ( 1)                                */
    CGPU_PIPELINE_TYPE_GRAPHICS,              /** ( 2)                                */
    CGPU_PIPELINE_TYPE_RAY_TRACING,           /** ( 3)                                */

    CGPU_PIPELINE_TYPE_COUNT

} ECGPUPipelineType;

typedef enum ECGPUShadingRate
{
    CGPU_SHADING_RATE_FULL,                   /** ( 0)                                */
    CGPU_SHADING_RATE_HALF,                   /** ( 1)                                */
    CGPU_SHADING_RATE_QUARTER,                /** ( 2)                                */
    CGPU_SHADING_RATE_1X2,                    /** ( 3)                                */
    CGPU_SHADING_RATE_2X1,                    /** ( 4)                                */
    CGPU_SHADING_RATE_2X4,                    /** ( 5)                                */
    CGPU_SHADING_RATE_4X2,                    /** ( 6)                                */

    CGPU_SHADING_RATE_COUNT

} ECGPUShadingRate;

typedef enum ECGPUShadingRateCombiner
{
    CGPU_SHADING_RATE_COMBINER_PASS_THROUGH,  /** ( 0)                                */
    CGPU_SHADING_RATE_COMBINER_OVERRIDE,      /** ( 1)                                */
    CGPU_SHADING_RATE_COMBINER_MIN,           /** ( 2)                                */
    CGPU_SHADING_RATE_COMBINER_MAX,           /** ( 3)                                */
    CGPU_SHADING_RATE_COMBINER_SUM,           /** ( 4)                                */

    CGPU_SHADING_RATE_COMBINER_COUNT

} ECGPUShadingRateCombiner;

typedef enum ECGPUQueueType
{
    CGPU_QUEUE_TYPE_GRAPHICS,                 /** ( 0)                                */
    CGPU_QUEUE_TYPE_COMPUTE,                  /** ( 1)                                */
    CGPU_QUEUE_TYPE_TRANSFER,                 /** ( 2)                                */
    CGPU_QUEUE_TYPE_TILE_MAPPING,             /** ( 3)                                */

    CGPU_QUEUE_TYPE_COUNT

} ECGPUQueueType;

typedef enum ECGPUVertexFormat
{
    CGPU_VERTEX_FORMAT_UNDEFINED,             /** ( 0)                                */
    CGPU_VERTEX_FORMAT_FLOAT32X1,             /** ( 1)                                */
    CGPU_VERTEX_FORMAT_FLOAT32X2,             /** ( 2)                                */
    CGPU_VERTEX_FORMAT_FLOAT32X3,             /** ( 3)                                */
    CGPU_VERTEX_FORMAT_FLOAT32X4,             /** ( 4)                                */
    CGPU_VERTEX_FORMAT_SINT32X1,              /** ( 5)                                */
    CGPU_VERTEX_FORMAT_SINT32X2,              /** ( 6)                                */
    CGPU_VERTEX_FORMAT_SINT32X3,              /** ( 7)                                */
    CGPU_VERTEX_FORMAT_SINT32X4,              /** ( 8)                                */
    CGPU_VERTEX_FORMAT_UINT32X1,              /** ( 9)                                */
    CGPU_VERTEX_FORMAT_UINT32X2,              /** (10)                                */
    CGPU_VERTEX_FORMAT_UINT32X3,              /** (11)                                */
    CGPU_VERTEX_FORMAT_UINT32X4,              /** (12)                                */
    CGPU_VERTEX_FORMAT_FLOAT16X2,             /** (13)                                */
    CGPU_VERTEX_FORMAT_FLOAT16X4,             /** (14)                                */
    CGPU_VERTEX_FORMAT_SINT16X2,              /** (15)                                */
    CGPU_VERTEX_FORMAT_SINT16X4,              /** (16)                                */
    CGPU_VERTEX_FORMAT_UINT16X2,              /** (17)                                */
    CGPU_VERTEX_FORMAT_UINT16X4,              /** (18)                                */
    CGPU_VERTEX_FORMAT_SNORM16X2,             /** (19)                                */
    CGPU_VERTEX_FORMAT_SNORM16X4,             /** (20)                                */
    CGPU_VERTEX_FORMAT_UNORM16X2,             /** (21)                                */
    CGPU_VERTEX_FORMAT_UNORM16X4,             /** (22)                                */
    CGPU_VERTEX_FORMAT_SINT8X4,               /** (23)                                */
    CGPU_VERTEX_FORMAT_UINT8X4,               /** (24)                                */
    CGPU_VERTEX_FORMAT_SNORM8X4,              /** (25)                                */
    CGPU_VERTEX_FORMAT_UNORM8X4,              /** (26)                                */

    CGPU_VERTEX_FORMAT_COUNT

} ECGPUVertexFormat;


typedef enum ECGPUColorMaskFlagBits
{
    CGPU_COLOR_MASK_R = 0x00000001,                        /** ( 0)                                */
    CGPU_COLOR_MASK_G = 0x00000002,                        /** ( 1)                                */
    CGPU_COLOR_MASK_B = 0x00000004,                        /** ( 2)                                */
    CGPU_COLOR_MASK_A = 0x00000008,                        /** ( 3)                                */
    CGPU_COLOR_MASK_RGB = CGPU_COLOR_MASK_R | CGPU_COLOR_MASK_G | CGPU_COLOR_MASK_B,
    CGPU_COLOR_MASK_RGBA = CGPU_COLOR_MASK_RGB | CGPU_COLOR_MASK_A,

} ECGPUColorMaskFlagBits;
typedef ECGPUFlags ECGPUColorMaskFlags;

typedef enum ECGPUCullModeFlagBits
{
    CGPU_CULL_MODE_NONE = 0x00000000,                      /** ( 0)                                */
    CGPU_CULL_MODE_BACK = 0x00000001,                      /** ( 1)                                */
    CGPU_CULL_MODE_FRONT = 0x00000002,                     /** ( 2)                                */
    CGPU_CULL_MODE_BOTH = CGPU_CULL_MODE_BACK | CGPU_CULL_MODE_FRONT,

} ECGPUCullModeFlagBits;
typedef ECGPUFlags ECGPUCullModeFlags;

typedef enum ECGPUStencilFaceFlagBits
{
    CGPU_STENCIL_FACE_FRONT = 0x00000001,                  /** ( 0)                                */
    CGPU_STENCIL_FACE_BACK = 0x00000002,                   /** ( 1)                                */
    CGPU_STENCIL_FACE_BOTH = CGPU_STENCIL_FACE_FRONT | CGPU_STENCIL_FACE_BACK,

} ECGPUStencilFaceFlagBits;
typedef ECGPUFlags ECGPUStencilFaceFlags;

typedef enum ECGPUShaderStageFlagBits
{
    CGPU_SHADER_STAGE_NONE = 0x00000000,                   /** ( 0)                                */
    CGPU_SHADER_STAGE_VERTEX = 0x00000001,                 /** ( 1)                                */
    CGPU_SHADER_STAGE_TESSELLATION_CONTROL = 0x00000002,   /** ( 2)                                */
    CGPU_SHADER_STAGE_TESSELLATION_EVALUATION = 0x00000004, /** ( 3)                                */
    CGPU_SHADER_STAGE_GEOMETRY = 0x00000008,               /** ( 4)                                */
    CGPU_SHADER_STAGE_FRAGMENT = 0x00000010,               /** ( 5)                                */
    CGPU_SHADER_STAGE_COMPUTE = 0x00000020,                /** ( 6)                                */
    CGPU_SHADER_STAGE_RAY_TRACING = 0x00000040,            /** ( 7)                                */
    CGPU_SHADER_STAGE_ALL_GRAPHICS = CGPU_SHADER_STAGE_VERTEX | CGPU_SHADER_STAGE_TESSELLATION_CONTROL | CGPU_SHADER_STAGE_TESSELLATION_EVALUATION | CGPU_SHADER_STAGE_GEOMETRY | CGPU_SHADER_STAGE_FRAGMENT,

} ECGPUShaderStageFlagBits;
typedef ECGPUFlags ECGPUShaderStageFlags;

typedef enum ECGPUPipelineStageFlagBits
{
    CGPU_PIPELINE_STAGE_INDEX = 0x00000001,                /** ( 0)                                */
    CGPU_PIPELINE_STAGE_VERTEX = 0x00000002,               /** ( 1)                                */
    CGPU_PIPELINE_STAGE_FRAGMENT = 0x00000004,             /** ( 2)                                */
    CGPU_PIPELINE_STAGE_DEPTH = 0x00000008,                /** ( 3)                                */
    CGPU_PIPELINE_STAGE_RENDER_TARGET = 0x00000010,        /** ( 4)                                */
    CGPU_PIPELINE_STAGE_COMPUTE = 0x00000020,              /** ( 5)                                */
    CGPU_PIPELINE_STAGE_RAY_TRACING = 0x00000040,          /** ( 6)                                */
    CGPU_PIPELINE_STAGE_COPY = 0x00000080,                 /** ( 7)                                */
    CGPU_PIPELINE_STAGE_RESOLVE = 0x00000100,              /** ( 8)                                */
    CGPU_PIPELINE_STAGE_EXECUTE_INDIRECT = 0x00000200,     /** ( 9)                                */

} ECGPUPipelineStageFlagBits;
typedef ECGPUFlags ECGPUPipelineStageFlags;

typedef enum ECGPUResourceStateFlagBits
{
    CGPU_RESOURCE_STATE_UNDEFINED = 0x00000000,            /** ( 0)                                */
    CGPU_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER = 0x00000001, /** ( 1)                                */
    CGPU_RESOURCE_STATE_INDEX_BUFFER = 0x00000002,         /** ( 2)                                */
    CGPU_RESOURCE_STATE_RENDER_TARGET = 0x00000004,        /** ( 3)                                */
    CGPU_RESOURCE_STATE_UNORDERED_ACCESS = 0x00000008,     /** ( 4)                                */
    CGPU_RESOURCE_STATE_DEPTH_WRITE = 0x00000010,          /** ( 5)                                */
    CGPU_RESOURCE_STATE_DEPTH_READ = 0x00000020,           /** ( 6)                                */
    CGPU_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE = 0x00000040, /** ( 7)                                */
    CGPU_RESOURCE_STATE_PIXEL_SHADER_RESOURCE = 0x00000080, /** ( 8)                                */
    CGPU_RESOURCE_STATE_STREAM_OUT = 0x00000100,           /** ( 9)                                */
    CGPU_RESOURCE_STATE_INDIRECT_ARGUMENT = 0x00000200,    /** (10)                                */
    CGPU_RESOURCE_STATE_COPY_DEST = 0x00000400,            /** (11)                                */
    CGPU_RESOURCE_STATE_COPY_SOURCE = 0x00000800,          /** (12)                                */
    CGPU_RESOURCE_STATE_PRESENT = 0x00001000,              /** (13)                                */
    CGPU_RESOURCE_STATE_COMMON = 0x00002000,               /** (14)                                */
    CGPU_RESOURCE_STATE_ACCELERATION_STRUCTURE = 0x00004000, /** (15)                                */
    CGPU_RESOURCE_STATE_SHADING_RATE_SOURCE = 0x00008000,  /** (16)                                */
    CGPU_RESOURCE_STATE_RESOLVE_DEST = 0x00010000,         /** (17)                                */
    CGPU_RESOURCE_STATE_SHADER_RESOURCE = CGPU_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE | CGPU_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
    CGPU_RESOURCE_STATE_GENERIC_READ = CGPU_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER | CGPU_RESOURCE_STATE_INDEX_BUFFER | CGPU_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE | CGPU_RESOURCE_STATE_PIXEL_SHADER_RESOURCE | CGPU_RESOURCE_STATE_INDIRECT_ARGUMENT | CGPU_RESOURCE_STATE_COPY_SOURCE,

} ECGPUResourceStateFlagBits;
typedef ECGPUFlags ECGPUResourceStateFlags;

typedef enum ECGPUBufferCreationUsageFlagBits
{
    CGPU_BUFFER_CREATION_USAGE_NONE = 0x00000000,          /** ( 0)                                */
    CGPU_BUFFER_CREATION_USAGE_DEDICATED = 0x00000001,     /** ( 1)                                */
    CGPU_BUFFER_CREATION_USAGE_PERSISTENT_MAP = 0x00000002, /** ( 2)                                */
    CGPU_BUFFER_CREATION_USAGE_HOST_VISIBLE = 0x00000004,  /** ( 3)                                */

} ECGPUBufferCreationUsageFlagBits;
typedef ECGPUFlags ECGPUBufferCreationUsageFlags;

typedef enum ECGPUTextureCreationUsageFlagBits
{
    CGPU_TEXTURE_CREATION_USAGE_NONE = 0x00000000,         /** ( 0)                                */
    CGPU_TEXTURE_CREATION_USAGE_DEDICATED = 0x00000001,    /** ( 1)                                */
    CGPU_TEXTURE_CREATION_USAGE_FORCE2D = 0x00000002,      /** ( 2)                                */
    CGPU_TEXTURE_CREATION_USAGE_FORCE3D = 0x00000004,      /** ( 3)                                */
    CGPU_TEXTURE_CREATION_USAGE_ALIASING_RESOURCE = 0x00000008, /** ( 4)                                */
    CGPU_TEXTURE_CREATION_USAGE_TILED_RESOURCE = 0x00000010, /** ( 5)                                */
    CGPU_TEXTURE_CREATION_USAGE_EXPORT = 0x00000020,       /** ( 6)                                */
    CGPU_TEXTURE_CREATION_USAGE_IMPORT_SHARED = 0x00000040, /** ( 7)                                */

} ECGPUTextureCreationUsageFlagBits;
typedef ECGPUFlags ECGPUTextureCreationUsageFlags;

typedef enum ECGPUSampleCountFlagBits
{
    CGPU_SAMPLE_COUNT_1 = 0x00000001,                      /** ( 0)                                */
    CGPU_SAMPLE_COUNT_2 = 0x00000002,                      /** ( 1)                                */
    CGPU_SAMPLE_COUNT_4 = 0x00000004,                      /** ( 2)                                */
    CGPU_SAMPLE_COUNT_8 = 0x00000008,                      /** ( 3)                                */
    CGPU_SAMPLE_COUNT_16 = 0x00000010,                     /** ( 4)                                */

} ECGPUSampleCountFlagBits;
typedef ECGPUFlags ECGPUSampleCountFlags;

typedef enum ECGPUResourceTypeFlagBits
{
    CGPU_RESOURCE_TYPE_NONE = 0x00000000,                  /** ( 0)                                */
    CGPU_RESOURCE_TYPE_SAMPLER = 0x00000001,               /** ( 1)                                */
    CGPU_RESOURCE_TYPE_TEXTURE = 0x00000002,               /** ( 2)                                */
    CGPU_RESOURCE_TYPE_RENDER_TARGET = 0x00000004,         /** ( 3)                                */
    CGPU_RESOURCE_TYPE_DEPTH_STENCIL = 0x00000008,         /** ( 4)                                */
    CGPU_RESOURCE_TYPE_RW_TEXTURE = 0x00000010,            /** ( 5)                                */
    CGPU_RESOURCE_TYPE_BUFFER = 0x00000020,                /** ( 6)                                */
    CGPU_RESOURCE_TYPE_BUFFER_RAW = 0x00000040,            /** ( 7)                                */
    CGPU_RESOURCE_TYPE_RW_BUFFER = 0x00000080,             /** ( 8)                                */
    CGPU_RESOURCE_TYPE_RW_BUFFER_RAW = 0x00000100,         /** ( 9)                                */
    CGPU_RESOURCE_TYPE_UNIFORM_BUFFER = 0x00000200,        /** (10)                                */
    CGPU_RESOURCE_TYPE_PUSH_CONSTANT = 0x00000400,         /** (11)                                */
    CGPU_RESOURCE_TYPE_VERTEX_BUFFER = 0x00000800,         /** (12)                                */
    CGPU_RESOURCE_TYPE_INDEX_BUFFER = 0x00001000,          /** (13)                                */
    CGPU_RESOURCE_TYPE_INDIRECT_BUFFER = 0x00002000,       /** (14)                                */
    CGPU_RESOURCE_TYPE_TEXTURE_CUBE = 0x00004000,          /** (15)                                */
    CGPU_RESOURCE_TYPE_RENDER_TARGET_MIP_SLICES = 0x00008000, /** (16)                                */
    CGPU_RESOURCE_TYPE_RENDER_TARGET_ARRAY_SLICES = 0x00010000, /** (17)                                */
    CGPU_RESOURCE_TYPE_RENDER_TARGET_DEPTH_SLICES = 0x00020000, /** (18)                                */
    CGPU_RESOURCE_TYPE_RAY_TRACING = 0x00040000,           /** (19)                                */
    CGPU_RESOURCE_TYPE_INPUT_ATTACHMENT = 0x00080000,      /** (20)                                */
    CGPU_RESOURCE_TYPE_TEXEL_BUFFER = 0x00100000,          /** (21)                                */
    CGPU_RESOURCE_TYPE_RW_TEXEL_BUFFER = 0x00200000,       /** (22)                                */
    CGPU_RESOURCE_TYPE_COMBINED_IMAGE_SAMPLER = 0x00400000, /** (23)                                */

} ECGPUResourceTypeFlagBits;
typedef ECGPUFlags ECGPUResourceTypeFlags;

typedef enum ECGPUTextureViewUsageFlagBits
{
    CGPU_TEXTURE_VIEW_USAGE_SRV = 0x00000001,              /** ( 0)                                */
    CGPU_TEXTURE_VIEW_USAGE_RTV_DSV = 0x00000002,          /** ( 1)                                */
    CGPU_TEXTURE_VIEW_USAGE_UAV = 0x00000004,              /** ( 2)                                */

} ECGPUTextureViewUsageFlagBits;
typedef ECGPUFlags ECGPUTextureViewUsageFlags;

typedef enum ECGPUTextureViewAspectFlagBits
{
    CGPU_TEXTURE_VIEW_ASPECT_COLOR = 0x00000001,           /** ( 0)                                */
    CGPU_TEXTURE_VIEW_ASPECT_DEPTH = 0x00000002,           /** ( 1)                                */
    CGPU_TEXTURE_VIEW_ASPECT_STENCIL = 0x00000004,         /** ( 2)                                */

} ECGPUTextureViewAspectFlagBits;
typedef ECGPUFlags ECGPUTextureViewAspectFlags;

typedef enum ECGPUTextureFormatSupportFlagBits
{
    CGPU_TEXTURE_FORMAT_SUPPORT_SAMPLE = 0x00000001,       /** ( 0)                                */
    CGPU_TEXTURE_FORMAT_SUPPORT_RENDER = 0x00000002,       /** ( 1)                                */
    CGPU_TEXTURE_FORMAT_SUPPORT_LOAD_STORE = 0x00000004,   /** ( 2)                                */
    CGPU_TEXTURE_FORMAT_SUPPORT_BLEND = 0x00000008,        /** ( 3)                                */
    CGPU_TEXTURE_FORMAT_SUPPORT_MSAA2X = 0x00000010,       /** ( 4)                                */
    CGPU_TEXTURE_FORMAT_SUPPORT_MSAA4X = 0x00000020,       /** ( 5)                                */
    CGPU_TEXTURE_FORMAT_SUPPORT_MSAA8X = 0x00000040,       /** ( 6)                                */
    CGPU_TEXTURE_FORMAT_SUPPORT_MSAA16X = 0x00000080,      /** ( 7)                                */

} ECGPUTextureFormatSupportFlagBits;
typedef ECGPUFlags ECGPUTextureFormatSupportFlags;

typedef enum ECGPUDynamicStateFeaturesFlagBits
{
    CGPU_DYNAMIC_STATE_FEATURES_CULL_MODE = 0x0000000000000001,    /** ( 0)                                */
    CGPU_DYNAMIC_STATE_FEATURES_FRONT_FACE = 0x0000000000000002,   /** ( 1)                                */
    CGPU_DYNAMIC_STATE_FEATURES_PRIMITIVE_TOPOLOGY = 0x0000000000000004, /** ( 2)                                */
    CGPU_DYNAMIC_STATE_FEATURES_DEPTH_TEST = 0x0000000000000008,   /** ( 3)                                */
    CGPU_DYNAMIC_STATE_FEATURES_DEPTH_WRITE = 0x0000000000000010,  /** ( 4)                                */
    CGPU_DYNAMIC_STATE_FEATURES_DEPTH_COMPARE = 0x0000000000000020, /** ( 5)                                */
    CGPU_DYNAMIC_STATE_FEATURES_DEPTH_BOUNDS_TEST = 0x0000000000000040, /** ( 6)                                */
    CGPU_DYNAMIC_STATE_FEATURES_STENCIL_TEST = 0x0000000000000080, /** ( 7)                                */
    CGPU_DYNAMIC_STATE_FEATURES_STENCIL_OP = 0x0000000000000100,   /** ( 8)                                */
    CGPU_DYNAMIC_STATE_FEATURES_RASTER_DISCARD = 0x0000000000000200, /** ( 9)                                */
    CGPU_DYNAMIC_STATE_FEATURES_DEPTH_BIAS = 0x0000000000000400,   /** (10)                                */
    CGPU_DYNAMIC_STATE_FEATURES_PRIMITIVE_RESTART = 0x0000000000000800, /** (11)                                */
    CGPU_DYNAMIC_STATE_FEATURES_LOGIC_OP = 0x0000000000001000,     /** (12)                                */
    CGPU_DYNAMIC_STATE_FEATURES_PATCH_CONTROL_POINTS = 0x0000000000002000, /** (13)                                */
    CGPU_DYNAMIC_STATE_FEATURES_TESSELLATION_DOMAIN_ORIGIN = 0x0000000000004000, /** (14)                                */
    CGPU_DYNAMIC_STATE_FEATURES_DEPTH_CLAMP_ENABLE = 0x0000000000008000, /** (15)                                */
    CGPU_DYNAMIC_STATE_FEATURES_POLYGON_MODE = 0x0000000000010000, /** (16)                                */
    CGPU_DYNAMIC_STATE_FEATURES_SAMPLE_COUNT = 0x0000000000020000, /** (17)                                */
    CGPU_DYNAMIC_STATE_FEATURES_SAMPLE_MASK = 0x0000000000040000,  /** (18)                                */
    CGPU_DYNAMIC_STATE_FEATURES_ALPHA_TO_COVERAGE_ENABLE = 0x0000000000080000, /** (19)                                */
    CGPU_DYNAMIC_STATE_FEATURES_ALPHA_TO_ONE_ENABLE = 0x0000000000100000, /** (20)                                */
    CGPU_DYNAMIC_STATE_FEATURES_LOGIC_OP_ENABLE = 0x0000000000200000, /** (21)                                */
    CGPU_DYNAMIC_STATE_FEATURES_COLOR_BLEND_ENABLE = 0x0000000000400000, /** (22)                                */
    CGPU_DYNAMIC_STATE_FEATURES_COLOR_BLEND_EQUATION = 0x0000000000800000, /** (23)                                */
    CGPU_DYNAMIC_STATE_FEATURES_COLOR_WRITE_MASK = 0x0000000001000000, /** (24)                                */
    CGPU_DYNAMIC_STATE_FEATURES_RASTER_STREAM = 0x0000000002000000, /** (25)                                */
    CGPU_DYNAMIC_STATE_FEATURES_CONSERVATIVE_RASTER_MODE = 0x0000000004000000, /** (26)                                */
    CGPU_DYNAMIC_STATE_FEATURES_EXTRA_PRIMITIVE_OVERESTIMATION_SIZE = 0x0000000008000000, /** (27)                                */
    CGPU_DYNAMIC_STATE_FEATURES_DEPTH_CLIP_ENABLE = 0x0000000010000000, /** (28)                                */
    CGPU_DYNAMIC_STATE_FEATURES_SAMPLE_LOCATIONS_ENABLE = 0x0000000020000000, /** (29)                                */
    CGPU_DYNAMIC_STATE_FEATURES_COLOR_BLEND_ADVANCED = 0x0000000040000000, /** (30)                                */
    CGPU_DYNAMIC_STATE_FEATURES_PROVOKING_VERTEX_MODE = 0x0000000080000000, /** (31)                                */
    CGPU_DYNAMIC_STATE_FEATURES_LINE_RASTERIZATION_MODE = 0x0000000100000000, /** (32)                                */
    CGPU_DYNAMIC_STATE_FEATURES_LINE_STIPPLE_ENABLE = 0x0000000200000000, /** (33)                                */
    CGPU_DYNAMIC_STATE_FEATURES_DEPTH_CLIP_NEGATIVE_ONE_TO_ONE = 0x0000000400000000, /** (34)                                */
    CGPU_DYNAMIC_STATE_FEATURES_VIEWPORT_WSCALING_ENABLE = 0x0000000800000000, /** (35)                                */
    CGPU_DYNAMIC_STATE_FEATURES_VIEWPORT_SWIZZLE = 0x0000001000000000, /** (36)                                */
    CGPU_DYNAMIC_STATE_FEATURES_COVERAGE_TO_COLOR_ENABLE = 0x0000002000000000, /** (37)                                */
    CGPU_DYNAMIC_STATE_FEATURES_COVERAGE_TO_COLOR_LOCATION = 0x0000004000000000, /** (38)                                */
    CGPU_DYNAMIC_STATE_FEATURES_COVERAGE_MODULATION_MODE = 0x0000008000000000, /** (39)                                */
    CGPU_DYNAMIC_STATE_FEATURES_COVERAGE_MODULATION_TABLE_ENABLE = 0x0000010000000000, /** (40)                                */
    CGPU_DYNAMIC_STATE_FEATURES_COVERAGE_MODULATION_TABLE = 0x0000020000000000, /** (41)                                */
    CGPU_DYNAMIC_STATE_FEATURES_COVERAGE_REDUCTION_MODE = 0x0000040000000000, /** (42)                                */
    CGPU_DYNAMIC_STATE_FEATURES_REPRESENTATIVE_FRAGMENT_TEST_ENABLE = 0x0000080000000000, /** (43)                                */
    CGPU_DYNAMIC_STATE_FEATURES_SHADING_RATE_IMAGE_ENABLE = 0x0000100000000000, /** (44)                                */
    CGPU_DYNAMIC_STATE_FEATURES_TIER1 = CGPU_DYNAMIC_STATE_FEATURES_CULL_MODE | CGPU_DYNAMIC_STATE_FEATURES_FRONT_FACE | CGPU_DYNAMIC_STATE_FEATURES_PRIMITIVE_TOPOLOGY | CGPU_DYNAMIC_STATE_FEATURES_DEPTH_TEST | CGPU_DYNAMIC_STATE_FEATURES_DEPTH_WRITE | CGPU_DYNAMIC_STATE_FEATURES_DEPTH_COMPARE | CGPU_DYNAMIC_STATE_FEATURES_DEPTH_BOUNDS_TEST | CGPU_DYNAMIC_STATE_FEATURES_STENCIL_TEST | CGPU_DYNAMIC_STATE_FEATURES_STENCIL_OP,
    CGPU_DYNAMIC_STATE_FEATURES_TIER2 = CGPU_DYNAMIC_STATE_FEATURES_TIER1 | CGPU_DYNAMIC_STATE_FEATURES_RASTER_DISCARD | CGPU_DYNAMIC_STATE_FEATURES_DEPTH_BIAS | CGPU_DYNAMIC_STATE_FEATURES_PRIMITIVE_RESTART | CGPU_DYNAMIC_STATE_FEATURES_LOGIC_OP | CGPU_DYNAMIC_STATE_FEATURES_PATCH_CONTROL_POINTS,
    CGPU_DYNAMIC_STATE_FEATURES_TIER3 = CGPU_DYNAMIC_STATE_FEATURES_TIER2 | CGPU_DYNAMIC_STATE_FEATURES_TESSELLATION_DOMAIN_ORIGIN | CGPU_DYNAMIC_STATE_FEATURES_DEPTH_CLAMP_ENABLE | CGPU_DYNAMIC_STATE_FEATURES_POLYGON_MODE | CGPU_DYNAMIC_STATE_FEATURES_SAMPLE_COUNT | CGPU_DYNAMIC_STATE_FEATURES_SAMPLE_MASK | CGPU_DYNAMIC_STATE_FEATURES_ALPHA_TO_COVERAGE_ENABLE | CGPU_DYNAMIC_STATE_FEATURES_ALPHA_TO_ONE_ENABLE | CGPU_DYNAMIC_STATE_FEATURES_LOGIC_OP_ENABLE | CGPU_DYNAMIC_STATE_FEATURES_COLOR_BLEND_ENABLE | CGPU_DYNAMIC_STATE_FEATURES_COLOR_BLEND_EQUATION | CGPU_DYNAMIC_STATE_FEATURES_COLOR_WRITE_MASK | CGPU_DYNAMIC_STATE_FEATURES_RASTER_STREAM | CGPU_DYNAMIC_STATE_FEATURES_CONSERVATIVE_RASTER_MODE | CGPU_DYNAMIC_STATE_FEATURES_EXTRA_PRIMITIVE_OVERESTIMATION_SIZE | CGPU_DYNAMIC_STATE_FEATURES_DEPTH_CLIP_ENABLE | CGPU_DYNAMIC_STATE_FEATURES_SAMPLE_LOCATIONS_ENABLE | CGPU_DYNAMIC_STATE_FEATURES_COLOR_BLEND_ADVANCED | CGPU_DYNAMIC_STATE_FEATURES_PROVOKING_VERTEX_MODE | CGPU_DYNAMIC_STATE_FEATURES_LINE_RASTERIZATION_MODE | CGPU_DYNAMIC_STATE_FEATURES_LINE_STIPPLE_ENABLE | CGPU_DYNAMIC_STATE_FEATURES_DEPTH_CLIP_NEGATIVE_ONE_TO_ONE | CGPU_DYNAMIC_STATE_FEATURES_VIEWPORT_WSCALING_ENABLE | CGPU_DYNAMIC_STATE_FEATURES_VIEWPORT_SWIZZLE | CGPU_DYNAMIC_STATE_FEATURES_COVERAGE_TO_COLOR_ENABLE | CGPU_DYNAMIC_STATE_FEATURES_COVERAGE_TO_COLOR_LOCATION | CGPU_DYNAMIC_STATE_FEATURES_COVERAGE_MODULATION_MODE | CGPU_DYNAMIC_STATE_FEATURES_COVERAGE_MODULATION_TABLE_ENABLE | CGPU_DYNAMIC_STATE_FEATURES_COVERAGE_MODULATION_TABLE | CGPU_DYNAMIC_STATE_FEATURES_COVERAGE_REDUCTION_MODE | CGPU_DYNAMIC_STATE_FEATURES_REPRESENTATIVE_FRAGMENT_TEST_ENABLE | CGPU_DYNAMIC_STATE_FEATURES_SHADING_RATE_IMAGE_ENABLE,

} ECGPUDynamicStateFeaturesFlagBits;
typedef ECGPUFlags64 ECGPUDynamicStateFeaturesFlags;


DEFINE_CGPU_OBJECT(CGPUInstance)

DEFINE_CGPU_OBJECT(CGPUAdapter)

DEFINE_CGPU_OBJECT(CGPUDevice)

DEFINE_CGPU_OBJECT(CGPUQueue)

DEFINE_CGPU_OBJECT(CGPUSemaphore)

DEFINE_CGPU_OBJECT(CGPUFence)

DEFINE_CGPU_OBJECT(CGPUCommandPool)

DEFINE_CGPU_OBJECT(CGPUCommandBuffer)

DEFINE_CGPU_OBJECT(CGPUQueryPool)

DEFINE_CGPU_OBJECT(CGPUComputePassEncoder)

DEFINE_CGPU_OBJECT(CGPURenderPassEncoder)

DEFINE_CGPU_OBJECT(CGPURenderPass)

DEFINE_CGPU_OBJECT(CGPUFramebuffer)

DEFINE_CGPU_OBJECT(CGPUStateBuffer)

DEFINE_CGPU_OBJECT(CGPURasterStateEncoder)

DEFINE_CGPU_OBJECT(CGPUShaderStateEncoder)

DEFINE_CGPU_OBJECT(CGPUUserStateEncoder)

DEFINE_CGPU_OBJECT(CGPUBinder)

DEFINE_CGPU_OBJECT(CGPUShaderLibrary)

DEFINE_CGPU_OBJECT(CGPURootSignaturePool)

DEFINE_CGPU_OBJECT(CGPURootSignature)

DEFINE_CGPU_OBJECT(CGPUDescriptorSet)

DEFINE_CGPU_OBJECT(CGPUShaderReflection)

DEFINE_CGPU_OBJECT(CGPUCompiledShader)

DEFINE_CGPU_OBJECT(CGPULinkedShader)

DEFINE_CGPU_OBJECT(CGPUBuffer)

DEFINE_CGPU_OBJECT(CGPUTexture)

DEFINE_CGPU_OBJECT(CGPUTextureView)

DEFINE_CGPU_OBJECT(CGPUSampler)

DEFINE_CGPU_OBJECT(CGPURenderPipeline)

DEFINE_CGPU_OBJECT(CGPUComputePipeline)

DEFINE_CGPU_OBJECT(CGPUMemoryPool)

DEFINE_CGPU_OBJECT(CGPUSwapChain)

DEFINE_CGPU_OBJECT(CGPUSurface)


typedef struct CGPUInstanceDescriptor CGPUInstanceDescriptor;
typedef struct CGPUInstanceFeatures CGPUInstanceFeatures;
typedef struct CGPUProcTable CGPUProcTable;
typedef struct CGPUSurfacesProcTable CGPUSurfacesProcTable;
typedef struct CGPURuntimeTable CGPURuntimeTable;
typedef struct CGPUAdapterDetail CGPUAdapterDetail;
typedef struct CGPUDeviceDescriptor CGPUDeviceDescriptor;
typedef struct CGPURootSignaturePoolDescriptor CGPURootSignaturePoolDescriptor;
typedef struct CGPURootSignatureDescriptor CGPURootSignatureDescriptor;
typedef struct CGPUDescriptorSetDescriptor CGPUDescriptorSetDescriptor;
typedef struct CGPUDescriptorData CGPUDescriptorData;
typedef struct CGPUComputePipelineDescriptor CGPUComputePipelineDescriptor;
typedef struct CGPURenderPipelineDescriptor CGPURenderPipelineDescriptor;
typedef struct CGPUQueryPoolDescriptor CGPUQueryPoolDescriptor;
typedef struct CGPUMemoryPoolDescriptor CGPUMemoryPoolDescriptor;
typedef struct CGPUQueueSubmitDescriptor CGPUQueueSubmitDescriptor;
typedef struct CGPUQueuePresentDescriptor CGPUQueuePresentDescriptor;
typedef struct CGPUTiledTextureRegions CGPUTiledTextureRegions;
typedef struct CGPUTiledTexturePackedMips CGPUTiledTexturePackedMips;
typedef struct CGPURenderPassDescriptor CGPURenderPassDescriptor;
typedef struct CGPUFramebufferDescriptor CGPUFramebufferDescriptor;
typedef struct CGPUCommandPoolDescriptor CGPUCommandPoolDescriptor;
typedef struct CGPUCommandBufferDescriptor CGPUCommandBufferDescriptor;
typedef struct CGPUShaderLibraryDescriptor CGPUShaderLibraryDescriptor;
typedef struct CGPUBufferDescriptor CGPUBufferDescriptor;
typedef struct CGPUBufferRange CGPUBufferRange;
typedef struct CGPUSamplerDescriptor CGPUSamplerDescriptor;
typedef struct CGPUTextureDescriptor CGPUTextureDescriptor;
typedef struct CGPUTextureViewDescriptor CGPUTextureViewDescriptor;
typedef struct CGPUTextureAliasingBindDescriptor CGPUTextureAliasingBindDescriptor;
typedef struct CGPUExportTextureDescriptor CGPUExportTextureDescriptor;
typedef struct CGPUImportTextureDescriptor CGPUImportTextureDescriptor;
typedef struct CGPUSwapChainDescriptor CGPUSwapChainDescriptor;
typedef struct CGPUAcquireNextDescriptor CGPUAcquireNextDescriptor;
typedef struct CGPUBufferToBufferTransfer CGPUBufferToBufferTransfer;
typedef struct CGPUTextureToTextureTransfer CGPUTextureToTextureTransfer;
typedef struct CGPUBufferToTextureTransfer CGPUBufferToTextureTransfer;
typedef struct CGPUBufferToTilesTransfer CGPUBufferToTilesTransfer;
typedef struct CGPUResourceBarrierDescriptor CGPUResourceBarrierDescriptor;
typedef struct CGPUQueryDescriptor CGPUQueryDescriptor;
typedef struct CGPUComputePassDescriptor CGPUComputePassDescriptor;
typedef struct CGPUBeginRenderPassInfo CGPUBeginRenderPassInfo;
typedef struct CGPUEventInfo CGPUEventInfo;
typedef struct CGPUMarkerInfo CGPUMarkerInfo;
typedef struct CGPUCompiledShaderDescriptor CGPUCompiledShaderDescriptor;
typedef struct CGPUStateBufferDescriptor CGPUStateBufferDescriptor;
typedef struct CGPUVertexLayout CGPUVertexLayout;

typedef void (*CGPUProcLogCallback)(void* user_data, ECGPULogSeverity severity, const char* fmt, ... );
typedef void* (*CGPUProcMalloc)(void* user_data, size_t size, const void* pool);
typedef void* (*CGPUProcRealloc)(void* user_data, void* ptr, size_t size, const void* pool);
typedef void* (*CGPUProcCalloc)(void* user_data, size_t count, size_t size, const void* pool);
typedef void (*CGPUProcFree)(void* user_data, void* ptr, const void* pool);
typedef void* (*CGPUProcMallocAligned)(void* user_data, size_t size, size_t alignment, const void* pool);
typedef void* (*CGPUProcReallocAligned)(void* user_data, void* ptr, size_t size, size_t alignment, const void* pool);
typedef void* (*CGPUProcCallocAligned)(void* user_data, size_t count, size_t size, size_t alignment, const void* pool);
typedef void (*CGPUProcFreeAligned)(void* user_data, void* ptr, const void* pool);
typedef CGPUInstanceId (*CGPUProcCreateInstance)(const CGPUInstanceDescriptor* desc);
typedef void (*CGPUProcFreeInstance)(CGPUInstanceId instance);
typedef void (*CGPUProcQueryInstanceFeatures)(CGPUInstanceId instance, CGPUInstanceFeatures* features);
typedef void (*CGPUProcEnumAdapters)(CGPUInstanceId instance, uint32_t* p_adapters_count, CGPUAdapterId* p_adapters);
typedef const CGPUAdapterDetail* (*CGPUProcQueryAdapterDetail)(CGPUAdapterId adapter);
typedef uint32_t (*CGPUProcQueryQueueCount)(CGPUAdapterId adapter, ECGPUQueueType type);
typedef CGPUDeviceId (*CGPUProcCreateDevice)(CGPUAdapterId adapter, const CGPUDeviceDescriptor* desc);
typedef void (*CGPUProcFreeDevice)(CGPUAdapterId adapter, CGPUDeviceId device);
typedef void (*CGPUProcQueryVideoMemoryInfo)(CGPUDeviceId device, uint64_t* total, uint64_t* used);
typedef void (*CGPUProcQuerySharedMemoryInfo)(CGPUDeviceId device, uint64_t* total, uint64_t* used);
typedef CGPUFenceId (*CGPUProcCreateFence)(CGPUDeviceId device);
typedef void (*CGPUProcWaitFences)(uint32_t fence_count, const CGPUFenceId* p_fences);
typedef ECGPUFenceStatus (*CGPUProcQueryFenceStatus)(CGPUFenceId fence);
typedef void (*CGPUProcFreeFence)(CGPUDeviceId device, CGPUFenceId fence);
typedef CGPUSemaphoreId (*CGPUProcCreateSemaphore)(CGPUDeviceId device);
typedef void (*CGPUProcFreeSemaphore)(CGPUDeviceId device, CGPUSemaphoreId semaphore);
typedef CGPURootSignaturePoolId (*CGPUProcCreateRootSignaturePool)(CGPUDeviceId device, const CGPURootSignaturePoolDescriptor* desc);
typedef void (*CGPUProcFreeRootSignaturePool)(CGPUDeviceId device, CGPURootSignaturePoolId pool);
typedef CGPURootSignatureId (*CGPUProcCreateRootSignature)(CGPUDeviceId device, const CGPURootSignatureDescriptor* desc);
typedef void (*CGPUProcFreeRootSignature)(CGPUDeviceId device, CGPURootSignatureId signature);
typedef CGPUDescriptorSetId (*CGPUProcCreateDescriptorSet)(CGPUDeviceId device, const CGPUDescriptorSetDescriptor* desc);
typedef void (*CGPUProcUpdateDescriptorSet)(CGPUDescriptorSetId set, uint32_t data_count, const CGPUDescriptorData* p_datas);
typedef void (*CGPUProcFreeDescriptorSet)(CGPUDeviceId device, CGPUDescriptorSetId set);
typedef CGPUComputePipelineId (*CGPUProcCreateComputePipeline)(CGPUDeviceId device, const CGPUComputePipelineDescriptor* desc);
typedef void (*CGPUProcFreeComputePipeline)(CGPUDeviceId device, CGPUComputePipelineId pipeline);
typedef CGPURenderPipelineId (*CGPUProcCreateRenderPipeline)(CGPUDeviceId device, const CGPURenderPipelineDescriptor* desc);
typedef void (*CGPUProcFreeRenderPipeline)(CGPUDeviceId device, CGPURenderPipelineId pipeline);
typedef CGPUQueryPoolId (*CGPUProcCreateQueryPool)(CGPUDeviceId device, const CGPUQueryPoolDescriptor* desc);
typedef void (*CGPUProcFreeQueryPool)(CGPUDeviceId device, CGPUQueryPoolId pool);
typedef CGPUMemoryPoolId (*CGPUProcCreateMemoryPool)(CGPUDeviceId device, const CGPUMemoryPoolDescriptor* desc);
typedef void (*CGPUProcFreeMemoryPool)(CGPUDeviceId device, CGPUMemoryPoolId pool);
typedef CGPUQueueId (*CGPUProcGetQueue)(CGPUDeviceId device, ECGPUQueueType type, uint32_t index);
typedef void (*CGPUProcSubmitQueue)(CGPUQueueId queue, const CGPUQueueSubmitDescriptor* desc);
typedef void (*CGPUProcQueuePresent)(CGPUQueueId queue, const CGPUQueuePresentDescriptor* desc);
typedef void (*CGPUProcWaitQueueIdle)(CGPUQueueId queue);
typedef float (*CGPUProcQueueGetTimestampPeriodNS)(CGPUQueueId queue);
typedef void (*CGPUProcQueueMapTiledTexture)(CGPUQueueId queue, const CGPUTiledTextureRegions* desc);
typedef void (*CGPUProcQueueUnmapTiledTexture)(CGPUQueueId queue, const CGPUTiledTextureRegions* desc);
typedef void (*CGPUProcQueueMapPackedMips)(CGPUQueueId queue, const CGPUTiledTexturePackedMips* desc);
typedef void (*CGPUProcQueueUnmapPackedMips)(CGPUQueueId queue, const CGPUTiledTexturePackedMips* desc);
typedef void (*CGPUProcFreeQueue)(CGPUDeviceId device, CGPUQueueId queue);
typedef CGPURenderPassId (*CGPUProcCreateRenderPass)(CGPUDeviceId device, const CGPURenderPassDescriptor* desc);
typedef CGPUFramebufferId (*CGPUProcCreateFramebuffer)(CGPUDeviceId device, const CGPUFramebufferDescriptor* desc);
typedef void (*CGPUProcFreeRenderPass)(CGPUDeviceId device, CGPURenderPassId render_pass);
typedef void (*CGPUProcFreeFramebuffer)(CGPUDeviceId device, CGPUFramebufferId framebuffer);
typedef CGPUCommandPoolId (*CGPUProcCreateCommandPool)(CGPUQueueId queue, const CGPUCommandPoolDescriptor* desc);
typedef CGPUCommandBufferId (*CGPUProcCreateCommandBuffer)(CGPUCommandPoolId pool, const CGPUCommandBufferDescriptor* desc);
typedef void (*CGPUProcResetCommandPool)(CGPUCommandPoolId pool);
typedef void (*CGPUProcFreeCommandBuffer)(CGPUCommandPoolId pool, CGPUCommandBufferId cmd);
typedef void (*CGPUProcFreeCommandPool)(CGPUQueueId queue, CGPUCommandPoolId pool);
typedef CGPUShaderLibraryId (*CGPUProcCreateShaderLibrary)(CGPUDeviceId device, const CGPUShaderLibraryDescriptor* desc);
typedef void (*CGPUProcFreeShaderLibrary)(CGPUDeviceId device, CGPUShaderLibraryId library);
typedef CGPUBufferId (*CGPUProcCreateBuffer)(CGPUDeviceId device, const CGPUBufferDescriptor* desc);
typedef void (*CGPUProcMapBuffer)(CGPUBufferId buffer, const CGPUBufferRange* range);
typedef void (*CGPUProcUnmapBuffer)(CGPUBufferId buffer);
typedef void (*CGPUProcFreeBuffer)(CGPUDeviceId device, CGPUBufferId buffer);
typedef CGPUSamplerId (*CGPUProcCreateSampler)(CGPUDeviceId device, const CGPUSamplerDescriptor* desc);
typedef void (*CGPUProcFreeSampler)(CGPUDeviceId device, CGPUSamplerId sampler);
typedef CGPUTextureId (*CGPUProcCreateTexture)(CGPUDeviceId device, const CGPUTextureDescriptor* desc);
typedef void (*CGPUProcFreeTexture)(CGPUDeviceId device, CGPUTextureId texture);
typedef CGPUTextureViewId (*CGPUProcCreateTextureView)(CGPUDeviceId device, const CGPUTextureViewDescriptor* desc);
typedef void (*CGPUProcFreeTextureView)(CGPUDeviceId device, CGPUTextureViewId render_target);
typedef bool (*CGPUProcTryBindAliasingTexture)(CGPUDeviceId device, const CGPUTextureAliasingBindDescriptor* desc);
typedef uint64_t (*CGPUProcExportSharedTextureHandle)(CGPUDeviceId device, const CGPUExportTextureDescriptor* desc);
typedef CGPUTextureId (*CGPUProcImportSharedTextureHandle)(CGPUDeviceId device, const CGPUImportTextureDescriptor* desc);
typedef CGPUSwapChainId (*CGPUProcCreateSwapChain)(CGPUDeviceId device, const CGPUSwapChainDescriptor* desc);
typedef uint32_t (*CGPUProcAcquireNextImage)(CGPUSwapChainId swapchain, const CGPUAcquireNextDescriptor* desc);
typedef void (*CGPUProcFreeSwapChain)(CGPUDeviceId device, CGPUSwapChainId swapchain);
typedef void (*CGPUProcCmdBegin)(CGPUCommandBufferId cmd);
typedef void (*CGPUProcCmdTransferBufferToBuffer)(CGPUCommandBufferId cmd, const CGPUBufferToBufferTransfer* desc);
typedef void (*CGPUProcCmdTransferTextureToTexture)(CGPUCommandBufferId cmd, const CGPUTextureToTextureTransfer* desc);
typedef void (*CGPUProcCmdTransferBufferToTexture)(CGPUCommandBufferId cmd, const CGPUBufferToTextureTransfer* desc);
typedef void (*CGPUProcCmdTransferBufferToTiles)(CGPUCommandBufferId cmd, const CGPUBufferToTilesTransfer* desc);
typedef void (*CGPUProcCmdResourceBarrier)(CGPUCommandBufferId cmd, const CGPUResourceBarrierDescriptor* desc);
typedef void (*CGPUProcCmdBeginQuery)(CGPUCommandBufferId cmd, CGPUQueryPoolId pool, const CGPUQueryDescriptor* desc);
typedef void (*CGPUProcCmdEndQuery)(CGPUCommandBufferId cmd, CGPUQueryPoolId pool, const CGPUQueryDescriptor* desc);
typedef void (*CGPUProcCmdResetQueryPool)(CGPUCommandBufferId cmd, CGPUQueryPoolId pool, uint32_t start_query, uint32_t query_count);
typedef void (*CGPUProcCmdResolveQuery)(CGPUCommandBufferId cmd, CGPUQueryPoolId pool, CGPUBufferId readback, uint32_t start_query, uint32_t query_count);
typedef void (*CGPUProcCmdEnd)(CGPUCommandBufferId cmd);
typedef CGPUComputePassEncoderId (*CGPUProcCmdBeginComputePass)(CGPUCommandBufferId cmd, const CGPUComputePassDescriptor* desc);
typedef void (*CGPUProcComputeEncoderBindDescriptorSet)(CGPUComputePassEncoderId encoder, CGPUDescriptorSetId set);
typedef void (*CGPUProcComputeEncoderBindPipeline)(CGPUComputePassEncoderId encoder, CGPUComputePipelineId pipeline);
typedef void (*CGPUProcComputeEncoderDispatch)(CGPUComputePassEncoderId encoder, uint32_t x, uint32_t y, uint32_t z);
typedef void (*CGPUProcCmdEndComputePass)(CGPUCommandBufferId cmd, CGPUComputePassEncoderId encoder);
typedef CGPURenderPassEncoderId (*CGPUProcCmdBeginRenderPass)(CGPUCommandBufferId cmd, const CGPUBeginRenderPassInfo* begin_info);
typedef void (*CGPUProcRenderEncoderSetShadingRate)(CGPURenderPassEncoderId encoder, ECGPUShadingRate shading_rate, ECGPUShadingRateCombiner post_rasterize_rate, ECGPUShadingRateCombiner final_rate);
typedef void (*CGPUProcRenderEncoderBindDescriptorSet)(CGPURenderPassEncoderId encoder, CGPUDescriptorSetId set);
typedef void (*CGPUProcRenderEncoderSetViewport)(CGPURenderPassEncoderId encoder, float x, float y, float width, float height, float min_depth, float max_depth);
typedef void (*CGPUProcRenderEncoderSetScissor)(CGPURenderPassEncoderId encoder, uint32_t x, uint32_t y, uint32_t width, uint32_t height);
typedef void (*CGPUProcRenderEncoderBindPipeline)(CGPURenderPassEncoderId encoder, CGPURenderPipelineId pipeline);
typedef void (*CGPUProcRenderEncoderBindVertexBuffers)(CGPURenderPassEncoderId encoder, uint32_t buffer_count, const CGPUBufferId* buffers, const uint32_t* strides, const uint32_t* offsets);
typedef void (*CGPUProcRenderEncoderBindIndexBuffer)(CGPURenderPassEncoderId encoder, CGPUBufferId buffer, uint32_t index_stride, uint64_t offset);
typedef void (*CGPUProcRenderEncoderPushConstants)(CGPURenderPassEncoderId encoder, CGPURootSignatureId rs, const char* name, const void* data);
typedef void (*CGPUProcComputeEncoderPushConstants)(CGPUComputePassEncoderId encoder, CGPURootSignatureId rs, const char* name, const void* data);
typedef void (*CGPUProcRenderEncoderDraw)(CGPURenderPassEncoderId encoder, uint32_t vertex_count, uint32_t first_vertex);
typedef void (*CGPUProcRenderEncoderDrawInstanced)(CGPURenderPassEncoderId encoder, uint32_t vertex_count, uint32_t first_vertex, uint32_t instance_count, uint32_t first_instance);
typedef void (*CGPUProcRenderEncoderDrawIndexed)(CGPURenderPassEncoderId encoder, uint32_t index_count, uint32_t first_index, uint32_t first_vertex);
typedef void (*CGPUProcRenderEncoderDrawIndexedInstanced)(CGPURenderPassEncoderId encoder, uint32_t index_count, uint32_t first_index, uint32_t instance_count, uint32_t first_instance, uint32_t first_vertex);
typedef void (*CGPUProcCmdEndRenderPass)(CGPUCommandBufferId cmd, CGPURenderPassEncoderId encoder);
typedef void (*CGPUProcCmdBeginEvent)(CGPUCommandBufferId cmd, const CGPUEventInfo* event);
typedef void (*CGPUProcCmdSetMarker)(CGPUCommandBufferId cmd, const CGPUMarkerInfo* marker);
typedef void (*CGPUProcCmdEndEvent)(CGPUCommandBufferId cmd);
typedef CGPULinkedShaderId (*CGPUProcCompileAndLinkShaders)(CGPURootSignatureId signature, uint32_t count, const CGPUCompiledShaderDescriptor* desc);
typedef void (*CGPUProcCompileShaders)(CGPURootSignatureId signature, uint32_t count, const CGPUCompiledShaderDescriptor* desc, CGPUCompiledShaderId* out_isas);
typedef void (*CGPUProcFreeCompiledShader)(CGPUCompiledShaderId shader);
typedef void (*CGPUProcFreeLinkedShader)(CGPULinkedShaderId shader);
typedef CGPUStateBufferId (*CGPUProcCreateStateBuffer)(CGPUCommandBufferId cmd, const CGPUStateBufferDescriptor* desc);
typedef void (*CGPUProcRenderEncoderBindStateBuffer)(CGPURenderPassEncoderId encoder, CGPUStateBufferId stream);
typedef void (*CGPUProcComputeEncoderBindStateBuffer)(CGPUComputePassEncoderId encoder, CGPUStateBufferId stream);
typedef void (*CGPUProcFreeStateBuffer)(CGPUStateBufferId stream);
typedef CGPURasterStateEncoderId (*CGPUProcOpenRasterStateEncoder)(CGPUStateBufferId stream, CGPURenderPassEncoderId encoder);
typedef void (*CGPUProcRasterStateEncoderSetViewport)(CGPURasterStateEncoderId encoder, float x, float y, float width, float height, float min_depth, float max_depth);
typedef void (*CGPUProcRasterStateEncoderSetScissor)(CGPURasterStateEncoderId encoder, uint32_t x, uint32_t y, uint32_t width, uint32_t height);
typedef void (*CGPUProcRasterStateEncoderSetCullMode)(CGPURasterStateEncoderId encoder, ECGPUCullModeFlags cull_mode);
typedef void (*CGPUProcRasterStateEncoderSetFrontFace)(CGPURasterStateEncoderId encoder, ECGPUFrontFace front_face);
typedef void (*CGPUProcRasterStateEncoderSetPrimitiveTopology)(CGPURasterStateEncoderId encoder, ECGPUPrimitiveTopology topology);
typedef void (*CGPUProcRasterStateEncoderSetDepthTestEnabled)(CGPURasterStateEncoderId encoder, bool enabled);
typedef void (*CGPUProcRasterStateEncoderSetDepthWriteEnabled)(CGPURasterStateEncoderId encoder, bool enabled);
typedef void (*CGPUProcRasterStateEncoderSetDepthCompareOp)(CGPURasterStateEncoderId encoder, ECGPUCompareOp compare_op);
typedef void (*CGPUProcRasterStateEncoderSetStencilTestEnabled)(CGPURasterStateEncoderId encoder, bool enabled);
typedef void (*CGPUProcRasterStateEncoderSetStencilCompareOp)(CGPURasterStateEncoderId encoder, ECGPUStencilFaceFlags faces, ECGPUStencilOp fail_op, ECGPUStencilOp pass_op, ECGPUStencilOp depth_fail_op, ECGPUCompareOp compare_op);
typedef void (*CGPUProcRasterStateEncoderSetFillMode)(CGPURasterStateEncoderId encoder, ECGPUFillMode fill_mode);
typedef void (*CGPUProcRasterStateEncoderSetSampleCount)(CGPURasterStateEncoderId encoder, ECGPUSampleCountFlags sample_count);
typedef void (*CGPUProcCloseRasterStateEncoder)(CGPURasterStateEncoderId encoder);
typedef CGPUShaderStateEncoderId (*CGPUProcOpenShaderStateEncoderR)(CGPUStateBufferId stream, CGPURenderPassEncoderId encoder);
typedef CGPUShaderStateEncoderId (*CGPUProcOpenShaderStateEncoderC)(CGPUStateBufferId stream, CGPUComputePassEncoderId encoder);
typedef void (*CGPUProcShaderStateEncoderBindShaders)(CGPUShaderStateEncoderId encoder, uint32_t stage_count, const ECGPUShaderStageFlags* stages, const CGPUCompiledShaderId* shaders);
typedef void (*CGPUProcShaderStateEncoderBindLinkedShader)(CGPUShaderStateEncoderId encoder, CGPULinkedShaderId linked);
typedef void (*CGPUProcCloseShaderStateEncoder)(CGPUShaderStateEncoderId encoder);
typedef CGPUUserStateEncoderId (*CGPUProcOpenUserStateEncoder)(CGPUStateBufferId stream, CGPURenderPassEncoderId encoder);
typedef void (*CGPUProcCloseUserStateEncoder)(CGPUUserStateEncoderId encoder);
typedef CGPUBinderId (*CGPUProcCreateBinder)(CGPUCommandBufferId cmd);
typedef void (*CGPUProcBinderBindVertexLayout)(CGPUBinderId binder, const CGPUVertexLayout* layout);
typedef void (*CGPUProcBinderBindVertexBuffer)(CGPUBinderId binder, uint32_t first_binding, uint32_t binding_count, const CGPUBufferId* buffers, const uint64_t* offsets, const uint64_t* sizes, const uint64_t* strides);
typedef void (*CGPUProcFreeBinder)(CGPUBinderId binder);
typedef CGPUSurfaceId (*CGPUProcCreateSurfaceFromNativeView)(CGPUDeviceId device, void* view);
typedef CGPUSurfaceId (*CGPUProcCreateSurfaceFromHwnd)(CGPUDeviceId device, HWND window);
typedef CGPUSurfaceId (*CGPUProcCreateSurfaceFromNativeWindow)(CGPUDeviceId device, ANativeWindowPtr window);
typedef void (*CGPUProcFreeSurface)(CGPUDeviceId device, CGPUSurfaceId surface);

typedef struct CGPULogger
{
    CGPUProcLogCallback  log_callback;
    void*                user_data;

} CGPULogger;

typedef struct CGPUAllocator
{
    CGPUProcMalloc       malloc_fn;
    CGPUProcRealloc      realloc_fn;
    CGPUProcCalloc       calloc_fn;
    CGPUProcFree         free_fn;
    CGPUProcMallocAligned malloc_aligned_fn;
    CGPUProcReallocAligned realloc_aligned_fn;
    CGPUProcCallocAligned calloc_aligned_fn;
    CGPUProcFreeAligned  free_aligned_fn;
    void*                user_data;

} CGPUAllocator;

typedef struct CGPUInstanceDescriptor
{
    ECGPUBackend         backend;
    bool                 enable_debug_layer;
    bool                 enable_gpu_based_validation;
    bool                 enable_set_name;
    CGPULogger           logger;
    CGPUAllocator        allocator;

} CGPUInstanceDescriptor;

typedef struct CGPUInstanceFeatures
{
    bool                 specialization_constant;

} CGPUInstanceFeatures;

typedef struct CGPUInstance
{
    const CGPUProcTable* proc_table;
    const CGPUSurfacesProcTable* surfaces_table;
    CGPURuntimeTable*    runtime_table;
    ECGPUBackend         backend;
    bool                 enable_set_name;
    CGPULogger           logger;
    CGPUAllocator        allocator;

} CGPUInstance;

typedef struct CGPUVendorPreset
{
    uint32_t             device_id;
    uint32_t             vendor_id;
    uint32_t             driver_version;
    char                 gpu_name[64];

} CGPUVendorPreset;

typedef struct CGPUFormatSupport
{
    bool                 shader_read;
    bool                 shader_write;
    bool                 render_target_write;

} CGPUFormatSupport;

typedef struct CGPUAdapterDetail
{
    uint32_t             uniform_buffer_alignment;
    uint32_t             upload_buffer_texture_alignment;
    uint32_t             upload_buffer_texture_row_alignment;
    uint32_t             max_vertex_input_bindings;
    uint32_t             wave_lane_count;
    uint64_t             host_visible_vram_budget;
    ECGPUDynamicStateFeaturesFlags dynamic_state_features;
    bool                 support_host_visible_vram;
    bool                 multidraw_indirect;
    bool                 support_geom_shader;
    bool                 support_tessellation;
    bool                 is_uma;
    bool                 is_virtual;
    bool                 is_cpu;
    bool                 support_tiled_buffer;
    bool                 support_tiled_texture;
    bool                 support_tiled_volume;
    bool                 support_shading_rate;
    bool                 support_shading_rate_mask;
    bool                 support_shading_rate_sv;
    CGPUFormatSupport    format_supports[CGPU_TEXTURE_FORMAT_COUNT];
    CGPUVendorPreset     vendor_preset;

} CGPUAdapterDetail;

typedef struct CGPUAdapter
{
    CGPUInstanceId       instance;
    const CGPUProcTable* proc_table_cache;

} CGPUAdapter;

typedef struct CGPUQueueGroupDescriptor
{
    uint32_t             queue_count;
    ECGPUQueueType       queue_type;

} CGPUQueueGroupDescriptor;

typedef struct CGPUDeviceDescriptor
{
    bool                 disable_pipeline_cache;
    uint32_t             queue_group_count;
    const CGPUQueueGroupDescriptor* p_queue_groups;

} CGPUDeviceDescriptor;

typedef struct CGPUDevice
{
    CGPUAdapterId        adapter;
    const CGPUProcTable* proc_table_cache;
    uint64_t             next_texture_id;
    bool                 is_lost;

} CGPUDevice;

typedef struct CGPUQueue
{
    CGPUDeviceId         device;
    ECGPUQueueType       type;
    uint32_t             index;

} CGPUQueue;

typedef struct CGPUFence
{
    CGPUDeviceId         device;

} CGPUFence;

typedef struct CGPUSemaphore
{
    CGPUDeviceId         device;

} CGPUSemaphore;

typedef struct CGPUCommandPool
{
    CGPUQueueId          queue;

} CGPUCommandPool;

typedef struct CGPUCommandBuffer
{
    CGPUDeviceId         device;
    CGPUCommandPoolId    pool;
    ECGPUPipelineType    current_dispatch;

} CGPUCommandBuffer;

typedef struct CGPUQueryPool
{
    CGPUDeviceId         device;
    uint32_t             count;

} CGPUQueryPool;

typedef struct CGPUComputePassEncoder
{
    CGPUDeviceId         device;

} CGPUComputePassEncoder;

typedef struct CGPURenderPassEncoder
{
    CGPUDeviceId         device;

} CGPURenderPassEncoder;

typedef struct CGPURenderPass
{
    CGPUDeviceId         device;

} CGPURenderPass;

typedef struct CGPUFramebufferInfo
{
    uint32_t             width;
    uint32_t             height;

} CGPUFramebufferInfo;

typedef struct CGPUFramebuffer
{
    CGPUDeviceId         device;
    const CGPUFramebufferInfo* info;

} CGPUFramebuffer;

typedef struct CGPUStateBuffer
{
    CGPUDeviceId         device;
    CGPUCommandBufferId  cmd;

} CGPUStateBuffer;

typedef struct CGPURasterStateEncoder
{
    CGPUDeviceId         device;

} CGPURasterStateEncoder;

typedef struct CGPUShaderStateEncoder
{
    CGPUDeviceId         device;

} CGPUShaderStateEncoder;

typedef struct CGPUUserStateEncoder
{
    CGPUDeviceId         device;

} CGPUUserStateEncoder;

typedef struct CGPUBinder
{
    CGPUDeviceId         device;
    CGPUCommandBufferId  cmd;

} CGPUBinder;

typedef struct CGPURootSignaturePoolDescriptor
{
    const char*          name;

} CGPURootSignaturePoolDescriptor;

typedef struct CGPURootSignaturePool
{
    CGPUDeviceId         device;
    ECGPUPipelineType    pipeline_type;

} CGPURootSignaturePool;

typedef struct CGPUVertexInput
{
    const char*          name;
    const char*          semantics;
    ECGPUVertexFormat    format;

} CGPUVertexInput;

typedef struct CGPUShaderResource
{
    const char*          name;
    uint64_t             name_hash;
    ECGPUResourceTypeFlags type;
    ECGPUTextureDimension dim;
    uint32_t             set;
    uint32_t             binding;
    uint32_t             size;
    uint32_t             offset;
    ECGPUShaderStageFlags stages;

} CGPUShaderResource;

typedef struct CGPUShaderReflection
{
    const char*          entry_name;
    ECGPUShaderStageFlags stage;
    uint32_t             vertex_input_count;
    CGPUVertexInput*     p_vertex_inputs;
    uint32_t             shader_resource_count;
    CGPUShaderResource*  p_shader_resources;
    uint32_t             thread_group_sizes[3];

} CGPUShaderReflection;

typedef struct CGPUShaderLibrary
{
    CGPUDeviceId         device;
    const char*          name;
    uint32_t             entry_count;
    CGPUShaderReflection* p_entry_reflections;

} CGPUShaderLibrary;

typedef union CGPUConstantSpecializationImpl
{
    uint64_t             u;
    int64_t              i;
    double               f;

} CGPUConstantSpecializationImpl;

typedef struct CGPUConstantSpecialization
{
    uint32_t             constant_id;
    CGPUConstantSpecializationImpl spec;

} CGPUConstantSpecialization;

typedef struct CGPUShaderEntryDescriptor
{
    CGPUShaderLibraryId  library;
    const char*          entry;
    ECGPUShaderStageFlags stage;
    uint32_t             constant_count;
    const CGPUConstantSpecialization* p_constants;

} CGPUShaderEntryDescriptor;

typedef struct CGPURootSignatureDescriptor
{
    uint32_t             shader_count;
    const CGPUShaderEntryDescriptor* p_shaders;
    uint32_t             static_sampler_count;
    const CGPUSamplerId* p_static_samplers;
    const char**         p_static_sampler_names;
    uint32_t             push_constant_count;
    const char**         p_push_constant_names;
    CGPURootSignaturePoolId pool;

} CGPURootSignatureDescriptor;

typedef struct CGPUParameterTable
{
    uint32_t             resources_count;
    CGPUShaderResource*  p_resources;
    uint32_t             set_index;

} CGPUParameterTable;

typedef struct CGPURootSignature
{
    CGPUDeviceId         device;
    uint32_t             table_count;
    CGPUParameterTable*  p_tables;
    uint32_t             push_constant_count;
    CGPUShaderResource*  p_push_constants;
    uint32_t             static_sampler_count;
    CGPUShaderResource*  p_static_samplers;
    ECGPUPipelineType    pipeline_type;
    CGPURootSignaturePoolId pool;
    CGPURootSignatureId  pool_sig;

} CGPURootSignature;

typedef struct CGPUDescriptorSet
{
    CGPURootSignatureId  root_signature;
    uint32_t             index;

} CGPUDescriptorSet;

typedef struct CGPUVertexAttribute
{
    const char*          semantic_name;
    uint32_t             array_size;
    ECGPUVertexFormat    format;
    uint32_t             binding;
    uint32_t             offset;
    uint32_t             elem_stride;
    ECGPUVertexInputRate rate;

} CGPUVertexAttribute;

typedef struct CGPUVertexLayout
{
    uint32_t             attribute_count;
    const CGPUVertexAttribute* p_attributes;

} CGPUVertexLayout;

typedef struct CGPUBlendAttachmentState
{
    bool                 enable;
    ECGPUBlendFactor     src_factor;
    ECGPUBlendFactor     dst_factor;
    ECGPUBlendFactor     src_alpha_factor;
    ECGPUBlendFactor     dst_alpha_factor;
    ECGPUBlendOp         blend_op;
    ECGPUBlendOp         blend_alpha_op;
    ECGPUColorMaskFlags  color_mask;

} CGPUBlendAttachmentState;

typedef struct CGPUBlendStateDescriptor
{
    uint32_t             attachment_count;
    const CGPUBlendAttachmentState* p_attachments;
    bool                 alpha_to_coverage;
    bool                 independent_blend;

} CGPUBlendStateDescriptor;

typedef struct CGPUDepthStateDescriptor
{
    bool                 depth_test;
    bool                 depth_write;
    ECGPUCompareOp       depth_op;
    bool                 stencil_test;
    uint8_t              stencil_read_mask;
    uint8_t              stencil_write_mask;
    ECGPUCompareOp       stencil_front_op;
    ECGPUStencilOp       stencil_front_fail_op;
    ECGPUStencilOp       depth_front_fail_op;
    ECGPUStencilOp       stencil_front_pass_op;
    ECGPUCompareOp       stencil_back_op;
    ECGPUStencilOp       stencil_back_fail_op;
    ECGPUStencilOp       depth_back_fail_op;
    ECGPUStencilOp       stencil_back_pass_op;

} CGPUDepthStateDescriptor;

typedef struct CGPURasterizerStateDescriptor
{
    ECGPUCullModeFlags   cull_mode;
    int32_t              depth_bias;
    float                slope_scaled_depth_bias;
    ECGPUFillMode        fill_mode;
    ECGPUFrontFace       front_face;
    bool                 enable_multi_sample;
    bool                 enable_scissor;
    bool                 enable_depth_clamp;

} CGPURasterizerStateDescriptor;

typedef struct CGPURenderPipelineDescriptor
{
    uint64_t             dynamic_state;
    CGPURootSignatureId  root_signature;
    const CGPUShaderEntryDescriptor* vertex_shader;
    const CGPUShaderEntryDescriptor* tesc_shader;
    const CGPUShaderEntryDescriptor* tese_shader;
    const CGPUShaderEntryDescriptor* geom_shader;
    const CGPUShaderEntryDescriptor* fragment_shader;
    const CGPUVertexLayout* vertex_layout;
    const CGPUBlendStateDescriptor* blend_state;
    const CGPUDepthStateDescriptor* depth_state;
    const CGPURasterizerStateDescriptor* rasterizer_state;
    CGPURenderPassId     render_pass;
    uint32_t             subpass;
    uint32_t             render_target_count;
    ECGPUSampleCountFlags sample_count;
    ECGPUPrimitiveTopology prim_topology;

} CGPURenderPipelineDescriptor;

typedef struct CGPURenderPipeline
{
    CGPUDeviceId         device;
    CGPURootSignatureId  root_signature;

} CGPURenderPipeline;

typedef struct CGPUComputePipelineDescriptor
{
    CGPURootSignatureId  root_signature;
    const CGPUShaderEntryDescriptor* compute_shader;

} CGPUComputePipelineDescriptor;

typedef struct CGPUComputePipeline
{
    CGPUDeviceId         device;
    CGPURootSignatureId  root_signature;

} CGPUComputePipeline;

typedef struct CGPUCompiledShader
{
    CGPUDeviceId         device;
    CGPURootSignatureId  root_signature;

} CGPUCompiledShader;

typedef struct CGPULinkedShader
{
    CGPUDeviceId         device;
    CGPURootSignatureId  root_signature;

} CGPULinkedShader;

typedef struct CGPUDescriptorSetDescriptor
{
    CGPURootSignatureId  root_signature;
    uint32_t             set_index;

} CGPUDescriptorSetDescriptor;

typedef struct CGPUBufferParams
{
    const uint64_t*      offsets;
    const uint64_t*      sizes;

} CGPUBufferParams;

typedef struct CGPUUavParams
{
    uint32_t             uav_mip_slice;
    bool                 blend_mip_chain;

} CGPUUavParams;

typedef union CGPUDescriptorDataParams
{
    CGPUBufferParams     buffers_params;
    CGPUUavParams        uav_params;
    bool                 enable_stencil_resource;

} CGPUDescriptorDataParams;

typedef union CGPUDescriptorDataResource
{
    void**               ptrs;
    const CGPUTextureViewId* textures;
    const CGPUSamplerId* samplers;
    CGPUBufferId*        buffers;
    CGPURenderPipelineId* render_pipelines;
    CGPUComputePipelineId* compute_pipelines;
    CGPUDescriptorSetId* descriptor_sets;

} CGPUDescriptorDataResource;

typedef struct CGPUDescriptorData
{
    const char*          name;
    uint32_t             binding;
    ECGPUResourceTypeFlags binding_type;
    CGPUDescriptorDataParams params;
    CGPUDescriptorDataResource resources;
    uint32_t             count;

} CGPUDescriptorData;

typedef struct CGPUBufferInfo
{
    uint64_t             size;
    uint8_t*             cpu_mapped_address;
    ECGPUResourceTypeFlags descriptors;
    ECGPUMemoryUsage     memory_usage;

} CGPUBufferInfo;

typedef struct CGPUBuffer
{
    CGPUDeviceId         device;
    const CGPUBufferInfo* info;

} CGPUBuffer;

typedef struct CGPUTextureInfo
{
    uint64_t             width;
    uint64_t             height;
    uint64_t             depth;
    uint32_t             mip_levels;
    uint32_t             array_size_minus_one;
    uint64_t             size_in_bytes;
    ECGPUTextureFormat   format;
    ECGPUSampleCountFlags sample_count;
    uint64_t             unique_id;
    ECGPUTextureViewAspectFlags aspect_mask;
    uint8_t              owns_image;
    uint8_t              is_cube;
    uint8_t              is_allocation_dedicated;
    uint8_t              is_restrict_dedicated;
    uint8_t              is_aliasing;
    uint8_t              is_tiled;
    uint8_t              is_imported;
    uint8_t              can_alias;
    uint8_t              can_export;

} CGPUTextureInfo;

typedef struct CGPUTiledSubresourceInfo
{
    uint16_t             layer;
    uint16_t             mip_level;
    uint32_t             width_in_tiles;
    uint16_t             height_in_tiles;
    uint16_t             depth_in_tiles;

} CGPUTiledSubresourceInfo;

typedef struct CGPUTiledTextureInfo
{
    uint64_t             tile_size;
    uint64_t             total_tiles_count;
    uint64_t             alive_tiles_count;
    uint32_t             tile_width_in_texels;
    uint32_t             tile_height_in_texels;
    uint32_t             tile_depth_in_texels;
    const CGPUTiledSubresourceInfo* subresources;
    uint32_t             packed_mip_start;
    uint32_t             packed_mip_count;
    uint64_t             alive_pack_count;
    bool                 pack_unaligned;

} CGPUTiledTextureInfo;

typedef struct CGPUTexture
{
    CGPUDeviceId         device;
    const CGPUTextureInfo* info;
    const CGPUTiledTextureInfo* tiled_resource;

} CGPUTexture;

typedef struct CGPUTextureViewDescriptor
{
    const char*          name;
    CGPUTextureId        texture;
    ECGPUTextureFormat   format;
    ECGPUTextureViewUsageFlags usages;
    ECGPUTextureViewAspectFlags aspects;
    ECGPUTextureDimension dims;
    uint8_t              base_array_layer;
    uint8_t              array_layer_count;
    uint8_t              base_mip_level;
    uint8_t              mip_level_count;

} CGPUTextureViewDescriptor;

typedef struct CGPUQueryPoolDescriptor
{
    ECGPUQueryType       type;
    uint32_t             query_count;

} CGPUQueryPoolDescriptor;

typedef struct CGPUTextureView
{
    CGPUDeviceId         device;
    CGPUTextureViewDescriptor info;

} CGPUTextureView;

typedef struct CGPUSampler
{
    CGPUDeviceId         device;

} CGPUSampler;

typedef struct CGPUSwapChain
{
    CGPUDeviceId         device;
    const CGPUTextureId* back_buffers;
    uint32_t             buffer_count;

} CGPUSwapChain;

struct CGPUSurface_s;
typedef struct CGPUSurface_s CGPUSurface_t;

typedef struct CGPUBufferRange
{
    uint64_t             offset;
    uint64_t             size;

} CGPUBufferRange;

typedef struct CGPUMemoryPoolDescriptor
{
    ECGPUMemoryPoolType  type;
    ECGPUMemoryUsage     memory_usage;
    uint64_t             block_size;
    uint32_t             min_block_count;
    uint32_t             max_block_count;
    uint64_t             min_alloc_alignment;

} CGPUMemoryPoolDescriptor;

typedef struct CGPUMemoryPool
{
    CGPUDeviceId         device;
    ECGPUMemoryPoolType  type;

} CGPUMemoryPool;

typedef struct CGPUQueueSubmitDescriptor
{
    uint32_t             cmd_count;
    const CGPUCommandBufferId* p_cmds;
    CGPUFenceId          signal_fence;
    uint32_t             wait_semaphore_count;
    const CGPUSemaphoreId* p_wait_semaphores;
    uint32_t             signal_semaphore_count;
    const CGPUSemaphoreId* p_signal_semaphores;

} CGPUQueueSubmitDescriptor;

typedef struct CGPUQueuePresentDescriptor
{
    CGPUSwapChainId      swapchain;
    uint32_t             wait_semaphore_count;
    const CGPUSemaphoreId* p_wait_semaphores;
    uint8_t              index;

} CGPUQueuePresentDescriptor;

typedef struct CGPUCoordinate
{
    uint32_t             x;
    uint32_t             y;
    uint32_t             z;

} CGPUCoordinate;

typedef struct CGPUCoordinateRegion
{
    CGPUCoordinate       start;
    CGPUCoordinate       end;

} CGPUCoordinateRegion;

typedef struct CGPUTextureCoordinateRegion
{
    CGPUCoordinate       start;
    CGPUCoordinate       end;
    uint32_t             mip_level;
    uint32_t             layer;

} CGPUTextureCoordinateRegion;

typedef struct CGPUTiledTextureRegions
{
    CGPUTextureId        texture;
    uint32_t             region_count;
    const CGPUTextureCoordinateRegion* p_regions;

} CGPUTiledTextureRegions;

typedef struct CGPUTiledTexturePackedMip
{
    CGPUTextureId        texture;
    uint32_t             layer;

} CGPUTiledTexturePackedMip;

typedef struct CGPUTiledTexturePackedMips
{
    uint32_t             packed_mip_count;
    const CGPUTiledTexturePackedMip* p_packed_mips;

} CGPUTiledTexturePackedMips;

typedef struct CGPUColorAttachment
{
    ECGPUTextureFormat   format;
    ECGPULoadAction      load_action;
    ECGPUStoreAction     store_action;

} CGPUColorAttachment;

typedef struct CGPUDepthStencilAttachment
{
    ECGPUTextureFormat   format;
    ECGPULoadAction      depth_load_action;
    ECGPUStoreAction     depth_store_action;
    ECGPULoadAction      stencil_load_action;
    ECGPUStoreAction     stencil_store_action;

} CGPUDepthStencilAttachment;

typedef struct CGPURenderPassDescriptor
{
    ECGPUSampleCountFlags sample_count;
    CGPUColorAttachment  color_attachments[CGPU_MAX_MRT_COUNT];
    CGPUDepthStencilAttachment depth_stencil;

} CGPURenderPassDescriptor;

typedef struct CGPUFramebufferDescriptor
{
    CGPURenderPassId     renderpass;
    uint32_t             attachment_count;
    CGPUTextureViewId    p_attachments[CGPU_MAX_ATTACHMENT_COUNT];
    uint32_t             width;
    uint32_t             height;
    uint32_t             layers;

} CGPUFramebufferDescriptor;

typedef struct CGPUPipelineReflection
{
    CGPUShaderReflection* stages[CGPU_SHADER_STAGE_COUNT];
    uint32_t             shader_resources_count;
    const CGPUShaderResource* p_shader_resources;

} CGPUPipelineReflection;

typedef struct CGPUClearValue
{
    float                color[4];
    float                depth;
    uint8_t              stencil;
    bool                 is_color;

} CGPUClearValue;

typedef struct CGPUQueryDescriptor
{
    uint32_t             index;
    ECGPUShaderStageFlags stage;

} CGPUQueryDescriptor;

typedef struct CGPUAcquireNextDescriptor
{
    CGPUSemaphoreId      signal_semaphore;
    CGPUFenceId          fence;

} CGPUAcquireNextDescriptor;

typedef struct CGPUTextureSubresource
{
    ECGPUTextureViewAspectFlags aspects;
    uint32_t             mip_level;
    uint32_t             base_array_layer;
    uint32_t             layer_count;

} CGPUTextureSubresource;

typedef struct CGPUBufferToBufferTransfer
{
    CGPUBufferId         dst;
    uint64_t             dst_offset;
    CGPUBufferId         src;
    uint64_t             src_offset;
    uint64_t             size;

} CGPUBufferToBufferTransfer;

typedef struct CGPUBufferToTilesTransfer
{
    CGPUBufferId         src;
    uint64_t             src_offset;
    CGPUTextureId        dst;
    CGPUTextureCoordinateRegion region;

} CGPUBufferToTilesTransfer;

typedef struct CGPUTextureToTextureTransfer
{
    CGPUTextureId        src;
    CGPUTextureSubresource src_subresource;
    CGPUTextureId        dst;
    CGPUTextureSubresource dst_subresource;

} CGPUTextureToTextureTransfer;

typedef struct CGPUBufferToTextureTransfer
{
    CGPUTextureId        dst;
    CGPUTextureSubresource dst_subresource;
    CGPUBufferId         src;
    uint64_t             src_offset;

} CGPUBufferToTextureTransfer;

typedef struct CGPUBufferBarrier
{
    CGPUBufferId         buffer;
    ECGPUResourceStateFlags src_state;
    ECGPUResourceStateFlags dst_state;
    uint8_t              queue_acquire;
    uint8_t              queue_release;
    ECGPUQueueType       queue_type;

} CGPUBufferBarrier;

typedef struct CGPUTextureBarrier
{
    CGPUTextureId        texture;
    ECGPUResourceStateFlags src_state;
    ECGPUResourceStateFlags dst_state;
    uint8_t              queue_acquire;
    uint8_t              queue_release;
    ECGPUQueueType       queue_type;
    uint8_t              subresource_barrier;
    uint8_t              mip_level;
    uint16_t             array_layer;

} CGPUTextureBarrier;

typedef struct CGPUResourceBarrierDescriptor
{
    uint32_t             buffer_barrier_count;
    const CGPUBufferBarrier* p_buffer_barriers;
    uint32_t             texture_barrier_count;
    const CGPUTextureBarrier* p_texture_barriers;

} CGPUResourceBarrierDescriptor;

typedef struct CGPUCommandPoolDescriptor
{
    const char*          name;

} CGPUCommandPoolDescriptor;

typedef struct CGPUCommandBufferDescriptor
{
    bool                 is_secondary;

} CGPUCommandBufferDescriptor;

typedef struct CGPUSwapChainDescriptor
{
    uint32_t             present_queue_count;
    const CGPUQueueId*   p_present_queues;
    CGPUSurfaceId        surface;
    uint32_t             image_count;
    uint32_t             width;
    uint32_t             height;
    bool                 enable_vsync;
    bool                 use_flip_swap_effect;
    ECGPUTextureFormat   format;

} CGPUSwapChainDescriptor;

typedef struct CGPUComputePassDescriptor
{
    const char*          name;

} CGPUComputePassDescriptor;

typedef struct CGPUCompiledShaderDescriptor
{
    CGPUShaderEntryDescriptor entry;
    void*                shader_code;
    uint64_t             code_size;

} CGPUCompiledShaderDescriptor;

typedef struct CGPUShaderLibraryDescriptor
{
    const char*          name;
    size_t               code_size;
    const uint8_t*       p_codes;
    ECGPUShaderStageFlags stage;
    bool                 reflection_only;

} CGPUShaderLibraryDescriptor;

typedef struct CGPUBufferDescriptor
{
    uint64_t             size;
    CGPUBufferId         count_buffer;
    const char*          name;
    ECGPUResourceTypeFlags descriptors;
    ECGPUMemoryUsage     memory_usage;
    ECGPUTextureFormat   format;
    ECGPUBufferCreationUsageFlags flags;
    uint64_t             first_element;
    uint64_t             element_count;
    uint64_t             element_stride;
    CGPUQueueId          owner_queue;
    ECGPUResourceStateFlags start_state;
    bool                 prefer_on_device;
    bool                 prefer_on_host;

} CGPUBufferDescriptor;

typedef struct CGPUTextureDescriptor
{
    const char*          name;
    const void*          native_handle;
    ECGPUTextureCreationUsageFlags flags;
    uint64_t             width;
    uint64_t             height;
    uint64_t             depth;
    uint32_t             array_size;
    ECGPUTextureFormat   format;
    uint32_t             mip_levels;
    ECGPUSampleCountFlags sample_count;
    uint32_t             sample_quality;
    CGPUQueueId          owner_queue;
    ECGPUResourceStateFlags start_state;
    ECGPUResourceTypeFlags descriptors;
    uint32_t             is_restrict_dedicated;

} CGPUTextureDescriptor;

typedef struct CGPUExportTextureDescriptor
{
    CGPUTextureId        texture;

} CGPUExportTextureDescriptor;

typedef struct CGPUImportTextureDescriptor
{
    ECGPUBackend         backend;
    uint64_t             shared_handle;
    uint64_t             width;
    uint64_t             height;
    uint64_t             depth;
    uint64_t             size_in_bytes;
    ECGPUTextureFormat   format;
    uint32_t             mip_levels;

} CGPUImportTextureDescriptor;

typedef struct CGPUTextureAliasingBindDescriptor
{
    CGPUTextureId        aliased;
    CGPUTextureId        aliasing;

} CGPUTextureAliasingBindDescriptor;

typedef struct CGPUSamplerDescriptor
{
    ECGPUFilterType      min_filter;
    ECGPUFilterType      mag_filter;
    ECGPUMipMapMode      mipmap_mode;
    ECGPUAddressMode     address_u;
    ECGPUAddressMode     address_v;
    ECGPUAddressMode     address_w;
    float                mip_lod_bias;
    float                max_anisotropy;
    ECGPUCompareOp       compare_func;

} CGPUSamplerDescriptor;

typedef struct CGPUBeginRenderPassInfo
{
    CGPURenderPassId     render_pass;
    CGPUFramebufferId    framebuffer;
    uint32_t             clear_value_count;
    const CGPUClearValue* p_clear_values;

} CGPUBeginRenderPassInfo;

typedef struct CGPUEventInfo
{
    const char*          name;
    float                color[4];

} CGPUEventInfo;

typedef struct CGPUMarkerInfo
{
    const char*          name;
    float                color[4];

} CGPUMarkerInfo;

struct CGPUStateBufferDescriptor_s;
typedef struct CGPUStateBufferDescriptor_s CGPUStateBufferDescriptor_t;

typedef struct CGPUProcTable
{
    CGPUProcCreateInstance create_instance;
    CGPUProcQueryInstanceFeatures query_instance_features;
    CGPUProcFreeInstance free_instance;
    CGPUProcEnumAdapters enum_adapters;
    CGPUProcQueryAdapterDetail query_adapter_detail;
    CGPUProcQueryVideoMemoryInfo query_video_memory_info;
    CGPUProcQuerySharedMemoryInfo query_shared_memory_info;
    CGPUProcQueryQueueCount query_queue_count;
    CGPUProcCreateDevice create_device;
    CGPUProcFreeDevice   free_device;
    CGPUProcCreateFence  create_fence;
    CGPUProcWaitFences   wait_fences;
    CGPUProcQueryFenceStatus query_fence_status;
    CGPUProcFreeFence    free_fence;
    CGPUProcCreateSemaphore create_semaphore;
    CGPUProcFreeSemaphore free_semaphore;
    CGPUProcCreateRootSignaturePool create_root_signature_pool;
    CGPUProcFreeRootSignaturePool free_root_signature_pool;
    CGPUProcCreateRootSignature create_root_signature;
    CGPUProcFreeRootSignature free_root_signature;
    CGPUProcCreateDescriptorSet create_descriptor_set;
    CGPUProcFreeDescriptorSet free_descriptor_set;
    CGPUProcUpdateDescriptorSet update_descriptor_set;
    CGPUProcCreateComputePipeline create_compute_pipeline;
    CGPUProcFreeComputePipeline free_compute_pipeline;
    CGPUProcCreateRenderPipeline create_render_pipeline;
    CGPUProcFreeRenderPipeline free_render_pipeline;
    CGPUProcCreateMemoryPool create_memory_pool;
    CGPUProcFreeMemoryPool free_memory_pool;
    CGPUProcCreateQueryPool create_query_pool;
    CGPUProcFreeQueryPool free_query_pool;
    CGPUProcGetQueue     get_queue;
    CGPUProcSubmitQueue  submit_queue;
    CGPUProcWaitQueueIdle wait_queue_idle;
    CGPUProcQueuePresent queue_present;
    CGPUProcQueueGetTimestampPeriodNS queue_get_timestamp_period;
    CGPUProcQueueMapTiledTexture queue_map_tiled_texture;
    CGPUProcQueueUnmapTiledTexture queue_unmap_tiled_texture;
    CGPUProcQueueMapPackedMips queue_map_packed_mips;
    CGPUProcQueueUnmapPackedMips queue_unmap_packed_mips;
    CGPUProcFreeQueue    free_queue;
    CGPUProcCreateRenderPass create_render_pass;
    CGPUProcCreateFramebuffer create_framebuffer;
    CGPUProcFreeRenderPass free_render_pass;
    CGPUProcFreeFramebuffer free_framebuffer;
    CGPUProcCreateCommandPool create_command_pool;
    CGPUProcCreateCommandBuffer create_command_buffer;
    CGPUProcResetCommandPool reset_command_pool;
    CGPUProcFreeCommandBuffer free_command_buffer;
    CGPUProcFreeCommandPool free_command_pool;
    CGPUProcCreateShaderLibrary create_shader_library;
    CGPUProcFreeShaderLibrary free_shader_library;
    CGPUProcCreateBuffer create_buffer;
    CGPUProcMapBuffer    map_buffer;
    CGPUProcUnmapBuffer  unmap_buffer;
    CGPUProcFreeBuffer   free_buffer;
    CGPUProcCreateSampler create_sampler;
    CGPUProcFreeSampler  free_sampler;
    CGPUProcCreateTexture create_texture;
    CGPUProcFreeTexture  free_texture;
    CGPUProcCreateTextureView create_texture_view;
    CGPUProcFreeTextureView free_texture_view;
    CGPUProcTryBindAliasingTexture try_bind_aliasing_texture;
    CGPUProcExportSharedTextureHandle export_shared_texture_handle;
    CGPUProcImportSharedTextureHandle import_shared_texture_handle;
    CGPUProcCreateSwapChain create_swapchain;
    CGPUProcAcquireNextImage acquire_next_image;
    CGPUProcFreeSwapChain free_swapchain;
    CGPUProcCmdBegin     cmd_begin;
    CGPUProcCmdTransferBufferToBuffer cmd_transfer_buffer_to_buffer;
    CGPUProcCmdTransferBufferToTexture cmd_transfer_buffer_to_texture;
    CGPUProcCmdTransferBufferToTiles cmd_transfer_buffer_to_tiles;
    CGPUProcCmdTransferTextureToTexture cmd_transfer_texture_to_texture;
    CGPUProcCmdResourceBarrier cmd_resource_barrier;
    CGPUProcCmdBeginQuery cmd_begin_query;
    CGPUProcCmdEndQuery  cmd_end_query;
    CGPUProcCmdResetQueryPool cmd_reset_query_pool;
    CGPUProcCmdResolveQuery cmd_resolve_query;
    CGPUProcCmdEnd       cmd_end;
    CGPUProcCmdBeginComputePass cmd_begin_compute_pass;
    CGPUProcComputeEncoderBindDescriptorSet compute_encoder_bind_descriptor_set;
    CGPUProcComputeEncoderPushConstants compute_encoder_push_constants;
    CGPUProcComputeEncoderBindPipeline compute_encoder_bind_pipeline;
    CGPUProcComputeEncoderDispatch compute_encoder_dispatch;
    CGPUProcCmdEndComputePass cmd_end_compute_pass;
    CGPUProcCmdBeginRenderPass cmd_begin_render_pass;
    CGPUProcRenderEncoderSetShadingRate render_encoder_set_shading_rate;
    CGPUProcRenderEncoderBindDescriptorSet render_encoder_bind_descriptor_set;
    CGPUProcRenderEncoderBindPipeline render_encoder_bind_pipeline;
    CGPUProcRenderEncoderBindVertexBuffers render_encoder_bind_vertex_buffers;
    CGPUProcRenderEncoderBindIndexBuffer render_encoder_bind_index_buffer;
    CGPUProcRenderEncoderPushConstants render_encoder_push_constants;
    CGPUProcRenderEncoderSetViewport render_encoder_set_viewport;
    CGPUProcRenderEncoderSetScissor render_encoder_set_scissor;
    CGPUProcRenderEncoderDraw render_encoder_draw;
    CGPUProcRenderEncoderDrawInstanced render_encoder_draw_instanced;
    CGPUProcRenderEncoderDrawIndexed render_encoder_draw_indexed;
    CGPUProcRenderEncoderDrawIndexedInstanced render_encoder_draw_indexed_instanced;
    CGPUProcCmdEndRenderPass cmd_end_render_pass;
    CGPUProcCmdBeginEvent cmd_begin_event;
    CGPUProcCmdSetMarker cmd_set_marker;
    CGPUProcCmdEndEvent  cmd_end_event;
    CGPUProcCompileAndLinkShaders compile_and_link_shaders;
    CGPUProcCompileShaders compile_shaders;
    CGPUProcFreeCompiledShader free_compiled_shader;
    CGPUProcFreeLinkedShader free_linked_shader;
    CGPUProcCreateStateBuffer create_state_buffer;
    CGPUProcRenderEncoderBindStateBuffer render_encoder_bind_state_buffer;
    CGPUProcComputeEncoderBindStateBuffer compute_encoder_bind_state_buffer;
    CGPUProcFreeStateBuffer free_state_buffer;
    CGPUProcOpenRasterStateEncoder open_raster_state_encoder;
    CGPUProcRasterStateEncoderSetViewport raster_state_encoder_set_viewport;
    CGPUProcRasterStateEncoderSetScissor raster_state_encoder_set_scissor;
    CGPUProcRasterStateEncoderSetCullMode raster_state_encoder_set_cull_mode;
    CGPUProcRasterStateEncoderSetFrontFace raster_state_encoder_set_front_face;
    CGPUProcRasterStateEncoderSetPrimitiveTopology raster_state_encoder_set_primitive_topology;
    CGPUProcRasterStateEncoderSetDepthTestEnabled raster_state_encoder_set_depth_test_enabled;
    CGPUProcRasterStateEncoderSetDepthWriteEnabled raster_state_encoder_set_depth_write_enabled;
    CGPUProcRasterStateEncoderSetDepthCompareOp raster_state_encoder_set_depth_compare_op;
    CGPUProcRasterStateEncoderSetStencilTestEnabled raster_state_encoder_set_stencil_test_enabled;
    CGPUProcRasterStateEncoderSetStencilCompareOp raster_state_encoder_set_stencil_compare_op;
    CGPUProcRasterStateEncoderSetFillMode raster_state_encoder_set_fill_mode;
    CGPUProcRasterStateEncoderSetSampleCount raster_state_encoder_set_sample_count;
    CGPUProcCloseRasterStateEncoder close_raster_state_encoder;
    CGPUProcOpenShaderStateEncoderR open_shader_state_encoder_r;
    CGPUProcOpenShaderStateEncoderC open_shader_state_encoder_c;
    CGPUProcShaderStateEncoderBindShaders shader_state_encoder_bind_shaders;
    CGPUProcShaderStateEncoderBindLinkedShader shader_state_encoder_bind_linked_shader;
    CGPUProcCloseShaderStateEncoder close_shader_state_encoder;
    CGPUProcOpenUserStateEncoder open_user_state_encoder;
    CGPUProcCloseUserStateEncoder close_user_state_encoder;
    CGPUProcCreateBinder create_binder;
    CGPUProcBinderBindVertexLayout binder_bind_vertex_layout;
    CGPUProcBinderBindVertexBuffer binder_bind_vertex_buffer;
    CGPUProcFreeBinder   free_binder;

} CGPUProcTable;

typedef struct CGPUSurfacesProcTable
{
    CGPUProcCreateSurfaceFromHwnd from_hwnd;
    CGPUProcCreateSurfaceFromNativeWindow from_native_window;
    CGPUProcFreeSurface  free_surface;

} CGPUSurfacesProcTable;

struct CGPURuntimeTable_s;
typedef struct CGPURuntimeTable_s CGPURuntimeTable_t;


CGPU_API CGPUInstanceId cgpu_create_instance(const CGPUInstanceDescriptor* desc);
CGPU_API void cgpu_free_instance(CGPUInstanceId instance);
CGPU_API ECGPUBackend cgpu_instance_get_backend(const CGPUInstanceId _this);
CGPU_API void cgpu_instance_query_instance_features(const CGPUInstanceId _this, CGPUInstanceFeatures* features);
CGPU_API void cgpu_instance_enum_adapters(const CGPUInstanceId _this, uint32_t* p_adapters_count, CGPUAdapterId* p_adapters);
CGPU_API const CGPUAdapterDetail* cgpu_adapter_query_adapter_detail(const CGPUAdapterId _this);
CGPU_API uint32_t cgpu_adapter_query_queue_count(const CGPUAdapterId _this, ECGPUQueueType type);
CGPU_API CGPUDeviceId cgpu_adapter_create_device(CGPUAdapterId _this, const CGPUDeviceDescriptor* desc);
CGPU_API void cgpu_adapter_free_device(CGPUAdapterId _this, CGPUDeviceId device);
CGPU_API void cgpu_device_query_video_memory_info(CGPUDeviceId _this, uint64_t* total, uint64_t* used);
CGPU_API void cgpu_device_query_shared_memory_info(CGPUDeviceId _this, uint64_t* total, uint64_t* used);
CGPU_API CGPUFenceId cgpu_device_create_fence(CGPUDeviceId _this);
CGPU_API void cgpu_device_free_fence(CGPUDeviceId _this, CGPUFenceId fence);
CGPU_API CGPUSemaphoreId cgpu_device_create_semaphore(CGPUDeviceId _this);
CGPU_API void cgpu_device_free_semaphore(CGPUDeviceId _this, CGPUSemaphoreId semaphore);
CGPU_API CGPURootSignaturePoolId cgpu_device_create_root_signature_pool(CGPUDeviceId _this, const CGPURootSignaturePoolDescriptor* desc);
CGPU_API void cgpu_device_free_root_signature_pool(CGPUDeviceId _this, CGPURootSignaturePoolId pool);
CGPU_API CGPURootSignatureId cgpu_device_create_root_signature(CGPUDeviceId _this, const CGPURootSignatureDescriptor* desc);
CGPU_API void cgpu_device_free_root_signature(CGPUDeviceId _this, CGPURootSignatureId signature);
CGPU_API CGPUDescriptorSetId cgpu_device_create_descriptor_set(CGPUDeviceId _this, const CGPUDescriptorSetDescriptor* desc);
CGPU_API void cgpu_device_free_descriptor_set(CGPUDeviceId _this, CGPUDescriptorSetId set);
CGPU_API CGPUComputePipelineId cgpu_device_create_compute_pipeline(CGPUDeviceId _this, const CGPUComputePipelineDescriptor* desc);
CGPU_API void cgpu_device_free_compute_pipeline(CGPUDeviceId _this, CGPUComputePipelineId pipeline);
CGPU_API CGPURenderPipelineId cgpu_device_create_render_pipeline(CGPUDeviceId _this, const CGPURenderPipelineDescriptor* desc);
CGPU_API void cgpu_device_free_render_pipeline(CGPUDeviceId _this, CGPURenderPipelineId pipeline);
CGPU_API CGPUQueryPoolId cgpu_device_create_query_pool(CGPUDeviceId _this, const CGPUQueryPoolDescriptor* desc);
CGPU_API void cgpu_device_free_query_pool(CGPUDeviceId _this, CGPUQueryPoolId pool);
CGPU_API CGPUMemoryPoolId cgpu_device_create_memory_pool(CGPUDeviceId _this, const CGPUMemoryPoolDescriptor* desc);
CGPU_API void cgpu_device_free_memory_pool(CGPUDeviceId _this, CGPUMemoryPoolId pool);
CGPU_API CGPUQueueId cgpu_device_get_queue(CGPUDeviceId _this, ECGPUQueueType type, uint32_t index);
CGPU_API void cgpu_device_free_queue(CGPUDeviceId _this, CGPUQueueId queue);
CGPU_API CGPURenderPassId cgpu_device_create_render_pass(CGPUDeviceId _this, const CGPURenderPassDescriptor* desc);
CGPU_API CGPUFramebufferId cgpu_device_create_framebuffer(CGPUDeviceId _this, const CGPUFramebufferDescriptor* desc);
CGPU_API void cgpu_device_free_render_pass(CGPUDeviceId _this, CGPURenderPassId render_pass);
CGPU_API void cgpu_device_free_framebuffer(CGPUDeviceId _this, CGPUFramebufferId framebuffer);
CGPU_API CGPUShaderLibraryId cgpu_device_create_shader_library(CGPUDeviceId _this, const CGPUShaderLibraryDescriptor* desc);
CGPU_API void cgpu_device_free_shader_library(CGPUDeviceId _this, CGPUShaderLibraryId library);
CGPU_API CGPUBufferId cgpu_device_create_buffer(CGPUDeviceId _this, const CGPUBufferDescriptor* desc);
CGPU_API void cgpu_device_free_buffer(CGPUDeviceId _this, CGPUBufferId buffer);
CGPU_API CGPUSamplerId cgpu_device_create_sampler(CGPUDeviceId _this, const CGPUSamplerDescriptor* desc);
CGPU_API void cgpu_device_free_sampler(CGPUDeviceId _this, CGPUSamplerId sampler);
CGPU_API CGPUTextureId cgpu_device_create_texture(CGPUDeviceId _this, const CGPUTextureDescriptor* desc);
CGPU_API void cgpu_device_free_texture(CGPUDeviceId _this, CGPUTextureId texture);
CGPU_API CGPUTextureViewId cgpu_device_create_texture_view(CGPUDeviceId _this, const CGPUTextureViewDescriptor* desc);
CGPU_API void cgpu_device_free_texture_view(CGPUDeviceId _this, CGPUTextureViewId render_target);
CGPU_API bool cgpu_device_try_bind_aliasing_texture(CGPUDeviceId _this, const CGPUTextureAliasingBindDescriptor* desc);
CGPU_API uint64_t cgpu_device_export_shared_texture_handle(CGPUDeviceId _this, const CGPUExportTextureDescriptor* desc);
CGPU_API CGPUTextureId cgpu_device_import_shared_texture_handle(CGPUDeviceId _this, const CGPUImportTextureDescriptor* desc);
CGPU_API CGPUSwapChainId cgpu_device_create_swap_chain(CGPUDeviceId _this, const CGPUSwapChainDescriptor* desc);
CGPU_API void cgpu_device_free_swap_chain(CGPUDeviceId _this, CGPUSwapChainId swapchain);
CGPU_API CGPUSurfaceId cgpu_device_create_surface_from_native_view(CGPUDeviceId _this, void* view);
CGPU_API CGPUSurfaceId cgpu_device_create_surface_from_hwnd(CGPUDeviceId _this, HWND window);
CGPU_API CGPUSurfaceId cgpu_device_create_surface_from_native_window(CGPUDeviceId _this, ANativeWindowPtr window);
CGPU_API void cgpu_device_free_surface(CGPUDeviceId _this, CGPUSurfaceId surface);
CGPU_API void cgpu_wait_fences(uint32_t fence_count, const CGPUFenceId* p_fences);
CGPU_API ECGPUFenceStatus cgpu_fence_query_status(CGPUFenceId _this);
CGPU_API void cgpu_queue_submit(CGPUQueueId _this, const CGPUQueueSubmitDescriptor* desc);
CGPU_API void cgpu_queue_present(CGPUQueueId _this, const CGPUQueuePresentDescriptor* desc);
CGPU_API void cgpu_queue_wait_idle(CGPUQueueId _this);
CGPU_API float cgpu_queue_get_timestamp_period_ns(CGPUQueueId _this);
CGPU_API void cgpu_queue_map_tiled_texture(CGPUQueueId _this, const CGPUTiledTextureRegions* desc);
CGPU_API void cgpu_queue_unmap_tiled_texture(CGPUQueueId _this, const CGPUTiledTextureRegions* desc);
CGPU_API void cgpu_queue_map_packed_mips(CGPUQueueId _this, const CGPUTiledTexturePackedMips* desc);
CGPU_API void cgpu_queue_unmap_packed_mips(CGPUQueueId _this, const CGPUTiledTexturePackedMips* desc);
CGPU_API CGPUCommandPoolId cgpu_queue_create_command_pool(CGPUQueueId _this, const CGPUCommandPoolDescriptor* desc);
CGPU_API void cgpu_queue_free_command_pool(CGPUQueueId _this, CGPUCommandPoolId pool);
CGPU_API void cgpu_descriptor_set_update(CGPUDescriptorSetId _this, uint32_t data_count, const CGPUDescriptorData* p_datas);
CGPU_API CGPUCommandBufferId cgpu_command_pool_create_command_buffer(CGPUCommandPoolId _this, const CGPUCommandBufferDescriptor* desc);
CGPU_API void cgpu_command_pool_reset(CGPUCommandPoolId _this);
CGPU_API void cgpu_command_pool_free_command_buffer(CGPUCommandPoolId _this, CGPUCommandBufferId cmd);
CGPU_API void cgpu_buffer_map(CGPUBufferId _this, const CGPUBufferRange* range);
CGPU_API void cgpu_buffer_unmap(CGPUBufferId _this);
CGPU_API uint32_t cgpu_swap_chain_acquire_next_image(CGPUSwapChainId _this, const CGPUAcquireNextDescriptor* desc);
CGPU_API void cgpu_command_buffer_begin(CGPUCommandBufferId _this);
CGPU_API void cgpu_command_buffer_transfer_buffer_to_buffer(CGPUCommandBufferId _this, const CGPUBufferToBufferTransfer* desc);
CGPU_API void cgpu_command_buffer_transfer_texture_to_texture(CGPUCommandBufferId _this, const CGPUTextureToTextureTransfer* desc);
CGPU_API void cgpu_command_buffer_transfer_buffer_to_texture(CGPUCommandBufferId _this, const CGPUBufferToTextureTransfer* desc);
CGPU_API void cgpu_command_buffer_transfer_buffer_to_tiles(CGPUCommandBufferId _this, const CGPUBufferToTilesTransfer* desc);
CGPU_API void cgpu_command_buffer_resource_barrier(CGPUCommandBufferId _this, const CGPUResourceBarrierDescriptor* desc);
CGPU_API void cgpu_command_buffer_begin_query(CGPUCommandBufferId _this, CGPUQueryPoolId pool, const CGPUQueryDescriptor* desc);
CGPU_API void cgpu_command_buffer_end_query(CGPUCommandBufferId _this, CGPUQueryPoolId pool, const CGPUQueryDescriptor* desc);
CGPU_API void cgpu_command_buffer_reset_query_pool(CGPUCommandBufferId _this, CGPUQueryPoolId pool, uint32_t start_query, uint32_t query_count);
CGPU_API void cgpu_command_buffer_resolve_query(CGPUCommandBufferId _this, CGPUQueryPoolId pool, CGPUBufferId readback, uint32_t start_query, uint32_t query_count);
CGPU_API void cgpu_command_buffer_end(CGPUCommandBufferId _this);
CGPU_API CGPUComputePassEncoderId cgpu_command_buffer_begin_compute_pass(CGPUCommandBufferId _this, const CGPUComputePassDescriptor* desc);
CGPU_API void cgpu_command_buffer_end_compute_pass(CGPUCommandBufferId _this, CGPUComputePassEncoderId encoder);
CGPU_API CGPURenderPassEncoderId cgpu_command_buffer_begin_render_pass(CGPUCommandBufferId _this, const CGPUBeginRenderPassInfo* begin_info);
CGPU_API void cgpu_command_buffer_end_render_pass(CGPUCommandBufferId _this, CGPURenderPassEncoderId encoder);
CGPU_API void cgpu_command_buffer_begin_event(CGPUCommandBufferId _this, const CGPUEventInfo* event);
CGPU_API void cgpu_command_buffer_set_marker(CGPUCommandBufferId _this, const CGPUMarkerInfo* marker);
CGPU_API void cgpu_command_buffer_end_event(CGPUCommandBufferId _this);
CGPU_API CGPUStateBufferId cgpu_command_buffer_create_state_buffer(CGPUCommandBufferId _this, const CGPUStateBufferDescriptor* desc);
CGPU_API void cgpu_command_buffer_free_state_buffer(CGPUCommandBufferId _this, CGPUStateBufferId stream);
CGPU_API CGPUBinderId cgpu_command_buffer_create_binder(CGPUCommandBufferId _this);
CGPU_API void cgpu_command_buffer_free_binder(CGPUCommandBufferId _this, CGPUBinderId binder);
CGPU_API void cgpu_compute_pass_encoder_bind_descriptor_set(CGPUComputePassEncoderId _this, CGPUDescriptorSetId set);
CGPU_API void cgpu_compute_pass_encoder_bind_compute_pipeline(CGPUComputePassEncoderId _this, CGPUComputePipelineId pipeline);
CGPU_API void cgpu_compute_pass_encoder_dispatch(CGPUComputePassEncoderId _this, uint32_t x, uint32_t y, uint32_t z);
CGPU_API void cgpu_compute_pass_encoder_push_constants(CGPUComputePassEncoderId _this, CGPURootSignatureId rs, const char* name, const void* data);
CGPU_API void cgpu_compute_pass_encoder_bind_state_buffer(CGPUComputePassEncoderId _this, CGPUStateBufferId stream);
CGPU_API void cgpu_render_pass_encoder_set_shading_rate(CGPURenderPassEncoderId _this, ECGPUShadingRate shading_rate, ECGPUShadingRateCombiner post_rasterize_rate, ECGPUShadingRateCombiner final_rate);
CGPU_API void cgpu_render_pass_encoder_bind_descriptor_set(CGPURenderPassEncoderId _this, CGPUDescriptorSetId set);
CGPU_API void cgpu_render_pass_encoder_set_viewport(CGPURenderPassEncoderId _this, float x, float y, float width, float height, float min_depth, float max_depth);
CGPU_API void cgpu_render_pass_encoder_set_scissor(CGPURenderPassEncoderId _this, uint32_t x, uint32_t y, uint32_t width, uint32_t height);
CGPU_API void cgpu_render_pass_encoder_bind_render_pipeline(CGPURenderPassEncoderId _this, CGPURenderPipelineId pipeline);
CGPU_API void cgpu_render_pass_encoder_bind_vertex_buffers(CGPURenderPassEncoderId _this, uint32_t buffer_count, const CGPUBufferId* p_buffers, const uint32_t* p_strides, const uint32_t* p_offsets);
CGPU_API void cgpu_render_pass_encoder_bind_index_buffer(CGPURenderPassEncoderId _this, CGPUBufferId buffer, uint32_t index_stride, uint64_t offset);
CGPU_API void cgpu_render_pass_encoder_push_constants(CGPURenderPassEncoderId _this, CGPURootSignatureId rs, const char* name, const void* data);
CGPU_API void cgpu_render_pass_encoder_draw(CGPURenderPassEncoderId _this, uint32_t vertex_count, uint32_t first_vertex);
CGPU_API void cgpu_render_pass_encoder_draw_instanced(CGPURenderPassEncoderId _this, uint32_t vertex_count, uint32_t first_vertex, uint32_t instance_count, uint32_t first_instance);
CGPU_API void cgpu_render_pass_encoder_draw_indexed(CGPURenderPassEncoderId _this, uint32_t index_count, uint32_t first_index, uint32_t first_vertex);
CGPU_API void cgpu_render_pass_encoder_draw_indexed_instanced(CGPURenderPassEncoderId _this, uint32_t index_count, uint32_t first_index, uint32_t instance_count, uint32_t first_instance, uint32_t first_vertex);
CGPU_API void cgpu_render_pass_encoder_bind_state_buffer(CGPURenderPassEncoderId _this, CGPUStateBufferId stream);
CGPU_API CGPULinkedShaderId cgpu_root_signature_compile_and_link_shaders(CGPURootSignatureId _this, uint32_t count, const CGPUCompiledShaderDescriptor* desc);
CGPU_API void cgpu_root_signature_compile_shaders(CGPURootSignatureId _this, uint32_t count, const CGPUCompiledShaderDescriptor* desc, CGPUCompiledShaderId* out_isas);
CGPU_API void cgpu_root_signature_free_compiled_shader(CGPURootSignatureId _this, CGPUCompiledShaderId shader);
CGPU_API void cgpu_root_signature_free_linked_shader(CGPURootSignatureId _this, CGPULinkedShaderId shader);
CGPU_API CGPURasterStateEncoderId cgpu_state_buffer_open_raster_state_encoder(CGPUStateBufferId _this, CGPURenderPassEncoderId encoder);
CGPU_API void cgpu_state_buffer_close_raster_state_encoder(CGPUStateBufferId _this, CGPURasterStateEncoderId encoder);
CGPU_API CGPUShaderStateEncoderId cgpu_state_buffer_open_shader_state_encoder_r(CGPUStateBufferId _this, CGPURenderPassEncoderId encoder);
CGPU_API CGPUShaderStateEncoderId cgpu_state_buffer_open_shader_state_encoder_c(CGPUStateBufferId _this, CGPUComputePassEncoderId encoder);
CGPU_API void cgpu_state_buffer_close_shader_state_encoder(CGPUStateBufferId _this, CGPUShaderStateEncoderId encoder);
CGPU_API CGPUUserStateEncoderId cgpu_state_buffer_open_user_state_encoder(CGPUStateBufferId _this, CGPURenderPassEncoderId encoder);
CGPU_API void cgpu_state_buffer_close_user_state_encoder(CGPUStateBufferId _this, CGPUUserStateEncoderId encoder);
CGPU_API void cgpu_raster_state_encoder_set_viewport(CGPURasterStateEncoderId _this, float x, float y, float width, float height, float min_depth, float max_depth);
CGPU_API void cgpu_raster_state_encoder_set_scissor(CGPURasterStateEncoderId _this, uint32_t x, uint32_t y, uint32_t width, uint32_t height);
CGPU_API void cgpu_raster_state_encoder_set_cull_mode(CGPURasterStateEncoderId _this, ECGPUCullModeFlags cull_mode);
CGPU_API void cgpu_raster_state_encoder_set_front_face(CGPURasterStateEncoderId _this, ECGPUFrontFace front_face);
CGPU_API void cgpu_raster_state_encoder_set_primitive_topology(CGPURasterStateEncoderId _this, ECGPUPrimitiveTopology topology);
CGPU_API void cgpu_raster_state_encoder_set_depth_test_enabled(CGPURasterStateEncoderId _this, bool enabled);
CGPU_API void cgpu_raster_state_encoder_set_depth_write_enabled(CGPURasterStateEncoderId _this, bool enabled);
CGPU_API void cgpu_raster_state_encoder_set_depth_compare_op(CGPURasterStateEncoderId _this, ECGPUCompareOp compare_op);
CGPU_API void cgpu_raster_state_encoder_set_stencil_test_enabled(CGPURasterStateEncoderId _this, bool enabled);
CGPU_API void cgpu_raster_state_encoder_set_stencil_compare_op(CGPURasterStateEncoderId _this, ECGPUStencilFaceFlags faces, ECGPUStencilOp fail_op, ECGPUStencilOp pass_op, ECGPUStencilOp depth_fail_op, ECGPUCompareOp compare_op);
CGPU_API void cgpu_raster_state_encoder_set_fill_mode(CGPURasterStateEncoderId _this, ECGPUFillMode fill_mode);
CGPU_API void cgpu_raster_state_encoder_set_sample_count(CGPURasterStateEncoderId _this, ECGPUSampleCountFlags sample_count);
CGPU_API void cgpu_shader_state_encoder_bind_shaders(CGPUShaderStateEncoderId _this, uint32_t stage_count, const ECGPUShaderStageFlags* p_stages, const CGPUCompiledShaderId* shaders);
CGPU_API void cgpu_shader_state_encoder_bind_linked_shader(CGPUShaderStateEncoderId _this, CGPULinkedShaderId linked);
CGPU_API void cgpu_binder_bind_vertex_layout(CGPUBinderId _this, const CGPUVertexLayout* layout);
CGPU_API void cgpu_binder_bind_vertex_buffer(CGPUBinderId _this, uint32_t first_binding, uint32_t binding_count, const CGPUBufferId* p_buffers, const uint64_t* p_offsets, const uint64_t* p_sizes, const uint64_t* p_strides);

static CGPU_FORCEINLINE bool FormatUtil_IsDepthStencilFormat(ECGPUTextureFormat const arg) {
    switch(arg) {
        case CGPU_TEXTURE_FORMAT_D24_UNORM_S8_UINT: return true;
        case CGPU_TEXTURE_FORMAT_D32_SFLOAT_S8_UINT: return true;
        case CGPU_TEXTURE_FORMAT_D32_SFLOAT: return true;
        case CGPU_TEXTURE_FORMAT_X8_D24_UNORM_PACK32: return true;
        case CGPU_TEXTURE_FORMAT_D16_UNORM: return true;
        case CGPU_TEXTURE_FORMAT_D16_UNORM_S8_UINT: return true;
        default: return false;
    }
    return false;
}

static CGPU_FORCEINLINE bool FormatUtil_IsDepthOnlyFormat(ECGPUTextureFormat const arg) {
    switch(arg) {
        case CGPU_TEXTURE_FORMAT_D32_SFLOAT: return true;
        case CGPU_TEXTURE_FORMAT_D16_UNORM: return true;
        default: return false;
    }
    return false;
}

static CGPU_FORCEINLINE uint32_t FormatUtil_BitSizeOfBlock(ECGPUTextureFormat const arg) {
    switch(arg) {
        case CGPU_TEXTURE_FORMAT_UNDEFINED: return 0;
        case CGPU_TEXTURE_FORMAT_R8_UNORM: return 8;
        case CGPU_TEXTURE_FORMAT_R8_SNORM: return 8;
        case CGPU_TEXTURE_FORMAT_R8_UINT: return 8;
        case CGPU_TEXTURE_FORMAT_R8_SINT: return 8;
        case CGPU_TEXTURE_FORMAT_R8_SRGB: return 8;
        case CGPU_TEXTURE_FORMAT_R8G8_UNORM: return 16;
        case CGPU_TEXTURE_FORMAT_R8G8_SNORM: return 16;
        case CGPU_TEXTURE_FORMAT_R8G8_UINT: return 16;
        case CGPU_TEXTURE_FORMAT_R8G8_SINT: return 16;
        case CGPU_TEXTURE_FORMAT_R8G8_SRGB: return 16;
        case CGPU_TEXTURE_FORMAT_R16_UNORM: return 16;
        case CGPU_TEXTURE_FORMAT_R16_SNORM: return 16;
        case CGPU_TEXTURE_FORMAT_R16_UINT: return 16;
        case CGPU_TEXTURE_FORMAT_R16_SINT: return 16;
        case CGPU_TEXTURE_FORMAT_R16_SFLOAT: return 16;
        case CGPU_TEXTURE_FORMAT_R8G8B8_UNORM: return 24;
        case CGPU_TEXTURE_FORMAT_R8G8B8_SNORM: return 24;
        case CGPU_TEXTURE_FORMAT_R8G8B8_UINT: return 24;
        case CGPU_TEXTURE_FORMAT_R8G8B8_SINT: return 24;
        case CGPU_TEXTURE_FORMAT_R8G8B8_SRGB: return 24;
        case CGPU_TEXTURE_FORMAT_B8G8R8_UNORM: return 24;
        case CGPU_TEXTURE_FORMAT_B8G8R8_SNORM: return 24;
        case CGPU_TEXTURE_FORMAT_B8G8R8_UINT: return 24;
        case CGPU_TEXTURE_FORMAT_B8G8R8_SINT: return 24;
        case CGPU_TEXTURE_FORMAT_B8G8R8_SRGB: return 24;
        case CGPU_TEXTURE_FORMAT_R16G16B16_UNORM: return 48;
        case CGPU_TEXTURE_FORMAT_R16G16B16_SNORM: return 48;
        case CGPU_TEXTURE_FORMAT_R16G16B16_UINT: return 48;
        case CGPU_TEXTURE_FORMAT_R16G16B16_SINT: return 48;
        case CGPU_TEXTURE_FORMAT_R16G16B16_SFLOAT: return 48;
        case CGPU_TEXTURE_FORMAT_R16G16B16A16_UNORM: return 64;
        case CGPU_TEXTURE_FORMAT_R16G16B16A16_SNORM: return 64;
        case CGPU_TEXTURE_FORMAT_R16G16B16A16_UINT: return 64;
        case CGPU_TEXTURE_FORMAT_R16G16B16A16_SINT: return 64;
        case CGPU_TEXTURE_FORMAT_R16G16B16A16_SFLOAT: return 64;
        case CGPU_TEXTURE_FORMAT_R32G32_UINT: return 64;
        case CGPU_TEXTURE_FORMAT_R32G32_SINT: return 64;
        case CGPU_TEXTURE_FORMAT_R32G32_SFLOAT: return 64;
        case CGPU_TEXTURE_FORMAT_R32G32B32_UINT: return 96;
        case CGPU_TEXTURE_FORMAT_R32G32B32_SINT: return 96;
        case CGPU_TEXTURE_FORMAT_R32G32B32_SFLOAT: return 96;
        case CGPU_TEXTURE_FORMAT_R32G32B32A32_UINT: return 128;
        case CGPU_TEXTURE_FORMAT_R32G32B32A32_SINT: return 128;
        case CGPU_TEXTURE_FORMAT_R32G32B32A32_SFLOAT: return 128;
        case CGPU_TEXTURE_FORMAT_R64_UINT: return 64;
        case CGPU_TEXTURE_FORMAT_R64_SINT: return 64;
        case CGPU_TEXTURE_FORMAT_R64_SFLOAT: return 64;
        case CGPU_TEXTURE_FORMAT_R64G64_UINT: return 128;
        case CGPU_TEXTURE_FORMAT_R64G64_SINT: return 128;
        case CGPU_TEXTURE_FORMAT_R64G64_SFLOAT: return 128;
        case CGPU_TEXTURE_FORMAT_R64G64B64_UINT: return 192;
        case CGPU_TEXTURE_FORMAT_R64G64B64_SINT: return 192;
        case CGPU_TEXTURE_FORMAT_R64G64B64_SFLOAT: return 192;
        case CGPU_TEXTURE_FORMAT_R64G64B64A64_UINT: return 256;
        case CGPU_TEXTURE_FORMAT_R64G64B64A64_SINT: return 256;
        case CGPU_TEXTURE_FORMAT_R64G64B64A64_SFLOAT: return 256;
        case CGPU_TEXTURE_FORMAT_D16_UNORM: return 16;
        case CGPU_TEXTURE_FORMAT_S8_UINT: return 8;
        case CGPU_TEXTURE_FORMAT_D32_SFLOAT_S8_UINT: return 64;
        case CGPU_TEXTURE_FORMAT_BC1_RGB_UNORM_BLOCK: return 64;
        case CGPU_TEXTURE_FORMAT_BC1_RGB_SRGB_BLOCK: return 64;
        case CGPU_TEXTURE_FORMAT_BC1_RGBA_UNORM_BLOCK: return 64;
        case CGPU_TEXTURE_FORMAT_BC1_RGBA_SRGB_BLOCK: return 64;
        case CGPU_TEXTURE_FORMAT_BC2_UNORM_BLOCK: return 128;
        case CGPU_TEXTURE_FORMAT_BC2_SRGB_BLOCK: return 128;
        case CGPU_TEXTURE_FORMAT_BC3_UNORM_BLOCK: return 128;
        case CGPU_TEXTURE_FORMAT_BC3_SRGB_BLOCK: return 128;
        case CGPU_TEXTURE_FORMAT_BC4_UNORM_BLOCK: return 64;
        case CGPU_TEXTURE_FORMAT_BC4_SNORM_BLOCK: return 64;
        case CGPU_TEXTURE_FORMAT_BC5_UNORM_BLOCK: return 128;
        case CGPU_TEXTURE_FORMAT_BC5_SNORM_BLOCK: return 128;
        case CGPU_TEXTURE_FORMAT_BC6H_UFLOAT_BLOCK: return 128;
        case CGPU_TEXTURE_FORMAT_BC6H_SFLOAT_BLOCK: return 128;
        case CGPU_TEXTURE_FORMAT_BC7_UNORM_BLOCK: return 128;
        case CGPU_TEXTURE_FORMAT_BC7_SRGB_BLOCK: return 128;
        case CGPU_TEXTURE_FORMAT_PVRTC1_2BPP_UNORM_BLOCK: return 64;
        case CGPU_TEXTURE_FORMAT_PVRTC1_4BPP_UNORM_BLOCK: return 64;
        case CGPU_TEXTURE_FORMAT_PVRTC2_2BPP_UNORM_BLOCK: return 64;
        case CGPU_TEXTURE_FORMAT_PVRTC2_4BPP_UNORM_BLOCK: return 64;
        case CGPU_TEXTURE_FORMAT_PVRTC1_2BPP_SRGB_BLOCK: return 64;
        case CGPU_TEXTURE_FORMAT_PVRTC1_4BPP_SRGB_BLOCK: return 64;
        case CGPU_TEXTURE_FORMAT_PVRTC2_2BPP_SRGB_BLOCK: return 64;
        case CGPU_TEXTURE_FORMAT_PVRTC2_4BPP_SRGB_BLOCK: return 64;
        case CGPU_TEXTURE_FORMAT_ETC2_R8G8B8_UNORM_BLOCK: return 64;
        case CGPU_TEXTURE_FORMAT_ETC2_R8G8B8_SRGB_BLOCK: return 64;
        case CGPU_TEXTURE_FORMAT_ETC2_R8G8B8A1_UNORM_BLOCK: return 64;
        case CGPU_TEXTURE_FORMAT_ETC2_R8G8B8A1_SRGB_BLOCK: return 64;
        case CGPU_TEXTURE_FORMAT_ETC2_R8G8B8A8_UNORM_BLOCK: return 64;
        case CGPU_TEXTURE_FORMAT_ETC2_R8G8B8A8_SRGB_BLOCK: return 64;
        case CGPU_TEXTURE_FORMAT_EAC_R11_UNORM_BLOCK: return 64;
        case CGPU_TEXTURE_FORMAT_EAC_R11_SNORM_BLOCK: return 64;
        case CGPU_TEXTURE_FORMAT_EAC_R11G11_UNORM_BLOCK: return 64;
        case CGPU_TEXTURE_FORMAT_EAC_R11G11_SNORM_BLOCK: return 64;
        case CGPU_TEXTURE_FORMAT_ASTC_4X4_UNORM_BLOCK: return 128;
        case CGPU_TEXTURE_FORMAT_ASTC_4X4_SRGB_BLOCK: return 128;
        case CGPU_TEXTURE_FORMAT_ASTC_5X4_UNORM_BLOCK: return 128;
        case CGPU_TEXTURE_FORMAT_ASTC_5X4_SRGB_BLOCK: return 128;
        case CGPU_TEXTURE_FORMAT_ASTC_5X5_UNORM_BLOCK: return 128;
        case CGPU_TEXTURE_FORMAT_ASTC_5X5_SRGB_BLOCK: return 128;
        case CGPU_TEXTURE_FORMAT_ASTC_6X5_UNORM_BLOCK: return 128;
        case CGPU_TEXTURE_FORMAT_ASTC_6X5_SRGB_BLOCK: return 128;
        case CGPU_TEXTURE_FORMAT_ASTC_6X6_UNORM_BLOCK: return 128;
        case CGPU_TEXTURE_FORMAT_ASTC_6X6_SRGB_BLOCK: return 128;
        case CGPU_TEXTURE_FORMAT_ASTC_8X5_UNORM_BLOCK: return 128;
        case CGPU_TEXTURE_FORMAT_ASTC_8X5_SRGB_BLOCK: return 128;
        case CGPU_TEXTURE_FORMAT_ASTC_8X6_UNORM_BLOCK: return 128;
        case CGPU_TEXTURE_FORMAT_ASTC_8X6_SRGB_BLOCK: return 128;
        case CGPU_TEXTURE_FORMAT_ASTC_8X8_UNORM_BLOCK: return 128;
        case CGPU_TEXTURE_FORMAT_ASTC_8X8_SRGB_BLOCK: return 128;
        case CGPU_TEXTURE_FORMAT_ASTC_10X5_UNORM_BLOCK: return 128;
        case CGPU_TEXTURE_FORMAT_ASTC_10X5_SRGB_BLOCK: return 128;
        case CGPU_TEXTURE_FORMAT_ASTC_10X6_UNORM_BLOCK: return 128;
        case CGPU_TEXTURE_FORMAT_ASTC_10X6_SRGB_BLOCK: return 128;
        case CGPU_TEXTURE_FORMAT_ASTC_10X8_UNORM_BLOCK: return 128;
        case CGPU_TEXTURE_FORMAT_ASTC_10X8_SRGB_BLOCK: return 128;
        case CGPU_TEXTURE_FORMAT_ASTC_10X10_UNORM_BLOCK: return 128;
        case CGPU_TEXTURE_FORMAT_ASTC_10X10_SRGB_BLOCK: return 128;
        case CGPU_TEXTURE_FORMAT_ASTC_12X10_UNORM_BLOCK: return 128;
        case CGPU_TEXTURE_FORMAT_ASTC_12X10_SRGB_BLOCK: return 128;
        case CGPU_TEXTURE_FORMAT_ASTC_12X12_UNORM_BLOCK: return 128;
        case CGPU_TEXTURE_FORMAT_ASTC_12X12_SRGB_BLOCK: return 128;
        case CGPU_TEXTURE_FORMAT_ASTC_4X4_SFLOAT_BLOCK: return 128;
        case CGPU_TEXTURE_FORMAT_ASTC_5X4_SFLOAT_BLOCK: return 128;
        case CGPU_TEXTURE_FORMAT_ASTC_5X5_SFLOAT_BLOCK: return 128;
        case CGPU_TEXTURE_FORMAT_ASTC_6X5_SFLOAT_BLOCK: return 128;
        case CGPU_TEXTURE_FORMAT_ASTC_6X6_SFLOAT_BLOCK: return 128;
        case CGPU_TEXTURE_FORMAT_ASTC_8X5_SFLOAT_BLOCK: return 128;
        case CGPU_TEXTURE_FORMAT_ASTC_8X6_SFLOAT_BLOCK: return 128;
        case CGPU_TEXTURE_FORMAT_ASTC_8X8_SFLOAT_BLOCK: return 128;
        case CGPU_TEXTURE_FORMAT_ASTC_10X5_SFLOAT_BLOCK: return 128;
        case CGPU_TEXTURE_FORMAT_ASTC_10X6_SFLOAT_BLOCK: return 128;
        case CGPU_TEXTURE_FORMAT_ASTC_10X8_SFLOAT_BLOCK: return 128;
        case CGPU_TEXTURE_FORMAT_ASTC_10X10_SFLOAT_BLOCK: return 128;
        case CGPU_TEXTURE_FORMAT_ASTC_12X10_SFLOAT_BLOCK: return 128;
        case CGPU_TEXTURE_FORMAT_ASTC_12X12_SFLOAT_BLOCK: return 128;
        default: return 32;
    }
    return 32;
}

static CGPU_FORCEINLINE uint32_t FormatUtil_WidthOfBlock(ECGPUTextureFormat const arg) {
    switch(arg) {
        case CGPU_TEXTURE_FORMAT_UNDEFINED: return 1;
        case CGPU_TEXTURE_FORMAT_BC1_RGB_UNORM_BLOCK: return 4;
        case CGPU_TEXTURE_FORMAT_BC1_RGB_SRGB_BLOCK: return 4;
        case CGPU_TEXTURE_FORMAT_BC1_RGBA_UNORM_BLOCK: return 4;
        case CGPU_TEXTURE_FORMAT_BC1_RGBA_SRGB_BLOCK: return 4;
        case CGPU_TEXTURE_FORMAT_BC2_UNORM_BLOCK: return 4;
        case CGPU_TEXTURE_FORMAT_BC2_SRGB_BLOCK: return 4;
        case CGPU_TEXTURE_FORMAT_BC3_UNORM_BLOCK: return 4;
        case CGPU_TEXTURE_FORMAT_BC3_SRGB_BLOCK: return 4;
        case CGPU_TEXTURE_FORMAT_BC4_UNORM_BLOCK: return 4;
        case CGPU_TEXTURE_FORMAT_BC4_SNORM_BLOCK: return 4;
        case CGPU_TEXTURE_FORMAT_BC5_UNORM_BLOCK: return 4;
        case CGPU_TEXTURE_FORMAT_BC5_SNORM_BLOCK: return 4;
        case CGPU_TEXTURE_FORMAT_BC6H_UFLOAT_BLOCK: return 4;
        case CGPU_TEXTURE_FORMAT_BC6H_SFLOAT_BLOCK: return 4;
        case CGPU_TEXTURE_FORMAT_BC7_UNORM_BLOCK: return 4;
        case CGPU_TEXTURE_FORMAT_BC7_SRGB_BLOCK: return 4;
        case CGPU_TEXTURE_FORMAT_PVRTC1_2BPP_UNORM_BLOCK: return 8;
        case CGPU_TEXTURE_FORMAT_PVRTC1_4BPP_UNORM_BLOCK: return 4;
        case CGPU_TEXTURE_FORMAT_PVRTC2_2BPP_UNORM_BLOCK: return 8;
        case CGPU_TEXTURE_FORMAT_PVRTC2_4BPP_UNORM_BLOCK: return 4;
        case CGPU_TEXTURE_FORMAT_PVRTC1_2BPP_SRGB_BLOCK: return 8;
        case CGPU_TEXTURE_FORMAT_PVRTC1_4BPP_SRGB_BLOCK: return 4;
        case CGPU_TEXTURE_FORMAT_PVRTC2_2BPP_SRGB_BLOCK: return 8;
        case CGPU_TEXTURE_FORMAT_PVRTC2_4BPP_SRGB_BLOCK: return 4;
        case CGPU_TEXTURE_FORMAT_ETC2_R8G8B8_UNORM_BLOCK: return 4;
        case CGPU_TEXTURE_FORMAT_ETC2_R8G8B8_SRGB_BLOCK: return 4;
        case CGPU_TEXTURE_FORMAT_ETC2_R8G8B8A1_UNORM_BLOCK: return 4;
        case CGPU_TEXTURE_FORMAT_ETC2_R8G8B8A1_SRGB_BLOCK: return 4;
        case CGPU_TEXTURE_FORMAT_ETC2_R8G8B8A8_UNORM_BLOCK: return 4;
        case CGPU_TEXTURE_FORMAT_ETC2_R8G8B8A8_SRGB_BLOCK: return 4;
        case CGPU_TEXTURE_FORMAT_EAC_R11_UNORM_BLOCK: return 4;
        case CGPU_TEXTURE_FORMAT_EAC_R11_SNORM_BLOCK: return 4;
        case CGPU_TEXTURE_FORMAT_EAC_R11G11_UNORM_BLOCK: return 4;
        case CGPU_TEXTURE_FORMAT_EAC_R11G11_SNORM_BLOCK: return 4;
        case CGPU_TEXTURE_FORMAT_ASTC_4X4_UNORM_BLOCK: return 4;
        case CGPU_TEXTURE_FORMAT_ASTC_4X4_SRGB_BLOCK: return 4;
        case CGPU_TEXTURE_FORMAT_ASTC_5X4_UNORM_BLOCK: return 5;
        case CGPU_TEXTURE_FORMAT_ASTC_5X4_SRGB_BLOCK: return 5;
        case CGPU_TEXTURE_FORMAT_ASTC_5X5_UNORM_BLOCK: return 5;
        case CGPU_TEXTURE_FORMAT_ASTC_5X5_SRGB_BLOCK: return 5;
        case CGPU_TEXTURE_FORMAT_ASTC_6X5_UNORM_BLOCK: return 6;
        case CGPU_TEXTURE_FORMAT_ASTC_6X5_SRGB_BLOCK: return 6;
        case CGPU_TEXTURE_FORMAT_ASTC_6X6_UNORM_BLOCK: return 6;
        case CGPU_TEXTURE_FORMAT_ASTC_6X6_SRGB_BLOCK: return 6;
        case CGPU_TEXTURE_FORMAT_ASTC_8X5_UNORM_BLOCK: return 8;
        case CGPU_TEXTURE_FORMAT_ASTC_8X5_SRGB_BLOCK: return 8;
        case CGPU_TEXTURE_FORMAT_ASTC_8X6_UNORM_BLOCK: return 8;
        case CGPU_TEXTURE_FORMAT_ASTC_8X6_SRGB_BLOCK: return 8;
        case CGPU_TEXTURE_FORMAT_ASTC_8X8_UNORM_BLOCK: return 8;
        case CGPU_TEXTURE_FORMAT_ASTC_8X8_SRGB_BLOCK: return 8;
        case CGPU_TEXTURE_FORMAT_ASTC_10X5_UNORM_BLOCK: return 10;
        case CGPU_TEXTURE_FORMAT_ASTC_10X5_SRGB_BLOCK: return 10;
        case CGPU_TEXTURE_FORMAT_ASTC_10X6_UNORM_BLOCK: return 10;
        case CGPU_TEXTURE_FORMAT_ASTC_10X6_SRGB_BLOCK: return 10;
        case CGPU_TEXTURE_FORMAT_ASTC_10X8_UNORM_BLOCK: return 10;
        case CGPU_TEXTURE_FORMAT_ASTC_10X8_SRGB_BLOCK: return 10;
        case CGPU_TEXTURE_FORMAT_ASTC_10X10_UNORM_BLOCK: return 10;
        case CGPU_TEXTURE_FORMAT_ASTC_10X10_SRGB_BLOCK: return 10;
        case CGPU_TEXTURE_FORMAT_ASTC_12X10_UNORM_BLOCK: return 12;
        case CGPU_TEXTURE_FORMAT_ASTC_12X10_SRGB_BLOCK: return 12;
        case CGPU_TEXTURE_FORMAT_ASTC_12X12_UNORM_BLOCK: return 12;
        case CGPU_TEXTURE_FORMAT_ASTC_12X12_SRGB_BLOCK: return 12;
        case CGPU_TEXTURE_FORMAT_ASTC_4X4_SFLOAT_BLOCK: return 4;
        case CGPU_TEXTURE_FORMAT_ASTC_5X4_SFLOAT_BLOCK: return 5;
        case CGPU_TEXTURE_FORMAT_ASTC_5X5_SFLOAT_BLOCK: return 5;
        case CGPU_TEXTURE_FORMAT_ASTC_6X5_SFLOAT_BLOCK: return 6;
        case CGPU_TEXTURE_FORMAT_ASTC_6X6_SFLOAT_BLOCK: return 6;
        case CGPU_TEXTURE_FORMAT_ASTC_8X5_SFLOAT_BLOCK: return 8;
        case CGPU_TEXTURE_FORMAT_ASTC_8X6_SFLOAT_BLOCK: return 8;
        case CGPU_TEXTURE_FORMAT_ASTC_8X8_SFLOAT_BLOCK: return 8;
        case CGPU_TEXTURE_FORMAT_ASTC_10X5_SFLOAT_BLOCK: return 10;
        case CGPU_TEXTURE_FORMAT_ASTC_10X6_SFLOAT_BLOCK: return 10;
        case CGPU_TEXTURE_FORMAT_ASTC_10X8_SFLOAT_BLOCK: return 10;
        case CGPU_TEXTURE_FORMAT_ASTC_10X10_SFLOAT_BLOCK: return 10;
        case CGPU_TEXTURE_FORMAT_ASTC_12X10_SFLOAT_BLOCK: return 12;
        case CGPU_TEXTURE_FORMAT_ASTC_12X12_SFLOAT_BLOCK: return 12;
        default: return 1;
    }
    return 1;
}

static CGPU_FORCEINLINE uint32_t FormatUtil_HeightOfBlock(ECGPUTextureFormat const arg) {
    switch(arg) {
        case CGPU_TEXTURE_FORMAT_UNDEFINED: return 1;
        case CGPU_TEXTURE_FORMAT_BC1_RGB_UNORM_BLOCK: return 4;
        case CGPU_TEXTURE_FORMAT_BC1_RGB_SRGB_BLOCK: return 4;
        case CGPU_TEXTURE_FORMAT_BC1_RGBA_UNORM_BLOCK: return 4;
        case CGPU_TEXTURE_FORMAT_BC1_RGBA_SRGB_BLOCK: return 4;
        case CGPU_TEXTURE_FORMAT_BC2_UNORM_BLOCK: return 4;
        case CGPU_TEXTURE_FORMAT_BC2_SRGB_BLOCK: return 4;
        case CGPU_TEXTURE_FORMAT_BC3_UNORM_BLOCK: return 4;
        case CGPU_TEXTURE_FORMAT_BC3_SRGB_BLOCK: return 4;
        case CGPU_TEXTURE_FORMAT_BC4_UNORM_BLOCK: return 4;
        case CGPU_TEXTURE_FORMAT_BC4_SNORM_BLOCK: return 4;
        case CGPU_TEXTURE_FORMAT_BC5_UNORM_BLOCK: return 4;
        case CGPU_TEXTURE_FORMAT_BC5_SNORM_BLOCK: return 4;
        case CGPU_TEXTURE_FORMAT_BC6H_UFLOAT_BLOCK: return 4;
        case CGPU_TEXTURE_FORMAT_BC6H_SFLOAT_BLOCK: return 4;
        case CGPU_TEXTURE_FORMAT_BC7_UNORM_BLOCK: return 4;
        case CGPU_TEXTURE_FORMAT_BC7_SRGB_BLOCK: return 4;
        case CGPU_TEXTURE_FORMAT_PVRTC1_2BPP_UNORM_BLOCK: return 4;
        case CGPU_TEXTURE_FORMAT_PVRTC1_4BPP_UNORM_BLOCK: return 4;
        case CGPU_TEXTURE_FORMAT_PVRTC2_2BPP_UNORM_BLOCK: return 4;
        case CGPU_TEXTURE_FORMAT_PVRTC2_4BPP_UNORM_BLOCK: return 4;
        case CGPU_TEXTURE_FORMAT_PVRTC1_2BPP_SRGB_BLOCK: return 4;
        case CGPU_TEXTURE_FORMAT_PVRTC1_4BPP_SRGB_BLOCK: return 4;
        case CGPU_TEXTURE_FORMAT_PVRTC2_2BPP_SRGB_BLOCK: return 4;
        case CGPU_TEXTURE_FORMAT_PVRTC2_4BPP_SRGB_BLOCK: return 4;
        case CGPU_TEXTURE_FORMAT_ETC2_R8G8B8_UNORM_BLOCK: return 4;
        case CGPU_TEXTURE_FORMAT_ETC2_R8G8B8_SRGB_BLOCK: return 4;
        case CGPU_TEXTURE_FORMAT_ETC2_R8G8B8A1_UNORM_BLOCK: return 4;
        case CGPU_TEXTURE_FORMAT_ETC2_R8G8B8A1_SRGB_BLOCK: return 4;
        case CGPU_TEXTURE_FORMAT_ETC2_R8G8B8A8_UNORM_BLOCK: return 4;
        case CGPU_TEXTURE_FORMAT_ETC2_R8G8B8A8_SRGB_BLOCK: return 4;
        case CGPU_TEXTURE_FORMAT_EAC_R11_UNORM_BLOCK: return 4;
        case CGPU_TEXTURE_FORMAT_EAC_R11_SNORM_BLOCK: return 4;
        case CGPU_TEXTURE_FORMAT_EAC_R11G11_UNORM_BLOCK: return 4;
        case CGPU_TEXTURE_FORMAT_EAC_R11G11_SNORM_BLOCK: return 4;
        case CGPU_TEXTURE_FORMAT_ASTC_4X4_UNORM_BLOCK: return 4;
        case CGPU_TEXTURE_FORMAT_ASTC_4X4_SRGB_BLOCK: return 4;
        case CGPU_TEXTURE_FORMAT_ASTC_5X4_UNORM_BLOCK: return 4;
        case CGPU_TEXTURE_FORMAT_ASTC_5X4_SRGB_BLOCK: return 4;
        case CGPU_TEXTURE_FORMAT_ASTC_5X5_UNORM_BLOCK: return 5;
        case CGPU_TEXTURE_FORMAT_ASTC_5X5_SRGB_BLOCK: return 5;
        case CGPU_TEXTURE_FORMAT_ASTC_6X5_UNORM_BLOCK: return 5;
        case CGPU_TEXTURE_FORMAT_ASTC_6X5_SRGB_BLOCK: return 5;
        case CGPU_TEXTURE_FORMAT_ASTC_6X6_UNORM_BLOCK: return 6;
        case CGPU_TEXTURE_FORMAT_ASTC_6X6_SRGB_BLOCK: return 6;
        case CGPU_TEXTURE_FORMAT_ASTC_8X5_UNORM_BLOCK: return 5;
        case CGPU_TEXTURE_FORMAT_ASTC_8X5_SRGB_BLOCK: return 5;
        case CGPU_TEXTURE_FORMAT_ASTC_8X6_UNORM_BLOCK: return 6;
        case CGPU_TEXTURE_FORMAT_ASTC_8X6_SRGB_BLOCK: return 6;
        case CGPU_TEXTURE_FORMAT_ASTC_8X8_UNORM_BLOCK: return 8;
        case CGPU_TEXTURE_FORMAT_ASTC_8X8_SRGB_BLOCK: return 8;
        case CGPU_TEXTURE_FORMAT_ASTC_10X5_UNORM_BLOCK: return 5;
        case CGPU_TEXTURE_FORMAT_ASTC_10X5_SRGB_BLOCK: return 5;
        case CGPU_TEXTURE_FORMAT_ASTC_10X6_UNORM_BLOCK: return 6;
        case CGPU_TEXTURE_FORMAT_ASTC_10X6_SRGB_BLOCK: return 6;
        case CGPU_TEXTURE_FORMAT_ASTC_10X8_UNORM_BLOCK: return 8;
        case CGPU_TEXTURE_FORMAT_ASTC_10X8_SRGB_BLOCK: return 8;
        case CGPU_TEXTURE_FORMAT_ASTC_10X10_UNORM_BLOCK: return 10;
        case CGPU_TEXTURE_FORMAT_ASTC_10X10_SRGB_BLOCK: return 10;
        case CGPU_TEXTURE_FORMAT_ASTC_12X10_UNORM_BLOCK: return 10;
        case CGPU_TEXTURE_FORMAT_ASTC_12X10_SRGB_BLOCK: return 10;
        case CGPU_TEXTURE_FORMAT_ASTC_12X12_UNORM_BLOCK: return 12;
        case CGPU_TEXTURE_FORMAT_ASTC_12X12_SRGB_BLOCK: return 12;
        case CGPU_TEXTURE_FORMAT_ASTC_4X4_SFLOAT_BLOCK: return 4;
        case CGPU_TEXTURE_FORMAT_ASTC_5X4_SFLOAT_BLOCK: return 4;
        case CGPU_TEXTURE_FORMAT_ASTC_5X5_SFLOAT_BLOCK: return 5;
        case CGPU_TEXTURE_FORMAT_ASTC_6X5_SFLOAT_BLOCK: return 5;
        case CGPU_TEXTURE_FORMAT_ASTC_6X6_SFLOAT_BLOCK: return 6;
        case CGPU_TEXTURE_FORMAT_ASTC_8X5_SFLOAT_BLOCK: return 5;
        case CGPU_TEXTURE_FORMAT_ASTC_8X6_SFLOAT_BLOCK: return 6;
        case CGPU_TEXTURE_FORMAT_ASTC_8X8_SFLOAT_BLOCK: return 8;
        case CGPU_TEXTURE_FORMAT_ASTC_10X5_SFLOAT_BLOCK: return 5;
        case CGPU_TEXTURE_FORMAT_ASTC_10X6_SFLOAT_BLOCK: return 6;
        case CGPU_TEXTURE_FORMAT_ASTC_10X8_SFLOAT_BLOCK: return 8;
        case CGPU_TEXTURE_FORMAT_ASTC_10X10_SFLOAT_BLOCK: return 10;
        case CGPU_TEXTURE_FORMAT_ASTC_12X10_SFLOAT_BLOCK: return 10;
        case CGPU_TEXTURE_FORMAT_ASTC_12X12_SFLOAT_BLOCK: return 12;
        default: return 1;
    }
    return 1;
}

static CGPU_FORCEINLINE uint32_t VertexFormatUtil_BitSizeOfBlock(ECGPUVertexFormat const arg) {
    switch(arg) {
        case CGPU_VERTEX_FORMAT_FLOAT32X1: return 32;
        case CGPU_VERTEX_FORMAT_FLOAT32X2: return 64;
        case CGPU_VERTEX_FORMAT_FLOAT32X3: return 96;
        case CGPU_VERTEX_FORMAT_FLOAT32X4: return 128;
        case CGPU_VERTEX_FORMAT_SINT32X1: return 32;
        case CGPU_VERTEX_FORMAT_SINT32X2: return 64;
        case CGPU_VERTEX_FORMAT_SINT32X3: return 96;
        case CGPU_VERTEX_FORMAT_SINT32X4: return 128;
        case CGPU_VERTEX_FORMAT_UINT32X1: return 32;
        case CGPU_VERTEX_FORMAT_UINT32X2: return 64;
        case CGPU_VERTEX_FORMAT_UINT32X3: return 96;
        case CGPU_VERTEX_FORMAT_UINT32X4: return 128;
        case CGPU_VERTEX_FORMAT_FLOAT16X2: return 32;
        case CGPU_VERTEX_FORMAT_FLOAT16X4: return 64;
        case CGPU_VERTEX_FORMAT_SINT16X2: return 32;
        case CGPU_VERTEX_FORMAT_SINT16X4: return 64;
        case CGPU_VERTEX_FORMAT_UINT16X2: return 32;
        case CGPU_VERTEX_FORMAT_UINT16X4: return 64;
        case CGPU_VERTEX_FORMAT_SNORM16X2: return 32;
        case CGPU_VERTEX_FORMAT_SNORM16X4: return 64;
        case CGPU_VERTEX_FORMAT_UNORM16X2: return 32;
        case CGPU_VERTEX_FORMAT_UNORM16X4: return 64;
        case CGPU_VERTEX_FORMAT_SINT8X4: return 32;
        case CGPU_VERTEX_FORMAT_UINT8X4: return 32;
        case CGPU_VERTEX_FORMAT_SNORM8X4: return 32;
        case CGPU_VERTEX_FORMAT_UNORM8X4: return 32;
        default: return 0;
    }
    return 0;
}


#ifdef __cplusplus
CGPU_EXTERN_C_END
#endif

#endif // CGPU_C99_H_HEADER_GUARD

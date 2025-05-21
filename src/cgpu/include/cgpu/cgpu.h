#ifndef CGPU_C99_H_HEADER_GUARD
#define CGPU_C99_H_HEADER_GUARD

#include <stdarg.h>  // va_list
#include <stdbool.h> // bool
#include <stdint.h>  // uint32_t
#include <stdlib.h>  // size_t

#define DEFINE_CGPU_OBJECT(name) typedef const struct name* name##Id;

typedef uint32_t ECGPUFlags;
typedef uint32_t ECGPUFlags64;

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
    CGPU_FRONT_FACE_COUNTER_CLOCK_WISE,       /** ( 0)                                */
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
typedef void (*CGPUProcQueryInstanceFeatures)(const CGPUInstanceId instance, CGPUInstanceFeatures* features);
typedef void (*CGPUProcEnumAdapters)(const CGPUInstanceId instance, CGPUAdapterId* adapters, uint32_t* adapters_num);
typedef const CGPUAdapterDetail* (*CGPUProcQueryAdapterDetail)(const CGPUAdapterId adapter);
typedef uint32_t (*CGPUProcQueryQueueCount)(const CGPUAdapterId adapter, ECGPUQueueType type);
typedef CGPUDeviceId (*CGPUProcCreateDevice)(CGPUAdapterId adapter, const CGPUDeviceDescriptor* desc);
typedef void (*CGPUProcFreeDevice)(CGPUAdapterId adapter, CGPUDeviceId device);
typedef void (*CGPUProcQueryVideoMemoryInfo)(CGPUDeviceId device, uint64_t* total, uint64_t* used);
typedef void (*CGPUProcQuerySharedMemoryInfo)(CGPUDeviceId device, uint64_t* total, uint64_t* used);
typedef CGPUFenceId (*CGPUProcCreateFence)(CGPUDeviceId device);
typedef void (*CGPUProcWaitFences)(const CGPUFenceId* fences, uint32_t fence);
typedef ECGPUFenceStatus (*CGPUProcQueryFenceStatus)(CGPUFenceId fence);
typedef void (*CGPUProcFreeFence)(CGPUFenceId fence);
typedef CGPUSemaphoreId (*CGPUProcCreateSemaphore)(CGPUDeviceId device);
typedef void (*CGPUProcFreeSemaphore)(CGPUSemaphoreId semaphore);
typedef CGPURootSignaturePoolId (*CGPUProcCreateRootSignaturePool)(CGPUDeviceId device, const CGPURootSignaturePoolDescriptor* desc);
typedef void (*CGPUProcFreeRootSignaturePool)(CGPURootSignaturePoolId pool);
typedef CGPURootSignatureId (*CGPUProcCreateRootSignature)(CGPUDeviceId device, const CGPURootSignatureDescriptor* desc);
typedef void (*CGPUProcFreeRootSignature)(CGPURootSignatureId signature);
typedef CGPUDescriptorSetId (*CGPUProcCreateDescriptorSet)(CGPUDeviceId device, const CGPUDescriptorSetDescriptor* desc);
typedef void (*CGPUProcUpdateDescriptorSet)(CGPUDescriptorSetId set, const CGPUDescriptorData* datas, uint32_t count);
typedef void (*CGPUProcFreeDescriptorSet)(CGPUDescriptorSetId set);
typedef CGPUComputePipelineId (*CGPUProcCreateComputePipeline)(CGPUDeviceId device, const struct CGPUComputePipelineDescriptor* desc);
typedef void (*CGPUProcFreeComputePipeline)(CGPUComputePipelineId pipeline);
typedef CGPURenderPipelineId (*CGPUProcCreateRenderPipeline)(CGPUDeviceId device, const CGPURenderPipelineDescriptor* desc);
typedef void (*CGPUProcFreeRenderPipeline)(CGPURenderPipelineId pipeline);

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
    ECGPUQueueType       queue_type;
    uint32_t             queue_count;

} CGPUQueueGroupDescriptor;

typedef struct CGPUDeviceDescriptor
{
    bool                 disable_pipeline_cache;
    CGPUQueueGroupDescriptor* queue_groups;
    uint32_t             queue_group_count;

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
    CGPUVertexInput*     vertex_inputs;
    CGPUShaderResource*  shader_resources;
    uint32_t             vertex_inputs_count;
    uint32_t             shader_resources_count;
    uint32_t             thread_group_sizes[3];

} CGPUShaderReflection;

typedef struct CGPUShaderLibrary
{
    CGPUDeviceId         device;
    const char*          name;
    CGPUShaderReflection* entry_reflections;
    uint32_t             entrys_count;

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
    const CGPUConstantSpecialization* constants;
    uint32_t             num_constants;

} CGPUShaderEntryDescriptor;

typedef struct CGPURootSignatureDescriptor
{
    CGPUShaderEntryDescriptor* shaders;
    uint32_t             shader_count;
    const char*          static_sampler_names;
    const CGPUSamplerId* static_samplers;
    uint32_t             static_sampler_count;
    const char*          push_constant_names;
    uint32_t             push_constant_count;
    CGPURootSignaturePoolId pool;

} CGPURootSignatureDescriptor;

typedef struct CGPUParameterTable
{
    CGPUShaderResource*  resources;
    uint32_t             resources_count;
    uint32_t             set_index;

} CGPUParameterTable;

typedef struct CGPURootSignature
{
    CGPUDeviceId         device;
    CGPUParameterTable*  tables;
    uint32_t             table_count;
    CGPUShaderResource*  push_constants;
    uint32_t             push_constant_count;
    CGPUShaderResource*  static_samplers;
    uint32_t             static_sampler_count;
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
    char                 semantic_name[64];
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
    CGPUVertexAttribute  attributes[15];

} CGPUVertexLayout;

typedef struct CGPUBlendStateDescriptor
{
    ECGPUBlendFactor     src_factors[8];
    ECGPUBlendFactor     dst_factors[8];
    ECGPUBlendFactor     src_alpha_factors[8];
    ECGPUBlendFactor     dst_alpha_factors[8];
    ECGPUBlendOp         blend_modes[8];
    ECGPUBlendOp         blend_alpha_modes[8];
    int32_t              masks[8];
    bool                 alpha_to_coverage;
    bool                 independent_blend;

} CGPUBlendStateDescriptor;

typedef struct CGPUDepthStateDescriptor
{
    bool                 depth_test;
    bool                 depth_write;
    ECGPUCompareOp       depth_func;
    bool                 stencil_test;
    uint8_t              stencil_read_mask;
    uint8_t              stencil_write_mask;
    ECGPUCompareOp       stencil_front_func;
    ECGPUStencilOp       stencil_front_fail;
    ECGPUStencilOp       depth_front_fail;
    ECGPUStencilOp       stencil_front_pass;
    ECGPUCompareOp       stencil_back_func;
    ECGPUStencilOp       stencil_back_fail;
    ECGPUStencilOp       depth_back_fail;
    ECGPUStencilOp       stencil_back_pass;

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
    const void**         ptrs;
    CGPUTextureViewId*   textures;
    CGPUSamplerId*       samplers;
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
    void*                cpu_mapped_address;
    uint32_t             descriptors;
    uint32_t             memory_usage;

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
    uint32_t             aspect_mask;
    uint32_t             node_index;
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

typedef struct CGPUTextureView
{
    CGPUDeviceId         device;
    CGPUTextureViewDescriptor info;

} CGPUTextureView;

typedef struct CGPUSampler
{
    CGPUDeviceId         device;

} CGPUSampler;

typedef struct CGPUBufferRange
{
    uint64_t             offset;
    uint64_t             size;

} CGPUBufferRange;


CGPU_API CGPUInstanceId cgpu_create_instance(const CGPUInstanceDescriptor* desc);
CGPU_API void cgpu_free_instance(CGPUInstanceId instance);
CGPU_API ECGPUBackend cgpu_get_backend(const CGPUInstanceId _this);
CGPU_API void cgpu_query_instance_features(const CGPUInstanceId _this, CGPUInstanceFeatures* features);
CGPU_API void cgpu_enum_adapters(const CGPUInstanceId _this, CGPUAdapterId* adapters, uint32_t* adapters_num);
CGPU_API const CGPUAdapterDetail* cgpu_query_adapter_detail(const CGPUAdapterId _this);
CGPU_API uint32_t cgpu_query_queue_count(const CGPUAdapterId _this, ECGPUQueueType type);
CGPU_API CGPUDeviceId cgpu_create_device(CGPUAdapterId _this, const CGPUDeviceDescriptor* desc);
CGPU_API void cgpu_free_device(CGPUAdapterId _this, CGPUDeviceId device);
CGPU_API void cgpu_query_video_memory_info(CGPUDeviceId _this, uint64_t* total, uint64_t* used);
CGPU_API void cgpu_query_shared_memory_info(CGPUDeviceId _this, uint64_t* total, uint64_t* used);
CGPU_API CGPUFenceId cgpu_create_fence(CGPUDeviceId _this);
CGPU_API void cgpu_wait_fences(const CGPUFenceId* fences, uint32_t fence);
CGPU_API ECGPUFenceStatus cgpu_query_fence_status(CGPUFenceId fence);
CGPU_API void cgpu_free_fence(CGPUFenceId fence);
CGPU_API CGPUSemaphoreId cgpu_create_semaphore(CGPUDeviceId _this);
CGPU_API void cgpu_free_semaphore(CGPUSemaphoreId semaphore);
CGPU_API CGPUSemaphoreId cgpu_create_semaphore(CGPUDeviceId _this);
CGPU_API void cgpu_free_semaphore(CGPUSemaphoreId semaphore);
CGPU_API CGPUSemaphoreId cgpu_create_semaphore(CGPUDeviceId _this);
CGPU_API CGPURootSignaturePoolId cgpu_create_root_signature_pool(CGPUDeviceId device, const CGPURootSignaturePoolDescriptor* desc);
CGPU_API void cgpu_free_root_signature_pool(CGPURootSignaturePoolId pool);
CGPU_API CGPURootSignatureId cgpu_create_root_signature(CGPUDeviceId device, const CGPURootSignatureDescriptor* desc);
CGPU_API void cgpu_free_root_signature(CGPURootSignatureId signature);
CGPU_API CGPUDescriptorSetId cgpu_create_descriptor_set(CGPUDeviceId device, const CGPUDescriptorSetDescriptor* desc);
CGPU_API void cgpu_update_descriptor_set(CGPUDescriptorSetId set, const CGPUDescriptorData* datas, uint32_t count);
CGPU_API void cgpu_free_descriptor_set(CGPUDescriptorSetId set);
CGPU_API CGPUComputePipelineId cgpu_create_compute_pipeline(CGPUDeviceId device, const struct CGPUComputePipelineDescriptor* desc);
CGPU_API void cgpu_free_compute_pipeline(CGPUComputePipelineId pipeline);
CGPU_API CGPURenderPipelineId cgpu_create_render_pipeline(CGPUDeviceId device, const CGPURenderPipelineDescriptor* desc);
CGPU_API void cgpu_free_render_pipeline(CGPURenderPipelineId pipeline);

#endif // CGPU_C99_H_HEADER_GUARD

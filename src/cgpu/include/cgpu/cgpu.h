#ifndef CGPU_C99_H_HEADER_GUARD
#define CGPU_C99_H_HEADER_GUARD

#include <stdarg.h>  // va_list
#include <stdbool.h> // bool
#include <stdint.h>  // uint32_t
#include <stdlib.h>  // size_t

#define DEFINE_CGPU_OBJECT2(name) typedef const struct name* name##_id;

typedef enum cgpu_backend_enum
{
    CGPU_BACKEND_VULKAN,                      /** ( 0) Vulkan                         */
    CGPU_BACKEND_D3D12,                       /** ( 1) D3D12                          */
    CGPU_BACKEND_METAL,                       /** ( 2) Metal                          */

    CGPU_BACKEND_COUNT

} cgpu_backend_enum;

typedef enum cgpu_blend_factor_enum
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

} cgpu_blend_factor_enum;

typedef enum cgpu_blend_op_enum
{
    CGPU_BLEND_OP_ADD,                        /** ( 0)                                */
    CGPU_BLEND_OP_SUBTRACT,                   /** ( 1)                                */
    CGPU_BLEND_OP_REVERSE_SUBTRACT,           /** ( 2)                                */
    CGPU_BLEND_OP_MIN,                        /** ( 3)                                */
    CGPU_BLEND_OP_MAX,                        /** ( 4)                                */

    CGPU_BLEND_OP_COUNT

} cgpu_blend_op_enum;

typedef enum cgpu_log_severity_enum
{
    CGPU_LOG_SEVERITY_TRACE,                  /** ( 0)                                */
    CGPU_LOG_SEVERITY_DEBUG,                  /** ( 1)                                */
    CGPU_LOG_SEVERITY_INFO,                   /** ( 2)                                */
    CGPU_LOG_SEVERITY_WARNING,                /** ( 3)                                */
    CGPU_LOG_SEVERITY_ERROR,                  /** ( 4)                                */
    CGPU_LOG_SEVERITY_FATAL,                  /** ( 5)                                */

    CGPU_LOG_SEVERITY_COUNT

} cgpu_log_severity_enum;

typedef enum cgpu_texture_format_enum
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

} cgpu_texture_format_enum;

typedef enum cgpu_filter_type_enum
{
    CGPU_FILTER_TYPE_NEAREST,                 /** ( 0)                                */
    CGPU_FILTER_TYPE_LINEAR,                  /** ( 1)                                */

    CGPU_FILTER_TYPE_COUNT

} cgpu_filter_type_enum;

typedef enum cgpu_address_mode_enum
{
    CGPU_ADDRESS_MODE_MIRROR,                 /** ( 0)                                */
    CGPU_ADDRESS_MODE_REPEAT,                 /** ( 1)                                */
    CGPU_ADDRESS_MODE_CLAMP_TO_EDGE,          /** ( 2)                                */
    CGPU_ADDRESS_MODE_CLAMP_TO_BORDER,        /** ( 3)                                */

    CGPU_ADDRESS_MODE_COUNT

} cgpu_address_mode_enum;

typedef enum cgpu_mip_map_mode_enum
{
    CGPU_MIP_MAP_MODE_NEAREST,                /** ( 0)                                */
    CGPU_MIP_MAP_MODE_LINEAR,                 /** ( 1)                                */

    CGPU_MIP_MAP_MODE_COUNT

} cgpu_mip_map_mode_enum;

typedef enum cgpu_load_action_enum
{
    CGPU_LOAD_ACTION_DONT_CARE,               /** ( 0)                                */
    CGPU_LOAD_ACTION_LOAD,                    /** ( 1)                                */
    CGPU_LOAD_ACTION_CLEAR,                   /** ( 2)                                */

    CGPU_LOAD_ACTION_COUNT

} cgpu_load_action_enum;

typedef enum cgpu_store_action_enum
{
    CGPU_STORE_ACTION_STORE,                  /** ( 0)                                */
    CGPU_STORE_ACTION_DISCARD,                /** ( 1)                                */

    CGPU_STORE_ACTION_COUNT

} cgpu_store_action_enum;

typedef enum cgpu_primitive_topology_enum
{
    CGPU_PRIMITIVE_TOPOLOGY_POINT_LIST,       /** ( 0)                                */
    CGPU_PRIMITIVE_TOPOLOGY_LINE_LIST,        /** ( 1)                                */
    CGPU_PRIMITIVE_TOPOLOGY_LINE_STRIP,       /** ( 2)                                */
    CGPU_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,    /** ( 3)                                */
    CGPU_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP,   /** ( 4)                                */
    CGPU_PRIMITIVE_TOPOLOGY_PATCH_LIST,       /** ( 5)                                */

    CGPU_PRIMITIVE_TOPOLOGY_COUNT

} cgpu_primitive_topology_enum;

typedef enum cgpu_compare_op_enum
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

} cgpu_compare_op_enum;

typedef enum cgpu_fill_mode_enum
{
    CGPU_FILL_MODE_SOLID,                     /** ( 0)                                */
    CGPU_FILL_MODE_WIRE_FRAME,                /** ( 1)                                */

    CGPU_FILL_MODE_COUNT

} cgpu_fill_mode_enum;

typedef enum cgpu_front_face_enum
{
    CGPU_FRONT_FACE_COUNTER_CLOCK_WISE,       /** ( 0)                                */
    CGPU_FRONT_FACE_CLOCK_WISE,               /** ( 1)                                */

    CGPU_FRONT_FACE_COUNT

} cgpu_front_face_enum;

typedef enum cgpu_vertex_input_rate_enum
{
    CGPU_VERTEX_INPUT_RATE_VERTEX,            /** ( 0)                                */
    CGPU_VERTEX_INPUT_RATE_INSTANCE,          /** ( 1)                                */

    CGPU_VERTEX_INPUT_RATE_COUNT

} cgpu_vertex_input_rate_enum;

typedef enum cgpu_stencil_op_enum
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

} cgpu_stencil_op_enum;

typedef enum cgpu_texture_dimension_enum
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

} cgpu_texture_dimension_enum;

typedef enum cgpu_shader_bytecode_type_enum
{
    CGPU_SHADER_BYTECODE_TYPE_SPIRV,          /** ( 0)                                */
    CGPU_SHADER_BYTECODE_TYPE_DXIL,           /** ( 1)                                */
    CGPU_SHADER_BYTECODE_TYPE_MTL,            /** ( 2)                                */

    CGPU_SHADER_BYTECODE_TYPE_COUNT

} cgpu_shader_bytecode_type_enum;

typedef enum cgpu_fence_status_enum
{
    CGPU_FENCE_STATUS_COMPLETE,               /** ( 0)                                */
    CGPU_FENCE_STATUS_INCOMPLETE,             /** ( 1)                                */
    CGPU_FENCE_STATUS_NOT_SUBMITTED,          /** ( 2)                                */

    CGPU_FENCE_STATUS_COUNT

} cgpu_fence_status_enum;

typedef enum cgpu_query_type_enum
{
    CGPU_QUERY_TYPE_TIMESTAMP,                /** ( 0)                                */
    CGPU_QUERY_TYPE_PIPELINE_STATISTICS,      /** ( 1)                                */
    CGPU_QUERY_TYPE_OCCLUSION,                /** ( 2)                                */

    CGPU_QUERY_TYPE_COUNT

} cgpu_query_type_enum;

typedef enum cgpu_memory_usage_enum
{
    CGPU_MEMORY_USAGE_UNKNOWN,                /** ( 0)                                */
    CGPU_MEMORY_USAGE_GPU_ONLY,               /** ( 1)                                */
    CGPU_MEMORY_USAGE_CPU_ONLY,               /** ( 2)                                */
    CGPU_MEMORY_USAGE_CPU_TO_GPU,             /** ( 3)                                */
    CGPU_MEMORY_USAGE_GPU_TO_CPU,             /** ( 4)                                */

    CGPU_MEMORY_USAGE_COUNT

} cgpu_memory_usage_enum;

typedef enum cgpu_memory_pool_type_enum
{
    CGPU_MEMORY_POOL_TYPE_AUTOMATIC,          /** ( 0)                                */
    CGPU_MEMORY_POOL_TYPE_LINEAR,             /** ( 1)                                */
    CGPU_MEMORY_POOL_TYPE_TILED,              /** ( 2)                                */

    CGPU_MEMORY_POOL_TYPE_COUNT

} cgpu_memory_pool_type_enum;

typedef enum cgpu_pipeline_type_enum
{
    CGPU_PIPELINE_TYPE_NONE,                  /** ( 0)                                */
    CGPU_PIPELINE_TYPE_COMPUTE,               /** ( 1)                                */
    CGPU_PIPELINE_TYPE_GRAPHICS,              /** ( 2)                                */
    CGPU_PIPELINE_TYPE_RAY_TRACING,           /** ( 3)                                */

    CGPU_PIPELINE_TYPE_COUNT

} cgpu_pipeline_type_enum;

typedef enum cgpu_shading_rate_enum
{
    CGPU_SHADING_RATE_FULL,                   /** ( 0)                                */
    CGPU_SHADING_RATE_HALF,                   /** ( 1)                                */
    CGPU_SHADING_RATE_QUARTER,                /** ( 2)                                */
    CGPU_SHADING_RATE_1X2,                    /** ( 3)                                */
    CGPU_SHADING_RATE_2X1,                    /** ( 4)                                */
    CGPU_SHADING_RATE_2X4,                    /** ( 5)                                */
    CGPU_SHADING_RATE_4X2,                    /** ( 6)                                */

    CGPU_SHADING_RATE_COUNT

} cgpu_shading_rate_enum;

typedef enum cgpu_shading_rate_combiner_enum
{
    CGPU_SHADING_RATE_COMBINER_PASS_THROUGH,  /** ( 0)                                */
    CGPU_SHADING_RATE_COMBINER_OVERRIDE,      /** ( 1)                                */
    CGPU_SHADING_RATE_COMBINER_MIN,           /** ( 2)                                */
    CGPU_SHADING_RATE_COMBINER_MAX,           /** ( 3)                                */
    CGPU_SHADING_RATE_COMBINER_SUM,           /** ( 4)                                */

    CGPU_SHADING_RATE_COMBINER_COUNT

} cgpu_shading_rate_combiner_enum;

typedef enum cgpu_queue_type_enum
{
    CGPU_QUEUE_TYPE_GRAPHICS,                 /** ( 0)                                */
    CGPU_QUEUE_TYPE_COMPUTE,                  /** ( 1)                                */
    CGPU_QUEUE_TYPE_TRANSFER,                 /** ( 2)                                */
    CGPU_QUEUE_TYPE_TILE_MAPPING,             /** ( 3)                                */

    CGPU_QUEUE_TYPE_COUNT

} cgpu_queue_type_enum;

typedef enum cgpu_vertex_format_enum
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

} cgpu_vertex_format_enum;


typedef enum cgpu_color_mask_flag
{
    CGPU_COLOR_MASK_R = 0x00000001,                        /** ( 0)                                */
    CGPU_COLOR_MASK_G = 0x00000002,                        /** ( 1)                                */
    CGPU_COLOR_MASK_B = 0x00000004,                        /** ( 2)                                */
    CGPU_COLOR_MASK_A = 0x00000008,                        /** ( 3)                                */
    CGPU_COLOR_MASK_RGB = CGPU_COLOR_MASK_R | CGPU_COLOR_MASK_G | CGPU_COLOR_MASK_B,
    CGPU_COLOR_MASK_RGBA = CGPU_COLOR_MASK_RGB | CGPU_COLOR_MASK_A,

} cgpu_color_mask_flag;

typedef enum cgpu_cull_mode_flag
{
    CGPU_CULL_MODE_NONE = 0x00000000,                      /** ( 0)                                */
    CGPU_CULL_MODE_BACK = 0x00000001,                      /** ( 1)                                */
    CGPU_CULL_MODE_FRONT = 0x00000002,                     /** ( 2)                                */
    CGPU_CULL_MODE_BOTH = CGPU_CULL_MODE_BACK | CGPU_CULL_MODE_FRONT,

} cgpu_cull_mode_flag;

typedef enum cgpu_stencil_face_flag
{
    CGPU_STENCIL_FACE_FRONT = 0x00000001,                  /** ( 0)                                */
    CGPU_STENCIL_FACE_BACK = 0x00000002,                   /** ( 1)                                */
    CGPU_STENCIL_FACE_BOTH = CGPU_STENCIL_FACE_FRONT | CGPU_STENCIL_FACE_BACK,

} cgpu_stencil_face_flag;

typedef enum cgpu_shader_stage_flag
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

} cgpu_shader_stage_flag;

typedef enum cgpu_pipeline_stage_flag
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

} cgpu_pipeline_stage_flag;

typedef enum cgpu_resource_state_flag
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

} cgpu_resource_state_flag;

typedef enum cgpu_buffer_creation_usage_flag
{
    CGPU_BUFFER_CREATION_USAGE_NONE = 0x00000000,          /** ( 0)                                */
    CGPU_BUFFER_CREATION_USAGE_DEDICATED = 0x00000001,     /** ( 1)                                */
    CGPU_BUFFER_CREATION_USAGE_PERSISTENT_MAP = 0x00000002, /** ( 2)                                */
    CGPU_BUFFER_CREATION_USAGE_HOST_VISIBLE = 0x00000004,  /** ( 3)                                */

} cgpu_buffer_creation_usage_flag;

typedef enum cgpu_texture_creation_usage_flag
{
    CGPU_TEXTURE_CREATION_USAGE_NONE = 0x00000000,         /** ( 0)                                */
    CGPU_TEXTURE_CREATION_USAGE_DEDICATED = 0x00000001,    /** ( 1)                                */
    CGPU_TEXTURE_CREATION_USAGE_FORCE2D = 0x00000002,      /** ( 2)                                */
    CGPU_TEXTURE_CREATION_USAGE_FORCE3D = 0x00000004,      /** ( 3)                                */
    CGPU_TEXTURE_CREATION_USAGE_ALIASING_RESOURCE = 0x00000008, /** ( 4)                                */
    CGPU_TEXTURE_CREATION_USAGE_TILED_RESOURCE = 0x00000010, /** ( 5)                                */
    CGPU_TEXTURE_CREATION_USAGE_EXPORT = 0x00000020,       /** ( 6)                                */
    CGPU_TEXTURE_CREATION_USAGE_IMPORT_SHARED = 0x00000040, /** ( 7)                                */

} cgpu_texture_creation_usage_flag;

typedef enum cgpu_sample_count_flag
{
    CGPU_SAMPLE_COUNT_1 = 0x00000001,                      /** ( 0)                                */
    CGPU_SAMPLE_COUNT_2 = 0x00000002,                      /** ( 1)                                */
    CGPU_SAMPLE_COUNT_4 = 0x00000004,                      /** ( 2)                                */
    CGPU_SAMPLE_COUNT_8 = 0x00000008,                      /** ( 3)                                */
    CGPU_SAMPLE_COUNT_16 = 0x00000010,                     /** ( 4)                                */

} cgpu_sample_count_flag;

typedef enum cgpu_resource_type_flag
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

} cgpu_resource_type_flag;

typedef enum cgpu_texture_view_usage_flag
{
    CGPU_TEXTURE_VIEW_USAGE_SRV = 0x00000001,              /** ( 0)                                */
    CGPU_TEXTURE_VIEW_USAGE_RTV_DSV = 0x00000002,          /** ( 1)                                */
    CGPU_TEXTURE_VIEW_USAGE_UAV = 0x00000004,              /** ( 2)                                */

} cgpu_texture_view_usage_flag;

typedef enum cgpu_texture_view_aspect_flag
{
    CGPU_TEXTURE_VIEW_ASPECT_COLOR = 0x00000001,           /** ( 0)                                */
    CGPU_TEXTURE_VIEW_ASPECT_DEPTH = 0x00000002,           /** ( 1)                                */
    CGPU_TEXTURE_VIEW_ASPECT_STENCIL = 0x00000004,         /** ( 2)                                */

} cgpu_texture_view_aspect_flag;

typedef enum cgpu_texture_format_support_flag
{
    CGPU_TEXTURE_FORMAT_SUPPORT_SAMPLE = 0x00000001,       /** ( 0)                                */
    CGPU_TEXTURE_FORMAT_SUPPORT_RENDER = 0x00000002,       /** ( 1)                                */
    CGPU_TEXTURE_FORMAT_SUPPORT_LOAD_STORE = 0x00000004,   /** ( 2)                                */
    CGPU_TEXTURE_FORMAT_SUPPORT_BLEND = 0x00000008,        /** ( 3)                                */
    CGPU_TEXTURE_FORMAT_SUPPORT_MSAA2X = 0x00000010,       /** ( 4)                                */
    CGPU_TEXTURE_FORMAT_SUPPORT_MSAA4X = 0x00000020,       /** ( 5)                                */
    CGPU_TEXTURE_FORMAT_SUPPORT_MSAA8X = 0x00000040,       /** ( 6)                                */
    CGPU_TEXTURE_FORMAT_SUPPORT_MSAA16X = 0x00000080,      /** ( 7)                                */

} cgpu_texture_format_support_flag;


DEFINE_CGPU_OBJECT2(cgpu_instance)


typedef struct cgpu_instance_descriptor cgpu_instance_descriptor_t;
typedef struct cgpu_instance_features cgpu_instance_features_t;
typedef struct cgpu_proc_table cgpu_proc_table_t;
typedef struct cgpu_surfaces_proc_table cgpu_surfaces_proc_table_t;
typedef struct cgpu_runtime_table cgpu_runtime_table_t;

typedef void (*cgpu_proc_log_callback)(void* user_data, cgpu_log_severity_enum severity, const char* fmt, ... );
typedef void* (*cgpu_proc_malloc)(void* user_data, size_t size, const void* pool);
typedef void* (*cgpu_proc_realloc)(void* user_data, void* ptr, size_t size, const void* pool);
typedef void* (*cgpu_proc_calloc)(void* user_data, size_t count, size_t size, const void* pool);
typedef void (*cgpu_proc_free)(void* user_data, void* ptr, const void* pool);
typedef void* (*cgpu_proc_malloc_aligned)(void* user_data, size_t size, size_t alignment, const void* pool);
typedef void* (*cgpu_proc_realloc_aligned)(void* user_data, void* ptr, size_t size, size_t alignment, const void* pool);
typedef void* (*cgpu_proc_calloc_aligned)(void* user_data, size_t count, size_t size, size_t alignment, const void* pool);
typedef void (*cgpu_proc_free_aligned)(void* user_data, void* ptr, const void* pool);
typedef cgpu_instance_id (*cgpu_proc_create_instance)(const cgpu_instance_descriptor_t* desc);
typedef void (*cgpu_proc_free_instance)(cgpu_instance_id instance);
typedef void (*cgpu_proc_instance_query_features)(cgpu_instance_id instance, cgpu_instance_features_t* features);

typedef struct cgpu_logger
{
    cgpu_proc_log_callback log_callback;
    void*                user_data;

} cgpu_logger_t;

typedef struct cgpu_allocator
{
    cgpu_proc_malloc     malloc_fn;
    cgpu_proc_realloc    realloc_fn;
    cgpu_proc_calloc     calloc_fn;
    cgpu_proc_free       free_fn;
    cgpu_proc_malloc_aligned malloc_aligned_fn;
    cgpu_proc_realloc_aligned realloc_aligned_fn;
    cgpu_proc_calloc_aligned calloc_aligned_fn;
    cgpu_proc_free_aligned free_aligned_fn;
    void*                user_data;

} cgpu_allocator_t;

typedef struct cgpu_instance_descriptor
{
    cgpu_backend_enum    backend;
    bool                 enable_debug_layer;
    bool                 enable_gpu_based_validation;
    bool                 enable_set_name;
    cgpu_logger_t        logger;
    cgpu_allocator_t     allocator;

} cgpu_instance_descriptor_t;

typedef struct cgpu_instance_features
{
    bool                 specialization_constant;

} cgpu_instance_features_t;

typedef struct cgpu_instance
{
    const cgpu_proc_table_t* proc_table;
    const cgpu_surfaces_proc_table_t* surfaces_table;
    cgpu_runtime_table_t* runtime_table;
    cgpu_backend_enum    backend;
    bool                 enable_set_name;
    cgpu_logger_t        logger;
    cgpu_allocator_t     allocator;

} cgpu_instance_t;

typedef struct cgpu_buffer_range
{
    uint64_t             offset;
    uint64_t             size;

} cgpu_buffer_range_t;


CGPU_API cgpu_instance_id cgpu_create_instance(const cgpu_instance_descriptor_t* desc);
CGPU_API void cgpu_free_instance(cgpu_instance_id instance);
CGPU_API cgpu_backend_enum cgpu_instance_get_backend(const cgpu_instance_id _this);
CGPU_API void cgpu_instance_query_features(const cgpu_instance_id _this, cgpu_instance_features_t* features);

#endif // CGPU_C99_H_HEADER_GUARD

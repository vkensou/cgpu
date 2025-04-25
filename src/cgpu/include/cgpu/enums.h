#ifndef CGPU_C99_H_HEADER_GUARD
#define CGPU_C99_H_HEADER_GUARD

#include <stdarg.h>  // va_list
#include <stdbool.h> // bool
#include <stdint.h>  // uint32_t
#include <stdlib.h>  // size_t

typedef enum cgpu_backend
{
    CGPU_BACKEND_VULKAN,                      /** ( 0) Vulkan                         */
    CGPU_BACKEND_D3D12,                       /** ( 1) D3D12                          */
    CGPU_BACKEND_METAL,                       /** ( 2) Metal                          */

    CGPU_BACKEND_COUNT

} cgpu_backend_enum;

typedef enum cgpu_blend_factor
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

typedef enum cgpu_blend_op
{
    CGPU_BLEND_OP_ADD,                        /** ( 0)                                */
    CGPU_BLEND_OP_SUBTRACT,                   /** ( 1)                                */
    CGPU_BLEND_OP_REVERSE_SUBTRACT,           /** ( 2)                                */
    CGPU_BLEND_OP_MIN,                        /** ( 3)                                */
    CGPU_BLEND_OP_MAX,                        /** ( 4)                                */

    CGPU_BLEND_OP_COUNT

} cgpu_blend_op_enum;

typedef enum cgpu_log_severity
{
    CGPU_LOG_SEVERITY_TRACE,                  /** ( 0)                                */
    CGPU_LOG_SEVERITY_DEBUG,                  /** ( 1)                                */
    CGPU_LOG_SEVERITY_INFO,                   /** ( 2)                                */
    CGPU_LOG_SEVERITY_WARNING,                /** ( 3)                                */
    CGPU_LOG_SEVERITY_ERROR,                  /** ( 4)                                */
    CGPU_LOG_SEVERITY_FATAL,                  /** ( 5)                                */

    CGPU_LOG_SEVERITY_COUNT

} cgpu_log_severity_enum;

typedef enum cgpu_texture_format
{
    CGPU_TEXTURE_FORMAT_UNDEFINED,            /** ( 0)                                */
    CGPU_TEXTURE_FORMAT_R4G4B4A4_UNORM_PACK16, /** ( 1)                                */
    CGPU_TEXTURE_FORMAT_B4G4R4A4_UNORM_PACK16, /** ( 2)                                */
    CGPU_TEXTURE_FORMAT_R5G6B5_UNORM_PACK16,  /** ( 3)                                */
    CGPU_TEXTURE_FORMAT_B5G6R5_UNORM_PACK16,  /** ( 4)                                */
    CGPU_TEXTURE_FORMAT_R5G5B5A1_UNORM_PACK16, /** ( 5)                                */
    CGPU_TEXTURE_FORMAT_B5G5R5A1_UNORM_PACK16, /** ( 6)                                */
    CGPU_TEXTURE_FORMAT_A1R5G5B5_UNORM_PACK16, /** ( 7)                                */
    CGPU_TEXTURE_FORMAT_R8_UNORM,             /** ( 8)                                */
    CGPU_TEXTURE_FORMAT_R8_SNORM,             /** ( 9)                                */
    CGPU_TEXTURE_FORMAT_R8_UINT,              /** (10)                                */
    CGPU_TEXTURE_FORMAT_R8_SINT,              /** (11)                                */
    CGPU_TEXTURE_FORMAT_R8_SRGB,              /** (12)                                */
    CGPU_TEXTURE_FORMAT_R8G8_UNORM,           /** (13)                                */
    CGPU_TEXTURE_FORMAT_R8G8_SNORM,           /** (14)                                */
    CGPU_TEXTURE_FORMAT_R8G8_UINT,            /** (15)                                */
    CGPU_TEXTURE_FORMAT_R8G8_SINT,            /** (16)                                */
    CGPU_TEXTURE_FORMAT_R8G8_SRGB,            /** (17)                                */
    CGPU_TEXTURE_FORMAT_R8G8B8_UNORM,         /** (18)                                */
    CGPU_TEXTURE_FORMAT_R8G8B8_SNORM,         /** (19)                                */
    CGPU_TEXTURE_FORMAT_R8G8B8_UINT,          /** (20)                                */
    CGPU_TEXTURE_FORMAT_R8G8B8_SINT,          /** (21)                                */
    CGPU_TEXTURE_FORMAT_R8G8B8_SRGB,          /** (22)                                */
    CGPU_TEXTURE_FORMAT_B8G8R8_UNORM,         /** (23)                                */
    CGPU_TEXTURE_FORMAT_B8G8R8_SNORM,         /** (24)                                */
    CGPU_TEXTURE_FORMAT_B8G8R8_UINT,          /** (25)                                */
    CGPU_TEXTURE_FORMAT_B8G8R8_SINT,          /** (26)                                */
    CGPU_TEXTURE_FORMAT_B8G8R8_SRGB,          /** (27)                                */
    CGPU_TEXTURE_FORMAT_R8G8B8A8_UNORM,       /** (28)                                */
    CGPU_TEXTURE_FORMAT_R8G8B8A8_SNORM,       /** (29)                                */
    CGPU_TEXTURE_FORMAT_R8G8B8A8_UINT,        /** (30)                                */
    CGPU_TEXTURE_FORMAT_R8G8B8A8_SINT,        /** (31)                                */
    CGPU_TEXTURE_FORMAT_R8G8B8A8_SRGB,        /** (32)                                */
    CGPU_TEXTURE_FORMAT_B8G8R8A8_UNORM,       /** (33)                                */
    CGPU_TEXTURE_FORMAT_B8G8R8A8_SNORM,       /** (34)                                */
    CGPU_TEXTURE_FORMAT_B8G8R8A8_UINT,        /** (35)                                */
    CGPU_TEXTURE_FORMAT_B8G8R8A8_SINT,        /** (36)                                */
    CGPU_TEXTURE_FORMAT_B8G8R8A8_SRGB,        /** (37)                                */
    CGPU_TEXTURE_FORMAT_A8B8G8R8_UNORM_PACK32, /** (38)                                */
    CGPU_TEXTURE_FORMAT_A8B8G8R8_SNORM_PACK32, /** (39)                                */
    CGPU_TEXTURE_FORMAT_A8B8G8R8_UINT_PACK32, /** (40)                                */
    CGPU_TEXTURE_FORMAT_A8B8G8R8_SINT_PACK32, /** (41)                                */
    CGPU_TEXTURE_FORMAT_A8B8G8R8_SRGB_PACK32, /** (42)                                */
    CGPU_TEXTURE_FORMAT_A2R10G10B10_UNORM_PACK32, /** (43)                                */
    CGPU_TEXTURE_FORMAT_A2R10G10B10_SNORM_PACK32, /** (44)                                */
    CGPU_TEXTURE_FORMAT_A2R10G10B10_UINT_PACK32, /** (45)                                */
    CGPU_TEXTURE_FORMAT_A2R10G10B10_SINT_PACK32, /** (46)                                */
    CGPU_TEXTURE_FORMAT_A2B10G10R10_UNORM_PACK32, /** (47)                                */
    CGPU_TEXTURE_FORMAT_A2B10G10R10_SNORM_PACK32, /** (48)                                */
    CGPU_TEXTURE_FORMAT_A2B10G10R10_UINT_PACK32, /** (49)                                */
    CGPU_TEXTURE_FORMAT_A2B10G10R10_SINT_PACK32, /** (50)                                */
    CGPU_TEXTURE_FORMAT_R16_UNORM,            /** (51)                                */
    CGPU_TEXTURE_FORMAT_R16_SNORM,            /** (52)                                */
    CGPU_TEXTURE_FORMAT_R16_UINT,             /** (53)                                */
    CGPU_TEXTURE_FORMAT_R16_SINT,             /** (54)                                */
    CGPU_TEXTURE_FORMAT_R16_SFLOAT,           /** (55)                                */
    CGPU_TEXTURE_FORMAT_R16G16_UNORM,         /** (56)                                */
    CGPU_TEXTURE_FORMAT_R16G16_SNORM,         /** (57)                                */
    CGPU_TEXTURE_FORMAT_R16G16_UINT,          /** (58)                                */
    CGPU_TEXTURE_FORMAT_R16G16_SINT,          /** (59)                                */
    CGPU_TEXTURE_FORMAT_R16G16_SFLOAT,        /** (60)                                */
    CGPU_TEXTURE_FORMAT_R16G16B16_UNORM,      /** (61)                                */
    CGPU_TEXTURE_FORMAT_R16G16B16_SNORM,      /** (62)                                */
    CGPU_TEXTURE_FORMAT_R16G16B16_UINT,       /** (63)                                */
    CGPU_TEXTURE_FORMAT_R16G16B16_SINT,       /** (64)                                */
    CGPU_TEXTURE_FORMAT_R16G16B16_SFLOAT,     /** (65)                                */
    CGPU_TEXTURE_FORMAT_R16G16B16A16_UNORM,   /** (66)                                */
    CGPU_TEXTURE_FORMAT_R16G16B16A16_SNORM,   /** (67)                                */
    CGPU_TEXTURE_FORMAT_R16G16B16A16_UINT,    /** (68)                                */
    CGPU_TEXTURE_FORMAT_R16G16B16A16_SINT,    /** (69)                                */
    CGPU_TEXTURE_FORMAT_R16G16B16A16_SFLOAT,  /** (70)                                */
    CGPU_TEXTURE_FORMAT_R32_UINT,             /** (71)                                */
    CGPU_TEXTURE_FORMAT_R32_SINT,             /** (72)                                */
    CGPU_TEXTURE_FORMAT_R32_SFLOAT,           /** (73)                                */
    CGPU_TEXTURE_FORMAT_R32G32_UINT,          /** (74)                                */
    CGPU_TEXTURE_FORMAT_R32G32_SINT,          /** (75)                                */
    CGPU_TEXTURE_FORMAT_R32G32_SFLOAT,        /** (76)                                */
    CGPU_TEXTURE_FORMAT_R32G32B32_UINT,       /** (77)                                */
    CGPU_TEXTURE_FORMAT_R32G32B32_SINT,       /** (78)                                */
    CGPU_TEXTURE_FORMAT_R32G32B32_SFLOAT,     /** (79)                                */
    CGPU_TEXTURE_FORMAT_R32G32B32A32_UINT,    /** (80)                                */
    CGPU_TEXTURE_FORMAT_R32G32B32A32_SINT,    /** (81)                                */
    CGPU_TEXTURE_FORMAT_R32G32B32A32_SFLOAT,  /** (82)                                */
    CGPU_TEXTURE_FORMAT_R64_UINT,             /** (83)                                */
    CGPU_TEXTURE_FORMAT_R64_SINT,             /** (84)                                */
    CGPU_TEXTURE_FORMAT_R64_SFLOAT,           /** (85)                                */
    CGPU_TEXTURE_FORMAT_R64G64_UINT,          /** (86)                                */
    CGPU_TEXTURE_FORMAT_R64G64_SINT,          /** (87)                                */
    CGPU_TEXTURE_FORMAT_R64G64_SFLOAT,        /** (88)                                */
    CGPU_TEXTURE_FORMAT_R64G64B64_UINT,       /** (89)                                */
    CGPU_TEXTURE_FORMAT_R64G64B64_SINT,       /** (90)                                */
    CGPU_TEXTURE_FORMAT_R64G64B64_SFLOAT,     /** (91)                                */
    CGPU_TEXTURE_FORMAT_R64G64B64A64_UINT,    /** (92)                                */
    CGPU_TEXTURE_FORMAT_R64G64B64A64_SINT,    /** (93)                                */
    CGPU_TEXTURE_FORMAT_R64G64B64A64_SFLOAT,  /** (94)                                */
    CGPU_TEXTURE_FORMAT_B10G11R11_UFLOAT_PACK32, /** (95)                                */
    CGPU_TEXTURE_FORMAT_E5B9G9R9_UFLOAT_PACK32, /** (96)                                */
    CGPU_TEXTURE_FORMAT_D16_UNORM,            /** (97)                                */
    CGPU_TEXTURE_FORMAT_X8_D24_UNORM_PACK32,  /** (98)                                */
    CGPU_TEXTURE_FORMAT_D32_SFLOAT,           /** (99)                                */
    CGPU_TEXTURE_FORMAT_S8_UINT,              /** (100)                                */
    CGPU_TEXTURE_FORMAT_D16_UNORM_S8_UINT,    /** (101)                                */
    CGPU_TEXTURE_FORMAT_D24_UNORM_S8_UINT,    /** (102)                                */
    CGPU_TEXTURE_FORMAT_D32_SFLOAT_S8_UINT,   /** (103)                                */

    CGPU_TEXTURE_FORMAT_COUNT

} cgpu_texture_format_enum;

typedef enum cgpu_filter_type
{
    CGPU_FILTER_TYPE_NEAREST,                 /** ( 0)                                */
    CGPU_FILTER_TYPE_LINEAR,                  /** ( 1)                                */

    CGPU_FILTER_TYPE_COUNT

} cgpu_filter_type_enum;

typedef enum cgpu_address_mode
{
    CGPU_ADDRESS_MODE_MIRROR,                 /** ( 0)                                */
    CGPU_ADDRESS_MODE_REPEAT,                 /** ( 1)                                */
    CGPU_ADDRESS_MODE_CLAMP_TO_EDGE,          /** ( 2)                                */
    CGPU_ADDRESS_MODE_CLAMP_TO_BORDER,        /** ( 3)                                */

    CGPU_ADDRESS_MODE_COUNT

} cgpu_address_mode_enum;

typedef enum cgpu_mip_map_mode
{
    CGPU_MIP_MAP_MODE_NEAREST,                /** ( 0)                                */
    CGPU_MIP_MAP_MODE_LINEAR,                 /** ( 1)                                */

    CGPU_MIP_MAP_MODE_COUNT

} cgpu_mip_map_mode_enum;

typedef enum cgpu_load_action
{
    CGPU_LOAD_ACTION_DONT_CARE,               /** ( 0)                                */
    CGPU_LOAD_ACTION_LOAD,                    /** ( 1)                                */
    CGPU_LOAD_ACTION_CLEAR,                   /** ( 2)                                */

    CGPU_LOAD_ACTION_COUNT

} cgpu_load_action_enum;

typedef enum cgpu_store_action
{
    CGPU_STORE_ACTION_STORE,                  /** ( 0)                                */
    CGPU_STORE_ACTION_DISCARD,                /** ( 1)                                */

    CGPU_STORE_ACTION_COUNT

} cgpu_store_action_enum;

typedef enum cgpu_primitive_topology
{
    CGPU_PRIMITIVE_TOPOLOGY_POINT_LIST,       /** ( 0)                                */
    CGPU_PRIMITIVE_TOPOLOGY_LINE_LIST,        /** ( 1)                                */
    CGPU_PRIMITIVE_TOPOLOGY_LINE_STRIP,       /** ( 2)                                */
    CGPU_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,    /** ( 3)                                */
    CGPU_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP,   /** ( 4)                                */
    CGPU_PRIMITIVE_TOPOLOGY_PATCH_LIST,       /** ( 5)                                */

    CGPU_PRIMITIVE_TOPOLOGY_COUNT

} cgpu_primitive_topology_enum;

typedef enum cgpu_compare_op
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

typedef enum cgpu_fill_mode
{
    CGPU_FILL_MODE_SOLID,                     /** ( 0)                                */
    CGPU_FILL_MODE_WIRE_FRAME,                /** ( 1)                                */

    CGPU_FILL_MODE_COUNT

} cgpu_fill_mode_enum;

typedef enum cgpu_front_face
{
    CGPU_FRONT_FACE_COUNTER_CLOCK_WISE,       /** ( 0)                                */
    CGPU_FRONT_FACE_CLOCK_WISE,               /** ( 1)                                */

    CGPU_FRONT_FACE_COUNT

} cgpu_front_face_enum;

typedef enum cgpu_vertex_input_rate
{
    CGPU_VERTEX_INPUT_RATE_VERTEX,            /** ( 0)                                */
    CGPU_VERTEX_INPUT_RATE_INSTANCE,          /** ( 1)                                */

    CGPU_VERTEX_INPUT_RATE_COUNT

} cgpu_vertex_input_rate_enum;

typedef enum cgpu_stencil_op
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

typedef enum cgpu_texture_dimension
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

typedef enum cgpu_shader_bytecode_type
{
    CGPU_SHADER_BYTECODE_TYPE_SPIRV,          /** ( 0)                                */
    CGPU_SHADER_BYTECODE_TYPE_DXIL,           /** ( 1)                                */
    CGPU_SHADER_BYTECODE_TYPE_MTL,            /** ( 2)                                */

    CGPU_SHADER_BYTECODE_TYPE_COUNT

} cgpu_shader_bytecode_type_enum;

typedef enum cgpu_fence_status
{
    CGPU_FENCE_STATUS_COMPLETE,               /** ( 0)                                */
    CGPU_FENCE_STATUS_INCOMPLETE,             /** ( 1)                                */
    CGPU_FENCE_STATUS_NOT_SUBMITTED,          /** ( 2)                                */

    CGPU_FENCE_STATUS_COUNT

} cgpu_fence_status_enum;

typedef enum cgpu_query_type
{
    CGPU_QUERY_TYPE_TIMESTAMP,                /** ( 0)                                */
    CGPU_QUERY_TYPE_PIPELINE_STATISTICS,      /** ( 1)                                */
    CGPU_QUERY_TYPE_OCCLUSION,                /** ( 2)                                */

    CGPU_QUERY_TYPE_COUNT

} cgpu_query_type_enum;

typedef enum cgpu_memory_usage
{
    CGPU_MEMORY_USAGE_UNKNOWN,                /** ( 0)                                */
    CGPU_MEMORY_USAGE_GPU_ONLY,               /** ( 1)                                */
    CGPU_MEMORY_USAGE_CPU_ONLY,               /** ( 2)                                */
    CGPU_MEMORY_USAGE_CPU_TO_GPU,             /** ( 3)                                */
    CGPU_MEMORY_USAGE_GPU_TO_CPU,             /** ( 4)                                */

    CGPU_MEMORY_USAGE_COUNT

} cgpu_memory_usage_enum;

typedef enum cgpu_memory_pool_type
{
    CGPU_MEMORY_POOL_TYPE_AUTOMATIC,          /** ( 0)                                */
    CGPU_MEMORY_POOL_TYPE_LINEAR,             /** ( 1)                                */
    CGPU_MEMORY_POOL_TYPE_TILED,              /** ( 2)                                */

    CGPU_MEMORY_POOL_TYPE_COUNT

} cgpu_memory_pool_type_enum;

typedef enum cgpu_pipeline_type
{
    CGPU_PIPELINE_TYPE_NONE,                  /** ( 0)                                */
    CGPU_PIPELINE_TYPE_COMPUTE,               /** ( 1)                                */
    CGPU_PIPELINE_TYPE_GRAPHICS,              /** ( 2)                                */
    CGPU_PIPELINE_TYPE_RAY_TRACING,           /** ( 3)                                */

    CGPU_PIPELINE_TYPE_COUNT

} cgpu_pipeline_type_enum;

typedef enum cgpu_shading_rate
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

typedef enum cgpu_shading_rate_combiner
{
    CGPU_SHADING_RATE_COMBINER_PASS_THROUGH,  /** ( 0)                                */
    CGPU_SHADING_RATE_COMBINER_OVERRIDE,      /** ( 1)                                */
    CGPU_SHADING_RATE_COMBINER_MIN,           /** ( 2)                                */
    CGPU_SHADING_RATE_COMBINER_MAX,           /** ( 3)                                */
    CGPU_SHADING_RATE_COMBINER_SUM,           /** ( 4)                                */

    CGPU_SHADING_RATE_COMBINER_COUNT

} cgpu_shading_rate_combiner_enum;

typedef enum cgpu_queue_type
{
    CGPU_QUEUE_TYPE_GRAPHICS,                 /** ( 0)                                */
    CGPU_QUEUE_TYPE_COMPUTE,                  /** ( 1)                                */
    CGPU_QUEUE_TYPE_TRANSFER,                 /** ( 2)                                */
    CGPU_QUEUE_TYPE_TILE_MAPPING,             /** ( 3)                                */

    CGPU_QUEUE_TYPE_COUNT

} cgpu_queue_type_enum;

typedef enum cgpu_vertex_format
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


typedef enum cgpu_color_mask
{
    CGPU_COLOR_MASK_R = 0x00000001,                        /** ( 0)                                */
    CGPU_COLOR_MASK_G = 0x00000002,                        /** ( 1)                                */
    CGPU_COLOR_MASK_B = 0x00000004,                        /** ( 2)                                */
    CGPU_COLOR_MASK_A = 0x00000008,                        /** ( 3)                                */
    CGPU_COLOR_MASK_RGB = CGPU_COLOR_MASK_R | CGPU_COLOR_MASK_G | CGPU_COLOR_MASK_B,
    CGPU_COLOR_MASK_RGBA = CGPU_COLOR_MASK_RGB | CGPU_COLOR_MASK_A,

} cgpu_color_mask_flag;

typedef enum cgpu_cull_mode
{
    CGPU_CULL_MODE_NONE = 0x00000000,                      /** ( 0)                                */
    CGPU_CULL_MODE_BACK = 0x00000001,                      /** ( 1)                                */
    CGPU_CULL_MODE_FRONT = 0x00000002,                     /** ( 2)                                */
    CGPU_CULL_MODE_BOTH = CGPU_CULL_MODE_BACK | CGPU_CULL_MODE_FRONT,

} cgpu_cull_mode_flag;

typedef enum cgpu_stencil_face
{
    CGPU_STENCIL_FACE_FRONT = 0x00000001,                  /** ( 0)                                */
    CGPU_STENCIL_FACE_BACK = 0x00000002,                   /** ( 1)                                */
    CGPU_STENCIL_FACE_BOTH = CGPU_STENCIL_FACE_FRONT | CGPU_STENCIL_FACE_BACK,

} cgpu_stencil_face_flag;

typedef enum cgpu_shader_stage
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

typedef enum cgpu_pipeline_stage
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

typedef enum cgpu_resource_state
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

typedef enum cgpu_buffer_creation_usage
{
    CGPU_BUFFER_CREATION_USAGE_NONE = 0x00000000,          /** ( 0)                                */
    CGPU_BUFFER_CREATION_USAGE_DEDICATED = 0x00000001,     /** ( 1)                                */
    CGPU_BUFFER_CREATION_USAGE_PERSISTENT_MAP = 0x00000002, /** ( 2)                                */
    CGPU_BUFFER_CREATION_USAGE_HOST_VISIBLE = 0x00000004,  /** ( 3)                                */

} cgpu_buffer_creation_usage_flag;

typedef enum cgpu_texture_creation_usage
{
    CGPU_TEXTURE_CREATION_USAGE_NONE = 0x00000000,         /** ( 0)                                */
    CGPU_TEXTURE_CREATION_USAGE_DEDICATED = 0x00000001,    /** ( 1)                                */
    CGPU_TEXTURE_CREATION_USAGE_EXPORT = 0x00000002,       /** ( 2)                                */
    CGPU_TEXTURE_CREATION_USAGE_FORCE2D = 0x00000004,      /** ( 3)                                */
    CGPU_TEXTURE_CREATION_USAGE_FORCE3D = 0x00000008,      /** ( 4)                                */
    CGPU_TEXTURE_CREATION_USAGE_ALIASING_RESOURCE = 0x00000010, /** ( 5)                                */
    CGPU_TEXTURE_CREATION_USAGE_TILED_RESOURCE = 0x00000020, /** ( 6)                                */

} cgpu_texture_creation_usage_flag;

typedef enum cgpu_sample_count
{
    CGPU_SAMPLE_COUNT_1 = 0x00000001,                      /** ( 0)                                */
    CGPU_SAMPLE_COUNT_2 = 0x00000002,                      /** ( 1)                                */
    CGPU_SAMPLE_COUNT_4 = 0x00000004,                      /** ( 2)                                */
    CGPU_SAMPLE_COUNT_8 = 0x00000008,                      /** ( 3)                                */
    CGPU_SAMPLE_COUNT_16 = 0x00000010,                     /** ( 4)                                */

} cgpu_sample_count_flag;

typedef enum cgpu_resource_type
{
    CGPU_RESOURCE_TYPE_NONE = 0x00000000,                  /** ( 0)                                */
    CGPU_RESOURCE_TYPE_SAMPLER = 0x00000001,               /** ( 1)                                */
    CGPU_RESOURCE_TYPE_TEXTURE = 0x00000002,               /** ( 2)                                */
    CGPU_RESOURCE_TYPE_RENDER_TARGET = 0x00000004,         /** ( 3)                                */
    CGPU_RESOURCE_TYPE_DEPTH_STENCIL = 0x00000008,         /** ( 4)                                */
    CGPU_RESOURCE_TYPE_RW_TEXTURE = 0x00000010,            /** ( 5)                                */
    CGPU_RESOURCE_TYPE_BUFFER = 0x00000020,                /** ( 6)                                */
    CGPU_RESOURCE_TYPE_RW_BUFFER = 0x00000040,             /** ( 7)                                */
    CGPU_RESOURCE_TYPE_UNIFORM_BUFFER = 0x00000080,        /** ( 8)                                */
    CGPU_RESOURCE_TYPE_PUSH_CONSTANT = 0x00000100,         /** ( 9)                                */
    CGPU_RESOURCE_TYPE_INDEX_BUFFER = 0x00000200,          /** (10)                                */
    CGPU_RESOURCE_TYPE_VERTEX_BUFFER = 0x00000400,         /** (11)                                */
    CGPU_RESOURCE_TYPE_INDIRECT_BUFFER = 0x00000800,       /** (12)                                */
    CGPU_RESOURCE_TYPE_TEXTURE_CUBE = 0x00001000,          /** (13)                                */
    CGPU_RESOURCE_TYPE_RAY_TRACING = 0x00002000,           /** (14)                                */
    CGPU_RESOURCE_TYPE_INPUT_ATTACHMENT = 0x00004000,      /** (15)                                */
    CGPU_RESOURCE_TYPE_TEXEL_BUFFER = 0x00008000,          /** (16)                                */
    CGPU_RESOURCE_TYPE_RW_TEXEL_BUFFER = 0x00010000,       /** (17)                                */
    CGPU_RESOURCE_TYPE_COMBINED_IMAGE_SAMPLER = 0x00020000, /** (18)                                */

} cgpu_resource_type_flag;

typedef enum cgpu_texture_view_usage
{
    CGPU_TEXTURE_VIEW_USAGE_SRV = 0x00000001,              /** ( 0)                                */
    CGPU_TEXTURE_VIEW_USAGE_RTV_DSV = 0x00000002,          /** ( 1)                                */
    CGPU_TEXTURE_VIEW_USAGE_UAV = 0x00000004,              /** ( 2)                                */

} cgpu_texture_view_usage_flag;

typedef enum cgpu_texture_view_aspect
{
    CGPU_TEXTURE_VIEW_ASPECT_COLOR = 0x00000001,           /** ( 0)                                */
    CGPU_TEXTURE_VIEW_ASPECT_DEPTH = 0x00000002,           /** ( 1)                                */
    CGPU_TEXTURE_VIEW_ASPECT_STENCIL = 0x00000004,         /** ( 2)                                */

} cgpu_texture_view_aspect_flag;

typedef enum cgpu_texture_formmat_support
{
    CGPU_TEXTURE_FORMMAT_SUPPORT_SAMPLE = 0x00000001,      /** ( 0)                                */
    CGPU_TEXTURE_FORMMAT_SUPPORT_RENDER = 0x00000002,      /** ( 1)                                */
    CGPU_TEXTURE_FORMMAT_SUPPORT_LOAD_STORE = 0x00000004,  /** ( 2)                                */
    CGPU_TEXTURE_FORMMAT_SUPPORT_BLEND = 0x00000008,       /** ( 3)                                */
    CGPU_TEXTURE_FORMMAT_SUPPORT_MSAA2X = 0x00000010,      /** ( 4)                                */
    CGPU_TEXTURE_FORMMAT_SUPPORT_MSAA4X = 0x00000020,      /** ( 5)                                */
    CGPU_TEXTURE_FORMMAT_SUPPORT_MSAA8X = 0x00000040,      /** ( 6)                                */
    CGPU_TEXTURE_FORMMAT_SUPPORT_MSAA16X = 0x00000080,     /** ( 7)                                */

} cgpu_texture_formmat_support_flag;


#endif // CGPU_C99_H_HEADER_GUARD

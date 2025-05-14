#pragma once
#include "platform.h"
#include "cgpu.h"

#ifdef __cplusplus
CGPU_EXTERN_C_BEGIN
#endif

/* clang-format off */
static CGPU_FORCEINLINE bool FormatUtil_IsDepthStencilFormat(ECGPUTextureFormat const fmt) {
    switch(fmt) {
        case CGPU_TEXTURE_FORMAT_D24_UNORM_S8_UINT:
        case CGPU_TEXTURE_FORMAT_D32_SFLOAT_S8_UINT:
        case CGPU_TEXTURE_FORMAT_D32_SFLOAT:
        case CGPU_TEXTURE_FORMAT_X8_D24_UNORM_PACK32:
        case CGPU_TEXTURE_FORMAT_D16_UNORM:
        case CGPU_TEXTURE_FORMAT_D16_UNORM_S8_UINT:
            return true;
        default: return false;
    }
    return false;
}

static CGPU_FORCEINLINE bool FormatUtil_IsDepthOnlyFormat(ECGPUTextureFormat const fmt) {
    switch(fmt) {
        case CGPU_TEXTURE_FORMAT_D32_SFLOAT:
        case CGPU_TEXTURE_FORMAT_D16_UNORM:
            return true;
        default: return false;
    }
    return false;
}

static CGPU_FORCEINLINE uint32_t FormatUtil_BitSizeOfBlock(ECGPUTextureFormat const fmt) {
	switch(fmt) {
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
		default: return 32;
	}
}

static CGPU_FORCEINLINE uint32_t FormatUtil_WidthOfBlock(ECGPUTextureFormat const fmt) {
    switch(fmt) {
    case CGPU_TEXTURE_FORMAT_UNDEFINED: return 1;
    default: return 1;
	}
}

static CGPU_FORCEINLINE uint32_t FormatUtil_HeightOfBlock(ECGPUTextureFormat const fmt) {
	switch(fmt) {
		case CGPU_TEXTURE_FORMAT_UNDEFINED: return 1;
		default: return 1;
	}
}
/* clang-format on */

#ifdef __cplusplus
CGPU_EXTERN_C_END
#endif

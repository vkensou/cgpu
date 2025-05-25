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

$cconsts

#define DEFINE_CGPU_OBJECT(name) typedef const struct name* name##Id;

typedef uint32_t ECGPUFlags;
typedef uint32_t ECGPUFlags64;
typedef struct HWND__* HWND;
typedef struct ANativeWindow ANativeWindow;

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

$cfuncptrs

$cstructs

$c99decl

$cswitches

#ifdef __cplusplus
CGPU_EXTERN_C_END
#endif

#endif // CGPU_C99_H_HEADER_GUARD

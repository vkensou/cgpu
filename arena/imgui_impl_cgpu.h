// dear imgui: Renderer Backend for Vulkan
// This needs to be used along with a Platform Backend (e.g. GLFW, SDL, Win32, custom..)

// Implemented features:
//  [!] Renderer: User texture binding. Use 'VkDescriptorSet' as ImTextureID. Read the FAQ about ImTextureID! See https://github.com/ocornut/imgui/pull/914 for discussions.
//  [X] Renderer: Large meshes support (64k+ vertices) with 16-bit indices.

// Important: on 32-bit systems, user texture binding is only supported if your imconfig file has '#define ImTextureID ImU64'.
// See imgui_impl_vulkan.cpp file for details.

// You can use unmodified imgui_impl_* files in your project. See examples/ folder for examples of using this.
// Prefer including the entire imgui/ repository into your project (either as a copy or as a submodule), and only build the backends you need.
// If you are new to Dear ImGui, read documentation from the docs/ folder + read the top of imgui.cpp.
// Read online: https://github.com/ocornut/imgui/tree/master/docs

// The aim of imgui_impl_vulkan.h/.cpp is to be usable in your engine without any modification.
// IF YOU FEEL YOU NEED TO MAKE ANY CHANGE TO THIS CODE, please share them and your feedback at https://github.com/ocornut/imgui/

// Important note to the reader who wish to integrate imgui_impl_vulkan.cpp/.h in their own engine/app.
// - Common ImGui_ImplCGPU_XXX functions and structures are used to interface with imgui_impl_vulkan.cpp/.h.
//   You will use those if you want to use this rendering backend in your engine/app.
// - Helper ImGui_ImplCGPUH_XXX functions and structures are only used by this example (main.cpp) and by
//   the backend itself (imgui_impl_vulkan.cpp), but should PROBABLY NOT be used by your own engine/app code.
// Read comments in imgui_impl_vulkan.h.

#pragma once
#ifndef IMGUI_DISABLE
#include "imgui.h"      // IMGUI_IMPL_API

// [Configuration] in order to use a custom Vulkan function loader:
// (1) You'll need to disable default Vulkan function prototypes.
//     We provide a '#define IMGUI_IMPL_VULKAN_NO_PROTOTYPES' convenience configuration flag.
//     In order to make sure this is visible from the imgui_impl_vulkan.cpp compilation unit:
//     - Add '#define IMGUI_IMPL_VULKAN_NO_PROTOTYPES' in your imconfig.h file
//     - Or as a compilation flag in your build system
//     - Or uncomment here (not recommended because you'd be modifying imgui sources!)
//     - Do not simply add it in a .cpp file!
// (2) Call ImGui_ImplCGPU_LoadFunctions() before ImGui_ImplCGPU_Init() with your custom function.
// If you have no idea what this is, leave it alone!
//#define IMGUI_IMPL_VULKAN_NO_PROTOTYPES

// Vulkan includes
#if defined(IMGUI_IMPL_VULKAN_NO_PROTOTYPES) && !defined(VK_NO_PROTOTYPES)
#define VK_NO_PROTOTYPES
#endif
#include "cgpu/api.h"

// Initialization data, for ImGui_ImplCGPU_Init()
// [Please zero-clear before use!]
struct ImGui_ImplCGPU_InitInfo
{
    CGPUInstanceId                      Instance;
    CGPUDeviceId                        Device;
    CGPUQueueId                         GfxQueue;
    CGPUQueueId                         PresentQueue;
    uint32_t                            ImageCount;             // >= MinImageCount
    CGPURootSignatureId                 RootSig;
    CGPURenderPipelineId                Pipeline;
    // Dynamic Rendering (Optional)
    ECGPUFormat                        ColorAttachmentFormat;  // Required for dynamic rendering

    // Allocation, CGPU
    // const VkAllocationCallbacks*    Allocator;
    // void                            (*CheckVkResultFn)(VkResult err);
};

// Called by user code
IMGUI_IMPL_API bool         ImGui_ImplCGPU_Init(ImGui_ImplCGPU_InitInfo* info);
IMGUI_IMPL_API bool         ImGui_ImplCGPU_PostInit(CGPURootSignatureId root_sig, CGPURenderPipelineId pipeline);
IMGUI_IMPL_API void         ImGui_ImplCGPU_Shutdown();
IMGUI_IMPL_API void         ImGui_ImplCGPU_NewFrame();
IMGUI_IMPL_API void         ImGui_ImplCGPU_RenderDrawData(ImDrawData* draw_data, CGPURenderPassEncoderId rp_encoder, CGPURootSignatureId root_sig, CGPURenderPipelineId pipeline);
IMGUI_IMPL_API bool         ImGui_ImplCGPU_CreateFontsTexture(CGPUQueueId queue, CGPURootSignatureId root_sig);
IMGUI_IMPL_API void         ImGui_ImplCGPU_DestroyFontUploadObjects();
IMGUI_IMPL_API void         ImGui_ImplCGPU_SetMinImageCount(uint32_t min_image_count); // To override MinImageCount after initialization (e.g. if swap chain is recreated)

struct ImGui_ImplCGPU_FrameRenderBuffers
{
    size_t        VertexBufferSize;
    size_t        IndexBufferSize;
    CGPUBufferId            VertexBuffer;
    CGPUBufferId            IndexBuffer;
};

struct ImGui_ImplCGPU_WindowRenderBuffers
{
    uint32_t            Index;
    uint32_t            Count;
    ImGui_ImplCGPU_FrameRenderBuffers* FrameRenderBuffers;
};

struct RenderWindow;
struct ImGui_Arena_ViewportData
{
    RenderWindow* window;

    ImGui_ImplCGPU_WindowRenderBuffers RenderBuffers;

    ImGui_Arena_ViewportData() { memset(&RenderBuffers, 0, sizeof(RenderBuffers)); }
};

#endif // #ifndef IMGUI_DISABLE
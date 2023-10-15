#include "imgui.h"
#include <vcruntime.h>
#ifndef IMGUI_DISABLE
#include "imgui_impl_cgpu.h"
#include <stdio.h>

// Visual Studio warnings
#ifdef _MSC_VER
#pragma warning (disable: 4127) // condition expression is constant
#endif

struct ImGui_ImplCGPU_FrameRenderBuffers
{
    size_t        VertexBufferSize;
    size_t        IndexBufferSize;
    CGPUBufferId            VertexBuffer;
    CGPUBufferId            IndexBuffer;
};

// Each viewport will hold 1 ImGui_ImplVulkanH_WindowRenderBuffers
// [Please zero-clear before use!]
struct ImGui_ImplCGPU_WindowRenderBuffers
{
    uint32_t            Index;
    uint32_t            Count;
    ImGui_ImplCGPU_FrameRenderBuffers*   FrameRenderBuffers;
};

void ImGui_ImplCGPUH_DestroyWindowRenderBuffers(CGPUDeviceId device, ImGui_ImplCGPU_WindowRenderBuffers* buffers);

// Vulkan data
struct ImGui_ImplCGPU_Data
{
    ImGui_ImplCGPU_InitInfo   CGPUInitInfo;

    CGPUTextureId                     FontImage;
    CGPUTextureViewId                 FontView;
    CGPUSamplerId                     FontSampler;
    CGPUDescriptorSetId               FontDescriptorSet;

    ImGui_ImplCGPU_WindowRenderBuffers MainWindowRenderBuffers;

    ImGui_ImplCGPU_Data()
    {
        memset((void*)this, 0, sizeof(*this));
    }
};

//-----------------------------------------------------------------------------
// FUNCTIONS
//-----------------------------------------------------------------------------

// Backend data stored in io.BackendRendererUserData to allow support for multiple Dear ImGui contexts
// It is STRONGLY preferred that you use docking branch with multi-viewports (== single Dear ImGui context + multiple windows) instead of multiple Dear ImGui contexts.
// FIXME: multi-context support is not tested and probably dysfunctional in this backend.
static ImGui_ImplCGPU_Data* ImGui_ImplCGPU_GetBackendData()
{
    return ImGui::GetCurrentContext() ? (ImGui_ImplCGPU_Data*)ImGui::GetIO().BackendRendererUserData : nullptr;
}

static void CreateOrResizeBuffer(CGPUBufferId& buffer, size_t& p_buffer_size, size_t new_size, CGPUResourceTypes resourceType, ECGPUResourceState state)
{
    ImGui_ImplCGPU_Data* bd = ImGui_ImplCGPU_GetBackendData();
    ImGui_ImplCGPU_InitInfo* v = &bd->CGPUInitInfo;
    if (buffer != CGPU_NULL)
        cgpu_free_buffer(buffer);

    CGPUBufferDescriptor buffer_desc = {
        .size = new_size,
        .name = u8"DataBuffer",
        .descriptors = resourceType,
        .memory_usage = CGPU_MEM_USAGE_GPU_ONLY,
        .flags = CGPU_BCF_HOST_VISIBLE,
        .start_state = state,
    };
    buffer = cgpu_create_buffer(v->Device, &buffer_desc);
    p_buffer_size = buffer->info->size;
}

static void ImGui_ImplCGPU_SetupRenderState(ImDrawData* draw_data, CGPURenderPipelineId pipeline, CGPURootSignatureId root_sig, CGPURenderPassEncoderId rp_encoder, ImGui_ImplCGPU_FrameRenderBuffers* rb, int fb_width, int fb_height)
{
    ImGui_ImplCGPU_Data* bd = ImGui_ImplCGPU_GetBackendData();

    // Bind pipeline:
    {
        cgpu_render_encoder_bind_pipeline(rp_encoder, pipeline);
    }

    // Bind Vertex And Index Buffer:
    if (draw_data->TotalVtxCount > 0)
    {
        //VkBuffer vertex_buffers[1] = { rb->VertexBuffer };
        //VkDeviceSize vertex_offset[1] = { 0 };
        const uint32_t vert_stride = sizeof(ImDrawVert);
        cgpu_render_encoder_bind_vertex_buffers(rp_encoder, 1, &rb->VertexBuffer, &vert_stride, nullptr);
        cgpu_render_encoder_bind_index_buffer(rp_encoder, rb->IndexBuffer, sizeof(uint16_t), 0);
    }

    // Setup viewport:
    {
		cgpu_render_encoder_set_viewport(rp_encoder,
			0.0f, 0.0f,
			(float)fb_width, (float)fb_height,
			0.f, 1.f);
    }

    // Setup scale and translation:
    // Our visible imgui space lies from draw_data->DisplayPps (top left) to draw_data->DisplayPos+data_data->DisplaySize (bottom right). DisplayPos is (0,0) for single viewport apps.
    {
        float scale[2];
        scale[0] = 2.0f / draw_data->DisplaySize.x;
        scale[1] = -2.0f / draw_data->DisplaySize.y;
        float translate[2];
        translate[0] = -1.0f;
        translate[1] = +1.0f;
        struct ConstantData
        {
            float scale[2];
            float translate[2];
        } data;
        data = {
            .scale = { scale[0], scale[1] },
            .translate = { translate[0], translate[1] },
        };
        cgpu_render_encoder_push_constants(rp_encoder, root_sig, u8"pc", &data);
    }
}

// Render function
void ImGui_ImplCGPU_RenderDrawData(ImDrawData* draw_data, CGPURenderPassEncoderId rp_encoder, CGPURootSignatureId root_sig, CGPURenderPipelineId pipeline)
{
    // Avoid rendering when minimized, scale coordinates for retina displays (screen coordinates != framebuffer coordinates)
    int fb_width = (int)(draw_data->DisplaySize.x * draw_data->FramebufferScale.x);
    int fb_height = (int)(draw_data->DisplaySize.y * draw_data->FramebufferScale.y);
    if (fb_width <= 0 || fb_height <= 0)
        return;

    ImGui_ImplCGPU_Data* bd = ImGui_ImplCGPU_GetBackendData();
    ImGui_ImplCGPU_InitInfo* v = &bd->CGPUInitInfo;
//     if (pipeline == CGPU_NULLPTR)
//         pipeline = bd->Pipeline;

    // Allocate array to store enough vertex/index buffers
    ImGui_ImplCGPU_WindowRenderBuffers* wrb = &bd->MainWindowRenderBuffers;
    if (wrb->FrameRenderBuffers == nullptr)
    {
        wrb->Index = 0;
        wrb->Count = v->ImageCount;
        wrb->FrameRenderBuffers = (ImGui_ImplCGPU_FrameRenderBuffers*)IM_ALLOC(sizeof(ImGui_ImplCGPU_FrameRenderBuffers) * wrb->Count);
        memset(wrb->FrameRenderBuffers, 0, sizeof(ImGui_ImplCGPU_FrameRenderBuffers) * wrb->Count);
    }
    IM_ASSERT(wrb->Count == v->ImageCount);
    wrb->Index = (wrb->Index + 1) % wrb->Count;
    ImGui_ImplCGPU_FrameRenderBuffers* rb = &wrb->FrameRenderBuffers[wrb->Index];

    if (draw_data->TotalVtxCount > 0)
    {
        // Create or resize the vertex/index buffers
        size_t vertex_size = draw_data->TotalVtxCount * sizeof(ImDrawVert);
        size_t index_size = draw_data->TotalIdxCount * sizeof(ImDrawIdx);
        if (rb->VertexBuffer == CGPU_NULL || rb->VertexBufferSize < vertex_size)
            CreateOrResizeBuffer(rb->VertexBuffer, rb->VertexBufferSize, vertex_size, CGPU_RESOURCE_TYPE_VERTEX_BUFFER, CGPU_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER);
        if (rb->IndexBuffer == CGPU_NULL || rb->IndexBufferSize < index_size)
            CreateOrResizeBuffer(rb->IndexBuffer, rb->IndexBufferSize, index_size, CGPU_RESOURCE_TYPE_INDEX_BUFFER, CGPU_RESOURCE_STATE_INDEX_BUFFER);

        // Upload vertex/index data into a single contiguous GPU buffer
        ImDrawVert* vtx_dst = nullptr;
        ImDrawIdx* idx_dst = nullptr;

        CGPUBufferRange range = { .offset = 0, .size = rb->VertexBufferSize };
        cgpu_map_buffer(rb->VertexBuffer, &range);
        vtx_dst = (ImDrawVert*)rb->VertexBuffer->info->cpu_mapped_address;

        range = { .offset = 0, .size = rb->IndexBufferSize };
        cgpu_map_buffer(rb->IndexBuffer, &range);
        idx_dst = (ImDrawIdx*)rb->IndexBuffer->info->cpu_mapped_address;

        for (int n = 0; n < draw_data->CmdListsCount; n++)
        {
            const ImDrawList* cmd_list = draw_data->CmdLists[n];
            memcpy(vtx_dst, cmd_list->VtxBuffer.Data, cmd_list->VtxBuffer.Size * sizeof(ImDrawVert));
            memcpy(idx_dst, cmd_list->IdxBuffer.Data, cmd_list->IdxBuffer.Size * sizeof(ImDrawIdx));
            vtx_dst += cmd_list->VtxBuffer.Size;
            idx_dst += cmd_list->IdxBuffer.Size;
        }

        cgpu_unmap_buffer(rb->VertexBuffer);
        cgpu_unmap_buffer(rb->IndexBuffer);
    }

    // Setup desired Vulkan state
    ImGui_ImplCGPU_SetupRenderState(draw_data, pipeline, root_sig, rp_encoder, rb, fb_width, fb_height);

    // Will project scissor/clipping rectangles into framebuffer space
    ImVec2 clip_off = draw_data->DisplayPos;         // (0,0) unless using multi-viewports
    ImVec2 clip_scale = draw_data->FramebufferScale; // (1,1) unless using retina display which are often (2,2)

    // Render command lists
    // (Because we merged all buffers into a single one, we maintain our own offset into them)
    int global_vtx_offset = 0;
    int global_idx_offset = 0;
    for (int n = 0; n < draw_data->CmdListsCount; n++)
    {
        const ImDrawList* cmd_list = draw_data->CmdLists[n];
        for (int cmd_i = 0; cmd_i < cmd_list->CmdBuffer.Size; cmd_i++)
        {
            const ImDrawCmd* pcmd = &cmd_list->CmdBuffer[cmd_i];
            if (pcmd->UserCallback != nullptr)
            {
                // User callback, registered via ImDrawList::AddCallback()
                // (ImDrawCallback_ResetRenderState is a special callback value used by the user to request the renderer to reset render state.)
                if (pcmd->UserCallback == ImDrawCallback_ResetRenderState)
                    ImGui_ImplCGPU_SetupRenderState(draw_data, pipeline, root_sig, rp_encoder, rb, fb_width, fb_height);
                else
                    pcmd->UserCallback(cmd_list, pcmd);
            }
            else
            {
                // Project scissor/clipping rectangles into framebuffer space
                ImVec2 clip_min((pcmd->ClipRect.x - clip_off.x) * clip_scale.x, (pcmd->ClipRect.y - clip_off.y) * clip_scale.y);
                ImVec2 clip_max((pcmd->ClipRect.z - clip_off.x) * clip_scale.x, (pcmd->ClipRect.w - clip_off.y) * clip_scale.y);

                // Clamp to viewport as vkCmdSetScissor() won't accept values that are off bounds
                if (clip_min.x < 0.0f) { clip_min.x = 0.0f; }
                if (clip_min.y < 0.0f) { clip_min.y = 0.0f; }
                if (clip_max.x > fb_width) { clip_max.x = (float)fb_width; }
                if (clip_max.y > fb_height) { clip_max.y = (float)fb_height; }
                if (clip_max.x <= clip_min.x || clip_max.y <= clip_min.y)
                    continue;

                // Apply scissor/clipping rectangle
                cgpu_render_encoder_set_scissor(rp_encoder, (clip_min.x), (clip_min.y), (clip_max.x - clip_min.x), (clip_max.y - clip_min.y));

                // // Bind DescriptorSet with font or user texture
                // VkDescriptorSet desc_set[1] = { (VkDescriptorSet)pcmd->TextureId };
                // if (sizeof(ImTextureID) < sizeof(ImU64))
                // {
                //     // We don't support texture switches if ImTextureID hasn't been redefined to be 64-bit. Do a flaky check that other textures haven't been used.
                //     IM_ASSERT(pcmd->TextureId == (ImTextureID)bd->FontDescriptorSet);
                //     desc_set[0] = bd->FontDescriptorSet;
                // }
                // vkCmdBindDescriptorSets(command_buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, bd->PipelineLayout, 0, 1, desc_set, 0, nullptr);
                cgpu_render_encoder_bind_descriptor_set(rp_encoder, bd->FontDescriptorSet);

                // Draw
                cgpu_render_encoder_draw_indexed(rp_encoder, pcmd->ElemCount, pcmd->IdxOffset + global_idx_offset, pcmd->VtxOffset + global_vtx_offset);
            }
        }
        global_idx_offset += cmd_list->IdxBuffer.Size;
        global_vtx_offset += cmd_list->VtxBuffer.Size;
    }

    // Note: at this point both vkCmdSetViewport() and vkCmdSetScissor() have been called.
    // Our last values will leak into user/application rendering IF:
    // - Your app uses a pipeline with VK_DYNAMIC_STATE_VIEWPORT or VK_DYNAMIC_STATE_SCISSOR dynamic state
    // - And you forgot to call vkCmdSetViewport() and vkCmdSetScissor() yourself to explicitly set that state.
    // If you use VK_DYNAMIC_STATE_VIEWPORT or VK_DYNAMIC_STATE_SCISSOR you are responsible for setting the values before rendering.
    // In theory we should aim to backup/restore those values but I am not sure this is possible.
    // We perform a call to vkCmdSetScissor() to set back a full viewport which is likely to fix things for 99% users but technically this is not perfect. (See github #4644)
    cgpu_render_encoder_set_scissor(rp_encoder, 0, 0, fb_width, fb_height);
}

bool ImGui_ImplCGPU_CreateFontsTexture(CGPUQueueId queue, CGPURootSignatureId root_sig)
{
    ImGuiIO& io = ImGui::GetIO();
    ImGui_ImplCGPU_Data* bd = ImGui_ImplCGPU_GetBackendData();
    ImGui_ImplCGPU_InitInfo* v = &bd->CGPUInitInfo;

    unsigned char* pixels;
    int width, height;
    io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);
    size_t upload_size = width * height * 4 * sizeof(char);

    CGPUTextureDescriptor font_texture_desc = 
    {
        .name = u8"ImGui Default Font Texture",
        .width = (uint64_t)width,
        .height = (uint64_t)height,
        .depth = 1,
        .array_size = 1,
        .format = CGPU_FORMAT_R8G8B8A8_UNORM,
        .mip_levels = 1,
        .owner_queue = queue,
        .start_state = CGPU_RESOURCE_STATE_COPY_DEST,
        .descriptors = CGPU_RESOURCE_TYPE_TEXTURE,
    };

    bd->FontImage = cgpu_create_texture(v->Device, &font_texture_desc);

    CGPUCommandPoolDescriptor cmd_pool_desc = {};
    CGPUCommandBufferDescriptor cmd_desc = {};
    CGPUBufferDescriptor upload_buffer_desc = {};
    upload_buffer_desc.name = u8"IMGUI_FontUploadBuffer";
    upload_buffer_desc.flags = CGPU_BCF_PERSISTENT_MAP_BIT;
    upload_buffer_desc.descriptors = CGPU_RESOURCE_TYPE_NONE;
    upload_buffer_desc.memory_usage = CGPU_MEM_USAGE_CPU_ONLY;
    upload_buffer_desc.size = upload_size;
    CGPUBufferId tex_upload_buffer = cgpu_create_buffer(queue->device, &upload_buffer_desc);
    {
        memcpy(tex_upload_buffer->info->cpu_mapped_address, pixels, upload_size);
    }
    auto cpy_cmd_pool = cgpu_create_command_pool(queue, &cmd_pool_desc);
    auto cpy_cmd = cgpu_create_command_buffer(cpy_cmd_pool, &cmd_desc);
    cgpu_cmd_begin(cpy_cmd);
    CGPUBufferToTextureTransfer b2t = {};
    b2t.src = tex_upload_buffer;
    b2t.src_offset = 0;
    b2t.dst = bd->FontImage;
    b2t.dst_subresource.mip_level = 0;
    b2t.dst_subresource.base_array_layer = 0;
    b2t.dst_subresource.layer_count = 1;
    cgpu_cmd_transfer_buffer_to_texture(cpy_cmd, &b2t);
    CGPUTextureBarrier srv_barrier = {};
    srv_barrier.texture = bd->FontImage;
    srv_barrier.src_state = CGPU_RESOURCE_STATE_COPY_DEST;
    srv_barrier.dst_state = CGPU_RESOURCE_STATE_SHADER_RESOURCE;
    CGPUResourceBarrierDescriptor barrier_desc1 = {};
    barrier_desc1.texture_barriers = &srv_barrier;
    barrier_desc1.texture_barriers_count = 1;
    cgpu_cmd_resource_barrier(cpy_cmd, &barrier_desc1);
    cgpu_cmd_end(cpy_cmd);
    CGPUQueueSubmitDescriptor cpy_submit = {};
    cpy_submit.cmds = &cpy_cmd;
    cpy_submit.cmds_count = 1;
    cgpu_submit_queue(queue, &cpy_submit);
    cgpu_wait_queue_idle(queue);
    cgpu_free_command_buffer(cpy_cmd);
    cgpu_free_command_pool(cpy_cmd_pool);
    cgpu_free_buffer(tex_upload_buffer);
    io.Fonts->TexID = (ImTextureID)(intptr_t)&bd->FontImage;

    CGPUTextureViewDescriptor view_desc = {
        .texture = bd->FontImage,
        .format = CGPU_FORMAT_R8G8B8A8_UNORM,
        .usages = CGPU_TVU_SRV,
        .aspects = CGPU_TVA_COLOR,
    };
    bd->FontView = cgpu_create_texture_view(v->Device, &view_desc);

    CGPUSamplerDescriptor sampler_desc = {
        .min_filter = CGPU_FILTER_TYPE_LINEAR,
        .mag_filter = CGPU_FILTER_TYPE_LINEAR,
        .mipmap_mode = CGPU_MIPMAP_MODE_LINEAR,
        .address_u = CGPU_ADDRESS_MODE_REPEAT,
        .address_v = CGPU_ADDRESS_MODE_REPEAT,
        .address_w = CGPU_ADDRESS_MODE_REPEAT,
        .mip_lod_bias = 0,
        .max_anisotropy = 1,
    };
    bd->FontSampler = cgpu_create_sampler(v->Device, &sampler_desc);

    CGPUDescriptorSetDescriptor set_desc = {
        .root_signature = root_sig,
        .set_index = 0,
    };
    bd->FontDescriptorSet = cgpu_create_descriptor_set(v->Device, &set_desc);

    CGPUDescriptorData datas[2];
    datas[0] = {
        .name = u8"fontTexture",
        .binding = 0,
        .binding_type = CGPU_RESOURCE_TYPE_TEXTURE,
        .textures = &bd->FontView,
        .count = 1,
    };
    datas[1] = {
        .name = u8"fontSampler",
        .binding = 0,
        .binding_type = CGPU_RESOURCE_TYPE_SAMPLER,
        .samplers = &bd->FontSampler,
        .count = 1,
    };

    cgpu_update_descriptor_set(bd->FontDescriptorSet, datas, 2);

    return true;
}

void    ImGui_ImplCGPU_DestroyDeviceObjects()
{
    ImGui_ImplCGPU_Data* bd = ImGui_ImplCGPU_GetBackendData();
    ImGui_ImplCGPU_InitInfo* v = &bd->CGPUInitInfo;
    ImGui_ImplCGPUH_DestroyWindowRenderBuffers(v->Device, &bd->MainWindowRenderBuffers);

    if (bd->FontView) { cgpu_free_texture_view(bd->FontView); bd->FontView = CGPU_NULLPTR; }
    if (bd->FontImage) { cgpu_free_texture(bd->FontImage); bd->FontImage = CGPU_NULLPTR; }
    if (bd->FontSampler) { cgpu_free_sampler(bd->FontSampler); bd->FontSampler = CGPU_NULLPTR; }
    if (bd->FontDescriptorSet) { cgpu_free_descriptor_set(bd->FontDescriptorSet); bd->FontDescriptorSet = CGPU_NULLPTR; }
}

bool    ImGui_ImplCGPU_Init(ImGui_ImplCGPU_InitInfo* info)
{
    ImGuiIO& io = ImGui::GetIO();
    IM_ASSERT(io.BackendRendererUserData == nullptr && "Already initialized a renderer backend!");

    // Setup backend capabilities flags
    ImGui_ImplCGPU_Data* bd = IM_NEW(ImGui_ImplCGPU_Data)();
    io.BackendRendererUserData = (void*)bd;
    io.BackendRendererName = "imgui_impl_cgpu";
    io.BackendFlags |= ImGuiBackendFlags_RendererHasVtxOffset;  // We can honor the ImDrawCmd::VtxOffset field, allowing for large meshes.

    IM_ASSERT(info->Instance != CGPU_NULL);
    IM_ASSERT(info->Device != CGPU_NULL);

    bd->CGPUInitInfo = *info;

    return true;
}

void ImGui_ImplCGPU_Shutdown()
{
    ImGui_ImplCGPU_Data* bd = ImGui_ImplCGPU_GetBackendData();
    IM_ASSERT(bd != nullptr && "No renderer backend to shutdown, or already shutdown?");
    ImGuiIO& io = ImGui::GetIO();

    ImGui_ImplCGPU_DestroyDeviceObjects();
    io.BackendRendererName = nullptr;
    io.BackendRendererUserData = nullptr;
    io.BackendFlags &= ~ImGuiBackendFlags_RendererHasVtxOffset;
    IM_DELETE(bd);
}

void ImGui_ImplCGPU_NewFrame()
{
    ImGui_ImplCGPU_Data* bd = ImGui_ImplCGPU_GetBackendData();
    IM_ASSERT(bd != nullptr && "Did you call ImGui_ImplCGPU_Init()?");
    IM_UNUSED(bd);
}

void ImGui_ImplCGPU_DestroyFrameRenderBuffers(CGPUDeviceId device, ImGui_ImplCGPU_FrameRenderBuffers* buffers)
{
    if (buffers->VertexBuffer) { cgpu_free_buffer(buffers->VertexBuffer); buffers->VertexBuffer = CGPU_NULLPTR; }
    if (buffers->IndexBuffer) { cgpu_free_buffer(buffers->IndexBuffer); buffers->IndexBuffer = CGPU_NULLPTR; }
    buffers->VertexBufferSize = 0;
    buffers->IndexBufferSize = 0;
}

void ImGui_ImplCGPUH_DestroyWindowRenderBuffers(CGPUDeviceId device, ImGui_ImplCGPU_WindowRenderBuffers* buffers)
{
    for (uint32_t n = 0; n < buffers->Count; n++)
        ImGui_ImplCGPU_DestroyFrameRenderBuffers(device, &buffers->FrameRenderBuffers[n]);
    IM_FREE(buffers->FrameRenderBuffers);
    buffers->FrameRenderBuffers = nullptr;
    buffers->Index = 0;
    buffers->Count = 0;
}
#endif // #ifndef IMGUI_DISABLE
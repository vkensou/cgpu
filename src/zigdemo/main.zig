const std = @import("std");
const cgpu = @import("cgpu");
const sdl = @import("zsdl3");
const imgui = @import("imgui");

fn readFile(allocator: std.mem.Allocator, filepath: [:0]const u8) !std.ArrayList(u8) {
    const cwd = std.fs.cwd();
    const file = try cwd.openFile(filepath, .{});
    defer file.close();

    const file_state = try file.stat();
    var content = std.ArrayList(u8).init(allocator);
    errdefer content.deinit();
    try content.resize(file_state.size);

    const size = try file.readAll(content.items);
    std.log.info("load file: {s}, size: {d}", .{ filepath, size });

    return content;
}

fn loadShader(device: cgpu.DeviceId, allocator: std.mem.Allocator, vs_filepath: [:0]const u8, ps_filepath: [:0]const u8) !Shader {
    const vs_content = try readFile(allocator, vs_filepath);
    defer vs_content.deinit();
    const vs_shader = device.createShaderLibrary(&.{ .name = "VertexShaderLibrary", .code_size = vs_content.items.len, .p_code = vs_content.items.ptr, .stage = .{ .vertex = true }, .reflection_only = false });

    const ps_content = try readFile(allocator, ps_filepath);
    defer ps_content.deinit();
    const ps_shader = device.createShaderLibrary(&.{ .name = "FragmentShaderLibrary", .code_size = ps_content.items.len, .p_code = ps_content.items.ptr, .stage = .{ .fragment = true }, .reflection_only = false });

    const shader_entries = [_]cgpu.ShaderEntryDescriptor{
        cgpu.ShaderEntryDescriptor{ .entry = "main", .stage = .{ .vertex = true }, .library = vs_shader, .p_constants = null, .constant_count = 0 },
        cgpu.ShaderEntryDescriptor{ .entry = "main", .stage = .{ .fragment = true }, .library = ps_shader, .p_constants = null, .constant_count = 0 },
    };
    const root_sig_descriptor = cgpu.RootSignatureDescriptor{ .shader_count = shader_entries.len, .p_shaders = &shader_entries, .static_sampler_count = 0, .p_static_samplers = null, .p_static_sampler_names = null, .push_constant_count = 0, .p_push_constant_names = null, .pool = null };
    const root_sig = device.createRootSignature(&root_sig_descriptor).?;
    return .{
        .root_sig = root_sig,
        .vs_shader = shader_entries[0],
        .ps_shader = shader_entries[1],
    };
}

const Shader = struct {
    root_sig: cgpu.RootSignatureId,
    vs_shader: cgpu.ShaderEntryDescriptor,
    ps_shader: cgpu.ShaderEntryDescriptor,
};

fn freeShader(device: cgpu.DeviceId, shader: *const Shader) void {
    device.freeShaderLibrary(shader.vs_shader.library);
    device.freeShaderLibrary(shader.ps_shader.library);
    device.freeRootSignature(shader.root_sig);
}

const WaitUploadTexture = struct {
    stage_buffer: cgpu.BufferId,
    texture: cgpu.TextureId,
};

const WaitToFree = struct {
    buffer: cgpu.BufferId,
    wait_frame: i32,
};

const WaitUploadTextureQueue = struct {
    queue: std.fifo.LinearFifo(WaitUploadTexture, .Dynamic),
    device: cgpu.DeviceId,
    allocator: std.mem.Allocator,
    wait_to_frees: std.ArrayList(WaitToFree),

    pub fn init(allocator: std.mem.Allocator, device: cgpu.DeviceId) WaitUploadTextureQueue {
        return .{
            .queue = std.fifo.LinearFifo(WaitUploadTexture, .Dynamic).init(allocator),
            .device = device,
            .allocator = allocator,
            .wait_to_frees = std.ArrayList(WaitToFree).init(allocator),
        };
    }

    pub fn deinit(self: *WaitUploadTextureQueue) void {
        while (self.queue.count > 0) {
            const item = self.queue.readItem().?;
            self.device.freeBuffer(item.stage_buffer);
        }

        for (self.wait_to_frees.items) |wait_to_free| {
            self.device.freeBuffer(wait_to_free.buffer);
        }
        self.wait_to_frees.deinit();

        self.queue.deinit();
    }

    pub fn upload(self: *WaitUploadTextureQueue, texture: cgpu.TextureId, data: []const u8) !void {
        const stage_descriptor = cgpu.BufferDescriptor{
            .size = data.len,
            .count_buffer = null,
            .name = "",
            .descriptors = .{},
            .memory_usage = .cpu_only,
            .format = .undefined,
            .flags = .{ .persistent_map = true },
            .first_element = 0,
            .element_count = 0,
            .element_stride = 0,
            .owner_queue = null,
            .start_state = .{},
            .prefer_on_device = false,
            .prefer_on_host = false,
        };
        const buffer = self.device.createBuffer(&stage_descriptor).?;
        @memcpy(buffer.info.*.cpu_mapped_address, data);
        try self.queue.writeItem(.{ .stage_buffer = buffer, .texture = texture });
    }

    pub fn do_upload(self: *WaitUploadTextureQueue, cmd: cgpu.CommandBufferId) !void {
        var i: i32 = @as(i32, @intCast(self.wait_to_frees.items.len)) - 1;
        while (i >= 0) : (i -= 1) {
            var wait_to_free = self.wait_to_frees.items[@intCast(i)];
            if (wait_to_free.wait_frame <= 0) {
                self.device.freeBuffer(wait_to_free.buffer);
                _ = self.wait_to_frees.swapRemove(@intCast(i));
            } else {
                wait_to_free.wait_frame -= 1;
                self.wait_to_frees.items[@intCast(i)] = wait_to_free;
            }
        }

        while (self.queue.count > 0) {
            const item = self.queue.readItem().?;
            const buffer_barrier: cgpu.BufferBarrier = .{ .buffer = item.stage_buffer, .src_state = cgpu.ResourceState{}, .dst_state = cgpu.ResourceState{ .copy_source = true }, .queue_acquire = 0, .queue_release = 0, .queue_type = .graphics };
            const texture_barrier: cgpu.TextureBarrier = .{ .texture = item.texture, .src_state = cgpu.ResourceState{}, .dst_state = cgpu.ResourceState{ .copy_dest = true }, .queue_acquire = 0, .queue_release = 0, .queue_type = .graphics, .subresource_barrier = 0, .mip_level = 0, .array_layer = 0 };
            const barrier_descriptor: cgpu.ResourceBarrierDescriptor = .{ .buffer_barrier_count = 1, .p_buffer_barriers = &[_]cgpu.BufferBarrier{buffer_barrier}, .texture_barrier_count = 1, .p_texture_barriers = &[_]cgpu.TextureBarrier{texture_barrier} };
            cmd.resourceBarrier(&barrier_descriptor);

            cmd.transferBufferToTexture(&.{ .src = item.stage_buffer, .src_offset = 0, .dst = item.texture, .dst_subresource = .{ .aspects = .{ .color = true }, .mip_level = 0, .base_array_layer = 0, .layer_count = 1 } });

            const texture_barrier2: cgpu.TextureBarrier = .{ .texture = item.texture, .src_state = cgpu.ResourceState{ .copy_dest = true }, .dst_state = cgpu.ResourceState.shader_resource, .queue_acquire = 0, .queue_release = 0, .queue_type = .graphics, .subresource_barrier = 0, .mip_level = 0, .array_layer = 0 };
            const barrier_descriptor2: cgpu.ResourceBarrierDescriptor = .{ .buffer_barrier_count = 0, .p_buffer_barriers = &[_]cgpu.BufferBarrier{}, .texture_barrier_count = 1, .p_texture_barriers = &[_]cgpu.TextureBarrier{texture_barrier2} };
            cmd.resourceBarrier(&barrier_descriptor2);

            try self.wait_to_frees.append(.{ .buffer = item.stage_buffer, .wait_frame = 3 });
        }
    }
};

const WaitUploadBuffer = struct {
    stage_buffer: cgpu.Buffer,
    buffer: cgpu.Buffer,
};

const FrameData = struct {
    swapchain_prepared_semaphore: cgpu.SemaphoreId,
    inflight_fence: cgpu.FenceId,
    cmdpool: cgpu.CommandPoolId,
    cmd: cgpu.CommandBufferId,
};

const SwapchainInfo = struct {
    back_buffer_texture: cgpu.TextureId,
    back_buffer_texture_view: cgpu.TextureViewId,
    framebuffer: cgpu.FramebufferId,
};

pub fn main() !void {
    var gpa = std.heap.GeneralPurposeAllocator(.{}){};
    defer {
        if (gpa.deinit() == .leak) @panic("memory leak!");
    }
    const allocator = gpa.allocator();

    try sdl.init(.{ .events = true });
    defer sdl.quit();

    const prop = try sdl.createProperties();
    defer sdl.destroyProperties(prop);
    _ = try sdl.setStringProperty(prop, sdl.prop_window_create_title_string, "cgpu demo");
    _ = try sdl.setFloatProperty(prop, sdl.prop_window_create_x_number, sdl.Window.pos_centered);
    _ = try sdl.setFloatProperty(prop, sdl.prop_window_create_y_number, sdl.Window.pos_centered);
    _ = try sdl.setFloatProperty(prop, sdl.prop_window_create_width_number, 800);
    _ = try sdl.setFloatProperty(prop, sdl.prop_window_create_height_number, 600);
    _ = try sdl.setBooleanProperty(prop, sdl.prop_window_create_external_graphics_context_boolean, true);

    const window = try sdl.createWindowWithProperties(prop);
    defer window.destroy();

    var ww: i32 = 0;
    var wh: i32 = 0;
    try window.getSize(&ww, &wh);

    const w: u32 = @intCast(ww);
    const h: u32 = @intCast(wh);
    const fw: f32 = @floatFromInt(w);
    const fh: f32 = @floatFromInt(h);

    imgui.init(allocator);
    defer imgui.deinit();

    var gui_style = imgui.Style.init();
    imgui.styleColorsDark(&gui_style);

    imgui.backend.init(window);
    defer imgui.backend.deinit();

    const instance_descriptor = cgpu.InstanceDescriptor{ .backend = .vulkan, .enable_debug_layer = true, .enable_gpu_based_validation = true, .enable_set_name = true, .logger = .{}, .allocator = .{} };

    const instance = cgpu.createInstance(&instance_descriptor).?;
    defer cgpu.freeInstance(instance);

    var adapters_count: u32 = 0;
    instance.enumAdapters(&adapters_count, null);
    const adapters = try allocator.alloc(cgpu.AdapterId, adapters_count);
    instance.enumAdapters(&adapters_count, adapters.ptr);
    defer allocator.free(adapters);

    const adapter = adapters[0];

    const queue_group_descriptor = cgpu.QueueGroupDescriptor{
        .queue_count = 1,
        .queue_type = .graphics,
    };
    const device_descriptor = cgpu.DeviceDescriptor{
        .disable_pipeline_cache = false,
        .queue_group_count = 1,
        .p_queue_groups = &queue_group_descriptor,
    };

    const device = adapter.createDevice(&device_descriptor).?;
    defer adapter.freeDevice(device);

    const queue = device.getQueue(.graphics, 0).?;
    defer device.freeQueue(queue);

    const windowProperties = try window.getProperties();
    const hwnd = sdl.getPointerProperty(windowProperties, sdl.prop_window_win32_hwnd_pointer, null);
    if (hwnd == null)
        return error.InitFailed;

    const surface = device.createSurfaceFromNativeView(hwnd.?);
    defer device.freeSurface(surface);

    const swap_chain_descriptor = cgpu.SwapChainDescriptor{
        .present_queue_count = 1,
        .p_present_queues = &[_]cgpu.QueueId{queue},
        .surface = surface,
        .image_count = 3,
        .width = w,
        .height = h,
        .enable_vsync = true,
        .use_flip_swap_effect = false,
        .format = .r8g8b8a8_unorm,
    };
    const swapchain = device.createSwapChain(&swap_chain_descriptor).?;
    defer device.freeSwapChain(swapchain);

    var texture_upload_queue = WaitUploadTextureQueue.init(allocator, device);
    defer texture_upload_queue.deinit();

    const shader = try loadShader(device, allocator, "shaders/hello.vert.spv", "shaders/hello.frag.spv");
    defer freeShader(device, &shader);

    const imgui_shader = try loadShader(device, allocator, "shaders/imgui.vert.spv", "shaders/imgui.frag.spv");
    defer freeShader(device, &imgui_shader);

    const font_tex_info = imgui.io.getFontsTextDataAsRgba32();
    const imgui_font_texture = device.createTexture(&.{
        .name = "",
        .native_handle = null,
        .flags = .{},
        .width = @intCast(font_tex_info.width),
        .height = @intCast(font_tex_info.height),
        .depth = 1,
        .array_size = 1,
        .format = .r8g8b8a8_unorm,
        .mip_levels = 1,
        .sample_count = .{},
        .sample_quality = 0,
        .owner_queue = queue,
        .start_state = .{},
        .descriptors = .{ .texture = true },
        .is_restrict_dedicated = 0,
    }).?;
    defer device.freeTexture(imgui_font_texture);

    const uploaded_data_32: [*]const u32 = font_tex_info.pixels.?;
    const uploaded_data: [*]const u8 = @ptrCast(uploaded_data_32);
    const uploaded_data_slice = uploaded_data[0..@intCast(font_tex_info.width * font_tex_info.height * 4)];
    try texture_upload_queue.upload(imgui_font_texture, uploaded_data_slice);

    const imgui_font_texture_view = device.createTextureView(&.{
        .name = "",
        .texture = imgui_font_texture,
        .format = imgui_font_texture.info.*.format,
        .usages = .{ .srv = true },
        .aspects = .{ .color = true },
        .dims = .@"2d",
        .base_array_layer = 0,
        .array_layer_count = 1,
        .base_mip_level = 0,
        .mip_level_count = @intCast(imgui_font_texture.info.*.mip_levels),
    }).?;
    defer device.freeTextureView(imgui_font_texture_view);

    const imgui_font_texture_sampler = device.createSampler(&.{
        .min_filter = .linear,
        .mag_filter = .linear,
        .mipmap_mode = .linear,
        .address_u = .clamp_to_edge,
        .address_v = .clamp_to_edge,
        .address_w = .clamp_to_edge,
        .mip_lod_bias = 0,
        .max_anisotropy = 1,
        .compare_func = .always,
    }).?;
    defer device.freeSampler(imgui_font_texture_sampler);

    var imgui_vertex_buffers = [3]?cgpu.BufferId{ null, null, null };
    var imgui_index_buffers = [3]?cgpu.BufferId{ null, null, null };
    for (0..3) |i| {
        imgui_vertex_buffers[i] = null;
        imgui_index_buffers[i] = null;
    }
    defer {
        for (0..3) |i| {
            if (imgui_vertex_buffers[i] != null)
                device.freeBuffer(imgui_vertex_buffers[i]);
            if (imgui_index_buffers[i] != null)
                device.freeBuffer(imgui_index_buffers[i]);
        }
    }

    const invalid_color_attachment = std.mem.zeroes(cgpu.ColorAttachment);

    const render_pass_descriptor = cgpu.RenderPassDescriptor{
        .sample_count = .{ .@"1" = true },
        .color_attachments = [_]cgpu.ColorAttachment{ .{ .format = swapchain.back_buffers[0].info.*.format, .load_action = .clear, .store_action = .store }, invalid_color_attachment, invalid_color_attachment, invalid_color_attachment, invalid_color_attachment, invalid_color_attachment, invalid_color_attachment, invalid_color_attachment },
        .depth_stencil = .{ .format = .undefined, .depth_load_action = .load, .depth_store_action = .store, .stencil_load_action = .load, .stencil_store_action = .store },
    };
    const render_pass = device.createRenderPass(&render_pass_descriptor).?;
    defer device.freeRenderPass(render_pass);

    const blend_mode = cgpu.BlendStateDescriptor{
        .attachment_count = 1,
        .p_attachments = &[_]cgpu.BlendAttachmentState{.{
            .enable = true,
            .src_factor = .src_alpha,
            .dst_factor = .one_minus_src_alpha,
            .src_alpha_factor = .src_alpha,
            .dst_alpha_factor = .one_minus_src_alpha,
            .blend_op = .add,
            .blend_alpha_op = .add,
            .color_mask = .{ .r = true, .g = true, .b = true, .a = true },
        }},
        .alpha_to_coverage = false,
        .independent_blend = true,
    };
    const render_pipeline = device.createRenderPipeline(&.{
        .dynamic_state = 0,
        .root_signature = shader.root_sig,
        .vertex_shader = &shader.vs_shader,
        .tesc_shader = null,
        .tese_shader = null,
        .geom_shader = null,
        .fragment_shader = &shader.ps_shader,
        .vertex_layout = null,
        .blend_state = &blend_mode,
        .depth_state = null,
        .rasterizer_state = null,
        .render_pass = render_pass,
        .subpass = 0,
        .render_target_count = 1,
        .sample_count = .{ .@"1" = true },
        .prim_topology = .triangle_list,
    }).?;
    defer device.freeRenderPipeline(render_pipeline);
    const imgui_vertex_layout = cgpu.VertexLayout{ .attribute_count = 3, .p_attributes = &[_]cgpu.VertexAttribute{
        cgpu.VertexAttribute{ .semantic_name = "POSITION", .array_size = 1, .format = .float32x2, .binding = 0, .offset = 0, .elem_stride = @sizeOf(f32) * 2, .rate = .vertex },
        cgpu.VertexAttribute{ .semantic_name = "TEXCOORD", .array_size = 1, .format = .float32x2, .binding = 0, .offset = @sizeOf(f32) * 2, .elem_stride = @sizeOf(f32) * 2, .rate = .vertex },
        cgpu.VertexAttribute{ .semantic_name = "COLOR", .array_size = 1, .format = .unorm8x4, .binding = 0, .offset = @sizeOf(f32) * 4, .elem_stride = @sizeOf(u32), .rate = .vertex },
    } };

    const imgui_blend_mode = cgpu.BlendStateDescriptor{
        .attachment_count = 1,
        .p_attachments = &[_]cgpu.BlendAttachmentState{.{
            .enable = true,
            .src_factor = .src_alpha,
            .dst_factor = .one_minus_src_alpha,
            .src_alpha_factor = .src_alpha,
            .dst_alpha_factor = .one_minus_src_alpha,
            .blend_op = .add,
            .blend_alpha_op = .add,
            .color_mask = .{ .r = true, .g = true, .b = true, .a = true },
        }},
        .alpha_to_coverage = false,
        .independent_blend = true,
    };

    const imgui_rasterizer_state = cgpu.RasterizerStateDescriptor{
        .cull_mode = .{},
        .depth_bias = 0,
        .slope_scaled_depth_bias = 0,
        .fill_mode = .solid,
        .front_face = .counter_clockwise,
        .enable_multi_sample = true,
        .enable_scissor = true,
        .enable_depth_clamp = true,
    };

    const imgui_render_pipeline = device.createRenderPipeline(&.{
        .dynamic_state = 0,
        .root_signature = imgui_shader.root_sig,
        .vertex_shader = &imgui_shader.vs_shader,
        .tesc_shader = null,
        .tese_shader = null,
        .geom_shader = null,
        .fragment_shader = &imgui_shader.ps_shader,
        .vertex_layout = &imgui_vertex_layout,
        .blend_state = &imgui_blend_mode,
        .depth_state = null,
        .rasterizer_state = &imgui_rasterizer_state,
        .render_pass = render_pass,
        .subpass = 0,
        .render_target_count = 1,
        .sample_count = .{ .@"1" = true },
        .prim_topology = .triangle_list,
    }).?;
    defer device.freeRenderPipeline(imgui_render_pipeline);

    const imgui_font_descriptor_set = device.createDescriptorSet(&.{ .root_signature = imgui_shader.root_sig, .set_index = 0 }).?;
    imgui_font_descriptor_set.update(2, &[_]cgpu.DescriptorData{
        .{ .name = null, .binding = 0, .binding_type = .{ .texture = true }, .count = 1, .params = .{ .enable_stencil_resource = false }, .resources = .{ .textures = &[_]cgpu.TextureViewId{imgui_font_texture_view} } },
        .{ .name = null, .binding = 1, .binding_type = .{ .sampler = true }, .count = 1, .params = .{ .enable_stencil_resource = false }, .resources = .{ .samplers = &[_]cgpu.SamplerId{imgui_font_texture_sampler} } },
    });
    defer device.freeDescriptorSet(imgui_font_descriptor_set);
    var frame_datas: [3]FrameData = undefined;
    for (0..frame_datas.len) |i| {
        const cmdpool = queue.createCommandPool(&.{ .name = "" }).?;
        const cmd = cmdpool.createCommandBuffer(&.{ .is_secondary = false }).?;
        frame_datas[i] = .{
            .inflight_fence = device.createFence().?,
            .swapchain_prepared_semaphore = device.createSemaphore().?,
            .cmdpool = cmdpool,
            .cmd = cmd,
        };
    }
    defer {
        for (frame_datas) |frame_data| {
            device.freeFence(frame_data.inflight_fence);
            device.freeSemaphore(frame_data.swapchain_prepared_semaphore);
            frame_data.cmdpool.freeCommandBuffer(frame_data.cmd);
            queue.freeCommandPool(frame_data.cmdpool);
        }
    }

    var swapchain_infos = std.ArrayList(SwapchainInfo).init(allocator);
    try swapchain_infos.ensureTotalCapacity(swapchain.buffer_count);
    for (0..swapchain.buffer_count) |i| {
        const back_buffer_texture = swapchain.back_buffers[i];
        const back_buffer_texture_view = device.createTextureView(&.{ .name = null, .texture = back_buffer_texture, .format = swapchain.back_buffers[i].*.info.*.format, .usages = .{ .rtv_dsv = true }, .aspects = .{ .color = true }, .dims = .@"2d", .base_array_layer = 0, .array_layer_count = 1, .base_mip_level = 0, .mip_level_count = 1 }).?;
        swapchain_infos.appendAssumeCapacity(.{
            .back_buffer_texture = back_buffer_texture,
            .back_buffer_texture_view = back_buffer_texture_view,
            .framebuffer = device.createFramebuffer(&.{ .renderpass = render_pass, .width = w, .height = h, .layers = 1, .attachment_count = 1, .p_attachments = [cgpu.MaxAttachmentCount]cgpu.TextureViewId{ back_buffer_texture_view, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined } }).?,
        });
    }
    defer {
        for (swapchain_infos.items) |info| {
            device.freeTextureView(info.back_buffer_texture_view);
            device.freeFramebuffer(info.framebuffer);
        }
        swapchain_infos.deinit();
    }
    const render_finished_semaphore = device.createSemaphore().?;
    defer device.freeSemaphore(render_finished_semaphore);
    const sampler = device.createSampler(&.{
        .min_filter = .linear,
        .mag_filter = .linear,
        .mipmap_mode = .linear,
        .address_u = .clamp_to_edge,
        .address_v = .clamp_to_edge,
        .address_w = .clamp_to_edge,
        .mip_lod_bias = 0,
        .max_anisotropy = 1,
        .compare_func = .always,
    }).?;
    defer device.freeSampler(sampler);

    var current_frame_index: usize = 0;
    var resource_index: usize = 0;
    var quit = false;
    while (!quit) {
        var event: sdl.Event = undefined;
        while (sdl.pollEvent(&event)) {
            _ = imgui.backend.processEvent(&event);
            if (event.type == .quit) {
                quit = true;
            }
        }

        imgui.backend.newFrame();
        imgui.newFrame();
        imgui.text("hello", .{});
        imgui.showDemoWindow(null);
        imgui.endFrame();

        imgui.render();

        current_frame_index = (current_frame_index + 1) % frame_datas.len;
        resource_index = (resource_index + 1) % 3;
        const current_frame_data = &frame_datas[current_frame_index];
        cgpu.waitFences(&current_frame_data.inflight_fence, 1);
        const next_swapchain_index_result = swapchain.acquireNextImage(&.{ .signal_semaphore = current_frame_data.swapchain_prepared_semaphore, .fence = null });
        if (next_swapchain_index_result == -1) break;
        const current_swapchain_index = next_swapchain_index_result;
        const current_swapchain_info = swapchain_infos.items[current_swapchain_index];

        current_frame_data.cmdpool.reset();
        var cmd = current_frame_data.cmd;
        cmd.begin();

        texture_upload_queue.do_upload(cmd) catch {};
        const imgui_draw_data = imgui.getDrawData();
        if (imgui_draw_data.total_vtx_count > 0) {
            const vertex_buffer_size: u64 = @intCast(imgui_draw_data.total_vtx_count * @sizeOf(imgui.DrawVert));
            if (imgui_vertex_buffers[resource_index] != null and imgui_vertex_buffers[resource_index].?.info.*.size < vertex_buffer_size) {
                device.freeBuffer(imgui_vertex_buffers[resource_index].?);
                imgui_vertex_buffers[resource_index] = null;
            }
            if (imgui_vertex_buffers[resource_index] == null) {
                imgui_vertex_buffers[resource_index] = device.createBuffer(&.{
                    .size = vertex_buffer_size,
                    .count_buffer = null,
                    .name = null,
                    .descriptors = .{ .vertex_buffer = true },
                    .memory_usage = .gpu_only,
                    .format = .undefined,
                    .flags = .{ .host_visible = true },
                    .first_element = 0,
                    .element_count = 0,
                    .element_stride = 0,
                    .owner_queue = null,
                    .start_state = cgpu.ResourceState{},
                    .prefer_on_device = false,
                    .prefer_on_host = false,
                }).?;
            }

            const index_buffer_size: u64 = @intCast(imgui_draw_data.total_idx_count * @sizeOf(imgui.DrawIdx));
            if (imgui_index_buffers[resource_index] != null and imgui_index_buffers[resource_index].?.info.*.size < index_buffer_size) {
                device.freeBuffer(imgui_index_buffers[resource_index].?);
                imgui_index_buffers[resource_index] = null;
            }
            if (imgui_index_buffers[resource_index] == null) {
                imgui_index_buffers[resource_index] = device.createBuffer(&.{
                    .size = index_buffer_size,
                    .count_buffer = null,
                    .name = null,
                    .descriptors = .{ .index_buffer = true },
                    .memory_usage = .gpu_only,
                    .format = .undefined,
                    .flags = .{ .host_visible = true },
                    .first_element = 0,
                    .element_count = 0,
                    .element_stride = 0,
                    .owner_queue = null,
                    .start_state = cgpu.ResourceState{},
                    .prefer_on_device = false,
                    .prefer_on_host = false,
                }).?;
            }

            var imgui_vertex_buffer = imgui_vertex_buffers[resource_index].?;
            var imgui_index_buffer = imgui_index_buffers[resource_index].?;
            imgui_vertex_buffer.map(null);
            imgui_index_buffer.map(null);
            var vertex_buffer_offset: u64 = 0;
            var index_buffer_offset: u64 = 0;
            for (0..@intCast(imgui_draw_data.cmd_lists_count)) |i| {
                const cmd_list = imgui_draw_data.cmd_lists.items[i];
                const ori_vertex_buffer = cmd_list.getVertexBuffer();
                const ori_index_buffer = cmd_list.getIndexBuffer();

                const copied_vertex_buffer_size: u64 = ori_vertex_buffer.len * @sizeOf(imgui.DrawVert);
                const copied_index_buffer_size: u64 = ori_index_buffer.len * @sizeOf(imgui.DrawIdx);

                const imgui_vertex_buffer_mapped_address: [*]u8 = imgui_vertex_buffer.info.*.cpu_mapped_address;
                @memcpy(imgui_vertex_buffer_mapped_address[vertex_buffer_offset .. vertex_buffer_offset + copied_vertex_buffer_size], @as([*]u8, @ptrCast(ori_vertex_buffer.ptr)));
                const imgui_index_buffer_mapped_address: [*]u8 = imgui_index_buffer.info.*.cpu_mapped_address;
                @memcpy(imgui_index_buffer_mapped_address[index_buffer_offset .. index_buffer_offset + copied_index_buffer_size], @as([*]u8, @ptrCast(ori_index_buffer.ptr)));

                vertex_buffer_offset += copied_vertex_buffer_size;
                index_buffer_offset += copied_index_buffer_size;
            }
            imgui_vertex_buffer.unmap();
            imgui_index_buffer.unmap();

            const buffer_barrier1: cgpu.BufferBarrier = .{ .buffer = imgui_vertex_buffer, .src_state = cgpu.ResourceState{}, .dst_state = cgpu.ResourceState{ .vertex_and_constant_buffer = true }, .queue_acquire = 0, .queue_release = 0, .queue_type = .graphics };
            const buffer_barrier2: cgpu.BufferBarrier = .{ .buffer = imgui_index_buffer, .src_state = cgpu.ResourceState{}, .dst_state = cgpu.ResourceState{ .index_buffer = true }, .queue_acquire = 0, .queue_release = 0, .queue_type = .graphics };
            const barrier_descriptor: cgpu.ResourceBarrierDescriptor = .{ .buffer_barrier_count = 1, .p_buffer_barriers = &[_]cgpu.BufferBarrier{ buffer_barrier1, buffer_barrier2 }, .texture_barrier_count = 0, .p_texture_barriers = &[_]cgpu.TextureBarrier{} };
            cmd.resourceBarrier(&barrier_descriptor);
        }

        const texture_barrier: cgpu.TextureBarrier = .{ .texture = current_swapchain_info.back_buffer_texture, .src_state = .{}, .dst_state = cgpu.ResourceState{ .render_target = true }, .queue_acquire = 0, .queue_release = 0, .queue_type = queue._type, .subresource_barrier = 0, .mip_level = 0, .array_layer = 0 };
        const barrier_descriptor: cgpu.ResourceBarrierDescriptor = .{ .buffer_barrier_count = 0, .p_buffer_barriers = &[_]cgpu.BufferBarrier{}, .texture_barrier_count = 1, .p_texture_barriers = &[_]cgpu.TextureBarrier{texture_barrier} };
        cmd.resourceBarrier(&barrier_descriptor);

        const encoder = cmd.beginRenderPass(&.{ .render_pass = render_pass, .framebuffer = current_swapchain_info.framebuffer, .clear_value_count = 1, .p_clear_values = &[_]cgpu.ClearValue{cgpu.ClearValue{ .color = [4]f32{ 0, 0, 0, 1 }, .depth = 1, .stencil = 0, .is_color = true }} }).?;
        encoder.setShadingRate(.full, .pass_through, .pass_through);
        encoder.setViewport(0, 0, fw, fh, 0, 1);
        encoder.setScissor(0, 0, w, h);
        encoder.bindRenderPipeline(render_pipeline);
        encoder.draw(3, 0);

        if (imgui_draw_data.total_vtx_count > 0) {
            encoder.bindRenderPipeline(imgui_render_pipeline);
            encoder.bindVertexBuffers(1, &(imgui_vertex_buffers[resource_index].?), @sizeOf(imgui.DrawVert), 0);
            encoder.bindIndexBuffer(imgui_index_buffers[resource_index].?, @sizeOf(imgui.DrawIdx), 0);
            encoder.bindDescriptorSet(imgui_font_descriptor_set);
            const Data = struct { scale_x: f32, scale_y: f32, translate_x: f32, translate_y: f32 };
            const scale_x = 2 / imgui_draw_data.display_size[0];
            const scale_y = -2 / imgui_draw_data.display_size[1];
            const data = Data{ .scale_x = scale_x, .scale_y = scale_y, .translate_x = -1 - imgui_draw_data.display_pos[0] * scale_x, .translate_y = 1 - imgui_draw_data.display_pos[1] * scale_y };
            encoder.pushConstants(imgui_shader.root_sig, "pc", &data);
            var global_idx_offset: u32 = 0;
            var global_vtx_offset: u32 = 0;
            const clip_offset_x: f32 = imgui_draw_data.display_pos[0];
            const clip_offset_y: f32 = imgui_draw_data.display_pos[1];
            const clip_scale_x: f32 = imgui_draw_data.framebuffer_scale[0];
            const clip_scale_y: f32 = imgui_draw_data.framebuffer_scale[1];
            for (0..@intCast(imgui_draw_data.cmd_lists_count)) |i| {
                const cmd_list = imgui_draw_data.cmd_lists.items[i];
                const imgui_cmd_buffer = cmd_list.getCmdBuffer();
                for (imgui_cmd_buffer) |imgui_cmd| {
                    const clip_min_x: u32 = @intFromFloat(@max(0, (imgui_cmd.clip_rect[0] - clip_offset_x) * clip_scale_x));
                    const clip_min_y: u32 = @intFromFloat(@max(0, (imgui_cmd.clip_rect[1] - clip_offset_y) * clip_scale_y));
                    const clip_max_x: u32 = @intFromFloat(@min(fw, (imgui_cmd.clip_rect[2] - clip_offset_x) * clip_scale_x));
                    const clip_max_y: u32 = @intFromFloat(@min(fh, (imgui_cmd.clip_rect[3] - clip_offset_y) * clip_scale_y));
                    if (clip_min_x > clip_max_x or clip_min_y > clip_max_y) continue;
                    const clip_width: u32 = clip_max_x - clip_min_x;
                    const clip_height: u32 = clip_max_y - clip_min_y;
                    encoder.setScissor(clip_min_x, clip_min_y, clip_width, clip_height);
                    encoder.drawIndexed(@intCast(imgui_cmd.elem_count), imgui_cmd.idx_offset + global_idx_offset, imgui_cmd.vtx_offset + global_vtx_offset);
                }
                global_idx_offset += @intCast(cmd_list.getIndexBufferLength());
                global_vtx_offset += @intCast(cmd_list.getVertexBufferLength());
            }
            encoder.setScissor(0, 0, w, h);
        }

        cmd.endRenderPass(encoder);

        const texture_barrier2: cgpu.TextureBarrier = .{ .texture = current_swapchain_info.back_buffer_texture, .src_state = .{ .render_target = true }, .dst_state = cgpu.ResourceState{ .present = true }, .queue_acquire = 0, .queue_release = 0, .queue_type = queue._type, .subresource_barrier = 0, .mip_level = 0, .array_layer = 0 };
        const barrier_descriptor2: cgpu.ResourceBarrierDescriptor = .{ .buffer_barrier_count = 0, .p_buffer_barriers = &[_]cgpu.BufferBarrier{}, .texture_barrier_count = 1, .p_texture_barriers = &[_]cgpu.TextureBarrier{texture_barrier2} };
        cmd.resourceBarrier(&barrier_descriptor2);

        cmd.end();

        queue.submit(&.{ .cmd_count = 1, .p_cmds = &[_]cgpu.CommandBufferId{cmd}, .signal_fence = current_frame_data.inflight_fence, .wait_semaphore_count = 1, .p_wait_semaphores = &[_]cgpu.SemaphoreId{current_frame_data.swapchain_prepared_semaphore}, .signal_semaphore_count = 1, .p_signal_semaphores = &[_]cgpu.SemaphoreId{render_finished_semaphore} });

        queue.present(&.{ .swapchain = swapchain, .wait_semaphore_count = 1, .p_wait_semaphores = &[_]cgpu.SemaphoreId{render_finished_semaphore}, .index = @intCast(next_swapchain_index_result) });
    }

    queue.waitIdle();
}

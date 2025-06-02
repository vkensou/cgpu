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
    const root_sig_descriptor = cgpu.RootSignatureDescriptor{ .shader_count = 0, .p_shaders = &shader_entries, .static_sampler_count = 0, .p_static_samplers = null, .p_static_sampler_names = null, .push_constant_count = 0, .p_push_constant_names = null, .pool = null };
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
        @memcpy(@as([*]u8, @ptrCast(buffer.info.*.cpu_mapped_address.?)), data);
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
            const barrier_descriptor: cgpu.ResourceBarrierDescriptor = .{ .buffer_barriers = &[_]cgpu.BufferBarrier{buffer_barrier}, .texture_barriers = &[_]cgpu.TextureBarrier{texture_barrier} };
            try cmd.placeResourceBarrier(&barrier_descriptor);

            cmd.transferBufferToTexture(&.{ .src = item.stage_buffer, .src_offset = 0, .dst = item.texture, .dst_subresource = .{ .aspects = .{ .color = true }, .mip_level = 0, .base_array_layer = 0, .layer_count = 1 } });

            const texture_barrier2: cgpu.TextureBarrier = .{ .texture = item.texture, .src_state = cgpu.ResourceState{ .copy_dest = true }, .dst_state = cgpu.ResourceState{ .shader_resource = true }, .queue_acquire = 0, .queue_release = 0, .queue_type = .graphics, .subresource_barrier = 0, .mip_level = 0, .array_layer = 0 };
            const barrier_descriptor2: cgpu.ResourceBarrierDescriptor = .{ .texture_barriers = &[_]cgpu.TextureBarrier{texture_barrier2} };
            try cmd.placeResourceBarrier(&barrier_descriptor2);

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
        .p_present_queues = @ptrCast(&queue),
        .surface = surface,
        .image_count = 3,
        .width = w,
        .height = h,
        .enable_vsync = true,
        .use_flip_swap_effect = false,
        .format = .r8g8b8a8_unorm,
    };
    const swapchain = device.createSwapChain(&swap_chain_descriptor);
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

    _ = fw;
    _ = fh;

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
    }
}

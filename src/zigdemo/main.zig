const std = @import("std");
const cgpu = @import("cgpu");
const sdl = @import("zsdl3");
const imgui = @import("imgui");

pub fn main() !void {
    var gpa = std.heap.GeneralPurposeAllocator(.{}){};
    defer {
        if (gpa.deinit() == .leak) @panic("memory leak!");
    }
    const allocator = gpa.allocator();

    try sdl.init(.{ .events = true });

    const prop = try sdl.createProperties();
    defer sdl.destroyProperties(prop);
    _ = try sdl.setStringProperty(prop, sdl.prop_window_create_title_string, "zgpu demo");
    _ = try sdl.setFloatProperty(prop, sdl.prop_window_create_x_number, sdl.Window.pos_centered);
    _ = try sdl.setFloatProperty(prop, sdl.prop_window_create_y_number, sdl.Window.pos_centered);
    _ = try sdl.setFloatProperty(prop, sdl.prop_window_create_width_number, 800);
    _ = try sdl.setFloatProperty(prop, sdl.prop_window_create_height_number, 600);
    _ = try sdl.setBooleanProperty(prop, sdl.prop_window_create_external_graphics_context_boolean, true);

    const window = try sdl.createWindowWithProperties(prop);
    var ww: i32 = 0;
    var wh: i32 = 0;
    try window.getSize(&ww, &wh);

    const w: u32 = @intCast(ww);
    const h: u32 = @intCast(wh);
    const fw: f32 = @floatFromInt(w);
    const fh: f32 = @floatFromInt(h);

    imgui.init(allocator);
    var gui_style = imgui.Style.init();
    imgui.styleColorsDark(&gui_style);

    imgui.backend.init(window);

    const instance_descriptor = cgpu.InstanceDescriptor{ .backend = .vulkan, .enable_debug_layer = true, .enable_gpu_based_validation = true, .enable_set_name = true, .logger = .{}, .allocator = .{} };

    const instance = cgpu.createInstance(&instance_descriptor);
    defer cgpu.freeInstance(instance);

    var adapters_count: u32 = 0;
    instance.enumAdapters(&adapters_count, null);
    const adapters = try allocator.alloc(cgpu.AdapterId, adapters_count);
    instance.enumAdapters(&adapters_count, adapters.ptr);
    defer allocator.free(adapters);

    const adapter = adapters[0];

    var queue_group_descriptor = cgpu.QueueGroupDescriptor{
        .queue_count = 1,
        .queue_type = .graphics,
    };
    var device_descriptor = cgpu.DeviceDescriptor{
        .disable_pipeline_cache = false,
        .queue_group_count = 1,
        .p_queue_groups = &queue_group_descriptor,
    };

    const device = adapter.createDevice(&device_descriptor);
    defer adapter.freeDevice(device);

    const font_tex_info = imgui.io.getFontsTextDataAsRgba32();
    _ = font_tex_info;
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

    imgui.backend.deinit();
    imgui.deinit();
    window.destroy();
    sdl.quit();
}

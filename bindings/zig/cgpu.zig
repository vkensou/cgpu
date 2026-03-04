// Copyright 2011-2023 Branimir Karadzic. All rights reserved.
// License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE

//
// AUTO GENERATED! DO NOT EDIT!
//

const std = @import("std");

pub const HWND = *anyopaque;
pub const ANativeWindowPtr = *anyopaque;

pub const Error = error{
    CreateFailed,
};

pub const MaxMrtCount: u32 = 8;

pub const MaxAttachmentCount: u32 = 9;

pub const MaxVertexAttributes: u32 = 15;

pub const ShaderStageCount: u32 = 6;

pub const Backend = enum(u32) {
    vulkan, // ( 0)                         Vulkan
    d3d12, // ( 1)                          D3D12
    metal, // ( 2)                          Metal
};

pub const BlendFactor = enum(u32) {
    zero, // ( 0)
    one, // ( 1)
    src_color, // ( 2)
    one_minus_src_color, // ( 3)
    dst_color, // ( 4)
    one_minus_dst_color, // ( 5)
    src_alpha, // ( 6)
    one_minus_src_alpha, // ( 7)
    dst_alpha, // ( 8)
    one_minus_dst_alpha, // ( 9)
    src_alpha_saturate, // (10)
};

pub const BlendOp = enum(u32) {
    add, // ( 0)
    subtract, // ( 1)
    reverse_subtract, // ( 2)
    min, // ( 3)
    max, // ( 4)
};

pub const ColorMask = packed struct(u32) {
    r: bool = false, // ( 0)
    g: bool = false, // ( 1)
    b: bool = false, // ( 2)
    a: bool = false, // ( 3)
    padding: u28 = 0,
    pub const rgb: ColorMask = .{ .b = true, .g = true, .r = true };
    pub const rgba: ColorMask = .{ .a = true, .b = true, .g = true, .r = true };
};

pub const LogSeverity = enum(u32) {
    trace, // ( 0)
    debug, // ( 1)
    info, // ( 2)
    warning, // ( 3)
    @"error", // ( 4)
    fatal, // ( 5)
};

pub const TextureFormat = enum(u32) {
    undefined, // ( 0)
    r4g4_unorm_pack8, // ( 1)
    r4g4b4a4_unorm_pack16, // ( 2)
    b4g4r4a4_unorm_pack16, // ( 3)
    r5g6b5_unorm_pack16, // ( 4)
    b5g6r5_unorm_pack16, // ( 5)
    r5g5b5a1_unorm_pack16, // ( 6)
    b5g5r5a1_unorm_pack16, // ( 7)
    a1r5g5b5_unorm_pack16, // ( 8)
    r8_unorm, // ( 9)
    r8_snorm, // (10)
    r8_uint, // (11)
    r8_sint, // (12)
    r8_srgb, // (13)
    r8g8_unorm, // (14)
    r8g8_snorm, // (15)
    r8g8_uint, // (16)
    r8g8_sint, // (17)
    r8g8_srgb, // (18)
    r8g8b8_unorm, // (19)
    r8g8b8_snorm, // (20)
    r8g8b8_uint, // (21)
    r8g8b8_sint, // (22)
    r8g8b8_srgb, // (23)
    b8g8r8_unorm, // (24)
    b8g8r8_snorm, // (25)
    b8g8r8_uint, // (26)
    b8g8r8_sint, // (27)
    b8g8r8_srgb, // (28)
    r8g8b8a8_unorm, // (29)
    r8g8b8a8_snorm, // (30)
    r8g8b8a8_uint, // (31)
    r8g8b8a8_sint, // (32)
    r8g8b8a8_srgb, // (33)
    b8g8r8a8_unorm, // (34)
    b8g8r8a8_snorm, // (35)
    b8g8r8a8_uint, // (36)
    b8g8r8a8_sint, // (37)
    b8g8r8a8_srgb, // (38)
    a8b8g8r8_unorm_pack32, // (39)
    a8b8g8r8_snorm_pack32, // (40)
    a8b8g8r8_uint_pack32, // (41)
    a8b8g8r8_sint_pack32, // (42)
    a8b8g8r8_srgb_pack32, // (43)
    a2r10g10b10_unorm_pack32, // (44)
    a2r10g10b10_snorm_pack32, // (45)
    a2r10g10b10_uint_pack32, // (46)
    a2r10g10b10_sint_pack32, // (47)
    a2b10g10r10_unorm_pack32, // (48)
    a2b10g10r10_snorm_pack32, // (49)
    a2b10g10r10_uint_pack32, // (50)
    a2b10g10r10_sint_pack32, // (51)
    r16_unorm, // (52)
    r16_snorm, // (53)
    r16_uint, // (54)
    r16_sint, // (55)
    r16_sfloat, // (56)
    r16g16_unorm, // (57)
    r16g16_snorm, // (58)
    r16g16_uint, // (59)
    r16g16_sint, // (60)
    r16g16_sfloat, // (61)
    r16g16b16_unorm, // (62)
    r16g16b16_snorm, // (63)
    r16g16b16_uint, // (64)
    r16g16b16_sint, // (65)
    r16g16b16_sfloat, // (66)
    r16g16b16a16_unorm, // (67)
    r16g16b16a16_snorm, // (68)
    r16g16b16a16_uint, // (69)
    r16g16b16a16_sint, // (70)
    r16g16b16a16_sfloat, // (71)
    r32_uint, // (72)
    r32_sint, // (73)
    r32_sfloat, // (74)
    r32g32_uint, // (75)
    r32g32_sint, // (76)
    r32g32_sfloat, // (77)
    r32g32b32_uint, // (78)
    r32g32b32_sint, // (79)
    r32g32b32_sfloat, // (80)
    r32g32b32a32_uint, // (81)
    r32g32b32a32_sint, // (82)
    r32g32b32a32_sfloat, // (83)
    r64_uint, // (84)
    r64_sint, // (85)
    r64_sfloat, // (86)
    r64g64_uint, // (87)
    r64g64_sint, // (88)
    r64g64_sfloat, // (89)
    r64g64b64_uint, // (90)
    r64g64b64_sint, // (91)
    r64g64b64_sfloat, // (92)
    r64g64b64a64_uint, // (93)
    r64g64b64a64_sint, // (94)
    r64g64b64a64_sfloat, // (95)
    b10g11r11_ufloat_pack32, // (96)
    e5b9g9r9_ufloat_pack32, // (97)
    d16_unorm, // (98)
    x8_d24_unorm_pack32, // (99)
    d32_sfloat, // (100)
    s8_uint, // (101)
    d16_unorm_s8_uint, // (102)
    d24_unorm_s8_uint, // (103)
    d32_sfloat_s8_uint, // (104)
    bc1_rgb_unorm_block, // (105)
    bc1_rgb_srgb_block, // (106)
    bc1_rgba_unorm_block, // (107)
    bc1_rgba_srgb_block, // (108)
    bc2_unorm_block, // (109)
    bc2_srgb_block, // (110)
    bc3_unorm_block, // (111)
    bc3_srgb_block, // (112)
    bc4_unorm_block, // (113)
    bc4_snorm_block, // (114)
    bc5_unorm_block, // (115)
    bc5_snorm_block, // (116)
    bc6h_ufloat_block, // (117)
    bc6h_sfloat_block, // (118)
    bc7_unorm_block, // (119)
    bc7_srgb_block, // (120)
    pvrtc1_2bpp_unorm_block, // (121)
    pvrtc1_4bpp_unorm_block, // (122)
    pvrtc2_2bpp_unorm_block, // (123)
    pvrtc2_4bpp_unorm_block, // (124)
    pvrtc1_2bpp_srgb_block, // (125)
    pvrtc1_4bpp_srgb_block, // (126)
    pvrtc2_2bpp_srgb_block, // (127)
    pvrtc2_4bpp_srgb_block, // (128)
    etc2_r8g8b8_unorm_block, // (129)
    etc2_r8g8b8_srgb_block, // (130)
    etc2_r8g8b8a1_unorm_block, // (131)
    etc2_r8g8b8a1_srgb_block, // (132)
    etc2_r8g8b8a8_unorm_block, // (133)
    etc2_r8g8b8a8_srgb_block, // (134)
    eac_r11_unorm_block, // (135)
    eac_r11_snorm_block, // (136)
    eac_r11g11_unorm_block, // (137)
    eac_r11g11_snorm_block, // (138)
    astc_4x4_unorm_block, // (139)
    astc_4x4_srgb_block, // (140)
    astc_5x4_unorm_block, // (141)
    astc_5x4_srgb_block, // (142)
    astc_5x5_unorm_block, // (143)
    astc_5x5_srgb_block, // (144)
    astc_6x5_unorm_block, // (145)
    astc_6x5_srgb_block, // (146)
    astc_6x6_unorm_block, // (147)
    astc_6x6_srgb_block, // (148)
    astc_8x5_unorm_block, // (149)
    astc_8x5_srgb_block, // (150)
    astc_8x6_unorm_block, // (151)
    astc_8x6_srgb_block, // (152)
    astc_8x8_unorm_block, // (153)
    astc_8x8_srgb_block, // (154)
    astc_10x5_unorm_block, // (155)
    astc_10x5_srgb_block, // (156)
    astc_10x6_unorm_block, // (157)
    astc_10x6_srgb_block, // (158)
    astc_10x8_unorm_block, // (159)
    astc_10x8_srgb_block, // (160)
    astc_10x10_unorm_block, // (161)
    astc_10x10_srgb_block, // (162)
    astc_12x10_unorm_block, // (163)
    astc_12x10_srgb_block, // (164)
    astc_12x12_unorm_block, // (165)
    astc_12x12_srgb_block, // (166)
    astc_4x4_sfloat_block, // (167)
    astc_5x4_sfloat_block, // (168)
    astc_5x5_sfloat_block, // (169)
    astc_6x5_sfloat_block, // (170)
    astc_6x6_sfloat_block, // (171)
    astc_8x5_sfloat_block, // (172)
    astc_8x6_sfloat_block, // (173)
    astc_8x8_sfloat_block, // (174)
    astc_10x5_sfloat_block, // (175)
    astc_10x6_sfloat_block, // (176)
    astc_10x8_sfloat_block, // (177)
    astc_10x10_sfloat_block, // (178)
    astc_12x10_sfloat_block, // (179)
    astc_12x12_sfloat_block, // (180)
};

pub const FilterType = enum(u32) {
    nearest, // ( 0)
    linear, // ( 1)
};

pub const AddressMode = enum(u32) {
    mirror, // ( 0)
    repeat, // ( 1)
    clamp_to_edge, // ( 2)
    clamp_to_border, // ( 3)
};

pub const MipMapMode = enum(u32) {
    nearest, // ( 0)
    linear, // ( 1)
};

pub const LoadAction = enum(u32) {
    dont_care, // ( 0)
    load, // ( 1)
    clear, // ( 2)
};

pub const StoreAction = enum(u32) {
    store, // ( 0)
    discard, // ( 1)
};

pub const PrimitiveTopology = enum(u32) {
    point_list, // ( 0)
    line_list, // ( 1)
    line_strip, // ( 2)
    triangle_list, // ( 3)
    triangle_strip, // ( 4)
    patch_list, // ( 5)
};

pub const CompareOp = enum(u32) {
    never, // ( 0)
    less, // ( 1)
    equal, // ( 2)
    less_equal, // ( 3)
    greater, // ( 4)
    not_equal, // ( 5)
    greater_equal, // ( 6)
    always, // ( 7)
};

pub const CullMode = packed struct(u32) {
    back: bool = false, // ( 0)
    front: bool = false, // ( 1)
    padding: u30 = 0,
    pub const both: CullMode = .{ .back = true, .front = true };
};

pub const FillMode = enum(u32) {
    solid, // ( 0)
    wire_frame, // ( 1)
};

pub const FrontFace = enum(u32) {
    counter_clockwise, // ( 0)
    clock_wise, // ( 1)
};

pub const VertexInputRate = enum(u32) {
    vertex, // ( 0)
    instance, // ( 1)
};

pub const StencilFace = packed struct(u32) {
    front: bool = false, // ( 0)
    back: bool = false, // ( 1)
    padding: u30 = 0,
    pub const both: StencilFace = .{ .back = true, .front = true };
};

pub const StencilOp = enum(u32) {
    keep, // ( 0)
    zero, // ( 1)
    replace, // ( 2)
    increment_and_clamp, // ( 3)
    decrement_and_clamp, // ( 4)
    invert, // ( 5)
    increment_and_wrap, // ( 6)
    decrement_and_wrap, // ( 7)
};

pub const TextureDimension = enum(u32) {
    undefined, // ( 0)
    @"1d", // ( 1)
    @"2d", // ( 2)
    @"2dms", // ( 3)
    @"3d", // ( 4)
    cube, // ( 5)
    @"1darray", // ( 6)
    @"2darray", // ( 7)
    @"2dmsarray", // ( 8)
    cube_array, // ( 9)
};

pub const ShaderBytecodeType = enum(u32) {
    spirv, // ( 0)
    dxil, // ( 1)
    mtl, // ( 2)
};

pub const TextureFormatUsage = enum(u32) {
    sample, // ( 0)
    render, // ( 1)
    load_store, // ( 2)
    blend, // ( 3)
    msaa2x, // ( 4)
    msaa4x, // ( 5)
    msaa8x, // ( 6)
    msaa16x, // ( 7)
};

pub const ShaderStage = packed struct(u32) {
    vertex: bool = false, // ( 0)
    tessellation_control: bool = false, // ( 1)
    tessellation_evaluation: bool = false, // ( 2)
    geometry: bool = false, // ( 3)
    fragment: bool = false, // ( 4)
    compute: bool = false, // ( 5)
    ray_tracing: bool = false, // ( 6)
    padding: u25 = 0,
    pub const all_graphics: ShaderStage = .{ .fragment = true, .geometry = true, .tessellation_control = true, .tessellation_evaluation = true, .vertex = true };
};

pub const PipelineStage = packed struct(u32) {
    index: bool = false, // ( 0)
    vertex: bool = false, // ( 1)
    fragment: bool = false, // ( 2)
    depth: bool = false, // ( 3)
    render_target: bool = false, // ( 4)
    compute: bool = false, // ( 5)
    ray_tracing: bool = false, // ( 6)
    copy: bool = false, // ( 7)
    resolve: bool = false, // ( 8)
    execute_indirect: bool = false, // ( 9)
    padding: u22 = 0,
};

pub const FenceStatus = enum(u32) {
    complete, // ( 0)
    incomplete, // ( 1)
    not_submitted, // ( 2)
};

pub const QueryType = enum(u32) {
    timestamp, // ( 0)
    pipeline_statistics, // ( 1)
    occlusion, // ( 2)
};

pub const ResourceState = packed struct(u32) {
    vertex_and_constant_buffer: bool = false, // ( 0)
    index_buffer: bool = false, // ( 1)
    render_target: bool = false, // ( 2)
    unordered_access: bool = false, // ( 3)
    depth_write: bool = false, // ( 4)
    depth_read: bool = false, // ( 5)
    non_pixel_shader_resource: bool = false, // ( 6)
    pixel_shader_resource: bool = false, // ( 7)
    stream_out: bool = false, // ( 8)
    indirect_argument: bool = false, // ( 9)
    copy_dest: bool = false, // (10)
    copy_source: bool = false, // (11)
    present: bool = false, // (12)
    common: bool = false, // (13)
    acceleration_structure: bool = false, // (14)
    shading_rate_source: bool = false, // (15)
    resolve_dest: bool = false, // (16)
    padding: u15 = 0,
    pub const shader_resource: ResourceState = .{ .non_pixel_shader_resource = true, .pixel_shader_resource = true };
    pub const generic_read: ResourceState = .{ .copy_source = true, .index_buffer = true, .indirect_argument = true, .non_pixel_shader_resource = true, .pixel_shader_resource = true, .vertex_and_constant_buffer = true };
};

pub const MemoryUsage = enum(u32) {
    unknown, // ( 0)
    gpu_only, // ( 1)
    cpu_only, // ( 2)
    cpu_to_gpu, // ( 3)
    gpu_to_cpu, // ( 4)
};

pub const MemoryPoolType = enum(u32) {
    automatic, // ( 0)
    linear, // ( 1)
    tiled, // ( 2)
};

pub const BufferCreationUsage = packed struct(u32) {
    dedicated: bool = false, // ( 0)
    persistent_map: bool = false, // ( 1)
    host_visible: bool = false, // ( 2)
    padding: u29 = 0,
};

pub const TextureCreationUsage = packed struct(u32) {
    dedicated: bool = false, // ( 0)
    force2d: bool = false, // ( 1)
    force3d: bool = false, // ( 2)
    aliasing_resource: bool = false, // ( 3)
    tiled_resource: bool = false, // ( 4)
    @"export": bool = false, // ( 5)
    import_shared: bool = false, // ( 6)
    padding: u25 = 0,
};

pub const SampleCount = packed struct(u32) {
    @"1": bool = false, // ( 0)
    @"2": bool = false, // ( 1)
    @"4": bool = false, // ( 2)
    @"8": bool = false, // ( 3)
    @"16": bool = false, // ( 4)
    padding: u27 = 0,
};

pub const PipelineType = enum(u32) {
    none, // ( 0)
    compute, // ( 1)
    graphics, // ( 2)
    ray_tracing, // ( 3)
};

pub const ResourceType = packed struct(u32) {
    sampler: bool = false, // ( 0)
    texture: bool = false, // ( 1)
    render_target: bool = false, // ( 2)
    depth_stencil: bool = false, // ( 3)
    rw_texture: bool = false, // ( 4)
    buffer: bool = false, // ( 5)
    buffer_raw: bool = false, // ( 6)
    rw_buffer: bool = false, // ( 7)
    rw_buffer_raw: bool = false, // ( 8)
    uniform_buffer: bool = false, // ( 9)
    push_constant: bool = false, // (10)
    vertex_buffer: bool = false, // (11)
    index_buffer: bool = false, // (12)
    indirect_buffer: bool = false, // (13)
    texture_cube: bool = false, // (14)
    render_target_mip_slices: bool = false, // (15)
    render_target_array_slices: bool = false, // (16)
    render_target_depth_slices: bool = false, // (17)
    ray_tracing: bool = false, // (18)
    input_attachment: bool = false, // (19)
    texel_buffer: bool = false, // (20)
    rw_texel_buffer: bool = false, // (21)
    combined_image_sampler: bool = false, // (22)
    padding: u9 = 0,
};

pub const TextureViewUsage = packed struct(u32) {
    srv: bool = false, // ( 0)
    rtv_dsv: bool = false, // ( 1)
    uav: bool = false, // ( 2)
    padding: u29 = 0,
};

pub const TextureViewAspect = packed struct(u32) {
    color: bool = false, // ( 0)
    depth: bool = false, // ( 1)
    stencil: bool = false, // ( 2)
    padding: u29 = 0,
};

pub const ShadingRate = enum(u32) {
    full, // ( 0)
    half, // ( 1)
    quarter, // ( 2)
    @"1x2", // ( 3)
    @"2x1", // ( 4)
    @"2x4", // ( 5)
    @"4x2", // ( 6)
};

pub const ShadingRateCombiner = enum(u32) {
    pass_through, // ( 0)
    override, // ( 1)
    min, // ( 2)
    max, // ( 3)
    sum, // ( 4)
};

pub const QueueType = enum(u32) {
    graphics, // ( 0)
    compute, // ( 1)
    transfer, // ( 2)
    tile_mapping, // ( 3)
};

pub const TextureFormatSupport = packed struct(u32) {
    sample: bool = false, // ( 0)
    render: bool = false, // ( 1)
    load_store: bool = false, // ( 2)
    blend: bool = false, // ( 3)
    msaa2x: bool = false, // ( 4)
    msaa4x: bool = false, // ( 5)
    msaa8x: bool = false, // ( 6)
    msaa16x: bool = false, // ( 7)
    padding: u24 = 0,
};

pub const VertexFormat = enum(u32) {
    undefined, // ( 0)
    float32x1, // ( 1)
    float32x2, // ( 2)
    float32x3, // ( 3)
    float32x4, // ( 4)
    sint32x1, // ( 5)
    sint32x2, // ( 6)
    sint32x3, // ( 7)
    sint32x4, // ( 8)
    uint32x1, // ( 9)
    uint32x2, // (10)
    uint32x3, // (11)
    uint32x4, // (12)
    float16x2, // (13)
    float16x4, // (14)
    sint16x2, // (15)
    sint16x4, // (16)
    uint16x2, // (17)
    uint16x4, // (18)
    snorm16x2, // (19)
    snorm16x4, // (20)
    unorm16x2, // (21)
    unorm16x4, // (22)
    sint8x4, // (23)
    uint8x4, // (24)
    snorm8x4, // (25)
    unorm8x4, // (26)
};

pub const DynamicStateFeatures = packed struct(u64) {
    cull_mode: bool = false, // ( 0)
    front_face: bool = false, // ( 1)
    primitive_topology: bool = false, // ( 2)
    depth_test: bool = false, // ( 3)
    depth_write: bool = false, // ( 4)
    depth_compare: bool = false, // ( 5)
    depth_bounds_test: bool = false, // ( 6)
    stencil_test: bool = false, // ( 7)
    stencil_op: bool = false, // ( 8)
    raster_discard: bool = false, // ( 9)
    depth_bias: bool = false, // (10)
    primitive_restart: bool = false, // (11)
    logic_op: bool = false, // (12)
    patch_control_points: bool = false, // (13)
    tessellation_domain_origin: bool = false, // (14)
    depth_clamp_enable: bool = false, // (15)
    polygon_mode: bool = false, // (16)
    sample_count: bool = false, // (17)
    sample_mask: bool = false, // (18)
    alpha_to_coverage_enable: bool = false, // (19)
    alpha_to_one_enable: bool = false, // (20)
    logic_op_enable: bool = false, // (21)
    color_blend_enable: bool = false, // (22)
    color_blend_equation: bool = false, // (23)
    color_write_mask: bool = false, // (24)
    raster_stream: bool = false, // (25)
    conservative_raster_mode: bool = false, // (26)
    extra_primitive_overestimation_size: bool = false, // (27)
    depth_clip_enable: bool = false, // (28)
    sample_locations_enable: bool = false, // (29)
    color_blend_advanced: bool = false, // (30)
    provoking_vertex_mode: bool = false, // (31)
    line_rasterization_mode: bool = false, // (32)
    line_stipple_enable: bool = false, // (33)
    depth_clip_negative_one_to_one: bool = false, // (34)
    viewport_wscaling_enable: bool = false, // (35)
    viewport_swizzle: bool = false, // (36)
    coverage_to_color_enable: bool = false, // (37)
    coverage_to_color_location: bool = false, // (38)
    coverage_modulation_mode: bool = false, // (39)
    coverage_modulation_table_enable: bool = false, // (40)
    coverage_modulation_table: bool = false, // (41)
    coverage_reduction_mode: bool = false, // (42)
    representative_fragment_test_enable: bool = false, // (43)
    shading_rate_image_enable: bool = false, // (44)
    padding: u19 = 0,
    pub const tier1: DynamicStateFeatures = .{ .cull_mode = true, .depth_bounds_test = true, .depth_compare = true, .depth_test = true, .depth_write = true, .front_face = true, .primitive_topology = true, .stencil_op = true, .stencil_test = true };
    pub const tier2: DynamicStateFeatures = .{ .cull_mode = true, .depth_bias = true, .depth_bounds_test = true, .depth_compare = true, .depth_test = true, .depth_write = true, .front_face = true, .logic_op = true, .patch_control_points = true, .primitive_restart = true, .primitive_topology = true, .raster_discard = true, .stencil_op = true, .stencil_test = true };
    pub const tier3: DynamicStateFeatures = .{ .alpha_to_coverage_enable = true, .alpha_to_one_enable = true, .color_blend_advanced = true, .color_blend_enable = true, .color_blend_equation = true, .color_write_mask = true, .conservative_raster_mode = true, .coverage_modulation_mode = true, .coverage_modulation_table = true, .coverage_modulation_table_enable = true, .coverage_reduction_mode = true, .coverage_to_color_enable = true, .coverage_to_color_location = true, .cull_mode = true, .depth_bias = true, .depth_bounds_test = true, .depth_clamp_enable = true, .depth_clip_enable = true, .depth_clip_negative_one_to_one = true, .depth_compare = true, .depth_test = true, .depth_write = true, .extra_primitive_overestimation_size = true, .front_face = true, .line_rasterization_mode = true, .line_stipple_enable = true, .logic_op = true, .logic_op_enable = true, .patch_control_points = true, .polygon_mode = true, .primitive_restart = true, .primitive_topology = true, .provoking_vertex_mode = true, .raster_discard = true, .raster_stream = true, .representative_fragment_test_enable = true, .sample_count = true, .sample_locations_enable = true, .sample_mask = true, .shading_rate_image_enable = true, .stencil_op = true, .stencil_test = true, .tessellation_domain_origin = true, .viewport_swizzle = true, .viewport_wscaling_enable = true };
};

pub const AcquireNextImageError = enum(u32) {
    success, // ( 0)
    sub_optimal, // ( 1)
    not_available, // ( 2)
    out_of_date, // ( 3)
    device_lost, // ( 4)
    other_fatal, // ( 5)
};

pub const SubmitError = enum(u32) {
    success, // ( 0)
    device_lost, // ( 1)
    other_fatal, // ( 2)
};

pub const PresentError = enum(u32) {
    success, // ( 0)
    sub_optimal, // ( 1)
    out_of_date, // ( 2)
    device_lost, // ( 3)
    other_fatal, // ( 4)
};

pub const LogCallback = fn (user_data: ?*anyopaque, severity: LogSeverity, fmt: [*:0]const u8, ...) callconv(.C) void;

pub const Malloc = fn (user_data: ?*anyopaque, size: usize, pool: ?*const anyopaque) callconv(.C) ?*anyopaque;

pub const Realloc = fn (user_data: ?*anyopaque, ptr: ?*anyopaque, size: usize, pool: ?*const anyopaque) callconv(.C) ?*anyopaque;

pub const Calloc = fn (user_data: ?*anyopaque, count: usize, size: usize, pool: ?*const anyopaque) callconv(.C) ?*anyopaque;

pub const Free = fn (user_data: ?*anyopaque, ptr: ?*anyopaque, pool: ?*const anyopaque) callconv(.C) void;

pub const MallocAligned = fn (user_data: ?*anyopaque, size: usize, alignment: usize, pool: ?*const anyopaque) callconv(.C) ?*anyopaque;

pub const ReallocAligned = fn (user_data: ?*anyopaque, ptr: ?*anyopaque, size: usize, alignment: usize, pool: ?*const anyopaque) callconv(.C) ?*anyopaque;

pub const CallocAligned = fn (user_data: ?*anyopaque, count: usize, size: usize, alignment: usize, pool: ?*const anyopaque) callconv(.C) ?*anyopaque;

pub const FreeAligned = fn (user_data: ?*anyopaque, ptr: ?*anyopaque, pool: ?*const anyopaque) callconv(.C) void;

pub const CreateInstance = fn (desc: *const InstanceDescriptor) callconv(.C) ?InstanceId;

pub const FreeInstance = fn (instance: InstanceId) callconv(.C) void;

pub const QueryInstanceFeatures = fn (instance: InstanceId, features: *InstanceFeatures) callconv(.C) void;

pub const EnumAdapters = fn (instance: InstanceId, p_adapters_count: *u32, p_adapters: ?[*]AdapterId) callconv(.C) void;

pub const CreateSurfaceFromNativeView = fn (instance: InstanceId, view: ?*anyopaque) callconv(.C) ?SurfaceId;

pub const CreateSurfaceFromHwnd = fn (instance: InstanceId, window: HWND) callconv(.C) ?SurfaceId;

pub const CreateSurfaceFromNativeWindow = fn (instance: InstanceId, window: ANativeWindowPtr) callconv(.C) ?SurfaceId;

pub const FreeSurface = fn (instance: InstanceId, surface: SurfaceId) callconv(.C) void;

pub const QueryAdapterDetail = fn (adapter: AdapterId) callconv(.C) ?*const AdapterDetail;

pub const QueryQueueCount = fn (adapter: AdapterId, _type: QueueType) callconv(.C) u32;

pub const CreateDevice = fn (adapter: AdapterId, desc: *const DeviceDescriptor) callconv(.C) ?DeviceId;

pub const FreeDevice = fn (adapter: AdapterId, device: DeviceId) callconv(.C) void;

pub const QueryVideoMemoryInfo = fn (device: DeviceId, total: *u64, used_bytes: *u64) callconv(.C) void;

pub const QuerySharedMemoryInfo = fn (device: DeviceId, total: *u64, used_bytes: *u64) callconv(.C) void;

pub const CreateFence = fn (device: DeviceId) callconv(.C) ?FenceId;

pub const WaitFences = fn (fence_count: u32, p_fences: [*]const FenceId) callconv(.C) void;

pub const ResetFences = fn (fence_count: u32, p_fences: [*]const FenceId) callconv(.C) void;

pub const QueryFenceStatus = fn (fence: FenceId) callconv(.C) FenceStatus;

pub const FreeFence = fn (device: DeviceId, fence: FenceId) callconv(.C) void;

pub const CreateSemaphore = fn (device: DeviceId) callconv(.C) ?SemaphoreId;

pub const FreeSemaphore = fn (device: DeviceId, semaphore: SemaphoreId) callconv(.C) void;

pub const CreateRootSignaturePool = fn (device: DeviceId, desc: *const RootSignaturePoolDescriptor) callconv(.C) ?RootSignaturePoolId;

pub const FreeRootSignaturePool = fn (device: DeviceId, pool: RootSignaturePoolId) callconv(.C) void;

pub const CreateRootSignature = fn (device: DeviceId, desc: *const RootSignatureDescriptor) callconv(.C) ?RootSignatureId;

pub const FreeRootSignature = fn (device: DeviceId, signature: RootSignatureId) callconv(.C) void;

pub const CreateDescriptorSet = fn (device: DeviceId, desc: *const DescriptorSetDescriptor) callconv(.C) ?DescriptorSetId;

pub const UpdateDescriptorSet = fn (set: DescriptorSetId, data_count: u32, p_datas: *const DescriptorData) callconv(.C) void;

pub const FreeDescriptorSet = fn (device: DeviceId, set: DescriptorSetId) callconv(.C) void;

pub const CreateComputePipeline = fn (device: DeviceId, desc: *const ComputePipelineDescriptor) callconv(.C) ?ComputePipelineId;

pub const FreeComputePipeline = fn (device: DeviceId, pipeline: ComputePipelineId) callconv(.C) void;

pub const CreateRenderPipeline = fn (device: DeviceId, desc: *const RenderPipelineDescriptor) callconv(.C) ?RenderPipelineId;

pub const FreeRenderPipeline = fn (device: DeviceId, pipeline: RenderPipelineId) callconv(.C) void;

pub const CreateQueryPool = fn (device: DeviceId, desc: *const QueryPoolDescriptor) callconv(.C) ?QueryPoolId;

pub const FreeQueryPool = fn (device: DeviceId, pool: QueryPoolId) callconv(.C) void;

pub const CreateMemoryPool = fn (device: DeviceId, desc: *const MemoryPoolDescriptor) callconv(.C) ?MemoryPoolId;

pub const FreeMemoryPool = fn (device: DeviceId, pool: MemoryPoolId) callconv(.C) void;

pub const GetQueue = fn (device: DeviceId, _type: QueueType, index: u32) callconv(.C) ?QueueId;

pub const SubmitQueue = fn (queue: QueueId, desc: *const QueueSubmitDescriptor) callconv(.C) SubmitError;

pub const QueuePresent = fn (queue: QueueId, desc: *const QueuePresentDescriptor) callconv(.C) PresentError;

pub const WaitQueueIdle = fn (queue: QueueId) callconv(.C) void;

pub const QueueGetTimestampPeriodNS = fn (queue: QueueId) callconv(.C) f32;

pub const QueueMapTiledTexture = fn (queue: QueueId, desc: *const TiledTextureRegions) callconv(.C) void;

pub const QueueUnmapTiledTexture = fn (queue: QueueId, desc: *const TiledTextureRegions) callconv(.C) void;

pub const QueueMapPackedMips = fn (queue: QueueId, desc: *const TiledTexturePackedMips) callconv(.C) void;

pub const QueueUnmapPackedMips = fn (queue: QueueId, desc: *const TiledTexturePackedMips) callconv(.C) void;

pub const FreeQueue = fn (device: DeviceId, queue: QueueId) callconv(.C) void;

pub const CreateRenderPass = fn (device: DeviceId, desc: *const RenderPassDescriptor) callconv(.C) ?RenderPassId;

pub const CreateFramebuffer = fn (device: DeviceId, desc: *const FramebufferDescriptor) callconv(.C) ?FramebufferId;

pub const FreeRenderPass = fn (device: DeviceId, render_pass: RenderPassId) callconv(.C) void;

pub const FreeFramebuffer = fn (device: DeviceId, framebuffer: FramebufferId) callconv(.C) void;

pub const CreateCommandPool = fn (queue: QueueId, desc: *const CommandPoolDescriptor) callconv(.C) ?CommandPoolId;

pub const CreateCommandBuffer = fn (pool: CommandPoolId, desc: *const CommandBufferDescriptor) callconv(.C) ?CommandBufferId;

pub const ResetCommandPool = fn (pool: CommandPoolId) callconv(.C) void;

pub const FreeCommandBuffer = fn (pool: CommandPoolId, cmd: CommandBufferId) callconv(.C) void;

pub const FreeCommandPool = fn (queue: QueueId, pool: CommandPoolId) callconv(.C) void;

pub const CreateShaderLibrary = fn (device: DeviceId, desc: *const ShaderLibraryDescriptor) callconv(.C) ?ShaderLibraryId;

pub const FreeShaderLibrary = fn (device: DeviceId, library: ShaderLibraryId) callconv(.C) void;

pub const CreateBuffer = fn (device: DeviceId, desc: *const BufferDescriptor) callconv(.C) ?BufferId;

pub const MapBuffer = fn (buffer: BufferId, range: ?*const BufferRange) callconv(.C) void;

pub const UnmapBuffer = fn (buffer: BufferId) callconv(.C) void;

pub const FreeBuffer = fn (device: DeviceId, buffer: BufferId) callconv(.C) void;

pub const CreateSampler = fn (device: DeviceId, desc: *const SamplerDescriptor) callconv(.C) ?SamplerId;

pub const FreeSampler = fn (device: DeviceId, sampler: SamplerId) callconv(.C) void;

pub const CreateTexture = fn (device: DeviceId, desc: *const TextureDescriptor) callconv(.C) ?TextureId;

pub const FreeTexture = fn (device: DeviceId, texture: TextureId) callconv(.C) void;

pub const CreateTextureView = fn (device: DeviceId, desc: *const TextureViewDescriptor) callconv(.C) ?TextureViewId;

pub const FreeTextureView = fn (device: DeviceId, render_target: TextureViewId) callconv(.C) void;

pub const TryBindAliasingTexture = fn (device: DeviceId, desc: *const TextureAliasingBindDescriptor) callconv(.C) bool;

pub const ExportSharedTextureHandle = fn (device: DeviceId, desc: *const ExportTextureDescriptor) callconv(.C) u64;

pub const ImportSharedTextureHandle = fn (device: DeviceId, desc: *const ImportTextureDescriptor) callconv(.C) ?TextureId;

pub const CreateSwapChain = fn (device: DeviceId, desc: *const SwapChainDescriptor) callconv(.C) ?SwapChainId;

pub const AcquireNextImage = fn (swapchain: SwapChainId, desc: *const AcquireNextDescriptor, p_image_index: *u32) callconv(.C) AcquireNextImageError;

pub const FreeSwapChain = fn (device: DeviceId, swapchain: SwapChainId) callconv(.C) void;

pub const CmdBegin = fn (cmd: CommandBufferId) callconv(.C) void;

pub const CmdTransferBufferToBuffer = fn (cmd: CommandBufferId, desc: *const BufferToBufferTransfer) callconv(.C) void;

pub const CmdTransferTextureToTexture = fn (cmd: CommandBufferId, desc: *const TextureToTextureTransfer) callconv(.C) void;

pub const CmdTransferBufferToTexture = fn (cmd: CommandBufferId, desc: *const BufferToTextureTransfer) callconv(.C) void;

pub const CmdTransferBufferToTiles = fn (cmd: CommandBufferId, desc: *const BufferToTilesTransfer) callconv(.C) void;

pub const CmdResourceBarrier = fn (cmd: CommandBufferId, desc: *const ResourceBarrierDescriptor) callconv(.C) void;

pub const CmdBeginQuery = fn (cmd: CommandBufferId, pool: QueryPoolId, desc: *const QueryDescriptor) callconv(.C) void;

pub const CmdEndQuery = fn (cmd: CommandBufferId, pool: QueryPoolId, desc: *const QueryDescriptor) callconv(.C) void;

pub const CmdResetQueryPool = fn (cmd: CommandBufferId, pool: QueryPoolId, start_query: u32, query_count: u32) callconv(.C) void;

pub const CmdResolveQuery = fn (cmd: CommandBufferId, pool: QueryPoolId, readback: BufferId, start_query: u32, query_count: u32) callconv(.C) void;

pub const CmdEnd = fn (cmd: CommandBufferId) callconv(.C) void;

pub const CmdBeginComputePass = fn (cmd: CommandBufferId, desc: *const ComputePassDescriptor) callconv(.C) ?ComputePassEncoderId;

pub const ComputeEncoderBindDescriptorSet = fn (encoder: ComputePassEncoderId, set: DescriptorSetId) callconv(.C) void;

pub const ComputeEncoderBindPipeline = fn (encoder: ComputePassEncoderId, pipeline: ComputePipelineId) callconv(.C) void;

pub const ComputeEncoderDispatch = fn (encoder: ComputePassEncoderId, x: u32, y: u32, z: u32) callconv(.C) void;

pub const CmdEndComputePass = fn (cmd: CommandBufferId, encoder: ComputePassEncoderId) callconv(.C) void;

pub const CmdBeginRenderPass = fn (cmd: CommandBufferId, begin_info: *const BeginRenderPassInfo) callconv(.C) ?RenderPassEncoderId;

pub const RenderEncoderSetShadingRate = fn (encoder: RenderPassEncoderId, shading_rate: ShadingRate, post_rasterize_rate: ShadingRateCombiner, final_rate: ShadingRateCombiner) callconv(.C) void;

pub const RenderEncoderBindDescriptorSet = fn (encoder: RenderPassEncoderId, set: DescriptorSetId) callconv(.C) void;

pub const RenderEncoderSetViewport = fn (encoder: RenderPassEncoderId, x: f32, y: f32, width: f32, height: f32, min_depth: f32, max_depth: f32) callconv(.C) void;

pub const RenderEncoderSetScissor = fn (encoder: RenderPassEncoderId, x: u32, y: u32, width: u32, height: u32) callconv(.C) void;

pub const RenderEncoderBindPipeline = fn (encoder: RenderPassEncoderId, pipeline: RenderPipelineId) callconv(.C) void;

pub const RenderEncoderBindVertexBuffers = fn (encoder: RenderPassEncoderId, buffer_count: u32, buffers: [*]const BufferId, strides: [*]const u32, offsets: ?[*]const u32) callconv(.C) void;

pub const RenderEncoderBindIndexBuffer = fn (encoder: RenderPassEncoderId, buffer: BufferId, index_stride: u32, offset: u64) callconv(.C) void;

pub const RenderEncoderPushConstants = fn (encoder: RenderPassEncoderId, rs: RootSignatureId, name: ?[*:0]const u8, data: *const void) callconv(.C) void;

pub const ComputeEncoderPushConstants = fn (encoder: ComputePassEncoderId, rs: RootSignatureId, name: ?[*:0]const u8, data: *const void) callconv(.C) void;

pub const RenderEncoderDraw = fn (encoder: RenderPassEncoderId, vertex_count: u32, first_vertex: u32) callconv(.C) void;

pub const RenderEncoderDrawInstanced = fn (encoder: RenderPassEncoderId, vertex_count: u32, first_vertex: u32, instance_count: u32, first_instance: u32) callconv(.C) void;

pub const RenderEncoderDrawIndexed = fn (encoder: RenderPassEncoderId, index_count: u32, first_index: u32, first_vertex: u32) callconv(.C) void;

pub const RenderEncoderDrawIndexedInstanced = fn (encoder: RenderPassEncoderId, index_count: u32, first_index: u32, instance_count: u32, first_instance: u32, first_vertex: u32) callconv(.C) void;

pub const CmdEndRenderPass = fn (cmd: CommandBufferId, encoder: RenderPassEncoderId) callconv(.C) void;

pub const CmdBeginEvent = fn (cmd: CommandBufferId, event: *const EventInfo) callconv(.C) void;

pub const CmdSetMarker = fn (cmd: CommandBufferId, marker: *const MarkerInfo) callconv(.C) void;

pub const CmdEndEvent = fn (cmd: CommandBufferId) callconv(.C) void;

pub const CompileAndLinkShaders = fn (signature: RootSignatureId, count: u32, desc: *const CompiledShaderDescriptor) callconv(.C) ?LinkedShaderId;

pub const CompileShaders = fn (signature: RootSignatureId, count: u32, desc: *const CompiledShaderDescriptor, out_isas: *CompiledShaderId) callconv(.C) void;

pub const FreeCompiledShader = fn (shader: CompiledShaderId) callconv(.C) void;

pub const FreeLinkedShader = fn (shader: LinkedShaderId) callconv(.C) void;

pub const CreateStateBuffer = fn (cmd: CommandBufferId, desc: *const StateBufferDescriptor) callconv(.C) ?StateBufferId;

pub const RenderEncoderBindStateBuffer = fn (encoder: RenderPassEncoderId, stream: StateBufferId) callconv(.C) void;

pub const ComputeEncoderBindStateBuffer = fn (encoder: ComputePassEncoderId, stream: StateBufferId) callconv(.C) void;

pub const FreeStateBuffer = fn (stream: StateBufferId) callconv(.C) void;

pub const OpenRasterStateEncoder = fn (stream: StateBufferId, encoder: RenderPassEncoderId) callconv(.C) ?RasterStateEncoderId;

pub const RasterStateEncoderSetViewport = fn (encoder: RasterStateEncoderId, x: f32, y: f32, width: f32, height: f32, min_depth: f32, max_depth: f32) callconv(.C) void;

pub const RasterStateEncoderSetScissor = fn (encoder: RasterStateEncoderId, x: u32, y: u32, width: u32, height: u32) callconv(.C) void;

pub const RasterStateEncoderSetCullMode = fn (encoder: RasterStateEncoderId, cull_mode: CullMode) callconv(.C) void;

pub const RasterStateEncoderSetFrontFace = fn (encoder: RasterStateEncoderId, front_face: FrontFace) callconv(.C) void;

pub const RasterStateEncoderSetPrimitiveTopology = fn (encoder: RasterStateEncoderId, topology: PrimitiveTopology) callconv(.C) void;

pub const RasterStateEncoderSetDepthTestEnabled = fn (encoder: RasterStateEncoderId, enabled: bool) callconv(.C) void;

pub const RasterStateEncoderSetDepthWriteEnabled = fn (encoder: RasterStateEncoderId, enabled: bool) callconv(.C) void;

pub const RasterStateEncoderSetDepthCompareOp = fn (encoder: RasterStateEncoderId, compare_op: CompareOp) callconv(.C) void;

pub const RasterStateEncoderSetStencilTestEnabled = fn (encoder: RasterStateEncoderId, enabled: bool) callconv(.C) void;

pub const RasterStateEncoderSetStencilCompareOp = fn (encoder: RasterStateEncoderId, faces: StencilFace, fail_op: StencilOp, pass_op: StencilOp, depth_fail_op: StencilOp, compare_op: CompareOp) callconv(.C) void;

pub const RasterStateEncoderSetFillMode = fn (encoder: RasterStateEncoderId, fill_mode: FillMode) callconv(.C) void;

pub const RasterStateEncoderSetSampleCount = fn (encoder: RasterStateEncoderId, sample_count: SampleCount) callconv(.C) void;

pub const CloseRasterStateEncoder = fn (encoder: RasterStateEncoderId) callconv(.C) void;

pub const OpenShaderStateEncoderR = fn (stream: StateBufferId, encoder: RenderPassEncoderId) callconv(.C) ?ShaderStateEncoderId;

pub const OpenShaderStateEncoderC = fn (stream: StateBufferId, encoder: ComputePassEncoderId) callconv(.C) ?ShaderStateEncoderId;

pub const ShaderStateEncoderBindShaders = fn (encoder: ShaderStateEncoderId, stage_count: u32, stages: *const ShaderStage, shaders: *const CompiledShaderId) callconv(.C) void;

pub const ShaderStateEncoderBindLinkedShader = fn (encoder: ShaderStateEncoderId, linked: LinkedShaderId) callconv(.C) void;

pub const CloseShaderStateEncoder = fn (encoder: ShaderStateEncoderId) callconv(.C) void;

pub const OpenUserStateEncoder = fn (stream: StateBufferId, encoder: RenderPassEncoderId) callconv(.C) ?UserStateEncoderId;

pub const CloseUserStateEncoder = fn (encoder: UserStateEncoderId) callconv(.C) void;

pub const CreateBinder = fn (cmd: CommandBufferId) callconv(.C) ?BinderId;

pub const BinderBindVertexLayout = fn (binder: BinderId, layout: *const VertexLayout) callconv(.C) void;

pub const BinderBindVertexBuffer = fn (binder: BinderId, first_binding: u32, binding_count: u32, buffers: *const BufferId, offsets: *const u64, sizes: *const u64, strides: *const u64) callconv(.C) void;

pub const FreeBinder = fn (binder: BinderId) callconv(.C) void;

pub const InstanceId = *Instance;

pub const AdapterId = *Adapter;

pub const DeviceId = *Device;

pub const QueueId = *Queue;

pub const SemaphoreId = *Semaphore;

pub const FenceId = *Fence;

pub const CommandPoolId = *CommandPool;

pub const CommandBufferId = *CommandBuffer;

pub const QueryPoolId = *QueryPool;

pub const ComputePassEncoderId = *ComputePassEncoder;

pub const RenderPassEncoderId = *RenderPassEncoder;

pub const RenderPassId = *RenderPass;

pub const FramebufferId = *Framebuffer;

pub const StateBufferId = *StateBuffer;

pub const RasterStateEncoderId = *RasterStateEncoder;

pub const ShaderStateEncoderId = *ShaderStateEncoder;

pub const UserStateEncoderId = *UserStateEncoder;

pub const BinderId = *Binder;

pub const ShaderLibraryId = *ShaderLibrary;

pub const RootSignaturePoolId = *RootSignaturePool;

pub const RootSignatureId = *RootSignature;

pub const DescriptorSetId = *DescriptorSet;

pub const ShaderReflectionId = *ShaderReflection;

pub const CompiledShaderId = *CompiledShader;

pub const LinkedShaderId = *LinkedShader;

pub const BufferId = *Buffer;

pub const TextureId = *Texture;

pub const TextureViewId = *TextureView;

pub const SamplerId = *Sampler;

pub const RenderPipelineId = *RenderPipeline;

pub const ComputePipelineId = *ComputePipeline;

pub const MemoryPoolId = *MemoryPool;

pub const SwapChainId = *SwapChain;

pub const SurfaceId = *Surface;

pub const Logger = extern struct {
    log_callback: ?*const LogCallback = null,
    user_data: ?*anyopaque = null,
};

pub const Allocator = extern struct {
    malloc_fn: ?*const Malloc = null,
    realloc_fn: ?*const Realloc = null,
    calloc_fn: ?*const Calloc = null,
    free_fn: ?*const Free = null,
    malloc_aligned_fn: ?*const MallocAligned = null,
    realloc_aligned_fn: ?*const ReallocAligned = null,
    calloc_aligned_fn: ?*const CallocAligned = null,
    free_aligned_fn: ?*const FreeAligned = null,
    user_data: ?*anyopaque = null,
};

pub const InstanceDescriptor = extern struct {
    backend: Backend,
    enable_debug_layer: bool,
    enable_gpu_based_validation: bool,
    enable_set_name: bool,
    logger: Logger,
    allocator: Allocator,
};

pub const InstanceFeatures = extern struct {
    specialization_constant: bool,
};

pub const Instance = extern struct {
    proc_table: *const ProcTable,
    surfaces_table: *const SurfacesProcTable,
    runtime_table: *RuntimeTable,
    backend: Backend,
    enable_set_name: bool,
    logger: Logger,
    allocator: Allocator,
    pub inline fn getBackend(self: *const Instance) Backend {
        return cgpu_instance_get_backend(self);
    }
    pub inline fn queryFeatures(self: *const Instance, features: *InstanceFeatures) void {
        return cgpu_instance_query_instance_features(self, features);
    }
    pub inline fn enumAdapters(self: *const Instance, p_adapters_count: *u32, p_adapters: ?[*]AdapterId) void {
        return cgpu_instance_enum_adapters(self, p_adapters_count, p_adapters);
    }
    pub inline fn createSurfaceFromNativeView(self: *Instance, view: ?*anyopaque) Error!SurfaceId {
        const result = cgpu_instance_create_surface_from_native_view(self, view);
        return if (result) |result_object|
            result_object
        else
            Error.CreateFailed;
    }
    pub inline fn createSurfaceFromHwnd(self: *Instance, window: HWND) Error!SurfaceId {
        const result = cgpu_instance_create_surface_from_hwnd(self, window);
        return if (result) |result_object|
            result_object
        else
            Error.CreateFailed;
    }
    pub inline fn createSurfaceFromNativeWindow(self: *Instance, window: ANativeWindowPtr) Error!SurfaceId {
        const result = cgpu_instance_create_surface_from_native_window(self, window);
        return if (result) |result_object|
            result_object
        else
            Error.CreateFailed;
    }
    pub inline fn freeSurface(self: *Instance, surface: SurfaceId) void {
        return cgpu_instance_free_surface(self, surface);
    }
};

pub const VendorPreset = extern struct {
    device_id: u32,
    vendor_id: u32,
    driver_version: u32,
    gpu_name: [64]u8,
};

pub const AdapterDetail = extern struct {
    uniform_buffer_alignment: u32,
    upload_buffer_texture_alignment: u32,
    upload_buffer_texture_row_alignment: u32,
    max_vertex_input_bindings: u32,
    wave_lane_count: u32,
    host_visible_vram_budget: u64,
    dynamic_state_features: DynamicStateFeatures,
    support_host_visible_vram: bool,
    multidraw_indirect: bool,
    support_geom_shader: bool,
    support_tessellation: bool,
    is_uma: bool,
    is_virtual: bool,
    is_cpu: bool,
    support_tiled_buffer: bool,
    support_tiled_texture: bool,
    support_tiled_volume: bool,
    support_shading_rate: bool,
    support_shading_rate_mask: bool,
    support_shading_rate_sv: bool,
    format_supports: [181]TextureFormatSupport,
    vendor_preset: VendorPreset,
};

pub const Adapter = extern struct {
    instance: InstanceId,
    proc_table_cache: *const ProcTable,
    pub inline fn queryDetail(self: *const Adapter) *const AdapterDetail {
        return cgpu_adapter_query_adapter_detail(self);
    }
    pub inline fn queryQueueCount(self: *const Adapter, _type: QueueType) u32 {
        return cgpu_adapter_query_queue_count(self, _type);
    }
    pub inline fn createDevice(self: *Adapter, desc: *const DeviceDescriptor) Error!DeviceId {
        const result = cgpu_adapter_create_device(self, desc);
        return if (result) |result_object|
            result_object
        else
            Error.CreateFailed;
    }
    pub inline fn freeDevice(self: *Adapter, device: DeviceId) void {
        return cgpu_adapter_free_device(self, device);
    }
};

pub const QueueGroupDescriptor = extern struct {
    queue_type: QueueType,
    queue_count: u32,
};

pub const DeviceDescriptor = extern struct {
    disable_pipeline_cache: bool,
    queue_group_count: u32,
    p_queue_groups: [*]const QueueGroupDescriptor,
};

pub const Device = extern struct {
    adapter: AdapterId,
    proc_table_cache: *const ProcTable,
    next_texture_id: u64,
    is_lost: bool,
    pub inline fn queryVideoMemoryInfo(self: *Device, total: *u64, used_bytes: *u64) void {
        return cgpu_device_query_video_memory_info(self, total, used_bytes);
    }
    pub inline fn querySharedMemoryInfo(self: *Device, total: *u64, used_bytes: *u64) void {
        return cgpu_device_query_shared_memory_info(self, total, used_bytes);
    }
    pub inline fn createFence(self: *Device) Error!FenceId {
        const result = cgpu_device_create_fence(self);
        return if (result) |result_object|
            result_object
        else
            Error.CreateFailed;
    }
    pub inline fn freeFence(self: *Device, fence: FenceId) void {
        return cgpu_device_free_fence(self, fence);
    }
    pub inline fn createSemaphore(self: *Device) Error!SemaphoreId {
        const result = cgpu_device_create_semaphore(self);
        return if (result) |result_object|
            result_object
        else
            Error.CreateFailed;
    }
    pub inline fn freeSemaphore(self: *Device, semaphore: SemaphoreId) void {
        return cgpu_device_free_semaphore(self, semaphore);
    }
    pub inline fn createRootSignaturePool(self: *Device, desc: *const RootSignaturePoolDescriptor) Error!RootSignaturePoolId {
        const result = cgpu_device_create_root_signature_pool(self, desc);
        return if (result) |result_object|
            result_object
        else
            Error.CreateFailed;
    }
    pub inline fn freeRootSignaturePool(self: *Device, pool: RootSignaturePoolId) void {
        return cgpu_device_free_root_signature_pool(self, pool);
    }
    pub inline fn createRootSignature(self: *Device, desc: *const RootSignatureDescriptor) Error!RootSignatureId {
        const result = cgpu_device_create_root_signature(self, desc);
        return if (result) |result_object|
            result_object
        else
            Error.CreateFailed;
    }
    pub inline fn freeRootSignature(self: *Device, signature: RootSignatureId) void {
        return cgpu_device_free_root_signature(self, signature);
    }
    pub inline fn createDescriptorSet(self: *Device, desc: *const DescriptorSetDescriptor) Error!DescriptorSetId {
        const result = cgpu_device_create_descriptor_set(self, desc);
        return if (result) |result_object|
            result_object
        else
            Error.CreateFailed;
    }
    pub inline fn freeDescriptorSet(self: *Device, set: DescriptorSetId) void {
        return cgpu_device_free_descriptor_set(self, set);
    }
    pub inline fn createComputePipeline(self: *Device, desc: *const ComputePipelineDescriptor) Error!ComputePipelineId {
        const result = cgpu_device_create_compute_pipeline(self, desc);
        return if (result) |result_object|
            result_object
        else
            Error.CreateFailed;
    }
    pub inline fn freeComputePipeline(self: *Device, pipeline: ComputePipelineId) void {
        return cgpu_device_free_compute_pipeline(self, pipeline);
    }
    pub inline fn createRenderPipeline(self: *Device, desc: *const RenderPipelineDescriptor) Error!RenderPipelineId {
        const result = cgpu_device_create_render_pipeline(self, desc);
        return if (result) |result_object|
            result_object
        else
            Error.CreateFailed;
    }
    pub inline fn freeRenderPipeline(self: *Device, pipeline: RenderPipelineId) void {
        return cgpu_device_free_render_pipeline(self, pipeline);
    }
    pub inline fn createQueryPool(self: *Device, desc: *const QueryPoolDescriptor) Error!QueryPoolId {
        const result = cgpu_device_create_query_pool(self, desc);
        return if (result) |result_object|
            result_object
        else
            Error.CreateFailed;
    }
    pub inline fn freeQueryPool(self: *Device, pool: QueryPoolId) void {
        return cgpu_device_free_query_pool(self, pool);
    }
    pub inline fn createMemoryPool(self: *Device, desc: *const MemoryPoolDescriptor) Error!MemoryPoolId {
        const result = cgpu_device_create_memory_pool(self, desc);
        return if (result) |result_object|
            result_object
        else
            Error.CreateFailed;
    }
    pub inline fn freeMemoryPool(self: *Device, pool: MemoryPoolId) void {
        return cgpu_device_free_memory_pool(self, pool);
    }
    pub inline fn getQueue(self: *Device, _type: QueueType, index: u32) Error!QueueId {
        const result = cgpu_device_get_queue(self, _type, index);
        return if (result) |result_object|
            result_object
        else
            Error.CreateFailed;
    }
    pub inline fn freeQueue(self: *Device, queue: QueueId) void {
        return cgpu_device_free_queue(self, queue);
    }
    pub inline fn createRenderPass(self: *Device, desc: *const RenderPassDescriptor) Error!RenderPassId {
        const result = cgpu_device_create_render_pass(self, desc);
        return if (result) |result_object|
            result_object
        else
            Error.CreateFailed;
    }
    pub inline fn createFramebuffer(self: *Device, desc: *const FramebufferDescriptor) Error!FramebufferId {
        const result = cgpu_device_create_framebuffer(self, desc);
        return if (result) |result_object|
            result_object
        else
            Error.CreateFailed;
    }
    pub inline fn freeRenderPass(self: *Device, render_pass: RenderPassId) void {
        return cgpu_device_free_render_pass(self, render_pass);
    }
    pub inline fn freeFramebuffer(self: *Device, framebuffer: FramebufferId) void {
        return cgpu_device_free_framebuffer(self, framebuffer);
    }
    pub inline fn createShaderLibrary(self: *Device, desc: *const ShaderLibraryDescriptor) Error!ShaderLibraryId {
        const result = cgpu_device_create_shader_library(self, desc);
        return if (result) |result_object|
            result_object
        else
            Error.CreateFailed;
    }
    pub inline fn freeShaderLibrary(self: *Device, library: ShaderLibraryId) void {
        return cgpu_device_free_shader_library(self, library);
    }
    pub inline fn createBuffer(self: *Device, desc: *const BufferDescriptor) Error!BufferId {
        const result = cgpu_device_create_buffer(self, desc);
        return if (result) |result_object|
            result_object
        else
            Error.CreateFailed;
    }
    pub inline fn freeBuffer(self: *Device, buffer: BufferId) void {
        return cgpu_device_free_buffer(self, buffer);
    }
    pub inline fn createSampler(self: *Device, desc: *const SamplerDescriptor) Error!SamplerId {
        const result = cgpu_device_create_sampler(self, desc);
        return if (result) |result_object|
            result_object
        else
            Error.CreateFailed;
    }
    pub inline fn freeSampler(self: *Device, sampler: SamplerId) void {
        return cgpu_device_free_sampler(self, sampler);
    }
    pub inline fn createTexture(self: *Device, desc: *const TextureDescriptor) Error!TextureId {
        const result = cgpu_device_create_texture(self, desc);
        return if (result) |result_object|
            result_object
        else
            Error.CreateFailed;
    }
    pub inline fn freeTexture(self: *Device, texture: TextureId) void {
        return cgpu_device_free_texture(self, texture);
    }
    pub inline fn createTextureView(self: *Device, desc: *const TextureViewDescriptor) Error!TextureViewId {
        const result = cgpu_device_create_texture_view(self, desc);
        return if (result) |result_object|
            result_object
        else
            Error.CreateFailed;
    }
    pub inline fn freeTextureView(self: *Device, render_target: TextureViewId) void {
        return cgpu_device_free_texture_view(self, render_target);
    }
    pub inline fn tryBindAliasingTexture(self: *Device, desc: *const TextureAliasingBindDescriptor) bool {
        return cgpu_device_try_bind_aliasing_texture(self, desc);
    }
    pub inline fn exportSharedTextureHandle(self: *Device, desc: *const ExportTextureDescriptor) u64 {
        return cgpu_device_export_shared_texture_handle(self, desc);
    }
    pub inline fn importSharedTextureHandle(self: *Device, desc: *const ImportTextureDescriptor) Error!TextureId {
        const result = cgpu_device_import_shared_texture_handle(self, desc);
        return if (result) |result_object|
            result_object
        else
            Error.CreateFailed;
    }
    pub inline fn createSwapChain(self: *Device, desc: *const SwapChainDescriptor) Error!SwapChainId {
        const result = cgpu_device_create_swap_chain(self, desc);
        return if (result) |result_object|
            result_object
        else
            Error.CreateFailed;
    }
    pub inline fn freeSwapChain(self: *Device, swapchain: SwapChainId) void {
        return cgpu_device_free_swap_chain(self, swapchain);
    }
};

pub const Queue = extern struct {
    device: DeviceId,
    _type: QueueType,
    index: u32,
    support_timestamp: bool,
    pub inline fn submit(self: *Queue, desc: *const QueueSubmitDescriptor) SubmitError {
        return cgpu_queue_submit(self, desc);
    }
    pub inline fn present(self: *Queue, desc: *const QueuePresentDescriptor) PresentError {
        return cgpu_queue_present(self, desc);
    }
    pub inline fn waitIdle(self: *Queue) void {
        return cgpu_queue_wait_idle(self);
    }
    pub inline fn getTimestampPeriodNs(self: *Queue) f32 {
        return cgpu_queue_get_timestamp_period_ns(self);
    }
    pub inline fn mapTiledTexture(self: *Queue, desc: *const TiledTextureRegions) void {
        return cgpu_queue_map_tiled_texture(self, desc);
    }
    pub inline fn unmapTiledTexture(self: *Queue, desc: *const TiledTextureRegions) void {
        return cgpu_queue_unmap_tiled_texture(self, desc);
    }
    pub inline fn mapPackedMips(self: *Queue, desc: *const TiledTexturePackedMips) void {
        return cgpu_queue_map_packed_mips(self, desc);
    }
    pub inline fn unmapPackedMips(self: *Queue, desc: *const TiledTexturePackedMips) void {
        return cgpu_queue_unmap_packed_mips(self, desc);
    }
    pub inline fn createCommandPool(self: *Queue, desc: *const CommandPoolDescriptor) Error!CommandPoolId {
        const result = cgpu_queue_create_command_pool(self, desc);
        return if (result) |result_object|
            result_object
        else
            Error.CreateFailed;
    }
    pub inline fn freeCommandPool(self: *Queue, pool: CommandPoolId) void {
        return cgpu_queue_free_command_pool(self, pool);
    }
};

pub const Fence = extern struct {
    device: DeviceId,
    pub inline fn queryStatus(self: *Fence) FenceStatus {
        return cgpu_fence_query_status(self);
    }
};

pub const Semaphore = extern struct {
    device: DeviceId,
};

pub const CommandPool = extern struct {
    queue: QueueId,
    pub inline fn createCommandBuffer(self: *CommandPool, desc: *const CommandBufferDescriptor) Error!CommandBufferId {
        const result = cgpu_command_pool_create_command_buffer(self, desc);
        return if (result) |result_object|
            result_object
        else
            Error.CreateFailed;
    }
    pub inline fn reset(self: *CommandPool) void {
        return cgpu_command_pool_reset(self);
    }
    pub inline fn freeCommandBuffer(self: *CommandPool, cmd: CommandBufferId) void {
        return cgpu_command_pool_free_command_buffer(self, cmd);
    }
};

pub const CommandBuffer = extern struct {
    device: DeviceId,
    pool: CommandPoolId,
    current_dispatch: PipelineType,
    pub inline fn begin(self: *CommandBuffer) void {
        return cgpu_command_buffer_begin(self);
    }
    pub inline fn transferBufferToBuffer(self: *CommandBuffer, desc: *const BufferToBufferTransfer) void {
        return cgpu_command_buffer_transfer_buffer_to_buffer(self, desc);
    }
    pub inline fn transferTextureToTexture(self: *CommandBuffer, desc: *const TextureToTextureTransfer) void {
        return cgpu_command_buffer_transfer_texture_to_texture(self, desc);
    }
    pub inline fn transferBufferToTexture(self: *CommandBuffer, desc: *const BufferToTextureTransfer) void {
        return cgpu_command_buffer_transfer_buffer_to_texture(self, desc);
    }
    pub inline fn transferBufferToTiles(self: *CommandBuffer, desc: *const BufferToTilesTransfer) void {
        return cgpu_command_buffer_transfer_buffer_to_tiles(self, desc);
    }
    pub inline fn resourceBarrier(self: *CommandBuffer, desc: *const ResourceBarrierDescriptor) void {
        return cgpu_command_buffer_resource_barrier(self, desc);
    }
    pub inline fn beginQuery(self: *CommandBuffer, pool: QueryPoolId, desc: *const QueryDescriptor) void {
        return cgpu_command_buffer_begin_query(self, pool, desc);
    }
    pub inline fn endQuery(self: *CommandBuffer, pool: QueryPoolId, desc: *const QueryDescriptor) void {
        return cgpu_command_buffer_end_query(self, pool, desc);
    }
    pub inline fn resetQueryPool(self: *CommandBuffer, pool: QueryPoolId, start_query: u32, query_count: u32) void {
        return cgpu_command_buffer_reset_query_pool(self, pool, start_query, query_count);
    }
    pub inline fn resolveQuery(self: *CommandBuffer, pool: QueryPoolId, readback: BufferId, start_query: u32, query_count: u32) void {
        return cgpu_command_buffer_resolve_query(self, pool, readback, start_query, query_count);
    }
    pub inline fn end(self: *CommandBuffer) void {
        return cgpu_command_buffer_end(self);
    }
    pub inline fn beginComputePass(self: *CommandBuffer, desc: *const ComputePassDescriptor) Error!ComputePassEncoderId {
        const result = cgpu_command_buffer_begin_compute_pass(self, desc);
        return if (result) |result_object|
            result_object
        else
            Error.CreateFailed;
    }
    pub inline fn endComputePass(self: *CommandBuffer, encoder: ComputePassEncoderId) void {
        return cgpu_command_buffer_end_compute_pass(self, encoder);
    }
    pub inline fn beginRenderPass(self: *CommandBuffer, begin_info: *const BeginRenderPassInfo) Error!RenderPassEncoderId {
        const result = cgpu_command_buffer_begin_render_pass(self, begin_info);
        return if (result) |result_object|
            result_object
        else
            Error.CreateFailed;
    }
    pub inline fn endRenderPass(self: *CommandBuffer, encoder: RenderPassEncoderId) void {
        return cgpu_command_buffer_end_render_pass(self, encoder);
    }
    pub inline fn beginEvent(self: *CommandBuffer, event: *const EventInfo) void {
        return cgpu_command_buffer_begin_event(self, event);
    }
    pub inline fn setMarker(self: *CommandBuffer, marker: *const MarkerInfo) void {
        return cgpu_command_buffer_set_marker(self, marker);
    }
    pub inline fn endEvent(self: *CommandBuffer) void {
        return cgpu_command_buffer_end_event(self);
    }
    pub inline fn createStateBuffer(self: *CommandBuffer, desc: *const StateBufferDescriptor) Error!StateBufferId {
        const result = cgpu_command_buffer_create_state_buffer(self, desc);
        return if (result) |result_object|
            result_object
        else
            Error.CreateFailed;
    }
    pub inline fn freeStateBuffer(self: *CommandBuffer, stream: StateBufferId) void {
        return cgpu_command_buffer_free_state_buffer(self, stream);
    }
    pub inline fn createBinder(self: *CommandBuffer) Error!BinderId {
        const result = cgpu_command_buffer_create_binder(self);
        return if (result) |result_object|
            result_object
        else
            Error.CreateFailed;
    }
    pub inline fn freeBinder(self: *CommandBuffer, binder: BinderId) void {
        return cgpu_command_buffer_free_binder(self, binder);
    }
};

pub const QueryPool = extern struct {
    device: DeviceId,
    count: u32,
};

pub const ComputePassEncoder = extern struct {
    device: DeviceId,
    pub inline fn bindDescriptorSet(self: *ComputePassEncoder, set: DescriptorSetId) void {
        return cgpu_compute_pass_encoder_bind_descriptor_set(self, set);
    }
    pub inline fn bindComputePipeline(self: *ComputePassEncoder, pipeline: ComputePipelineId) void {
        return cgpu_compute_pass_encoder_bind_compute_pipeline(self, pipeline);
    }
    pub inline fn dispatch(self: *ComputePassEncoder, x: u32, y: u32, z: u32) void {
        return cgpu_compute_pass_encoder_dispatch(self, x, y, z);
    }
    pub inline fn pushConstants(self: *ComputePassEncoder, rs: RootSignatureId, name: ?[*:0]const u8, data: *const anyopaque) void {
        return cgpu_compute_pass_encoder_push_constants(self, rs, name, data);
    }
    pub inline fn bindStateBuffer(self: *ComputePassEncoder, stream: StateBufferId) void {
        return cgpu_compute_pass_encoder_bind_state_buffer(self, stream);
    }
};

pub const RenderPassEncoder = extern struct {
    device: DeviceId,
    pub inline fn setShadingRate(self: *RenderPassEncoder, shading_rate: ShadingRate, post_rasterize_rate: ShadingRateCombiner, final_rate: ShadingRateCombiner) void {
        return cgpu_render_pass_encoder_set_shading_rate(self, shading_rate, post_rasterize_rate, final_rate);
    }
    pub inline fn bindDescriptorSet(self: *RenderPassEncoder, set: DescriptorSetId) void {
        return cgpu_render_pass_encoder_bind_descriptor_set(self, set);
    }
    pub inline fn setViewport(self: *RenderPassEncoder, x: f32, y: f32, width: f32, height: f32, min_depth: f32, max_depth: f32) void {
        return cgpu_render_pass_encoder_set_viewport(self, x, y, width, height, min_depth, max_depth);
    }
    pub inline fn setScissor(self: *RenderPassEncoder, x: u32, y: u32, width: u32, height: u32) void {
        return cgpu_render_pass_encoder_set_scissor(self, x, y, width, height);
    }
    pub inline fn bindRenderPipeline(self: *RenderPassEncoder, pipeline: RenderPipelineId) void {
        return cgpu_render_pass_encoder_bind_render_pipeline(self, pipeline);
    }
    pub inline fn bindVertexBuffers(self: *RenderPassEncoder, buffer_count: u32, p_buffers: [*]const BufferId, p_strides: [*]const u32, p_offsets: ?[*]const u32) void {
        return cgpu_render_pass_encoder_bind_vertex_buffers(self, buffer_count, p_buffers, p_strides, p_offsets);
    }
    pub inline fn bindIndexBuffer(self: *RenderPassEncoder, buffer: BufferId, index_stride: u32, offset: u64) void {
        return cgpu_render_pass_encoder_bind_index_buffer(self, buffer, index_stride, offset);
    }
    pub inline fn pushConstants(self: *RenderPassEncoder, rs: RootSignatureId, name: ?[*:0]const u8, data: *const anyopaque) void {
        return cgpu_render_pass_encoder_push_constants(self, rs, name, data);
    }
    pub inline fn draw(self: *RenderPassEncoder, vertex_count: u32, first_vertex: u32) void {
        return cgpu_render_pass_encoder_draw(self, vertex_count, first_vertex);
    }
    pub inline fn drawInstanced(self: *RenderPassEncoder, vertex_count: u32, first_vertex: u32, instance_count: u32, first_instance: u32) void {
        return cgpu_render_pass_encoder_draw_instanced(self, vertex_count, first_vertex, instance_count, first_instance);
    }
    pub inline fn drawIndexed(self: *RenderPassEncoder, index_count: u32, first_index: u32, first_vertex: u32) void {
        return cgpu_render_pass_encoder_draw_indexed(self, index_count, first_index, first_vertex);
    }
    pub inline fn drawIndexedInstanced(self: *RenderPassEncoder, index_count: u32, first_index: u32, instance_count: u32, first_instance: u32, first_vertex: u32) void {
        return cgpu_render_pass_encoder_draw_indexed_instanced(self, index_count, first_index, instance_count, first_instance, first_vertex);
    }
    pub inline fn bindStateBuffer(self: *RenderPassEncoder, stream: StateBufferId) void {
        return cgpu_render_pass_encoder_bind_state_buffer(self, stream);
    }
};

pub const RenderPass = extern struct {
    device: DeviceId,
};

pub const FramebufferInfo = extern struct {
    width: u32,
    height: u32,
};

pub const Framebuffer = extern struct {
    device: DeviceId,
    info: *const FramebufferInfo,
};

pub const StateBuffer = extern struct {
    device: DeviceId,
    cmd: CommandBufferId,
    pub inline fn openRasterStateEncoder(self: *StateBuffer, encoder: RenderPassEncoderId) Error!RasterStateEncoderId {
        const result = cgpu_state_buffer_open_raster_state_encoder(self, encoder);
        return if (result) |result_object|
            result_object
        else
            Error.CreateFailed;
    }
    pub inline fn closeRasterStateEncoder(self: *StateBuffer, encoder: RasterStateEncoderId) void {
        return cgpu_state_buffer_close_raster_state_encoder(self, encoder);
    }
    pub inline fn openShaderStateEncoderR(self: *StateBuffer, encoder: RenderPassEncoderId) Error!ShaderStateEncoderId {
        const result = cgpu_state_buffer_open_shader_state_encoder_r(self, encoder);
        return if (result) |result_object|
            result_object
        else
            Error.CreateFailed;
    }
    pub inline fn openShaderStateEncoderC(self: *StateBuffer, encoder: ComputePassEncoderId) Error!ShaderStateEncoderId {
        const result = cgpu_state_buffer_open_shader_state_encoder_c(self, encoder);
        return if (result) |result_object|
            result_object
        else
            Error.CreateFailed;
    }
    pub inline fn closeShaderStateEncoder(self: *StateBuffer, encoder: ShaderStateEncoderId) void {
        return cgpu_state_buffer_close_shader_state_encoder(self, encoder);
    }
    pub inline fn openUserStateEncoder(self: *StateBuffer, encoder: RenderPassEncoderId) Error!UserStateEncoderId {
        const result = cgpu_state_buffer_open_user_state_encoder(self, encoder);
        return if (result) |result_object|
            result_object
        else
            Error.CreateFailed;
    }
    pub inline fn closeUserStateEncoder(self: *StateBuffer, encoder: UserStateEncoderId) void {
        return cgpu_state_buffer_close_user_state_encoder(self, encoder);
    }
};

pub const RasterStateEncoder = extern struct {
    device: DeviceId,
    pub inline fn setViewport(self: *RasterStateEncoder, x: f32, y: f32, width: f32, height: f32, min_depth: f32, max_depth: f32) void {
        return cgpu_raster_state_encoder_set_viewport(self, x, y, width, height, min_depth, max_depth);
    }
    pub inline fn setScissor(self: *RasterStateEncoder, x: u32, y: u32, width: u32, height: u32) void {
        return cgpu_raster_state_encoder_set_scissor(self, x, y, width, height);
    }
    pub inline fn setCullMode(self: *RasterStateEncoder, cull_mode: CullMode) void {
        return cgpu_raster_state_encoder_set_cull_mode(self, cull_mode);
    }
    pub inline fn setFrontFace(self: *RasterStateEncoder, front_face: FrontFace) void {
        return cgpu_raster_state_encoder_set_front_face(self, front_face);
    }
    pub inline fn setPrimitiveTopology(self: *RasterStateEncoder, topology: PrimitiveTopology) void {
        return cgpu_raster_state_encoder_set_primitive_topology(self, topology);
    }
    pub inline fn setDepthTestEnabled(self: *RasterStateEncoder, enabled: bool) void {
        return cgpu_raster_state_encoder_set_depth_test_enabled(self, enabled);
    }
    pub inline fn setDepthWriteEnabled(self: *RasterStateEncoder, enabled: bool) void {
        return cgpu_raster_state_encoder_set_depth_write_enabled(self, enabled);
    }
    pub inline fn setDepthCompareOp(self: *RasterStateEncoder, compare_op: CompareOp) void {
        return cgpu_raster_state_encoder_set_depth_compare_op(self, compare_op);
    }
    pub inline fn setStencilTestEnabled(self: *RasterStateEncoder, enabled: bool) void {
        return cgpu_raster_state_encoder_set_stencil_test_enabled(self, enabled);
    }
    pub inline fn setStencilCompareOp(self: *RasterStateEncoder, faces: StencilFace, fail_op: StencilOp, pass_op: StencilOp, depth_fail_op: StencilOp, compare_op: CompareOp) void {
        return cgpu_raster_state_encoder_set_stencil_compare_op(self, faces, fail_op, pass_op, depth_fail_op, compare_op);
    }
    pub inline fn setFillMode(self: *RasterStateEncoder, fill_mode: FillMode) void {
        return cgpu_raster_state_encoder_set_fill_mode(self, fill_mode);
    }
    pub inline fn setSampleCount(self: *RasterStateEncoder, sample_count: SampleCount) void {
        return cgpu_raster_state_encoder_set_sample_count(self, sample_count);
    }
};

pub const ShaderStateEncoder = extern struct {
    device: DeviceId,
    pub inline fn bindShaders(self: *ShaderStateEncoder, stage_count: u32, p_stages: *const ShaderStage, shaders: *const CompiledShaderId) void {
        return cgpu_shader_state_encoder_bind_shaders(self, stage_count, p_stages, shaders);
    }
    pub inline fn bindLinkedShader(self: *ShaderStateEncoder, linked: LinkedShaderId) void {
        return cgpu_shader_state_encoder_bind_linked_shader(self, linked);
    }
};

pub const UserStateEncoder = extern struct {
    device: DeviceId,
};

pub const Binder = extern struct {
    device: DeviceId,
    cmd: CommandBufferId,
    pub inline fn bindVertexLayout(self: *Binder, layout: *const VertexLayout) void {
        return cgpu_binder_bind_vertex_layout(self, layout);
    }
    pub inline fn bindVertexBuffer(self: *Binder, first_binding: u32, binding_count: u32, p_buffers: *const BufferId, p_offsets: *const u64, p_sizes: *const u64, p_strides: *const u64) void {
        return cgpu_binder_bind_vertex_buffer(self, first_binding, binding_count, p_buffers, p_offsets, p_sizes, p_strides);
    }
};

pub const RootSignaturePoolDescriptor = extern struct {
    name: ?[*:0]const u8 = null,
};

pub const RootSignaturePool = extern struct {
    device: DeviceId,
    pipeline_type: PipelineType,
};

pub const VertexInput = extern struct {
    name: ?[*:0]const u8 = null,
    semantics: ?[*:0]const u8 = null,
    format: VertexFormat,
};

pub const ShaderResource = extern struct {
    name: ?[*:0]const u8 = null,
    name_hash: u64,
    _type: ResourceType,
    dim: TextureDimension,
    set: u32,
    binding: u32,
    size: u32,
    offset: u32,
    stages: ShaderStage,
};

pub const ShaderReflection = extern struct {
    entry_name: ?[*:0]const u8 = null,
    stage: ShaderStage,
    vertex_input_count: u32,
    p_vertex_inputs: [*]VertexInput,
    shader_resource_count: u32,
    p_shader_resources: [*]ShaderResource,
    thread_group_sizes: [3]u32,
};

pub const ShaderLibrary = extern struct {
    device: DeviceId,
    name: ?[*:0]const u8 = null,
    entry_count: u32,
    p_entry_reflections: [*]ShaderReflection,
};

pub const ConstantSpecializationImpl = extern union {
    u: u64,
    i: i64,
    f: f64,
};

pub const ConstantSpecialization = extern struct {
    constant_i_d: u32,
    spec: ConstantSpecializationImpl,
};

pub const ShaderEntryDescriptor = extern struct {
    library: ?ShaderLibraryId = null,
    entry: ?[*:0]const u8 = null,
    stage: ShaderStage,
    constant_count: u32,
    p_constants: ?[*]const ConstantSpecialization = null,
};

pub const RootSignatureDescriptor = extern struct {
    shader_count: u32,
    p_shaders: [*]const ShaderEntryDescriptor,
    static_sampler_count: u32,
    p_static_samplers: ?[*]const SamplerId = null,
    p_static_sampler_names: ?[*][*:0]const u8 = null,
    push_constant_count: u32,
    p_push_constant_names: ?[*][*:0]const u8 = null,
    pool: ?RootSignaturePoolId = null,
};

pub const ParameterTable = extern struct {
    resources_count: u32,
    p_resources: [*]ShaderResource,
    set_index: u32,
};

pub const RootSignature = extern struct {
    device: DeviceId,
    table_count: u32,
    p_tables: [*]ParameterTable,
    push_constant_count: u32,
    p_push_constants: [*]ShaderResource,
    static_sampler_count: u32,
    p_static_samplers: [*]ShaderResource,
    pipeline_type: PipelineType,
    pool: RootSignaturePoolId,
    pool_sig: RootSignatureId,
    pub inline fn compileAndLinkShaders(self: *RootSignature, count: u32, desc: *const CompiledShaderDescriptor) Error!LinkedShaderId {
        const result = cgpu_root_signature_compile_and_link_shaders(self, count, desc);
        return if (result) |result_object|
            result_object
        else
            Error.CreateFailed;
    }
    pub inline fn compileShaders(self: *RootSignature, count: u32, desc: *const CompiledShaderDescriptor, out_isas: *CompiledShaderId) void {
        return cgpu_root_signature_compile_shaders(self, count, desc, out_isas);
    }
    pub inline fn freeCompiledShader(self: *RootSignature, shader: CompiledShaderId) void {
        return cgpu_root_signature_free_compiled_shader(self, shader);
    }
    pub inline fn freeLinkedShader(self: *RootSignature, shader: LinkedShaderId) void {
        return cgpu_root_signature_free_linked_shader(self, shader);
    }
};

pub const DescriptorSet = extern struct {
    root_signature: RootSignatureId,
    index: u32,
    pub inline fn update(self: *DescriptorSet, data_count: u32, p_datas: [*]const DescriptorData) void {
        return cgpu_descriptor_set_update(self, data_count, p_datas);
    }
};

pub const VertexAttribute = extern struct {
    semantic_name: ?[*:0]const u8 = null,
    array_size: u32,
    format: VertexFormat,
    binding: u32,
    offset: u32,
    elem_stride: u32,
    rate: VertexInputRate,
};

pub const VertexLayout = extern struct {
    attribute_count: u32,
    p_attributes: [*]const VertexAttribute,
};

pub const BlendAttachmentState = extern struct {
    enable: bool,
    src_factor: BlendFactor,
    dst_factor: BlendFactor,
    src_alpha_factor: BlendFactor,
    dst_alpha_factor: BlendFactor,
    blend_op: BlendOp,
    blend_alpha_op: BlendOp,
    color_mask: ColorMask,
};

pub const BlendStateDescriptor = extern struct {
    attachment_count: u32,
    p_attachments: [*]const BlendAttachmentState,
    alpha_to_coverage: bool,
    independent_blend: bool,
};

pub const DepthStateDescriptor = extern struct {
    depth_test: bool,
    depth_write: bool,
    depth_op: CompareOp,
    stencil_test: bool,
    stencil_read_mask: u8,
    stencil_write_mask: u8,
    stencil_front_op: CompareOp,
    stencil_front_fail_op: StencilOp,
    depth_front_fail_op: StencilOp,
    stencil_front_pass_op: StencilOp,
    stencil_back_op: CompareOp,
    stencil_back_fail_op: StencilOp,
    depth_back_fail_op: StencilOp,
    stencil_back_pass_op: StencilOp,
};

pub const RasterizerStateDescriptor = extern struct {
    cull_mode: CullMode,
    depth_bias: i32,
    slope_scaled_depth_bias: f32,
    fill_mode: FillMode,
    front_face: FrontFace,
    enable_multi_sample: bool,
    enable_scissor: bool,
    enable_depth_clamp: bool,
};

pub const RenderPipelineDescriptor = extern struct {
    dynamic_state: u64,
    root_signature: RootSignatureId,
    vertex_shader: ?*const ShaderEntryDescriptor = null,
    tesc_shader: ?*const ShaderEntryDescriptor = null,
    tese_shader: ?*const ShaderEntryDescriptor = null,
    geom_shader: ?*const ShaderEntryDescriptor = null,
    fragment_shader: ?*const ShaderEntryDescriptor = null,
    vertex_layout: ?*const VertexLayout = null,
    blend_state: ?*const BlendStateDescriptor = null,
    depth_state: ?*const DepthStateDescriptor = null,
    rasterizer_state: ?*const RasterizerStateDescriptor = null,
    render_pass: RenderPassId,
    subpass: u32,
    render_target_count: u32,
    sample_count: SampleCount,
    prim_topology: PrimitiveTopology,
};

pub const RenderPipeline = extern struct {
    device: DeviceId,
    root_signature: RootSignatureId,
};

pub const ComputePipelineDescriptor = extern struct {
    root_signature: RootSignatureId,
    compute_shader: *const ShaderEntryDescriptor,
};

pub const ComputePipeline = extern struct {
    device: DeviceId,
    root_signature: RootSignatureId,
};

pub const CompiledShader = extern struct {
    device: DeviceId,
    root_signature: RootSignatureId,
};

pub const LinkedShader = extern struct {
    device: DeviceId,
    root_signature: RootSignatureId,
};

pub const DescriptorSetDescriptor = extern struct {
    root_signature: RootSignatureId,
    set_index: u32,
};

pub const BufferParams = extern struct {
    offsets: [*]const u64,
    sizes: [*]const u64,
};

pub const UavParams = extern struct {
    uav_mip_slice: u32,
    blend_mip_chain: bool,
};

pub const DescriptorDataParams = extern union {
    buffers_params: BufferParams,
    uav_params: UavParams,
    enable_stencil_resource: bool,
};

pub const DescriptorDataResource = extern union {
    ptrs: [*]*anyopaque,
    textures: [*]const TextureViewId,
    samplers: [*]const SamplerId,
    buffers: [*]BufferId,
    render_pipelines: [*]RenderPipelineId,
    compute_pipelines: [*]ComputePipelineId,
    descriptor_sets: [*]DescriptorSetId,
};

pub const DescriptorData = extern struct {
    name: ?[*:0]const u8 = null,
    binding: u32,
    binding_type: ResourceType,
    params: DescriptorDataParams,
    resources: DescriptorDataResource,
    count: u32,
};

pub const BufferInfo = extern struct {
    size: u64,
    cpu_mapped_address: [*]u8,
    descriptors: ResourceType,
    memory_usage: MemoryUsage,
};

pub const Buffer = extern struct {
    device: DeviceId,
    info: *const BufferInfo,
    pub inline fn map(self: *Buffer, range: ?*const BufferRange) void {
        return cgpu_buffer_map(self, range);
    }
    pub inline fn unmap(self: *Buffer) void {
        return cgpu_buffer_unmap(self);
    }
};

pub const TextureInfo = extern struct {
    width: u64,
    height: u64,
    depth: u64,
    mip_levels: u32,
    array_size_minus_one: u32,
    size_in_bytes: u64,
    format: TextureFormat,
    sample_count: SampleCount,
    unique_id: u64,
    aspect_mask: TextureViewAspect,
    owns_image: u8,
    is_cube: u8,
    is_allocation_dedicated: u8,
    is_restrict_dedicated: u8,
    is_aliasing: u8,
    is_tiled: u8,
    is_imported: u8,
    can_alias: u8,
    can_export: u8,
};

pub const TiledSubresourceInfo = extern struct {
    layer: u16,
    mip_level: u16,
    width_in_tiles: u32,
    height_in_tiles: u16,
    depth_in_tiles: u16,
};

pub const TiledTextureInfo = extern struct {
    tile_size: u64,
    total_tiles_count: u64,
    alive_tiles_count: u64,
    tile_width_in_texels: u32,
    tile_height_in_texels: u32,
    tile_depth_in_texels: u32,
    subresources: *const TiledSubresourceInfo,
    packed_mip_start: u32,
    packed_mip_count: u32,
    alive_pack_count: u64,
    pack_unaligned: bool,
};

pub const Texture = extern struct {
    device: DeviceId,
    info: *const TextureInfo,
    tiled_resource: *const TiledTextureInfo,
};

pub const TextureViewDescriptor = extern struct {
    name: ?[*:0]const u8 = null,
    texture: TextureId,
    format: TextureFormat,
    usages: TextureViewUsage,
    aspects: TextureViewAspect,
    dims: TextureDimension,
    base_array_layer: u32,
    array_layer_count: u32,
    base_mip_level: u32,
    mip_level_count: u32,
};

pub const QueryPoolDescriptor = extern struct {
    _type: QueryType,
    query_count: u32,
};

pub const TextureView = extern struct {
    device: DeviceId,
    info: TextureViewDescriptor,
};

pub const Sampler = extern struct {
    device: DeviceId,
};

pub const SwapChain = extern struct {
    device: DeviceId,
    back_buffer_count: u32,
    p_back_buffers: [*]const TextureId,
    pub inline fn acquireNextImage(self: *SwapChain, desc: *const AcquireNextDescriptor, p_image_index: *u32) AcquireNextImageError {
        return cgpu_swap_chain_acquire_next_image(self, desc, p_image_index);
    }
};

pub const Surface = extern struct {};

pub const BufferRange = extern struct {
    offset: u64,
    size: u64,
};

pub const MemoryPoolDescriptor = extern struct {
    _type: MemoryPoolType,
    memory_usage: MemoryUsage,
    block_size: u64,
    min_block_count: u32,
    max_block_count: u32,
    min_alloc_alignment: u64,
};

pub const MemoryPool = extern struct {
    device: DeviceId,
    _type: MemoryPoolType,
};

pub const QueueSubmitDescriptor = extern struct {
    cmd_count: u32,
    p_cmds: [*]const CommandBufferId,
    signal_fence: FenceId,
    wait_semaphore_count: u32,
    p_wait_semaphores: [*]const SemaphoreId,
    signal_semaphore_count: u32,
    p_signal_semaphores: [*]const SemaphoreId,
};

pub const QueuePresentDescriptor = extern struct {
    swapchain: SwapChainId,
    wait_semaphore_count: u32,
    p_wait_semaphores: [*]const SemaphoreId,
    index: u8,
};

pub const Coordinate = extern struct {
    x: u32,
    y: u32,
    z: u32,
};

pub const CoordinateRegion = extern struct {
    start: Coordinate,
    end: Coordinate,
};

pub const TextureCoordinateRegion = extern struct {
    start: Coordinate,
    end: Coordinate,
    mip_level: u32,
    layer: u32,
};

pub const TiledTextureRegions = extern struct {
    texture: TextureId,
    region_count: u32,
    p_regions: [*]const TextureCoordinateRegion,
};

pub const TiledTexturePackedMip = extern struct {
    texture: TextureId,
    layer: u32,
};

pub const TiledTexturePackedMips = extern struct {
    packed_mip_count: u32,
    p_packed_mips: [*]const TiledTexturePackedMip,
};

pub const ColorAttachment = extern struct {
    format: TextureFormat,
    load_action: LoadAction,
    store_action: StoreAction,
};

pub const DepthStencilAttachment = extern struct {
    format: TextureFormat,
    depth_load_action: LoadAction,
    depth_store_action: StoreAction,
    stencil_load_action: LoadAction,
    stencil_store_action: StoreAction,
};

pub const RenderPassDescriptor = extern struct {
    sample_count: SampleCount,
    color_attachments: [MaxMrtCount]ColorAttachment,
    depth_stencil: DepthStencilAttachment,
};

pub const FramebufferDescriptor = extern struct {
    renderpass: RenderPassId,
    attachment_count: u32,
    p_attachments: [MaxAttachmentCount]TextureViewId,
    width: u32,
    height: u32,
    layers: u32,
};

pub const PipelineReflection = extern struct {
    stages: [ShaderStageCount]*ShaderReflection,
    shader_resources_count: u32,
    p_shader_resources: [*]const ShaderResource,
};

pub const ClearValue = extern struct {
    color: [4]f32,
    depth: f32,
    stencil: u8,
    is_color: bool,
};

pub const QueryDescriptor = extern struct {
    index: u32,
    stage: ShaderStage,
};

pub const AcquireNextDescriptor = extern struct {
    signal_semaphore: ?SemaphoreId = null,
    fence: ?FenceId = null,
};

pub const TextureSubresource = extern struct {
    aspects: TextureViewAspect,
    mip_level: u32,
    base_array_layer: u32,
    layer_count: u32,
};

pub const TextureRegion = extern struct {
    x: u32,
    y: u32,
    z: u32,
    width: u32,
    height: u32,
    depth: u32,
};

pub const BufferTextureLayout = extern struct {
    offset: u64,
    row_pitch: u64,
    slice_pitch: u64,
};

pub const BufferToBufferTransfer = extern struct {
    src: BufferId,
    src_offset: u64,
    size: u64,
    dst: BufferId,
    dst_offset: u64,
};

pub const BufferToTilesTransfer = extern struct {
    src: BufferId,
    src_offset: u64,
    dst: TextureId,
    region: TextureCoordinateRegion,
};

pub const TextureToTextureTransfer = extern struct {
    src: TextureId,
    src_subresource: TextureSubresource,
    src_region: TextureRegion,
    dst: TextureId,
    dst_subresource: TextureSubresource,
    dst_coordinate: Coordinate,
};

pub const BufferToTextureTransfer = extern struct {
    src: BufferId,
    src_layout: BufferTextureLayout,
    dst: TextureId,
    dst_subresource: TextureSubresource,
    dst_region: TextureRegion,
};

pub const BufferBarrier = extern struct {
    buffer: BufferId,
    src_state: ResourceState,
    dst_state: ResourceState,
    queue_acquire: u8,
    queue_release: u8,
    queue_type: QueueType,
};

pub const TextureBarrier = extern struct {
    texture: TextureId,
    src_state: ResourceState,
    dst_state: ResourceState,
    queue_acquire: u8,
    queue_release: u8,
    queue_type: QueueType,
    subresource_barrier: u8,
    mip_level: u8,
    array_layer: u16,
};

pub const ResourceBarrierDescriptor = extern struct {
    buffer_barrier_count: u32,
    p_buffer_barriers: [*]const BufferBarrier,
    texture_barrier_count: u32,
    p_texture_barriers: [*]const TextureBarrier,
};

pub const CommandPoolDescriptor = extern struct {
    name: ?[*:0]const u8 = null,
};

pub const CommandBufferDescriptor = extern struct {
    is_secondary: bool,
};

pub const SwapChainDescriptor = extern struct {
    present_queue_count: u32,
    p_present_queues: [*]const QueueId,
    surface: SurfaceId,
    image_count: u32,
    width: u32,
    height: u32,
    enable_vsync: bool,
    use_flip_swap_effect: bool,
    format: TextureFormat,
    old_swap_chain: ?SwapChainId = null,
};

pub const ComputePassDescriptor = extern struct {
    name: ?[*:0]const u8 = null,
};

pub const CompiledShaderDescriptor = extern struct {
    entry: ShaderEntryDescriptor,
    shader_code: *anyopaque,
    code_size: u64,
};

pub const ShaderLibraryDescriptor = extern struct {
    name: ?[*:0]const u8 = null,
    code_size: usize,
    p_codes: [*]const u8,
    stage: ShaderStage,
    reflection_only: bool,
};

pub const BufferDescriptor = extern struct {
    size: u64,
    count_buffer: ?BufferId = null,
    name: ?[*:0]const u8 = null,
    descriptors: ResourceType,
    memory_usage: MemoryUsage,
    format: TextureFormat,
    flags: BufferCreationUsage,
    first_element: u64,
    element_count: u64,
    element_stride: u64,
    owner_queue: ?QueueId = null,
    start_state: ResourceState,
    prefer_on_device: bool,
    prefer_on_host: bool,
};

pub const TextureDescriptor = extern struct {
    name: ?[*:0]const u8 = null,
    native_handle: ?*const anyopaque = null,
    flags: TextureCreationUsage,
    width: u64,
    height: u64,
    depth: u64,
    array_size: u32,
    format: TextureFormat,
    mip_levels: u32,
    sample_count: SampleCount,
    sample_quality: u32,
    owner_queue: ?QueueId = null,
    start_state: ResourceState,
    descriptors: ResourceType,
    is_restrict_dedicated: u32,
};

pub const ExportTextureDescriptor = extern struct {
    texture: TextureId,
};

pub const ImportTextureDescriptor = extern struct {
    backend: Backend,
    shared_handle: u64,
    width: u64,
    height: u64,
    depth: u64,
    size_in_bytes: u64,
    format: TextureFormat,
    mip_levels: u32,
};

pub const TextureAliasingBindDescriptor = extern struct {
    aliased: TextureId,
    aliasing: TextureId,
};

pub const SamplerDescriptor = extern struct {
    min_filter: FilterType,
    mag_filter: FilterType,
    mipmap_mode: MipMapMode,
    address_u: AddressMode,
    address_v: AddressMode,
    address_w: AddressMode,
    mip_lod_bias: f32,
    max_anisotropy: f32,
    compare_func: CompareOp,
};

pub const BeginRenderPassInfo = extern struct {
    render_pass: RenderPassId,
    framebuffer: FramebufferId,
    clear_value_count: u32,
    p_clear_values: ?[*]const ClearValue = null,
};

pub const EventInfo = extern struct {
    name: ?[*:0]const u8 = null,
    color: [4]f32,
};

pub const MarkerInfo = extern struct {
    name: ?[*:0]const u8 = null,
    color: [4]f32,
};

pub const StateBufferDescriptor = extern struct {};

pub const ProcTable = extern struct {
    create_instance: ?*const CreateInstance = null,
    query_instance_features: ?*const QueryInstanceFeatures = null,
    free_instance: ?*const FreeInstance = null,
    enum_adapters: ?*const EnumAdapters = null,
    query_adapter_detail: ?*const QueryAdapterDetail = null,
    query_video_memory_info: ?*const QueryVideoMemoryInfo = null,
    query_shared_memory_info: ?*const QuerySharedMemoryInfo = null,
    query_queue_count: ?*const QueryQueueCount = null,
    create_device: ?*const CreateDevice = null,
    free_device: ?*const FreeDevice = null,
    create_fence: ?*const CreateFence = null,
    wait_fences: ?*const WaitFences = null,
    reset_fences: ?*const ResetFences = null,
    query_fence_status: ?*const QueryFenceStatus = null,
    free_fence: ?*const FreeFence = null,
    create_semaphore: ?*const CreateSemaphore = null,
    free_semaphore: ?*const FreeSemaphore = null,
    create_root_signature_pool: ?*const CreateRootSignaturePool = null,
    free_root_signature_pool: ?*const FreeRootSignaturePool = null,
    create_root_signature: ?*const CreateRootSignature = null,
    free_root_signature: ?*const FreeRootSignature = null,
    create_descriptor_set: ?*const CreateDescriptorSet = null,
    free_descriptor_set: ?*const FreeDescriptorSet = null,
    update_descriptor_set: ?*const UpdateDescriptorSet = null,
    create_compute_pipeline: ?*const CreateComputePipeline = null,
    free_compute_pipeline: ?*const FreeComputePipeline = null,
    create_render_pipeline: ?*const CreateRenderPipeline = null,
    free_render_pipeline: ?*const FreeRenderPipeline = null,
    create_memory_pool: ?*const CreateMemoryPool = null,
    free_memory_pool: ?*const FreeMemoryPool = null,
    create_query_pool: ?*const CreateQueryPool = null,
    free_query_pool: ?*const FreeQueryPool = null,
    get_queue: ?*const GetQueue = null,
    submit_queue: ?*const SubmitQueue = null,
    wait_queue_idle: ?*const WaitQueueIdle = null,
    queue_present: ?*const QueuePresent = null,
    queue_get_timestamp_period: ?*const QueueGetTimestampPeriodNS = null,
    queue_map_tiled_texture: ?*const QueueMapTiledTexture = null,
    queue_unmap_tiled_texture: ?*const QueueUnmapTiledTexture = null,
    queue_map_packed_mips: ?*const QueueMapPackedMips = null,
    queue_unmap_packed_mips: ?*const QueueUnmapPackedMips = null,
    free_queue: ?*const FreeQueue = null,
    create_render_pass: ?*const CreateRenderPass = null,
    create_framebuffer: ?*const CreateFramebuffer = null,
    free_render_pass: ?*const FreeRenderPass = null,
    free_framebuffer: ?*const FreeFramebuffer = null,
    create_command_pool: ?*const CreateCommandPool = null,
    create_command_buffer: ?*const CreateCommandBuffer = null,
    reset_command_pool: ?*const ResetCommandPool = null,
    free_command_buffer: ?*const FreeCommandBuffer = null,
    free_command_pool: ?*const FreeCommandPool = null,
    create_shader_library: ?*const CreateShaderLibrary = null,
    free_shader_library: ?*const FreeShaderLibrary = null,
    create_buffer: ?*const CreateBuffer = null,
    map_buffer: ?*const MapBuffer = null,
    unmap_buffer: ?*const UnmapBuffer = null,
    free_buffer: ?*const FreeBuffer = null,
    create_sampler: ?*const CreateSampler = null,
    free_sampler: ?*const FreeSampler = null,
    create_texture: ?*const CreateTexture = null,
    free_texture: ?*const FreeTexture = null,
    create_texture_view: ?*const CreateTextureView = null,
    free_texture_view: ?*const FreeTextureView = null,
    try_bind_aliasing_texture: ?*const TryBindAliasingTexture = null,
    export_shared_texture_handle: ?*const ExportSharedTextureHandle = null,
    import_shared_texture_handle: ?*const ImportSharedTextureHandle = null,
    create_swap_chain: ?*const CreateSwapChain = null,
    acquire_next_image: ?*const AcquireNextImage = null,
    free_swap_chain: ?*const FreeSwapChain = null,
    cmd_begin: ?*const CmdBegin = null,
    cmd_transfer_buffer_to_buffer: ?*const CmdTransferBufferToBuffer = null,
    cmd_transfer_buffer_to_texture: ?*const CmdTransferBufferToTexture = null,
    cmd_transfer_buffer_to_tiles: ?*const CmdTransferBufferToTiles = null,
    cmd_transfer_texture_to_texture: ?*const CmdTransferTextureToTexture = null,
    cmd_resource_barrier: ?*const CmdResourceBarrier = null,
    cmd_begin_query: ?*const CmdBeginQuery = null,
    cmd_end_query: ?*const CmdEndQuery = null,
    cmd_reset_query_pool: ?*const CmdResetQueryPool = null,
    cmd_resolve_query: ?*const CmdResolveQuery = null,
    cmd_end: ?*const CmdEnd = null,
    cmd_begin_compute_pass: ?*const CmdBeginComputePass = null,
    compute_encoder_bind_descriptor_set: ?*const ComputeEncoderBindDescriptorSet = null,
    compute_encoder_push_constants: ?*const ComputeEncoderPushConstants = null,
    compute_encoder_bind_pipeline: ?*const ComputeEncoderBindPipeline = null,
    compute_encoder_dispatch: ?*const ComputeEncoderDispatch = null,
    cmd_end_compute_pass: ?*const CmdEndComputePass = null,
    cmd_begin_render_pass: ?*const CmdBeginRenderPass = null,
    render_encoder_set_shading_rate: ?*const RenderEncoderSetShadingRate = null,
    render_encoder_bind_descriptor_set: ?*const RenderEncoderBindDescriptorSet = null,
    render_encoder_bind_pipeline: ?*const RenderEncoderBindPipeline = null,
    render_encoder_bind_vertex_buffers: ?*const RenderEncoderBindVertexBuffers = null,
    render_encoder_bind_index_buffer: ?*const RenderEncoderBindIndexBuffer = null,
    render_encoder_push_constants: ?*const RenderEncoderPushConstants = null,
    render_encoder_set_viewport: ?*const RenderEncoderSetViewport = null,
    render_encoder_set_scissor: ?*const RenderEncoderSetScissor = null,
    render_encoder_draw: ?*const RenderEncoderDraw = null,
    render_encoder_draw_instanced: ?*const RenderEncoderDrawInstanced = null,
    render_encoder_draw_indexed: ?*const RenderEncoderDrawIndexed = null,
    render_encoder_draw_indexed_instanced: ?*const RenderEncoderDrawIndexedInstanced = null,
    cmd_end_render_pass: ?*const CmdEndRenderPass = null,
    cmd_begin_event: ?*const CmdBeginEvent = null,
    cmd_set_marker: ?*const CmdSetMarker = null,
    cmd_end_event: ?*const CmdEndEvent = null,
    compile_and_link_shaders: ?*const CompileAndLinkShaders = null,
    compile_shaders: ?*const CompileShaders = null,
    free_compiled_shader: ?*const FreeCompiledShader = null,
    free_linked_shader: ?*const FreeLinkedShader = null,
    create_state_buffer: ?*const CreateStateBuffer = null,
    render_encoder_bind_state_buffer: ?*const RenderEncoderBindStateBuffer = null,
    compute_encoder_bind_state_buffer: ?*const ComputeEncoderBindStateBuffer = null,
    free_state_buffer: ?*const FreeStateBuffer = null,
    open_raster_state_encoder: ?*const OpenRasterStateEncoder = null,
    raster_state_encoder_set_viewport: ?*const RasterStateEncoderSetViewport = null,
    raster_state_encoder_set_scissor: ?*const RasterStateEncoderSetScissor = null,
    raster_state_encoder_set_cull_mode: ?*const RasterStateEncoderSetCullMode = null,
    raster_state_encoder_set_front_face: ?*const RasterStateEncoderSetFrontFace = null,
    raster_state_encoder_set_primitive_topology: ?*const RasterStateEncoderSetPrimitiveTopology = null,
    raster_state_encoder_set_depth_test_enabled: ?*const RasterStateEncoderSetDepthTestEnabled = null,
    raster_state_encoder_set_depth_write_enabled: ?*const RasterStateEncoderSetDepthWriteEnabled = null,
    raster_state_encoder_set_depth_compare_op: ?*const RasterStateEncoderSetDepthCompareOp = null,
    raster_state_encoder_set_stencil_test_enabled: ?*const RasterStateEncoderSetStencilTestEnabled = null,
    raster_state_encoder_set_stencil_compare_op: ?*const RasterStateEncoderSetStencilCompareOp = null,
    raster_state_encoder_set_fill_mode: ?*const RasterStateEncoderSetFillMode = null,
    raster_state_encoder_set_sample_count: ?*const RasterStateEncoderSetSampleCount = null,
    close_raster_state_encoder: ?*const CloseRasterStateEncoder = null,
    open_shader_state_encoder_r: ?*const OpenShaderStateEncoderR = null,
    open_shader_state_encoder_c: ?*const OpenShaderStateEncoderC = null,
    shader_state_encoder_bind_shaders: ?*const ShaderStateEncoderBindShaders = null,
    shader_state_encoder_bind_linked_shader: ?*const ShaderStateEncoderBindLinkedShader = null,
    close_shader_state_encoder: ?*const CloseShaderStateEncoder = null,
    open_user_state_encoder: ?*const OpenUserStateEncoder = null,
    close_user_state_encoder: ?*const CloseUserStateEncoder = null,
    create_binder: ?*const CreateBinder = null,
    binder_bind_vertex_layout: ?*const BinderBindVertexLayout = null,
    binder_bind_vertex_buffer: ?*const BinderBindVertexBuffer = null,
    free_binder: ?*const FreeBinder = null,
};

pub const SurfacesProcTable = extern struct {
    from_hwnd: ?*const CreateSurfaceFromHwnd = null,
    from_native_window: ?*const CreateSurfaceFromNativeWindow = null,
    free_surface: ?*const FreeSurface = null,
};

pub const RuntimeTable = extern struct {};

pub fn FormatUtil_IsDepthStencilFormat(arg: TextureFormat) bool {
    return switch (arg) {
        .d24_unorm_s8_uint => true,
        .d32_sfloat_s8_uint => true,
        .d32_sfloat => true,
        .x8_d24_unorm_pack32 => true,
        .d16_unorm => true,
        .d16_unorm_s8_uint => true,
        .s8_uint => true,
        else => false,
    };
}

pub fn FormatUtil_IsDepthOnlyFormat(arg: TextureFormat) bool {
    return switch (arg) {
        .d32_sfloat => true,
        .d16_unorm => true,
        else => false,
    };
}

pub fn FormatUtil_ContainDepth(arg: TextureFormat) bool {
    return switch (arg) {
        .d24_unorm_s8_uint => true,
        .d32_sfloat_s8_uint => true,
        .d32_sfloat => true,
        .x8_d24_unorm_pack32 => true,
        .d16_unorm => true,
        .d16_unorm_s8_uint => true,
        else => false,
    };
}

pub fn FormatUtil_ContainStencil(arg: TextureFormat) bool {
    return switch (arg) {
        .d24_unorm_s8_uint => true,
        .d32_sfloat_s8_uint => true,
        .d16_unorm_s8_uint => true,
        .s8_uint => true,
        else => false,
    };
}

pub fn FormatUtil_BitSizeOfBlock(arg: TextureFormat) u32 {
    return switch (arg) {
        .undefined => 0,
        .r8_unorm => 8,
        .r8_snorm => 8,
        .r8_uint => 8,
        .r8_sint => 8,
        .r8_srgb => 8,
        .r8g8_unorm => 16,
        .r8g8_snorm => 16,
        .r8g8_uint => 16,
        .r8g8_sint => 16,
        .r8g8_srgb => 16,
        .r16_unorm => 16,
        .r16_snorm => 16,
        .r16_uint => 16,
        .r16_sint => 16,
        .r16_sfloat => 16,
        .r8g8b8_unorm => 24,
        .r8g8b8_snorm => 24,
        .r8g8b8_uint => 24,
        .r8g8b8_sint => 24,
        .r8g8b8_srgb => 24,
        .b8g8r8_unorm => 24,
        .b8g8r8_snorm => 24,
        .b8g8r8_uint => 24,
        .b8g8r8_sint => 24,
        .b8g8r8_srgb => 24,
        .r16g16b16_unorm => 48,
        .r16g16b16_snorm => 48,
        .r16g16b16_uint => 48,
        .r16g16b16_sint => 48,
        .r16g16b16_sfloat => 48,
        .r16g16b16a16_unorm => 64,
        .r16g16b16a16_snorm => 64,
        .r16g16b16a16_uint => 64,
        .r16g16b16a16_sint => 64,
        .r16g16b16a16_sfloat => 64,
        .r32g32_uint => 64,
        .r32g32_sint => 64,
        .r32g32_sfloat => 64,
        .r32g32b32_uint => 96,
        .r32g32b32_sint => 96,
        .r32g32b32_sfloat => 96,
        .r32g32b32a32_uint => 128,
        .r32g32b32a32_sint => 128,
        .r32g32b32a32_sfloat => 128,
        .r64_uint => 64,
        .r64_sint => 64,
        .r64_sfloat => 64,
        .r64g64_uint => 128,
        .r64g64_sint => 128,
        .r64g64_sfloat => 128,
        .r64g64b64_uint => 192,
        .r64g64b64_sint => 192,
        .r64g64b64_sfloat => 192,
        .r64g64b64a64_uint => 256,
        .r64g64b64a64_sint => 256,
        .r64g64b64a64_sfloat => 256,
        .d16_unorm => 16,
        .s8_uint => 8,
        .d32_sfloat_s8_uint => 64,
        .bc1_rgb_unorm_block => 64,
        .bc1_rgb_srgb_block => 64,
        .bc1_rgba_unorm_block => 64,
        .bc1_rgba_srgb_block => 64,
        .bc2_unorm_block => 128,
        .bc2_srgb_block => 128,
        .bc3_unorm_block => 128,
        .bc3_srgb_block => 128,
        .bc4_unorm_block => 64,
        .bc4_snorm_block => 64,
        .bc5_unorm_block => 128,
        .bc5_snorm_block => 128,
        .bc6h_ufloat_block => 128,
        .bc6h_sfloat_block => 128,
        .bc7_unorm_block => 128,
        .bc7_srgb_block => 128,
        .pvrtc1_2bpp_unorm_block => 64,
        .pvrtc1_4bpp_unorm_block => 64,
        .pvrtc2_2bpp_unorm_block => 64,
        .pvrtc2_4bpp_unorm_block => 64,
        .pvrtc1_2bpp_srgb_block => 64,
        .pvrtc1_4bpp_srgb_block => 64,
        .pvrtc2_2bpp_srgb_block => 64,
        .pvrtc2_4bpp_srgb_block => 64,
        .etc2_r8g8b8_unorm_block => 64,
        .etc2_r8g8b8_srgb_block => 64,
        .etc2_r8g8b8a1_unorm_block => 64,
        .etc2_r8g8b8a1_srgb_block => 64,
        .etc2_r8g8b8a8_unorm_block => 64,
        .etc2_r8g8b8a8_srgb_block => 64,
        .eac_r11_unorm_block => 64,
        .eac_r11_snorm_block => 64,
        .eac_r11g11_unorm_block => 64,
        .eac_r11g11_snorm_block => 64,
        .astc_4x4_unorm_block => 128,
        .astc_4x4_srgb_block => 128,
        .astc_5x4_unorm_block => 128,
        .astc_5x4_srgb_block => 128,
        .astc_5x5_unorm_block => 128,
        .astc_5x5_srgb_block => 128,
        .astc_6x5_unorm_block => 128,
        .astc_6x5_srgb_block => 128,
        .astc_6x6_unorm_block => 128,
        .astc_6x6_srgb_block => 128,
        .astc_8x5_unorm_block => 128,
        .astc_8x5_srgb_block => 128,
        .astc_8x6_unorm_block => 128,
        .astc_8x6_srgb_block => 128,
        .astc_8x8_unorm_block => 128,
        .astc_8x8_srgb_block => 128,
        .astc_10x5_unorm_block => 128,
        .astc_10x5_srgb_block => 128,
        .astc_10x6_unorm_block => 128,
        .astc_10x6_srgb_block => 128,
        .astc_10x8_unorm_block => 128,
        .astc_10x8_srgb_block => 128,
        .astc_10x10_unorm_block => 128,
        .astc_10x10_srgb_block => 128,
        .astc_12x10_unorm_block => 128,
        .astc_12x10_srgb_block => 128,
        .astc_12x12_unorm_block => 128,
        .astc_12x12_srgb_block => 128,
        .astc_4x4_sfloat_block => 128,
        .astc_5x4_sfloat_block => 128,
        .astc_5x5_sfloat_block => 128,
        .astc_6x5_sfloat_block => 128,
        .astc_6x6_sfloat_block => 128,
        .astc_8x5_sfloat_block => 128,
        .astc_8x6_sfloat_block => 128,
        .astc_8x8_sfloat_block => 128,
        .astc_10x5_sfloat_block => 128,
        .astc_10x6_sfloat_block => 128,
        .astc_10x8_sfloat_block => 128,
        .astc_10x10_sfloat_block => 128,
        .astc_12x10_sfloat_block => 128,
        .astc_12x12_sfloat_block => 128,
        else => 32,
    };
}

pub fn FormatUtil_WidthOfBlock(arg: TextureFormat) u32 {
    return switch (arg) {
        .undefined => 1,
        .bc1_rgb_unorm_block => 4,
        .bc1_rgb_srgb_block => 4,
        .bc1_rgba_unorm_block => 4,
        .bc1_rgba_srgb_block => 4,
        .bc2_unorm_block => 4,
        .bc2_srgb_block => 4,
        .bc3_unorm_block => 4,
        .bc3_srgb_block => 4,
        .bc4_unorm_block => 4,
        .bc4_snorm_block => 4,
        .bc5_unorm_block => 4,
        .bc5_snorm_block => 4,
        .bc6h_ufloat_block => 4,
        .bc6h_sfloat_block => 4,
        .bc7_unorm_block => 4,
        .bc7_srgb_block => 4,
        .pvrtc1_2bpp_unorm_block => 8,
        .pvrtc1_4bpp_unorm_block => 4,
        .pvrtc2_2bpp_unorm_block => 8,
        .pvrtc2_4bpp_unorm_block => 4,
        .pvrtc1_2bpp_srgb_block => 8,
        .pvrtc1_4bpp_srgb_block => 4,
        .pvrtc2_2bpp_srgb_block => 8,
        .pvrtc2_4bpp_srgb_block => 4,
        .etc2_r8g8b8_unorm_block => 4,
        .etc2_r8g8b8_srgb_block => 4,
        .etc2_r8g8b8a1_unorm_block => 4,
        .etc2_r8g8b8a1_srgb_block => 4,
        .etc2_r8g8b8a8_unorm_block => 4,
        .etc2_r8g8b8a8_srgb_block => 4,
        .eac_r11_unorm_block => 4,
        .eac_r11_snorm_block => 4,
        .eac_r11g11_unorm_block => 4,
        .eac_r11g11_snorm_block => 4,
        .astc_4x4_unorm_block => 4,
        .astc_4x4_srgb_block => 4,
        .astc_5x4_unorm_block => 5,
        .astc_5x4_srgb_block => 5,
        .astc_5x5_unorm_block => 5,
        .astc_5x5_srgb_block => 5,
        .astc_6x5_unorm_block => 6,
        .astc_6x5_srgb_block => 6,
        .astc_6x6_unorm_block => 6,
        .astc_6x6_srgb_block => 6,
        .astc_8x5_unorm_block => 8,
        .astc_8x5_srgb_block => 8,
        .astc_8x6_unorm_block => 8,
        .astc_8x6_srgb_block => 8,
        .astc_8x8_unorm_block => 8,
        .astc_8x8_srgb_block => 8,
        .astc_10x5_unorm_block => 10,
        .astc_10x5_srgb_block => 10,
        .astc_10x6_unorm_block => 10,
        .astc_10x6_srgb_block => 10,
        .astc_10x8_unorm_block => 10,
        .astc_10x8_srgb_block => 10,
        .astc_10x10_unorm_block => 10,
        .astc_10x10_srgb_block => 10,
        .astc_12x10_unorm_block => 12,
        .astc_12x10_srgb_block => 12,
        .astc_12x12_unorm_block => 12,
        .astc_12x12_srgb_block => 12,
        .astc_4x4_sfloat_block => 4,
        .astc_5x4_sfloat_block => 5,
        .astc_5x5_sfloat_block => 5,
        .astc_6x5_sfloat_block => 6,
        .astc_6x6_sfloat_block => 6,
        .astc_8x5_sfloat_block => 8,
        .astc_8x6_sfloat_block => 8,
        .astc_8x8_sfloat_block => 8,
        .astc_10x5_sfloat_block => 10,
        .astc_10x6_sfloat_block => 10,
        .astc_10x8_sfloat_block => 10,
        .astc_10x10_sfloat_block => 10,
        .astc_12x10_sfloat_block => 12,
        .astc_12x12_sfloat_block => 12,
        else => 1,
    };
}

pub fn FormatUtil_HeightOfBlock(arg: TextureFormat) u32 {
    return switch (arg) {
        .undefined => 1,
        .bc1_rgb_unorm_block => 4,
        .bc1_rgb_srgb_block => 4,
        .bc1_rgba_unorm_block => 4,
        .bc1_rgba_srgb_block => 4,
        .bc2_unorm_block => 4,
        .bc2_srgb_block => 4,
        .bc3_unorm_block => 4,
        .bc3_srgb_block => 4,
        .bc4_unorm_block => 4,
        .bc4_snorm_block => 4,
        .bc5_unorm_block => 4,
        .bc5_snorm_block => 4,
        .bc6h_ufloat_block => 4,
        .bc6h_sfloat_block => 4,
        .bc7_unorm_block => 4,
        .bc7_srgb_block => 4,
        .pvrtc1_2bpp_unorm_block => 4,
        .pvrtc1_4bpp_unorm_block => 4,
        .pvrtc2_2bpp_unorm_block => 4,
        .pvrtc2_4bpp_unorm_block => 4,
        .pvrtc1_2bpp_srgb_block => 4,
        .pvrtc1_4bpp_srgb_block => 4,
        .pvrtc2_2bpp_srgb_block => 4,
        .pvrtc2_4bpp_srgb_block => 4,
        .etc2_r8g8b8_unorm_block => 4,
        .etc2_r8g8b8_srgb_block => 4,
        .etc2_r8g8b8a1_unorm_block => 4,
        .etc2_r8g8b8a1_srgb_block => 4,
        .etc2_r8g8b8a8_unorm_block => 4,
        .etc2_r8g8b8a8_srgb_block => 4,
        .eac_r11_unorm_block => 4,
        .eac_r11_snorm_block => 4,
        .eac_r11g11_unorm_block => 4,
        .eac_r11g11_snorm_block => 4,
        .astc_4x4_unorm_block => 4,
        .astc_4x4_srgb_block => 4,
        .astc_5x4_unorm_block => 4,
        .astc_5x4_srgb_block => 4,
        .astc_5x5_unorm_block => 5,
        .astc_5x5_srgb_block => 5,
        .astc_6x5_unorm_block => 5,
        .astc_6x5_srgb_block => 5,
        .astc_6x6_unorm_block => 6,
        .astc_6x6_srgb_block => 6,
        .astc_8x5_unorm_block => 5,
        .astc_8x5_srgb_block => 5,
        .astc_8x6_unorm_block => 6,
        .astc_8x6_srgb_block => 6,
        .astc_8x8_unorm_block => 8,
        .astc_8x8_srgb_block => 8,
        .astc_10x5_unorm_block => 5,
        .astc_10x5_srgb_block => 5,
        .astc_10x6_unorm_block => 6,
        .astc_10x6_srgb_block => 6,
        .astc_10x8_unorm_block => 8,
        .astc_10x8_srgb_block => 8,
        .astc_10x10_unorm_block => 10,
        .astc_10x10_srgb_block => 10,
        .astc_12x10_unorm_block => 10,
        .astc_12x10_srgb_block => 10,
        .astc_12x12_unorm_block => 12,
        .astc_12x12_srgb_block => 12,
        .astc_4x4_sfloat_block => 4,
        .astc_5x4_sfloat_block => 4,
        .astc_5x5_sfloat_block => 5,
        .astc_6x5_sfloat_block => 5,
        .astc_6x6_sfloat_block => 6,
        .astc_8x5_sfloat_block => 5,
        .astc_8x6_sfloat_block => 6,
        .astc_8x8_sfloat_block => 8,
        .astc_10x5_sfloat_block => 5,
        .astc_10x6_sfloat_block => 6,
        .astc_10x8_sfloat_block => 8,
        .astc_10x10_sfloat_block => 10,
        .astc_12x10_sfloat_block => 10,
        .astc_12x12_sfloat_block => 12,
        else => 1,
    };
}

pub fn VertexFormatUtil_BitSizeOfBlock(arg: VertexFormat) u32 {
    return switch (arg) {
        .float32x1 => 32,
        .float32x2 => 64,
        .float32x3 => 96,
        .float32x4 => 128,
        .sint32x1 => 32,
        .sint32x2 => 64,
        .sint32x3 => 96,
        .sint32x4 => 128,
        .uint32x1 => 32,
        .uint32x2 => 64,
        .uint32x3 => 96,
        .uint32x4 => 128,
        .float16x2 => 32,
        .float16x4 => 64,
        .sint16x2 => 32,
        .sint16x4 => 64,
        .uint16x2 => 32,
        .uint16x4 => 64,
        .snorm16x2 => 32,
        .snorm16x4 => 64,
        .unorm16x2 => 32,
        .unorm16x4 => 64,
        .sint8x4 => 32,
        .uint8x4 => 32,
        .snorm8x4 => 32,
        .unorm8x4 => 32,
        else => 0,
    };
}

pub inline fn createInstance(desc: *const InstanceDescriptor) Error!InstanceId {
    const result = cgpu_create_instance(desc);
    return if (result) |result_object|
        result_object
    else
        Error.CreateFailed;
}
extern fn cgpu_create_instance(desc: *const InstanceDescriptor) ?InstanceId;

pub inline fn freeInstance(instance: InstanceId) void {
    return cgpu_free_instance(instance);
}
extern fn cgpu_free_instance(instance: InstanceId) void;

extern fn cgpu_instance_get_backend(self: [*c]const Instance) Backend;

extern fn cgpu_instance_query_instance_features(self: [*c]const Instance, features: *InstanceFeatures) void;

extern fn cgpu_instance_enum_adapters(self: [*c]const Instance, p_adapters_count: *u32, p_adapters: ?[*]AdapterId) void;

extern fn cgpu_instance_create_surface_from_native_view(self: [*c]Instance, view: ?*anyopaque) ?SurfaceId;

extern fn cgpu_instance_create_surface_from_hwnd(self: [*c]Instance, window: HWND) ?SurfaceId;

extern fn cgpu_instance_create_surface_from_native_window(self: [*c]Instance, window: ANativeWindowPtr) ?SurfaceId;

extern fn cgpu_instance_free_surface(self: [*c]Instance, surface: SurfaceId) void;

extern fn cgpu_adapter_query_adapter_detail(self: [*c]const Adapter) *const AdapterDetail;

extern fn cgpu_adapter_query_queue_count(self: [*c]const Adapter, _type: QueueType) u32;

extern fn cgpu_adapter_create_device(self: [*c]Adapter, desc: *const DeviceDescriptor) ?DeviceId;

extern fn cgpu_adapter_free_device(self: [*c]Adapter, device: DeviceId) void;

extern fn cgpu_device_query_video_memory_info(self: [*c]Device, total: *u64, used_bytes: *u64) void;

extern fn cgpu_device_query_shared_memory_info(self: [*c]Device, total: *u64, used_bytes: *u64) void;

extern fn cgpu_device_create_fence(self: [*c]Device) ?FenceId;

extern fn cgpu_device_free_fence(self: [*c]Device, fence: FenceId) void;

extern fn cgpu_device_create_semaphore(self: [*c]Device) ?SemaphoreId;

extern fn cgpu_device_free_semaphore(self: [*c]Device, semaphore: SemaphoreId) void;

extern fn cgpu_device_create_root_signature_pool(self: [*c]Device, desc: *const RootSignaturePoolDescriptor) ?RootSignaturePoolId;

extern fn cgpu_device_free_root_signature_pool(self: [*c]Device, pool: RootSignaturePoolId) void;

extern fn cgpu_device_create_root_signature(self: [*c]Device, desc: *const RootSignatureDescriptor) ?RootSignatureId;

extern fn cgpu_device_free_root_signature(self: [*c]Device, signature: RootSignatureId) void;

extern fn cgpu_device_create_descriptor_set(self: [*c]Device, desc: *const DescriptorSetDescriptor) ?DescriptorSetId;

extern fn cgpu_device_free_descriptor_set(self: [*c]Device, set: DescriptorSetId) void;

extern fn cgpu_device_create_compute_pipeline(self: [*c]Device, desc: *const ComputePipelineDescriptor) ?ComputePipelineId;

extern fn cgpu_device_free_compute_pipeline(self: [*c]Device, pipeline: ComputePipelineId) void;

extern fn cgpu_device_create_render_pipeline(self: [*c]Device, desc: *const RenderPipelineDescriptor) ?RenderPipelineId;

extern fn cgpu_device_free_render_pipeline(self: [*c]Device, pipeline: RenderPipelineId) void;

extern fn cgpu_device_create_query_pool(self: [*c]Device, desc: *const QueryPoolDescriptor) ?QueryPoolId;

extern fn cgpu_device_free_query_pool(self: [*c]Device, pool: QueryPoolId) void;

extern fn cgpu_device_create_memory_pool(self: [*c]Device, desc: *const MemoryPoolDescriptor) ?MemoryPoolId;

extern fn cgpu_device_free_memory_pool(self: [*c]Device, pool: MemoryPoolId) void;

extern fn cgpu_device_get_queue(self: [*c]Device, _type: QueueType, index: u32) ?QueueId;

extern fn cgpu_device_free_queue(self: [*c]Device, queue: QueueId) void;

extern fn cgpu_device_create_render_pass(self: [*c]Device, desc: *const RenderPassDescriptor) ?RenderPassId;

extern fn cgpu_device_create_framebuffer(self: [*c]Device, desc: *const FramebufferDescriptor) ?FramebufferId;

extern fn cgpu_device_free_render_pass(self: [*c]Device, render_pass: RenderPassId) void;

extern fn cgpu_device_free_framebuffer(self: [*c]Device, framebuffer: FramebufferId) void;

extern fn cgpu_device_create_shader_library(self: [*c]Device, desc: *const ShaderLibraryDescriptor) ?ShaderLibraryId;

extern fn cgpu_device_free_shader_library(self: [*c]Device, library: ShaderLibraryId) void;

extern fn cgpu_device_create_buffer(self: [*c]Device, desc: *const BufferDescriptor) ?BufferId;

extern fn cgpu_device_free_buffer(self: [*c]Device, buffer: BufferId) void;

extern fn cgpu_device_create_sampler(self: [*c]Device, desc: *const SamplerDescriptor) ?SamplerId;

extern fn cgpu_device_free_sampler(self: [*c]Device, sampler: SamplerId) void;

extern fn cgpu_device_create_texture(self: [*c]Device, desc: *const TextureDescriptor) ?TextureId;

extern fn cgpu_device_free_texture(self: [*c]Device, texture: TextureId) void;

extern fn cgpu_device_create_texture_view(self: [*c]Device, desc: *const TextureViewDescriptor) ?TextureViewId;

extern fn cgpu_device_free_texture_view(self: [*c]Device, render_target: TextureViewId) void;

extern fn cgpu_device_try_bind_aliasing_texture(self: [*c]Device, desc: *const TextureAliasingBindDescriptor) bool;

extern fn cgpu_device_export_shared_texture_handle(self: [*c]Device, desc: *const ExportTextureDescriptor) u64;

extern fn cgpu_device_import_shared_texture_handle(self: [*c]Device, desc: *const ImportTextureDescriptor) ?TextureId;

extern fn cgpu_device_create_swap_chain(self: [*c]Device, desc: *const SwapChainDescriptor) ?SwapChainId;

extern fn cgpu_device_free_swap_chain(self: [*c]Device, swapchain: SwapChainId) void;

pub inline fn waitFences(fence_count: u32, p_fences: [*]const FenceId) void {
    return cgpu_wait_fences(fence_count, p_fences);
}
extern fn cgpu_wait_fences(fence_count: u32, p_fences: [*]const FenceId) void;

pub inline fn resetFences(fence_count: u32, p_fences: [*]const FenceId) void {
    return cgpu_reset_fences(fence_count, p_fences);
}
extern fn cgpu_reset_fences(fence_count: u32, p_fences: [*]const FenceId) void;

extern fn cgpu_fence_query_status(self: [*c]Fence) FenceStatus;

extern fn cgpu_queue_submit(self: [*c]Queue, desc: *const QueueSubmitDescriptor) SubmitError;

extern fn cgpu_queue_present(self: [*c]Queue, desc: *const QueuePresentDescriptor) PresentError;

extern fn cgpu_queue_wait_idle(self: [*c]Queue) void;

extern fn cgpu_queue_get_timestamp_period_ns(self: [*c]Queue) f32;

extern fn cgpu_queue_map_tiled_texture(self: [*c]Queue, desc: *const TiledTextureRegions) void;

extern fn cgpu_queue_unmap_tiled_texture(self: [*c]Queue, desc: *const TiledTextureRegions) void;

extern fn cgpu_queue_map_packed_mips(self: [*c]Queue, desc: *const TiledTexturePackedMips) void;

extern fn cgpu_queue_unmap_packed_mips(self: [*c]Queue, desc: *const TiledTexturePackedMips) void;

extern fn cgpu_queue_create_command_pool(self: [*c]Queue, desc: *const CommandPoolDescriptor) ?CommandPoolId;

extern fn cgpu_queue_free_command_pool(self: [*c]Queue, pool: CommandPoolId) void;

extern fn cgpu_descriptor_set_update(self: [*c]DescriptorSet, data_count: u32, p_datas: [*]const DescriptorData) void;

extern fn cgpu_command_pool_create_command_buffer(self: [*c]CommandPool, desc: *const CommandBufferDescriptor) ?CommandBufferId;

extern fn cgpu_command_pool_reset(self: [*c]CommandPool) void;

extern fn cgpu_command_pool_free_command_buffer(self: [*c]CommandPool, cmd: CommandBufferId) void;

extern fn cgpu_buffer_map(self: [*c]Buffer, range: ?*const BufferRange) void;

extern fn cgpu_buffer_unmap(self: [*c]Buffer) void;

extern fn cgpu_swap_chain_acquire_next_image(self: [*c]SwapChain, desc: *const AcquireNextDescriptor, p_image_index: *u32) AcquireNextImageError;

extern fn cgpu_command_buffer_begin(self: [*c]CommandBuffer) void;

extern fn cgpu_command_buffer_transfer_buffer_to_buffer(self: [*c]CommandBuffer, desc: *const BufferToBufferTransfer) void;

extern fn cgpu_command_buffer_transfer_texture_to_texture(self: [*c]CommandBuffer, desc: *const TextureToTextureTransfer) void;

extern fn cgpu_command_buffer_transfer_buffer_to_texture(self: [*c]CommandBuffer, desc: *const BufferToTextureTransfer) void;

extern fn cgpu_command_buffer_transfer_buffer_to_tiles(self: [*c]CommandBuffer, desc: *const BufferToTilesTransfer) void;

extern fn cgpu_command_buffer_resource_barrier(self: [*c]CommandBuffer, desc: *const ResourceBarrierDescriptor) void;

extern fn cgpu_command_buffer_begin_query(self: [*c]CommandBuffer, pool: QueryPoolId, desc: *const QueryDescriptor) void;

extern fn cgpu_command_buffer_end_query(self: [*c]CommandBuffer, pool: QueryPoolId, desc: *const QueryDescriptor) void;

extern fn cgpu_command_buffer_reset_query_pool(self: [*c]CommandBuffer, pool: QueryPoolId, start_query: u32, query_count: u32) void;

extern fn cgpu_command_buffer_resolve_query(self: [*c]CommandBuffer, pool: QueryPoolId, readback: BufferId, start_query: u32, query_count: u32) void;

extern fn cgpu_command_buffer_end(self: [*c]CommandBuffer) void;

extern fn cgpu_command_buffer_begin_compute_pass(self: [*c]CommandBuffer, desc: *const ComputePassDescriptor) ?ComputePassEncoderId;

extern fn cgpu_command_buffer_end_compute_pass(self: [*c]CommandBuffer, encoder: ComputePassEncoderId) void;

extern fn cgpu_command_buffer_begin_render_pass(self: [*c]CommandBuffer, begin_info: *const BeginRenderPassInfo) ?RenderPassEncoderId;

extern fn cgpu_command_buffer_end_render_pass(self: [*c]CommandBuffer, encoder: RenderPassEncoderId) void;

extern fn cgpu_command_buffer_begin_event(self: [*c]CommandBuffer, event: *const EventInfo) void;

extern fn cgpu_command_buffer_set_marker(self: [*c]CommandBuffer, marker: *const MarkerInfo) void;

extern fn cgpu_command_buffer_end_event(self: [*c]CommandBuffer) void;

extern fn cgpu_command_buffer_create_state_buffer(self: [*c]CommandBuffer, desc: *const StateBufferDescriptor) ?StateBufferId;

extern fn cgpu_command_buffer_free_state_buffer(self: [*c]CommandBuffer, stream: StateBufferId) void;

extern fn cgpu_command_buffer_create_binder(self: [*c]CommandBuffer) ?BinderId;

extern fn cgpu_command_buffer_free_binder(self: [*c]CommandBuffer, binder: BinderId) void;

extern fn cgpu_compute_pass_encoder_bind_descriptor_set(self: [*c]ComputePassEncoder, set: DescriptorSetId) void;

extern fn cgpu_compute_pass_encoder_bind_compute_pipeline(self: [*c]ComputePassEncoder, pipeline: ComputePipelineId) void;

extern fn cgpu_compute_pass_encoder_dispatch(self: [*c]ComputePassEncoder, x: u32, y: u32, z: u32) void;

extern fn cgpu_compute_pass_encoder_push_constants(self: [*c]ComputePassEncoder, rs: RootSignatureId, name: ?[*:0]const u8, data: *const anyopaque) void;

extern fn cgpu_compute_pass_encoder_bind_state_buffer(self: [*c]ComputePassEncoder, stream: StateBufferId) void;

extern fn cgpu_render_pass_encoder_set_shading_rate(self: [*c]RenderPassEncoder, shading_rate: ShadingRate, post_rasterize_rate: ShadingRateCombiner, final_rate: ShadingRateCombiner) void;

extern fn cgpu_render_pass_encoder_bind_descriptor_set(self: [*c]RenderPassEncoder, set: DescriptorSetId) void;

extern fn cgpu_render_pass_encoder_set_viewport(self: [*c]RenderPassEncoder, x: f32, y: f32, width: f32, height: f32, min_depth: f32, max_depth: f32) void;

extern fn cgpu_render_pass_encoder_set_scissor(self: [*c]RenderPassEncoder, x: u32, y: u32, width: u32, height: u32) void;

extern fn cgpu_render_pass_encoder_bind_render_pipeline(self: [*c]RenderPassEncoder, pipeline: RenderPipelineId) void;

extern fn cgpu_render_pass_encoder_bind_vertex_buffers(self: [*c]RenderPassEncoder, buffer_count: u32, p_buffers: [*]const BufferId, p_strides: [*]const u32, p_offsets: ?[*]const u32) void;

extern fn cgpu_render_pass_encoder_bind_index_buffer(self: [*c]RenderPassEncoder, buffer: BufferId, index_stride: u32, offset: u64) void;

extern fn cgpu_render_pass_encoder_push_constants(self: [*c]RenderPassEncoder, rs: RootSignatureId, name: ?[*:0]const u8, data: *const anyopaque) void;

extern fn cgpu_render_pass_encoder_draw(self: [*c]RenderPassEncoder, vertex_count: u32, first_vertex: u32) void;

extern fn cgpu_render_pass_encoder_draw_instanced(self: [*c]RenderPassEncoder, vertex_count: u32, first_vertex: u32, instance_count: u32, first_instance: u32) void;

extern fn cgpu_render_pass_encoder_draw_indexed(self: [*c]RenderPassEncoder, index_count: u32, first_index: u32, first_vertex: u32) void;

extern fn cgpu_render_pass_encoder_draw_indexed_instanced(self: [*c]RenderPassEncoder, index_count: u32, first_index: u32, instance_count: u32, first_instance: u32, first_vertex: u32) void;

extern fn cgpu_render_pass_encoder_bind_state_buffer(self: [*c]RenderPassEncoder, stream: StateBufferId) void;

extern fn cgpu_root_signature_compile_and_link_shaders(self: [*c]RootSignature, count: u32, desc: *const CompiledShaderDescriptor) ?LinkedShaderId;

extern fn cgpu_root_signature_compile_shaders(self: [*c]RootSignature, count: u32, desc: *const CompiledShaderDescriptor, out_isas: *CompiledShaderId) void;

extern fn cgpu_root_signature_free_compiled_shader(self: [*c]RootSignature, shader: CompiledShaderId) void;

extern fn cgpu_root_signature_free_linked_shader(self: [*c]RootSignature, shader: LinkedShaderId) void;

extern fn cgpu_state_buffer_open_raster_state_encoder(self: [*c]StateBuffer, encoder: RenderPassEncoderId) ?RasterStateEncoderId;

extern fn cgpu_state_buffer_close_raster_state_encoder(self: [*c]StateBuffer, encoder: RasterStateEncoderId) void;

extern fn cgpu_state_buffer_open_shader_state_encoder_r(self: [*c]StateBuffer, encoder: RenderPassEncoderId) ?ShaderStateEncoderId;

extern fn cgpu_state_buffer_open_shader_state_encoder_c(self: [*c]StateBuffer, encoder: ComputePassEncoderId) ?ShaderStateEncoderId;

extern fn cgpu_state_buffer_close_shader_state_encoder(self: [*c]StateBuffer, encoder: ShaderStateEncoderId) void;

extern fn cgpu_state_buffer_open_user_state_encoder(self: [*c]StateBuffer, encoder: RenderPassEncoderId) ?UserStateEncoderId;

extern fn cgpu_state_buffer_close_user_state_encoder(self: [*c]StateBuffer, encoder: UserStateEncoderId) void;

extern fn cgpu_raster_state_encoder_set_viewport(self: [*c]RasterStateEncoder, x: f32, y: f32, width: f32, height: f32, min_depth: f32, max_depth: f32) void;

extern fn cgpu_raster_state_encoder_set_scissor(self: [*c]RasterStateEncoder, x: u32, y: u32, width: u32, height: u32) void;

extern fn cgpu_raster_state_encoder_set_cull_mode(self: [*c]RasterStateEncoder, cull_mode: CullMode) void;

extern fn cgpu_raster_state_encoder_set_front_face(self: [*c]RasterStateEncoder, front_face: FrontFace) void;

extern fn cgpu_raster_state_encoder_set_primitive_topology(self: [*c]RasterStateEncoder, topology: PrimitiveTopology) void;

extern fn cgpu_raster_state_encoder_set_depth_test_enabled(self: [*c]RasterStateEncoder, enabled: bool) void;

extern fn cgpu_raster_state_encoder_set_depth_write_enabled(self: [*c]RasterStateEncoder, enabled: bool) void;

extern fn cgpu_raster_state_encoder_set_depth_compare_op(self: [*c]RasterStateEncoder, compare_op: CompareOp) void;

extern fn cgpu_raster_state_encoder_set_stencil_test_enabled(self: [*c]RasterStateEncoder, enabled: bool) void;

extern fn cgpu_raster_state_encoder_set_stencil_compare_op(self: [*c]RasterStateEncoder, faces: StencilFace, fail_op: StencilOp, pass_op: StencilOp, depth_fail_op: StencilOp, compare_op: CompareOp) void;

extern fn cgpu_raster_state_encoder_set_fill_mode(self: [*c]RasterStateEncoder, fill_mode: FillMode) void;

extern fn cgpu_raster_state_encoder_set_sample_count(self: [*c]RasterStateEncoder, sample_count: SampleCount) void;

extern fn cgpu_shader_state_encoder_bind_shaders(self: [*c]ShaderStateEncoder, stage_count: u32, p_stages: *const ShaderStage, shaders: *const CompiledShaderId) void;

extern fn cgpu_shader_state_encoder_bind_linked_shader(self: [*c]ShaderStateEncoder, linked: LinkedShaderId) void;

extern fn cgpu_binder_bind_vertex_layout(self: [*c]Binder, layout: *const VertexLayout) void;

extern fn cgpu_binder_bind_vertex_buffer(self: [*c]Binder, first_binding: u32, binding_count: u32, p_buffers: *const BufferId, p_offsets: *const u64, p_sizes: *const u64, p_strides: *const u64) void;

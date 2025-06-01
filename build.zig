const std = @import("std");

pub fn build(b: *std.Build) !void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const cgpu_module = b.addModule("cgpu", .{
        .target = target,
        .optimize = optimize,
        .link_libc = true,
        .link_libcpp = true,
    });

    const cgpu = b.addLibrary(.{
        .linkage = .static,
        .name = "cgpu",
        .root_module = cgpu_module,
    });

    cgpu_module.addIncludePath(b.path("src/cgpu/include"));
    cgpu_module.addIncludePath(b.path("src/cgpu/common/include"));
    cgpu_module.addCSourceFiles(
        .{
            .root = b.path("src/cgpu"),
            .files = &.{
                "common/cgpu.c",
                "common/hash.c",
                "common/memory.c",
                "common/cgpu.cpp",
                "common/root_sig_pool.cpp",
                "common/root_sig_table.cpp",
            },
        },
    );

    if (target.result.os.tag == .windows or target.result.os.tag == .linux) {
        cgpu_module.addCMacro("CGPU_USE_VULKAN", "");
        cgpu_module.addCMacro("VK_NO_PROTOTYPES", "");
        cgpu_module.addIncludePath(b.path("src/cgpu/backend/vulkan/include"));

        const vulkan_headers = try compileVulkanHeaders(b, target, optimize);
        linkLibrary(cgpu_module, vulkan_headers);

        const volk = try compileVolk(b, target, optimize);
        linkLibrary(cgpu_module, volk);

        cgpu_module.addCSourceFiles(.{
            .root = b.path("src/cgpu/backend/vulkan/src"),
            .files = &.{
                "cgpu_vulkan_instance.cpp",
                "cgpu_vulkan_resources.c",
                "cgpu_vulkan_surfaces.c",
                "cgpu_vulkan_windows.c",
                "cgpu_vulkan.c",
                "cgpu_vulkan2.c",
                "proc_table.c",
                "vulkan_utils.c",
                "volk.c",
                "vma.cpp",
            },
        });
        if (target.result.os.tag == .windows) {
            cgpu_module.addCMacro("VK_USE_PLATFORM_WIN32_KHR", "");
            cgpu_module.addCSourceFile(.{ .file = b.path("src/cgpu/backend/vulkan/src/cgpu_vulkan_windows.c") });
        }
    }

    const xxhash = try compileXXHash(b, target, optimize);
    linkLibrary(cgpu_module, xxhash);

    const phmap = try compilePHMap(b, target, optimize);
    linkLibrary(cgpu_module, phmap);

    const spirv_reflect = try compileSpirvReflect(b, target, optimize);
    linkLibrary(cgpu_module, spirv_reflect);

    const want_demo = b.option(bool, "want_demo", "build zgpu demo") orelse false;
    if (want_demo) {
        const demo_module = b.addModule("demo", .{
            .target = target,
            .optimize = optimize,
            .link_libc = true,
            .link_libcpp = true,
        });
        demo_module.addCSourceFiles(.{ .root = b.path("src/demo"), .files = &.{
            "main.cpp",
            "GpuTimeStamps.cpp",
            "imgui_impl_sdl2.cpp",
            "imgui_impl_cgpu.cpp",
            "renderdoc_helper.cpp",
        } });

        if (b.lazyDependency("sdl2", .{ .target = target, .optimize = optimize })) |sdl2_depend| {
            demo_module.linkLibrary(sdl2_depend.artifact("SDL2"));
            demo_module.addIncludePath(sdl2_depend.path("include"));
            demo_module.addIncludePath(sdl2_depend.path("include-pregen"));
        }

        if (b.lazyDependency("zgui", .{ .target = target, .optimize = optimize })) |zgui_depend| {
            demo_module.linkLibrary(zgui_depend.artifact("imgui"));
            demo_module.addIncludePath(zgui_depend.path("libs/imgui"));
        }

        demo_module.addIncludePath(b.path("src/cgpu/include"));
        demo_module.linkLibrary(cgpu);

        const demo = b.addExecutable(.{
            .name = "demo",
            .root_module = demo_module,
        });

        b.installArtifact(demo);

        const run = b.addRunArtifact(demo);
        const run_step = b.step("run", "");
        run_step.dependOn(&run.step);
    }
}

const Library = struct {
    library: ?*std.Build.Step.Compile,
    includes: std.ArrayList(std.Build.LazyPath),
};

fn compilePHMap(b: *std.Build, target: std.Build.ResolvedTarget, optimize: std.builtin.OptimizeMode) !Library {
    _ = target;
    _ = optimize;

    const phmap = b.dependency("phmap", .{});

    var phmap_library = Library{
        .library = null,
        .includes = std.ArrayList(std.Build.LazyPath).init(b.allocator),
    };

    try phmap_library.includes.append(phmap.path(""));

    return phmap_library;
}

fn compileXXHash(b: *std.Build, target: std.Build.ResolvedTarget, optimize: std.builtin.OptimizeMode) !Library {
    const xxhash_upstream = b.dependency("xxhash", .{});

    const xxhash_module = b.addModule("xxhash", .{
        .target = target,
        .optimize = optimize,
        .link_libc = true,
        .link_libcpp = true,
    });

    const xxhash = b.addLibrary(.{
        .linkage = .static,
        .name = "xxhash",
        .root_module = xxhash_module,
    });

    xxhash_module.addCSourceFiles(
        .{
            .root = xxhash_upstream.path(""),
            .files = &.{
                "xxhash.c",
            },
        },
    );

    var xxhash_library = Library{
        .library = xxhash,
        .includes = std.ArrayList(std.Build.LazyPath).init(b.allocator),
    };

    try xxhash_library.includes.append(xxhash_upstream.path(""));

    return xxhash_library;
}

fn compileVulkanHeaders(b: *std.Build, target: std.Build.ResolvedTarget, optimize: std.builtin.OptimizeMode) !Library {
    _ = target;
    _ = optimize;

    const vulkan_headers = b.dependency("vulkan_headers", .{});

    var vulkan_headers_library = Library{
        .library = null,
        .includes = std.ArrayList(std.Build.LazyPath).init(b.allocator),
    };

    try vulkan_headers_library.includes.append(vulkan_headers.path("include"));

    return vulkan_headers_library;
}

fn compileVolk(b: *std.Build, target: std.Build.ResolvedTarget, optimize: std.builtin.OptimizeMode) !Library {
    _ = target;
    _ = optimize;

    const volk = b.dependency("volk", .{});

    var volk_library = Library{
        .library = null,
        .includes = std.ArrayList(std.Build.LazyPath).init(b.allocator),
    };

    try volk_library.includes.append(volk.path(""));

    return volk_library;
}

fn compileSpirvReflect(b: *std.Build, target: std.Build.ResolvedTarget, optimize: std.builtin.OptimizeMode) !Library {
    const safety = switch (optimize) {
        .Debug, .ReleaseSafe => true,
        .ReleaseFast, .ReleaseSmall => false,
    };

    const optimize_external: std.builtin.OptimizeMode = switch (optimize) {
        // Can remove this conditional once this makes it into a Zig release, or by tagging a
        // version of this library for Zig 0.14.0 and then removing the conditional in a later
        // commit:
        // https://github.com/ziglang/zig/pull/23140
        .Debug => if (target.result.os.tag == .windows) .ReleaseFast else .ReleaseSafe,
        else => optimize,
    };

    const spirv_reflect_upstream = b.dependency("SPIRV-Reflect", .{});
    const spirv_reflect = b.addStaticLibrary(.{
        .name = "SPIRV-Reflect",
        .target = target,
        .optimize = optimize_external,
    });
    if (safety) {
        spirv_reflect.root_module.addCMacro("SPIRV_REFLECT_ENABLE_ASSERTS", "1");
    }
    spirv_reflect.addCSourceFile(.{
        .file = spirv_reflect_upstream.path("spirv_reflect.c"),
        .flags = &.{
            "-Wall",
            "-Werror",
        },
    });
    spirv_reflect.linkLibC();

    var spirv_reflect_library = Library{
        .library = spirv_reflect,
        .includes = std.ArrayList(std.Build.LazyPath).init(b.allocator),
    };

    try spirv_reflect_library.includes.append(spirv_reflect_upstream.path("."));

    return spirv_reflect_library;
}

fn linkLibrary(module: *std.Build.Module, library: Library) void {
    if (library.library) |lib|
        module.linkLibrary(lib);
    for (library.includes.items) |include_path| {
        module.addIncludePath(include_path);
    }
}

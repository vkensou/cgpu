add_rules("mode.debug", "mode.release", "mode.releasedbg")
add_cxflags("/EHsc")
set_languages("cxx20")
if (is_os("windows")) then 
    add_defines("NOMINMAX")
end

add_requires("volk 1.3.268+0", {configs = {vs_runtime = "MD", header_only = true}})
add_requires("xxhash v0.8.2")
add_requires("parallel-hashmap 1.35")
add_requires("libsdl 2.28.5", {configs = {sdlmain = false}})
add_requires("spirv-reflect 1.3.268+0")
add_requires("imgui v1.89.8-docking", {configs = {debug = true}})

if is_os("windows") or is_os("linux") or is_os("android")  then
    option("use_vulkan")
        set_showmenu(true )
        set_default(true)
end

target("cgpu")
    set_kind("static")

    add_packages("xxhash")
    add_packages("parallel-hashmap")
    
    add_options("use_vulkan")

    add_includedirs("src/cgpu/include", {public = true})
    add_headerfiles("src/cgpu/include/(cgpu/*.h)")
    add_includedirs("src/cgpu/common/include", {public = false})
    add_headerfiles("src/cgpu/common/include/*.h", {install = false})
    add_files("src/cgpu/common/*.c")
    add_files("src/cgpu/common/*.cpp")

    if has_config("use_vulkan") then
        add_defines("CGPU_USE_VULKAN")
        add_defines("VK_NO_PROTOTYPES")
        add_packages("volk")
        add_packages("spirv-reflect")
        add_includedirs("src/cgpu/backend/vulkan/include", {public = false})
        add_headerfiles("src/cgpu/backend/vulkan/include/*.h", {install = false})
        add_files("src/cgpu/backend/vulkan/src/cgpu_vulkan.c")
        add_files("src/cgpu/backend/vulkan/src/cgpu_vulkan2.c")
        add_files("src/cgpu/backend/vulkan/src/proc_table.c")
        add_files("src/cgpu/backend/vulkan/src/cgpu_vulkan_surfaces.c")
        add_files("src/cgpu/backend/vulkan/src/cgpu_vulkan_instance.cpp")
        add_files("src/cgpu/backend/vulkan/src/cgpu_vulkan_resources.c")
        add_files("src/cgpu/backend/vulkan/src/vulkan_utils.c")
        add_files("src/cgpu/backend/vulkan/src/vma.cpp")
        add_files("src/cgpu/backend/vulkan/src/volk.c")
        if is_os("windows") then
            add_defines("VK_USE_PLATFORM_WIN32_KHR")
            add_files("src/cgpu/backend/vulkan/src/cgpu_vulkan_windows.c")
        end
    end

target("demo")
    set_kind("binary")
    set_rundir("$(projectdir)")

    add_deps("cgpu")
    add_packages("libsdl")
    add_packages("imgui")

    add_headerfiles("src/demo/*.h")
    add_files("src/demo/*.cpp")

target("oval")
    set_kind("binary")
    set_rundir("$(projectdir)")

    add_deps("cgpu")
    add_packages("libsdl")

    add_headerfiles("src/oval/*.h")
    add_files("src/oval/*.cpp")

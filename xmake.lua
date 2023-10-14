add_rules("mode.debug", "mode.release", "mode.releasedbg")
add_cxflags("/EHsc")
set_languages("cxx20")
if (is_os("windows")) then 
    add_defines("NOMINMAX")
    if (is_mode("release")) then
        set_runtimes("MD")
    else
        set_runtimes("MDd")
    end
end

add_requires("volk", {configs = {vs_runtime = "MD", header_only = true}})
add_requires("xxhash")
add_requires("parallel-hashmap")
add_requires("libsdl")
add_requires("spirv-reflect")

if is_os("windows") or is_os("linux") or is_os("android")  then
    option("use_vulkan")
        set_default(false)
        add_defines("CGPU_USE_VULKAN")
end

target("cgpu")
    set_kind("static")

    add_packages("xxhash")
    add_packages("parallel-hashmap")
    
    -- add_options("use_vulkan")

    add_includedirs("include", {public = true})
    add_headerfiles("include/cgpu/*.h")
    add_includedirs("src/common/include", {public = false})
    add_headerfiles("src/common/include/*.h")
    add_files("src/common/*.c")
    add_files("src/common/*.cpp")

    -- if is_config("use_vulkan") then
        add_defines("CGPU_USE_VULKAN")
        add_defines("VK_NO_PROTOTYPES")
        add_packages("volk")
        add_packages("spirv-reflect")
        add_includedirs("src/backend/vulkan/include")
        add_headerfiles("src/backend/vulkan/include/*.h")
        add_files("src/backend/vulkan/src/cgpu_vulkan.c")
        add_files("src/backend/vulkan/src/cgpu_vulkan2.c")
        add_files("src/backend/vulkan/src/proc_table.c")
        add_files("src/backend/vulkan/src/cgpu_vulkan_surfaces.c")
        add_files("src/backend/vulkan/src/cgpu_vulkan_instance.cpp")
        add_files("src/backend/vulkan/src/cgpu_vulkan_resources.c")
        add_files("src/backend/vulkan/src/vulkan_utils.c")
        add_files("src/backend/vulkan/src/vma.cpp")
        add_files("src/backend/vulkan/src/volk.c")
        if is_os("windows") then
            add_defines("VK_USE_PLATFORM_WIN32_KHR")
            add_files("src/backend/vulkan/src/cgpu_vulkan_windows.c")
        end
    -- end

target("arena")
    set_kind("binary")
    set_rundir("$(projectdir)")

    add_deps("cgpu")
    add_packages("libsdl")

    add_files("arena/*.cpp")
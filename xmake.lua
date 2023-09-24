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

    -- if is_config("use_vulkan") then
        add_defines("CGPU_USE_VULKAN")
        add_packages("volk")
        add_includedirs("src/backend/vulkan/include")
        add_headerfiles("src/backend/vulkan/include/*.h")
        add_files("src/backend/vulkan/src/cgpu_vulkan_instance.cpp")
        if is_os("windows") then
            add_files("src/backend/vulkan/src/cgpu_vulkan_windows.cpp")
        end
    -- end
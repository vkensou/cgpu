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

if not is_os("ios") and not is_os("macosx") then
    add_requires("volk", {configs = {vs_runtime = "MD", header_only = true}})
end

target("cgpu")
    set_kind("static")

    if not is_os("ios") and not is_os("macosx") then
        add_packages("volk")
    end

    add_includedirs("include", {public = true})
    add_headerfiles("include/cgpu/*.h")
    add_files("src/cgpu/*.cpp")

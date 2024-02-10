.\tools\slang\slangc shaders\hello.hlsl -profile sm_5_0 -entry vert -o shaders\hello.vert.spv -O3 -emit-spirv-directly
.\tools\slang\slangc shaders\hello.hlsl -profile sm_5_0 -entry frag -o shaders\hello.frag.spv -O3 -emit-spirv-directly

.\tools\slang\slangc shaders\imgui.hlsl -profile sm_5_0 -entry vert -o shaders\imgui.vert.spv -O3 -emit-spirv-directly
.\tools\slang\slangc shaders\imgui.hlsl -profile sm_5_0 -entry frag -o shaders\imgui.frag.spv -O3 -emit-spirv-directly

.\tools\slang\slangc shaders\oval.hlsl -profile sm_5_0 -entry vert -o shaders\oval.vert.spv -O3 -emit-spirv-directly
.\tools\slang\slangc shaders\oval.hlsl -profile sm_5_0 -entry frag -o shaders\oval.frag.spv -O3 -emit-spirv-directly
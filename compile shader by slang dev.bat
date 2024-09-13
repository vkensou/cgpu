.\tools\slang\slangc shaders\hello.hlsl -profile sm_5_0 -capability SPIRV_1_3 -entry vert -o shaders\hello.vert.spv -O0 -g3 -line-directive-mode none -emit-spirv-directly
.\tools\slang\slangc shaders\hello.hlsl -profile sm_5_0 -capability SPIRV_1_3 -entry frag -o shaders\hello.frag.spv -O0 -g3 -line-directive-mode none -emit-spirv-directly

.\tools\slang\slangc shaders\imgui.hlsl -profile sm_5_0 -capability SPIRV_1_3 -entry vert -o shaders\imgui.vert.spv -O0 -g3 -line-directive-mode none -emit-spirv-directly
.\tools\slang\slangc shaders\imgui.hlsl -profile sm_5_0 -capability SPIRV_1_3 -entry frag -o shaders\imgui.frag.spv -O0 -g3 -line-directive-mode none -emit-spirv-directly

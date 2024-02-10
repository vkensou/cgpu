.\tools\dxc\dxc shaders\hello.hlsl -spirv -T vs_6_0 -E vert -fspv-entrypoint-name=main -Fo shaders\hello.vert.spv -O3
.\tools\dxc\dxc shaders\hello.hlsl -spirv -T ps_6_0 -E frag -fspv-entrypoint-name=main -Fo shaders\hello.frag.spv -O3

.\tools\dxc\dxc shaders\imgui.hlsl -spirv -T vs_6_0 -E vert -fspv-entrypoint-name=main -Fo shaders\imgui.vert.spv -O3
.\tools\dxc\dxc shaders\imgui.hlsl -spirv -T ps_6_0 -E frag -fspv-entrypoint-name=main -Fo shaders\imgui.frag.spv -O3

.\tools\dxc\dxc shaders\oval.hlsl -spirv -T vs_6_0 -E vert -fspv-entrypoint-name=main -Fo shaders\oval.vert.spv -O3
.\tools\dxc\dxc shaders\oval.hlsl -spirv -T ps_6_0 -E frag -fspv-entrypoint-name=main -Fo shaders\oval.frag.spv -O3
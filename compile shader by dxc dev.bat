.\tools\dxc\dxc shaders\hello.hlsl -spirv -T vs_6_0 -E vert -fspv-entrypoint-name=main -Fo shaders\hello.vert.spv -Od -Zi
.\tools\dxc\dxc shaders\hello.hlsl -spirv -T ps_6_0 -E frag -fspv-entrypoint-name=main -Fo shaders\hello.frag.spv -Od -Zi

.\tools\dxc\dxc shaders\imgui.hlsl -spirv -T vs_6_0 -E vert -fspv-entrypoint-name=main -Fo shaders\imgui.vert.spv -Od -Zi
.\tools\dxc\dxc shaders\imgui.hlsl -spirv -T ps_6_0 -E frag -fspv-entrypoint-name=main -Fo shaders\imgui.frag.spv -Od -Zi

.\tools\dxc\dxc shaders\oval.hlsl -spirv -T vs_6_0 -E vert -fspv-entrypoint-name=main -Fo shaders\oval.vert.spv -Od -Zi
.\tools\dxc\dxc shaders\oval.hlsl -spirv -T ps_6_0 -E frag -fspv-entrypoint-name=main -Fo shaders\oval.frag.spv -Od -Zi
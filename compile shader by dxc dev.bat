.\tools\dxc\dxc shaders\hello.vert.hlsl -spirv -T vs_6_0 -Fo shaders\hello.vert.spv -Od -Zi
.\tools\dxc\dxc shaders\hello.frag.hlsl -spirv -T ps_6_0 -Fo shaders\hello.frag.spv -Od -Zi

.\tools\dxc\dxc shaders\imgui.vert.hlsl -spirv -T vs_6_0 -Fo shaders\imgui.vert.spv -Od -Zi
.\tools\dxc\dxc shaders\imgui.frag.hlsl -spirv -T ps_6_0 -Fo shaders\imgui.frag.spv -Od -Zi
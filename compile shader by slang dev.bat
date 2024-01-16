.\tools\slang\slangc -profile sm_5_0 -stage vertex shaders\hello.vert.hlsl -o shaders\hello.vert.spv -O0 -g3 -line-directive-mode none
.\tools\slang\slangc -profile sm_5_0 -stage fragment shaders\hello.frag.hlsl -o shaders\hello.frag.spv -O0 -g3 -line-directive-mode none

.\tools\slang\slangc -profile sm_5_0 -stage vertex shaders\imgui.vert.hlsl -o shaders\imgui.vert.spv -O0 -g3 -line-directive-mode none
.\tools\slang\slangc -profile sm_5_0 -stage fragment shaders\imgui.frag.hlsl -o shaders\imgui.frag.spv -O0 -g3 -line-directive-mode none
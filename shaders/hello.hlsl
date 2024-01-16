static const float4 positions[3] = {
    float4( 0.0,  0.5, 0, 1),
    float4(-0.5, -0.5, 0, 1),
	float4( 0.5, -0.5, 0, 1)
};

static const float3 colors[3] = {
	float3(1.0, 0.0, 0.0),
	float3(0.0, 1.0, 0.0),
	float3(0.0, 0.0, 1.0),
};

struct VSInput
{
    uint vertexId : SV_VERTEXID;
};

struct VSOutput
{
	float4 Pos : SV_POSITION;
    [[vk::location(0)]]
    float3 Color : COLOR0;
};

[shader("vertex")]
VSOutput vert(VSInput input)
{
	VSOutput output = (VSOutput)0;
	output.Color = colors[input.vertexId];
	output.Pos = positions[input.vertexId];
	return output;
}

[shader("pixel")]
float4 frag(VSOutput input) : SV_TARGET
{
	return float4(input.Color, 1);
}
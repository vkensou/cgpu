struct VSInput
{
    [[vk::location(0)]]
    float2 Pos : POSITION0;
};

struct VSOutput
{
	float4 Pos : SV_POSITION;
};

[shader("vertex")]
VSOutput vert(VSInput input)
{
	VSOutput output = (VSOutput)0;
	output.Pos = float4(input.Pos, 0.0, 1.0);
	return output;
}

[shader("pixel")]
float4 frag(VSOutput input) : SV_TARGET
{
	return float4(1, 0.5, 0, 1);
}
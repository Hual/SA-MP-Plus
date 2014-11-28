float4x4 WorldViewProj : WorldViewProjection;

struct VS_INPUT
{
	float3 Position: POSITION0;
	float4 Color : COLOR0;
};

struct VS_OUTPUT
{
	float4 NewPosition : POSITION0;
	float InterpolatedColor : COLOR0;
};


VS_OUTPUT VS(VS_INPUT vsIn)
{
	VS_OUTPUT vsOut;

	vsOut.NewPosition = mul(float4(vsIn.Position, 1.0f), WorldViewProj);
	return vsOut;
}

float PS(VS_OUTPUT psIn) : COLOR
{
	return psIn.InterpolatedColor;
}

technique T0
{
	pass P0
	{
		CullMode = None;
		VertexShader = compile vs_3_0 VS();
		PixelShader = compile vs_3_0 PS();
	}
};
// Description: Reflection shader.
// Reference: http://www.rastertek.com/tutdx11.html

cbuffer TransformBuffer : register(b0)
{
	matrix wvp[2];
	matrix reflectionWVP;
}

Texture2D shaderTexture : register(t0);
Texture2D reflectionTexture : register(t1);
SamplerState textureSampler : register(s0);

struct VS_INPUT
{
	float3 position : POSITION;
	float2 texCoord : TEXCOORD0;
};

struct VS_OUTPUT
{
	float4 position : SV_Position;
	float2 texCoord : TEXCOORD0;
	float4 reflectionPosition : TEXCOORD1;
	float4 position2 : TEXCOORD2;
};

VS_OUTPUT VS(VS_INPUT input)
{
	VS_OUTPUT output;

	output.position = mul(float4(input.position, 1.0f), wvp[0]);
	output.position2 = mul(float4(input.position, 1.0f), wvp[1]);
	output.texCoord = input.texCoord;
	output.reflectionPosition = mul(float4(input.position, 1.0f), reflectionWVP);

	return output;
}

float4 PS(VS_OUTPUT input) : SV_Target
{
	float4 textureColor;
	float2 reflectTexCoord;
	float4 reflectionColor;
	float4 color;

	// Sample the texture pixel at this location.
	textureColor = shaderTexture.Sample(textureSampler, input.texCoord);

	// Calculate the projected reflection texture coordinates.
	reflectTexCoord.x = input.reflectionPosition.x / input.reflectionPosition.w / 2.0f + 0.5f;
	reflectTexCoord.y = -input.reflectionPosition.y / input.reflectionPosition.w / 2.0f + 0.5f;

	//reflectTexCoord = (input.reflectionPosition.xy / input.reflectionPosition.w + 1.0f) * 0.5f;
	//reflectTexCoord.y = 1.0f - reflectTexCoord.y;

	// Sample the texture pixel from the reflection texture using the projected texture coordinates.
	reflectionColor = reflectionTexture.Sample(textureSampler, reflectTexCoord);

	float realDepth = 1.0f - input.position2.z / input.position2.w;
	float recordedDepth = reflectionTexture.Sample(textureSampler, reflectTexCoord).r;

	if (saturate(reflectTexCoord.x) == reflectTexCoord.x &&
		saturate(reflectTexCoord.y) == reflectTexCoord.y &&
		realDepth + 0.00001f < recordedDepth)
	{
		color = lerp(textureColor, reflectionColor, 0.15f);
	}
	else
	{
		color = textureColor;
	}

	return color;
}
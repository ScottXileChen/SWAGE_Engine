// Description: fire shader.
// Reference: http://www.rastertek.com/tutdx11.html

cbuffer TransformBuffer : register(b0)
{
	matrix wvp;
}

cbuffer NoiseBuffer : register(b1)
{
	float frameTime;
	float3 scrollSpeeds;
	float3 scales;
	float padding;
};

cbuffer DistortionBuffer : register(b2)
{
	float2 distortion1;
	float2 distortion2;
	float2 distortion3;
	float distortionScale;
	float distortionBias;
};

Texture2D fireTexture : register(t0);
Texture2D noiseTexture : register(t1);
Texture2D alphaTexture : register(t2);
SamplerState textureSampler : register(s0);
SamplerState textureSampler2 : register(s1);

struct VS_INPUT
{
	float3 position : POSITION;
	float2 texCoord : TEXCOORD0;
};

struct VS_OUTPUT
{
	float4 position : SV_Position;
	float2 texCoord : TEXCOORD0;
	float2 texCoord1 : TEXCOORD1;
	float2 texCoord2 : TEXCOORD2;
	float2 texCoord3 : TEXCOORD3;
};

VS_OUTPUT VS(VS_INPUT input)
{
	VS_OUTPUT output;

	output.position = mul(float4(input.position, 1.0f), wvp);
	output.texCoord = input.texCoord;
	output.texCoord1 = (input.texCoord * scales.x);
	output.texCoord1.y = output.texCoord1.y + (frameTime * scrollSpeeds.x);

	output.texCoord2 = (input.texCoord * scales.y);
	output.texCoord2.y = output.texCoord2.y + (frameTime * scrollSpeeds.y);

	output.texCoord3 = (input.texCoord * scales.z);
	output.texCoord3.y = output.texCoord3.y + (frameTime * scrollSpeeds.z);

	return output;
}

float4 PS(VS_OUTPUT input) : SV_Target
{
	float4 noise1;
	float4 noise2;
	float4 noise3;
	float4 finalNoise;
	float perturb;
	float2 noiseCoords;
	float4 fireColor;
	float4 alphaColor;

	noise1 = noiseTexture.Sample(textureSampler, input.texCoord1);
	noise2 = noiseTexture.Sample(textureSampler, input.texCoord2);
	noise3 = noiseTexture.Sample(textureSampler, input.texCoord3);

	noise1 = (noise1 - 0.5f) * 2.0f;
	noise2 = (noise2 - 0.5f) * 2.0f;
	noise3 = (noise3 - 0.5f) * 2.0f;
	
	noise1.xy = noise1.xy * distortion1.xy;
	noise2.xy = noise2.xy * distortion2.xy;
	noise3.xy = noise3.xy * distortion3.xy;

	finalNoise = noise1 + noise2 + noise3;
	
	perturb = ((1.0f - input.texCoord.y) * distortionScale) + distortionBias;

	noiseCoords.xy = (finalNoise.xy * perturb) + input.texCoord.xy;

	fireColor = fireTexture.Sample(textureSampler2, noiseCoords.xy);

	alphaColor = alphaTexture.Sample(textureSampler2, noiseCoords.xy);
	float4 alphaColor2 = alphaTexture.Sample(textureSampler2, input.texCoord.xy);

	fireColor = fireColor * alphaColor2.r + alphaColor * alphaColor2.r;

	return fireColor;
}
// Description: water shader.
// Reference: http://www.rastertek.com/tutdx11.html

cbuffer TransformBuffer : register(b0)
{
	matrix wvp;
	matrix reflectionWVP;
	matrix refractionWVP;
}

cbuffer ReflectionBuffer : register(b1)
{
	matrix reflectionMatrix;
}

cbuffer WaterBuffer : register(b2)
{
	float waterTranslation;
	float reflectRefractScale;
}

Texture2D reflectionTexture : register(t0);
Texture2D refractionTexture : register(t1);
Texture2D normalTexture : register(t2);
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
	float4 reflectionPosition : TEXCOORD1;
	float4 refractionPosition : TEXCOORD2;
};

VS_OUTPUT VS(VS_INPUT input)
{
	VS_OUTPUT output;

	matrix reflectProjectWorld;
	matrix viewProjectWorld;

	//output.position = mul(float4(input.position, 1.0f), worldMatrix);
	//output.position = mul(output.position, viewMatrix);
	//output.position = mul(output.position, projectionMatrix);
	output.position = mul(float4(input.position, 1.0f), wvp);

	output.texCoord = input.texCoord;

	// Create the reflection projection world matrix just like the reflection tutorial and calculate the reflection coordinates from it.
	//reflectProjectWorld = mul(reflectionMatrix, projectionMatrix);
	//reflectProjectWorld = mul(worldMatrix, reflectProjectWorld);
	//reflectProjectWorld = transpose(reflectProjectWorld);
	output.reflectionPosition = mul(float4(input.position, 1.0f), reflectionWVP);

	// Refraction coordinates are calculated in the same way as the reflection coordinates except that we use a view projection world matrix for them.
	//viewProjectWorld = mul(viewMatrix, projectionMatrix);
	//viewProjectWorld = mul(worldMatrix, viewProjectWorld);

	output.refractionPosition = mul(float4(input.position, 1.0f), refractionWVP);

	return output;
}

float4 PS(VS_OUTPUT input) : SV_Target
{
	float2 reflectTexCoord;
	float2 refractTexCoord;
	float4 normalMap;
	float3 normal;
	float4 reflectionColor;
	float4 refractionColor;
	float4 color;

	input.texCoord.y += waterTranslation;

	// Convert both the reflection and refraction coordinates into texture coordinates in the -1 to +1 range.
	reflectTexCoord.x = input.reflectionPosition.x / input.reflectionPosition.w / 2.0f + 0.5f;
	reflectTexCoord.y = -input.reflectionPosition.y / input.reflectionPosition.w / 2.0f + 0.5f;
	//reflectTexCoord = (input.reflectionPosition.xy / input.reflectionPosition.w + 1.0f) * 0.5f;
	//reflectTexCoord.y = 1.0f - reflectTexCoord.y;

	//refractTexCoord = (input.refractionPosition.xy / input.refractionPosition.w + 1.0f) * 0.5f;
	//refractTexCoord.y = 1.0f - reflectTexCoord.y;
	refractTexCoord.x = input.refractionPosition.x / input.refractionPosition.w / 2.0f + 0.5f;
	refractTexCoord.y = -input.refractionPosition.y / input.refractionPosition.w / 2.0f + 0.5f;

	normalMap = normalTexture.Sample(textureSampler, input.texCoord);

	// Expand the range of the normal from (0,1) to (-1,+1).
	normal = (normalMap.xyz * 2.0f) - 1.0f;

	// Re-position the texture coordinate sampling position by the normal map value to simulate the rippling wave effect.
	reflectTexCoord = reflectTexCoord + (normal.xy * reflectRefractScale);
	refractTexCoord = refractTexCoord + (normal.xy * reflectRefractScale);

	// Sample the texture pixels from the textures using the updated texture coordinates.
	reflectionColor = reflectionTexture.Sample(textureSampler2, reflectTexCoord);
	//reflectionColor = reflectionTexture.Sample(textureSampler, input.texCoord);
	refractionColor = refractionTexture.Sample(textureSampler, refractTexCoord);

	// Combine the reflection and refraction results for the final color.
	color = lerp(reflectionColor, refractionColor, 0.6f);

	return color;
}
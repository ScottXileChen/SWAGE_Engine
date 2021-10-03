// Description: refraction shader.
// Reference: http://www.rastertek.com/tutdx11.html

cbuffer TransformBuffer : register(b0)
{
	matrix wvp;
	matrix worldMatrix;
}

cbuffer ClipPlaneBuffer : register(b1)
{
	float4 clipPlane;
}

cbuffer LightBuffer : register(b2)
{
	float4 ambientColor;
	float4 diffuseColor;
	float3 lightDirection;
}

Texture2D shaderTexture : register(t0);
SamplerState textureSampler : register(s0);

struct VS_INPUT
{
	float3 position : POSITION;
	float3 normal : NORMAL;
	float2 texCoord : TEXCOORD0;
};

struct VS_OUTPUT
{
	float4 position : SV_Position;
	float3 normal : NORMAL;
	float2 texCoord : TEXCOORD0;
	float clip : SV_ClipDistance0;
};

VS_OUTPUT VS(VS_INPUT input)
{
	VS_OUTPUT output;

	//output.position = mul(float4(input.position, 1.0f), worldMatrix);
	//output.position = mul(output.position, viewMatrix);
	//output.position = mul(output.position, projectionMatrix);
	output.position = mul(float4(input.position, 1.0f), wvp);

	output.texCoord = input.texCoord;

	output.normal = mul(input.normal, (float3x3)worldMatrix);
	output.normal = normalize(output.normal);

	output.clip = dot(mul(input.position, worldMatrix), clipPlane);

	return output;
}

float4 PS(VS_OUTPUT input) : SV_Target
{
	float4 textureColor;
	float3 lightDir;
	float lightIntensity;
	float4 color;

	textureColor = shaderTexture.Sample(textureSampler, input.texCoord);

	color = ambientColor;

	lightDir = -lightDirection;

	lightIntensity = saturate(dot(input.normal, lightDir));
	if (lightIntensity > 0.0f)
	{
		color += (diffuseColor * lightIntensity);
	}

	color = saturate(color);
	color = color * textureColor;

	return color;
}
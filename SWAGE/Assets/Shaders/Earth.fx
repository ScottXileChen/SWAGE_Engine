// Description: Simple shader that does transform and lighting.

cbuffer TransformBuffer : register(b0)
{
	matrix world;
	matrix wvp;
	float3 viewPosition;
}

cbuffer LightBuffer : register(b1)
{
	float3 lightDirection;
	float4 lightAmbient;
	float4 lightDiffuse;
	float4 lightSpecular;
}

cbuffer MaterialBuffer : register(b2)
{
	float4 materialAmbient;
	float4 materialDiffuse;
	float4 materialSpecular;
	float specularPower;
}

cbuffer SettingsBuffer : register(b3)
{
	float displacementWeight;
	bool isNormalMapOn;
	bool isSpecularMapOn;
}

Texture2D diffuseMap : register(t0);
Texture2D specularMap : register(t1);
Texture2D displacementMap : register(t2);
Texture2D normalMap : register(t3);
Texture2D nightMap : register(t4);
SamplerState textureSampler : register(s0);

struct VS_INPUT
{
	float3 position : POSITION;
	float3 normal : NORMAL;
	float3 tangent : TANGENT;
	float2 texCoord : TEXCOORD;
};

struct VS_OUTPUT
{
	float4 position : SV_Position;
	float3 normal : TEXCOORD0;
	float3 dirToView : TEXCOORD1;
	float2 texCoord : TEXCOORD2;
	float3 tangent : TEXCOORD3;
	float3 binormal : TEXCOORD4;
};

VS_OUTPUT VS(VS_INPUT input)
{
	float4 displacement = displacementMap.SampleLevel(textureSampler, input.texCoord, 0).x;
	float3 position = input.position + (input.normal * (float3)displacement * displacementWeight);

	float3 worldPosition = mul(float4(position, 1.0f), world).xyz;
	float3 worldNormal = mul(input.normal, (float3x3)world);
	float3 worldTangent = mul(input.tangent, (float3x3)world);
	float3 worldBinormal = cross(worldNormal, worldTangent);

	VS_OUTPUT output;
	output.position = mul(float4(position, 1.0f), wvp);
	output.normal = worldNormal;
	output.tangent = worldTangent;
	output.binormal = worldBinormal;
	output.dirToView = normalize(viewPosition - worldPosition);
	output.texCoord = input.texCoord;

	return output;
}

float4 PS(VS_OUTPUT input) : SV_Target
{
	float3 normal;
	if (isNormalMapOn)
	{
		// Get normal from texture and convert from [0, 1] to [-1, 1]
		float4 normalMapColor = normalMap.Sample(textureSampler, input.texCoord);
		float3 unpackedNormal = normalize(float3((normalMapColor.xy * 2.0f) - 1.0f, normalMapColor.z));

		// Fix normals from rasterizer and construct the tangent space matrix
		float3 n = normalize(input.normal);
		float3 b = normalize(input.binormal);
		float3 t = normalize(input.tangent);
		float3x3 tbnw = float3x3(t, b, n);

		// True normal to use for lighting
		normal = normalize(mul(unpackedNormal, tbnw));
	}
	else
	{
		normal = normalize(input.normal);
	}

	float3 dirToView = normalize(input.dirToView);

	float4 ambient = lightAmbient * materialAmbient;

	float3 dirToLight = -lightDirection;
	float timeOfDayFactor = dot(normal, dirToLight);
	float diffuseIntensity = saturate(timeOfDayFactor);
	float4 diffuse = diffuseIntensity * lightDiffuse * materialDiffuse;

	float3 reflected = normalize(reflect(lightDirection, normal));
	float specularBase = saturate(dot(reflected, dirToView));
	float specularIntensity = pow(specularBase, specularPower);
	float4 specular = specularIntensity * lightSpecular * materialSpecular;

	float4 diffuseMapColor = diffuseMap.Sample(textureSampler, input.texCoord);

	float4 specularMapColor = isSpecularMapOn ? specularMap.Sample(textureSampler, input.texCoord) : 1.0f;

	if (timeOfDayFactor > -0.3f)
	{
		return (ambient + diffuse) * diffuseMapColor + (specular * specularMapColor.r);
	}
	else
	{
		float4 nightMapColor = nightMap.Sample(textureSampler, input.texCoord);
		return nightMapColor * 0.4f;
	}
}
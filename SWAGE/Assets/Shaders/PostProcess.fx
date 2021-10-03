// Description: Post Processing shader.
// Reference: https://www.geeks3d.com/20101123/shader-library-predators-thermal-vision-post-processing-filter-glsl/
// Reference: https://www.geeks3d.com/20101029/shader-library-pixelation-post-processing-effect-glsl/

cbuffer PostProcessParams : register(b0)
{
	float offset;
	float pixel_w;
	float pixel_h;
	float screenWidth;
	float screenHeight;
};

Texture2D textureMap : register(t0);
SamplerState textureSampler : register(s0);

struct VS_INPUT
{
	float3 position : POSITION;
	float2 texCoord : TEXCOORD;
};

struct VS_OUTPUT
{
	float4 position : SV_Position;
	float2 texCoord : TEXCOORD;
};

VS_OUTPUT VS(VS_INPUT input)
{
	VS_OUTPUT output;
	output.position = float4(input.position, 1.0f);
	output.texCoord = input.texCoord;
	return output;
}

float4 PS(VS_OUTPUT input) : SV_Target
{
	float3 screenColor = textureMap.Sample(textureSampler, input.texCoord).rgb;

	float2 uv = input.texCoord.xy;
	float3 tc = float3(1.0, 0.0, 0.0);
	if (uv.x < (offset - 0.005f))
	{
		float3 pixcol = screenColor;
		float3 colors[3];
		colors[0] = float3(0, 0, 1);
		colors[1] = float3(1, 1, 0);
		colors[2] = float3(1, 0, 0);
		float lum = dot(float3(0.30f, 0.59f, 0.11f), pixcol.rgb);
		int ix = (lum < 0.5) ? 0 : 1;
		tc = lerp(colors[ix], colors[ix + 1], (lum - float(ix)*0.5f) / 0.5f);
	}
	else if (uv.x >= (offset + 0.005f))
	{
		//tc = screenColor;
		float dx = pixel_w * (1.0f / screenWidth);
		float dy = pixel_h * (1.0f / screenHeight);
		float2 coord = float2(dx * floor(uv.x / dx), dy * floor(uv.y / dy));
		tc = (float3)textureMap.Sample(textureSampler, coord).rgb;
	}

	return float4(tc, 1.0f);
}
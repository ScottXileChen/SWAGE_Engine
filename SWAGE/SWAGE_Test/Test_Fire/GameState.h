#pragma once

#include <SWAGE/Inc/SWAGE.h>

class GameState : public SWAGE::AppState
{
public:
	void Initialize() override;
	void Terminate() override;

	void Update(float deltaTime) override;
	void Render() override;
	void DebugUI() override;

private:
	struct NoiseBufferType
	{
		float frameTime;
		SWAGE::Math::Vector3 scrollSpeeds;
		SWAGE::Math::Vector3 scales;
		float padding;
	};

	struct DistortionBufferType
	{
		SWAGE::Math::Vector2 distortion1;
		SWAGE::Math::Vector2 distortion2;
		SWAGE::Math::Vector2 distortion3;
		float distortionScale;
		float distortionBias;
	};

	struct TransformData
	{
		SWAGE::Math::Matrix4 wvp;
	};

	void RenderScene();
	void PostProcess();

	SWAGE::Graphics::Camera mCamera;

	SWAGE::Graphics::TypedConstantBuffer<NoiseBufferType> mNoiseBufferTypeBuffer;
	SWAGE::Graphics::TypedConstantBuffer<DistortionBufferType> mDistortionBufferTypeBuffer;
	SWAGE::Graphics::TypedConstantBuffer<TransformData> mTransformDataBuffer;

	SWAGE::Graphics::MeshPX mFireMesh;
	SWAGE::Graphics::MeshBuffer mFireMeshBuffer;

	SWAGE::Graphics::VertexShader mFireVertexShader;
	SWAGE::Graphics::PixelShader mFirePixelShader;

	SWAGE::Graphics::Sampler mSampler;
	SWAGE::Graphics::Sampler mSampler2;

	SWAGE::Graphics::Texture mFireTexture;
	SWAGE::Graphics::Texture mNoiseTexture;
	SWAGE::Graphics::Texture mAlphaTexture;

	SWAGE::Graphics::BlendState mBlendState;

	NoiseBufferType mNoise;
	DistortionBufferType mDistortion;

	SWAGE::Math::Vector3 mRotation;
	float mFPS = 0.0f;
};
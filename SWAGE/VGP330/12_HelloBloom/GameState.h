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
	void RenderScene();
	void RenderBrightness();
	void ApplyBlur();
	void PostProcess();

	struct EarthTransformData
	{
		SWAGE::Math::Matrix4 world;
		SWAGE::Math::Matrix4 wvp;
		SWAGE::Math::Vector3 viewPosition;
		float padding;
	};

	SWAGE::Graphics::Camera mCamera;

	SWAGE::Graphics::RenderTarget mBaseRenderTarget;
	SWAGE::Graphics::RenderTarget mBloomRenderTarget;
	SWAGE::Graphics::RenderTarget mBlurRenderTarget;

	SWAGE::Graphics::TypedConstantBuffer<EarthTransformData> mEarthTransformBuffer;
	SWAGE::Graphics::TypedConstantBuffer<SWAGE::Math::Matrix4> mTexturingTransformBuffer;
	SWAGE::Graphics::TypedConstantBuffer<SWAGE::Math::Vector4> mBlurSettingsBuffer;
	SWAGE::Graphics::TypedConstantBuffer<SWAGE::Graphics::DirectionalLight> mLightBuffer;
	SWAGE::Graphics::TypedConstantBuffer<SWAGE::Graphics::Material> mMaterialBuffer;

	SWAGE::Graphics::DirectionalLight mDirectionalLight;
	SWAGE::Graphics::Material mMaterial;

	SWAGE::Graphics::Mesh mEarthMesh;
	SWAGE::Graphics::MeshBuffer mEarthMeshBuffer;
	SWAGE::Graphics::MeshPX mSunMesh;
	SWAGE::Graphics::MeshBuffer mSunMeshBuffer;

	SWAGE::Graphics::VertexShader mTexturingVertexShader;
	SWAGE::Graphics::PixelShader mTexturingPixelShader;

	SWAGE::Graphics::VertexShader mEarthVertexShader;
	SWAGE::Graphics::PixelShader mEarthPixelShader;

	SWAGE::Graphics::VertexShader mGaussianBlurVertexShader;
	SWAGE::Graphics::PixelShader mGaussianBlurXPixelShader;
	SWAGE::Graphics::PixelShader mGaussianBlurYPixelShader;

	SWAGE::Graphics::VertexShader mBloomVertexShader;
	SWAGE::Graphics::PixelShader mBloomPixelShader;

	SWAGE::Graphics::Sampler mSampler;
	SWAGE::Graphics::Texture mEarthDiffuseTexture;
	SWAGE::Graphics::Texture mEarthSpecularTexture;
	SWAGE::Graphics::Texture mEarthDisplacmentTexture;
	SWAGE::Graphics::Texture mEarthNormalTexture;
	SWAGE::Graphics::Texture mSunDiffuseTexture;
	SWAGE::Graphics::Texture mBlankTexture;

	SWAGE::Math::Vector3 mRotation;
	float mFPS = 0.0f;

	SWAGE::Graphics::MeshPX mScreenMesh;
	SWAGE::Graphics::MeshBuffer mScreenMeshBuffer;

	int mBlurIterations = 10;
	float mBlurSaturation = 0.28f;
};
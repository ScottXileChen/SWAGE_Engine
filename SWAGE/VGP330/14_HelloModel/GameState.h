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
	void RenderDepthMap();
	void RenderScene();
	void PostProcess();

	struct EarthTransformData
	{
		SWAGE::Math::Matrix4 world;
		SWAGE::Math::Matrix4 wvp[2];
		SWAGE::Math::Vector3 viewPosition;
		float padding;
	};

	struct StandSettingBuffer
	{
		float displacementWeight;
		int isNormalMapOn;
		int isSpecularMapOn;
		int padding;
	};

	SWAGE::Graphics::Camera mDefaultCamera;
	SWAGE::Graphics::Camera mLightCamera;
	SWAGE::Graphics::Camera* mActiveCamera = nullptr;

	SWAGE::Graphics::RenderTarget mDepthRenderTarget; // <-- record depth from light source
	//SWAGE::Graphics::RenderTarget mBaseRenderTarget;  // <-- original scene, think "screenshot"
	SWAGE::Graphics::RenderTarget mBloomRenderTarget; // <-- only the "bright" pixels
	SWAGE::Graphics::RenderTarget mBlurRenderTarget;  // <-- amplify the brightness

	SWAGE::Graphics::TypedConstantBuffer<SWAGE::Math::Matrix4> mDepthMapTransformBuffer;
	SWAGE::Graphics::TypedConstantBuffer<EarthTransformData> mEarthTransformBuffer;
	SWAGE::Graphics::TypedConstantBuffer<SWAGE::Math::Matrix4> mTexturingTransformBuffer;
	SWAGE::Graphics::TypedConstantBuffer<SWAGE::Math::Vector4> mBlurSettingsBuffer;
	SWAGE::Graphics::TypedConstantBuffer<SWAGE::Graphics::DirectionalLight> mLightBuffer;
	SWAGE::Graphics::TypedConstantBuffer<StandSettingBuffer> mSettingBuffer;
	SWAGE::Graphics::TypedConstantBuffer<SWAGE::Graphics::Material> mMaterialBuffer;

	SWAGE::Graphics::DirectionalLight mDirectionalLight;
	SWAGE::Graphics::Material mMaterial;

	SWAGE::Graphics::Mesh mGroundMesh;
	SWAGE::Graphics::MeshBuffer mGroundMeshBuffer;

	SWAGE::Graphics::Mesh mModelMesh;
	SWAGE::Graphics::MeshBuffer mModelMeshBuffer;

	SWAGE::Graphics::VertexShader mStandardVertexShader;
	SWAGE::Graphics::PixelShader mStandardPixelShader;

	SWAGE::Graphics::VertexShader mDepthMapVertexShader;
	SWAGE::Graphics::PixelShader mDepthMapPixelShader;

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
	//SWAGE::Graphics::Texture mEarthNormalTexture;
	SWAGE::Graphics::Texture mBlankTexture;
	SWAGE::Graphics::Texture mGroundTexture;

	SWAGE::Math::Vector3 mRotation;
	SWAGE::Math::Vector3 mTransformPosition;
	float mFPS = 0.0f;

	SWAGE::Graphics::MeshPX mScreenMesh;
	SWAGE::Graphics::MeshBuffer mScreenMeshBuffer;

	int mBlurIterations = 10;
	float mBlurSaturation = 0.0f;//0.28f;

	float mLightCameraDistance = 20.0f;
};
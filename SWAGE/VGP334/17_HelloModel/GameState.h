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

	void SetFancyVertex();
private:
	struct TransformData
	{
		SWAGE::Math::Matrix4 world;
		SWAGE::Math::Matrix4 wvp[2];
		SWAGE::Math::Vector3 viewPosition;
		float padding;
	};

	struct TransformData2
	{
		SWAGE::Math::Matrix4 wvp;
	};

	struct Setting
	{
		float displacementWeight;
		int isNormalMapOn;
		int isSpecularMapOn;
		int isSkinning;
	};

	struct BoneTransformData
	{
		SWAGE::Math::Matrix4 boneTransforms[256];
	};

	SWAGE::Graphics::Camera mCamera;

	SWAGE::Graphics::TypedConstantBuffer<TransformData> mTransformBuffer;
	SWAGE::Graphics::TypedConstantBuffer<TransformData2> mTransformBuffer2;
	SWAGE::Graphics::TypedConstantBuffer<BoneTransformData> mBoneTransformBuffer;
	SWAGE::Graphics::TypedConstantBuffer<SWAGE::Graphics::DirectionalLight> mLightBuffer;
	SWAGE::Graphics::TypedConstantBuffer<SWAGE::Graphics::Material> mMaterialBuffer;
	SWAGE::Graphics::TypedConstantBuffer<Setting> mSettingBuffer;

	SWAGE::Graphics::BlendState mBlendState;

	//TODO: Show these in ImGui so we can change them on the fly.
	SWAGE::Graphics::DirectionalLight mDirectionalLight;
	SWAGE::Graphics::Material mMaterial;

	SWAGE::Graphics::Sampler mSamplers[3];

	SWAGE::Graphics::Model mModel[3];

	SWAGE::Graphics::VertexShader mVertexShader;
	SWAGE::Graphics::PixelShader mPixelShader;

	SWAGE::Graphics::VertexShader mTextureVertexShader;
	SWAGE::Graphics::PixelShader mTexturePixelShader;

	SWAGE::Graphics::VertexShader mCloudVertexShader;
	SWAGE::Graphics::PixelShader mCloudPixelShader;

	SWAGE::Math::Vector3 mPosition;
	SWAGE::Math::Vector3 mRotation;

	SWAGE::Graphics::Animator mAnimator[3];

	float mCloudRotation;
	float mAnimationTime = 0;
	float mFPS = 0.0f;
};
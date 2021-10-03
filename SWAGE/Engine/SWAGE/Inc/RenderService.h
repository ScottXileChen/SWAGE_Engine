#pragma once

#include "Service.h"

namespace SWAGE
{
	class AnimatorComponent;
	class ModelComponent;
	class TransformComponent;

	class RenderService final : public Service
	{
	public:
		SET_TYPE_ID(ServiceId::Render);

		void Initialize() override;
		void Terminate() override;

		void Update(float deltaTime) override;
		void Render() override;
		void DebugUI() override;

		void Register(const ModelComponent* modelComponent);
		void Unregister(const ModelComponent* modelComponent);

	private:
		struct Entry
		{
			const AnimatorComponent* animatorComponent = nullptr;
			const ModelComponent* modelComponent = nullptr;
			const TransformComponent* transformComponent = nullptr;
		};

		struct TransformData
		{
			SWAGE::Math::Matrix4 world;
			SWAGE::Math::Matrix4 wvp[2];
			SWAGE::Math::Vector3 viewPosition;
			float padding;
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

		std::vector<Entry> mRenderEntries;

		SWAGE::Graphics::Camera mCamera;

		SWAGE::Graphics::TypedConstantBuffer<TransformData> mTransformBuffer;
		SWAGE::Graphics::TypedConstantBuffer<BoneTransformData> mBoneTransformBuffer;
		SWAGE::Graphics::TypedConstantBuffer<SWAGE::Graphics::DirectionalLight> mLightBuffer;
		SWAGE::Graphics::TypedConstantBuffer<SWAGE::Graphics::Material> mMaterialBuffer;
		SWAGE::Graphics::TypedConstantBuffer<Setting> mSettingBuffer;

		SWAGE::Graphics::BlendState mBlendState;

		//TODO: Show these in ImGui so we can change them on the fly.
		SWAGE::Graphics::DirectionalLight mDirectionalLight;
		SWAGE::Graphics::Material mMaterial;

		SWAGE::Graphics::Sampler mSamplers[3];

		//SWAGE::Graphics::Model mModel[3];

		SWAGE::Graphics::VertexShader mVertexShader;
		SWAGE::Graphics::PixelShader mPixelShader;

		SWAGE::Graphics::VertexShader mTextureVertexShader;
		SWAGE::Graphics::PixelShader mTexturePixelShader;

		SWAGE::Graphics::VertexShader mCloudVertexShader;
		SWAGE::Graphics::PixelShader mCloudPixelShader;

		float mAnimationTime = 0;
	};
}

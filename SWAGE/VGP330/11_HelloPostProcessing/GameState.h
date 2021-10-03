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
	void RenderScene();
	void PostProcess();

	struct PostProcessParams
	{
		float offset;
		float pixel_w;
		float pixel_h;
		float screenWidth;
		float screenHeight;
		SWAGE::Math::Vector3 padding;
	};

	struct TransformData
	{
		SWAGE::Math::Matrix4 world;
		SWAGE::Math::Matrix4 wvp;
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
		float displacementWeight2;
		bool isNormalMapOn1;
		bool isNormalMapOn2;
		bool isNormalMapOn3;
	};

	SWAGE::Graphics::Camera mCamera;

	SWAGE::Graphics::RenderTarget mRenderTarget;

	SWAGE::Graphics::TypedConstantBuffer<TransformData> mTransformBuffer;
	SWAGE::Graphics::TypedConstantBuffer<TransformData2> mTransformBuffer2;
	SWAGE::Graphics::TypedConstantBuffer<SWAGE::Graphics::DirectionalLight> mLightBuffer;
	SWAGE::Graphics::TypedConstantBuffer<SWAGE::Graphics::Material> mMaterialBuffer;
	SWAGE::Graphics::TypedConstantBuffer<Setting> mSettingBuffer;
	SWAGE::Graphics::TypedConstantBuffer<PostProcessParams> mPostProcessParams;
	
	SWAGE::Graphics::BlendState mBlendState;

	//TODO: Show these in ImGui so we can change them on the fly.
	SWAGE::Graphics::DirectionalLight mDirectionalLight;
	SWAGE::Graphics::Material mMaterial;

	SWAGE::Graphics::Texture mTexture[6];
	SWAGE::Graphics::Sampler mSamplers[3];

	//TODO:
	// -Add VertexPN and MeshPN to Graphics.
	// -Add MeshBuilder::CreateSpherePN
	SWAGE::Graphics::MeshBuffer mSphereBuffer;
	SWAGE::Graphics::MeshBase<SWAGE::Graphics::Vertex> mSphereMesh;

	SWAGE::Graphics::Texture mSkyBoxTexture;
	SWAGE::Graphics::MeshBuffer mSkyBoxBuffer;
	SWAGE::Graphics::MeshBase<SWAGE::Graphics::VertexPX> mSkyBoxMesh;

	SWAGE::Graphics::Texture mEarthCloudTexture;
	SWAGE::Graphics::MeshBuffer mEarthCloudBuffer;
	SWAGE::Graphics::MeshBase<SWAGE::Graphics::VertexPNX> mEarthCloudMesh;

	SWAGE::Graphics::VertexShader mVertexShader;
	SWAGE::Graphics::PixelShader mPixelShader;

	SWAGE::Graphics::VertexShader mTextureVertexShader;
	SWAGE::Graphics::PixelShader mTexturePixelShader;

	SWAGE::Graphics::VertexShader mCloudVertexShader;
	SWAGE::Graphics::PixelShader mCloudPixelShader;

	SWAGE::Graphics::VertexShader mPostProcessVertexShader;
	SWAGE::Graphics::PixelShader mPostProcessPixelShader;

	SWAGE::Math::Vector3 mPosition;
	SWAGE::Math::Vector3 mRoataion;

	float mCloudRoataion;
	
	float mFPS = 0.0f;

	SWAGE::Graphics::MeshPX mScreenMesh;
	SWAGE::Graphics::MeshBuffer nScreenMeshBuffer;
};
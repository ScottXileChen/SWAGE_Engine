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
	struct TransformData
	{
		//SWAGE::Math::Matrix4 worldMatrix;
		//SWAGE::Math::Matrix4 viewMatrix;
		//SWAGE::Math::Matrix4 projectionMatrix;
		SWAGE::Math::Matrix4 wvp[2];
		SWAGE::Math::Matrix4 Rewvp;
		SWAGE::Math::Matrix4 Rawvp;
	};

	struct TransformData2
	{
		SWAGE::Math::Matrix4 wvp;
		SWAGE::Math::Matrix4 world;
	};

	struct ReflectionBuffer
	{
		SWAGE::Math::Matrix4 reflectionMatrix;
	};

	struct WaterBuffer
	{
		float waterTranslation;
		float reflectRefractScale;
		SWAGE::Math::Vector2 padding;
	};

	struct ClipPlaneBuffer
	{
		SWAGE::Math::Vector4 clipPlane;
	};

	struct LightBuffer
	{
		SWAGE::Graphics::Color ambientColor;
		SWAGE::Graphics::Color diffuseColor;
		SWAGE::Math::Vector3 lightDirection;
		float padding;
	};

	void RenderReflection();
	void RenderRefraction();
	void RenderScene();
	void PostProcess();
	SWAGE::Math::Matrix4 GetReflectionViewMatrix(float height);

	SWAGE::Graphics::Camera mCamera;
	SWAGE::Graphics::Camera mCamera2;

	SWAGE::Graphics::TypedConstantBuffer<TransformData> mTransformDataBuffer;
	SWAGE::Graphics::TypedConstantBuffer<TransformData2> mTransformDataBuffer2;
	SWAGE::Graphics::TypedConstantBuffer<ReflectionBuffer> mReflectionBuffer;
	SWAGE::Graphics::TypedConstantBuffer<WaterBuffer> mWaterBuffer;
	SWAGE::Graphics::TypedConstantBuffer<ClipPlaneBuffer> mClipPlaneBuffer;
	SWAGE::Graphics::TypedConstantBuffer<LightBuffer> mLightBuffer;

	SWAGE::Graphics::DirectionalLight mDirectionalLight;
	SWAGE::Graphics::Material mMaterial;

	SWAGE::Graphics::RenderTarget mRefractionRenderTarget;
	SWAGE::Graphics::RenderTarget mReflectionRenderTarget;

	SWAGE::Graphics::MeshPX mWaterMesh;
	SWAGE::Graphics::MeshBuffer mWaterMeshBuffer;

	SWAGE::Graphics::MeshPX mCubeMesh;
	SWAGE::Graphics::MeshBuffer mCubeMeshBuffer;


	SWAGE::Graphics::MeshPNX mCube2Mesh;
	SWAGE::Graphics::MeshBuffer mCube2MeshBuffer;

	SWAGE::Graphics::VertexShader mWaterVertexShader;
	SWAGE::Graphics::PixelShader mWaterPixelShader;
	SWAGE::Graphics::VertexShader mRefractionVertexShader;
	SWAGE::Graphics::PixelShader mRefractionPixelShader;
	SWAGE::Graphics::VertexShader mTextureVertexShader;
	SWAGE::Graphics::PixelShader mTexturePixelShader;

	SWAGE::Graphics::Sampler mSampler;
	SWAGE::Graphics::Sampler mSampler2;

	SWAGE::Graphics::Texture mWaterTexture;
	SWAGE::Graphics::Texture mRefractionTexture;
	SWAGE::Graphics::Texture mReflectionTexture;

	WaterBuffer waterBuffer;
	LightBuffer lightBuffer;
	ClipPlaneBuffer clipPlaneBuffer;

	SWAGE::Math::Vector3 mRotation;
	float mFPS = 0.0f;
};
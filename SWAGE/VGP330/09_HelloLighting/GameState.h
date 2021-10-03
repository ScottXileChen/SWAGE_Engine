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
		SWAGE::Math::Matrix4 wvp;
		SWAGE::Math::Vector3 viewPosition;
		float padding;
	};

	SWAGE::Graphics::Camera mCamera;

	SWAGE::Graphics::TypedConstantBuffer<TransformData> mTransformBuffer;
	SWAGE::Graphics::TypedConstantBuffer<SWAGE::Graphics::DirectionalLight> mLightBuffer;
	SWAGE::Graphics::TypedConstantBuffer<SWAGE::Graphics::Material> mMaterialBuffer;
	
	//TODO: Show these in ImGui so we can change them on the fly.
	SWAGE::Graphics::DirectionalLight mDirectionalLight;
	SWAGE::Graphics::Material mMaterial;

	//TODO:
	// -Add VertexPN and MeshPN to Graphics.
	// -Add MeshBuilder::CreateSpherePN
	SWAGE::Graphics::MeshBuffer mSphereBuffer;
	SWAGE::Graphics::MeshBase<SWAGE::Graphics::VertexPN> mSphereMesh;

	SWAGE::Graphics::VertexShader mVertexShader[2];
	SWAGE::Graphics::PixelShader mPixelShader[2];

	SWAGE::Math::Vector3 mPosition;
	SWAGE::Math::Vector3 mRoataion;
	
	float mFPS = 0.0f;
};
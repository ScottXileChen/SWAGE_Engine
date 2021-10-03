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
		SWAGE::Math::Matrix4 wvp;
	};

	SWAGE::Graphics::Camera mCamera;

	SWAGE::Graphics::TypedConstantBuffer<TransformData> mConstantBuffer;

	SWAGE::Graphics::Texture mTexture;
	SWAGE::Graphics::Sampler mSamplers[3];

	SWAGE::Graphics::MeshBuffer mCubeVertexBuffer;
	SWAGE::Graphics::MeshBase<SWAGE::Graphics::VertexPX> mCubeMesh;

	SWAGE::Graphics::MeshBuffer mPlaneVertexBuffer;
	SWAGE::Graphics::MeshBase<SWAGE::Graphics::VertexPX> mPlaneMesh;

	SWAGE::Graphics::MeshBuffer mCylinderVertexBuffer;
	SWAGE::Graphics::MeshBase<SWAGE::Graphics::VertexPX> mCylinderMesh;

	SWAGE::Graphics::VertexShader mVertexShader;
	SWAGE::Graphics::PixelShader mPixelShader;

	SWAGE::Math::Vector3 mPosition;
	SWAGE::Math::Vector3 mRoataion;
	
	float mFPS = 0.0f;
};
#pragma once

#include <SWAGE/Inc/SWAGE.h>
#include "Planet.h"

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

	SWAGE::Graphics::Texture mSkyBoxTexture;
	SWAGE::Graphics::Sampler mSamplers[3];

	SWAGE::Graphics::MeshBuffer mSkyBoxBuffer;
	SWAGE::Graphics::MeshBase<SWAGE::Graphics::VertexPX> mSkyBoxMesh;

	Planets planets;

	SWAGE::Graphics::VertexShader mVertexShader;
	SWAGE::Graphics::PixelShader mPixelShader;

	SWAGE::Math::Vector3 mPosition;
	SWAGE::Math::Vector3 mRoataion;
	
	float mFPS = 0.0f;
};
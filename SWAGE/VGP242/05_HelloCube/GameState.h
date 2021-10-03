#pragma once

#include <SWAGE/Inc/SWAGE.h>

class GameState : public SWAGE::AppState
{
public:
	void Initialize() override;
	void Terminate() override;

	void Update(float deltaTime) override;
	void Render() override;

	void SetFancyVertex();
private:
	struct TransformData
	{
		SWAGE::Math::Matrix4 wvp;
	};

	SWAGE::Graphics::Camera mCamera;

	SWAGE::Graphics::TypedConstantBuffer<TransformData> mConstantBuffer;

	//std::vector<Vertex> mHeartVertices;
	//std::vector<Vertex> mTriforceVertices;
	//std::vector<Vertex> mFancyVertices;
	std::vector<SWAGE::Graphics::VertexPC> mVertices[3];

	SWAGE::Graphics::MeshBuffer mVertexBuffer[3];

	SWAGE::Graphics::MeshBuffer mCubeVertexBuffer;
	SWAGE::Graphics::MeshBase<SWAGE::Graphics::VertexPC> mCubeMesh;

	SWAGE::Graphics::VertexShader mVertexShader;
	SWAGE::Graphics::PixelShader mPixelShader;

	SWAGE::Math::Vector3 mPosition;
	SWAGE::Math::Vector3 mRoataion;
};
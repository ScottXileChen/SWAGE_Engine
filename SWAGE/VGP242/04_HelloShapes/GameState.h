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

	//std::vector<Vertex> mHeartVertices;
	//std::vector<Vertex> mTriforceVertices;
	//std::vector<Vertex> mFancyVertices;
	std::vector<SWAGE::Graphics::VertexPC> mVertices[3];

	SWAGE::Graphics::MeshBuffer mVertexBuffer[3];

	SWAGE::Graphics::VertexShader mVertexShader;
	SWAGE::Graphics::PixelShader mPixelShader;
};
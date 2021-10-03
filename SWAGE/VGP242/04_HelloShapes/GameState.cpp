#include "GameState.h"

using namespace SWAGE::Graphics;
using namespace SWAGE::Input;
using namespace SWAGE::Math;

int vertexBufferSwitcher = 0;

void GameState::Initialize()
{
	// NDC - Normalized Device Coordinate
	//
	//          +-----------------+
	//         /                 /|
	//   1.0  +-----------------+ |
	//	      |        ^        | |
	//	      |        |        | |
	//	      | <------+------> | |
	//	      |        |        | | 1.0
	//	      |        v        |/
	//	-1.0  +-----------------+ 0.0
	//      -1.0               1.0
	//
	//mVertices.push_back({ Vector3{  0.0f,  0.5f, 0.0f }, Colors::Red });
	//mVertices.push_back({ Vector3{  0.5f, -0.5f, 0.0f }, Colors::Green });
	//mVertices.push_back({ Vector3{ -0.5f, -0.5f, 0.0f }, Colors::Blue });

	//*************************** Heart ****************************************
	// Left Top:
	mVertices[0].push_back({ Vector3{ -0.35f, 0.9f,  0.0f }, Colors::White });
	mVertices[0].push_back({ Vector3{   0.0f, 0.5f,  0.0f }, Colors::LightBlue });
	mVertices[0].push_back({ Vector3{  -0.7f, 0.5f,  0.0f }, Colors::LightBlue });

	// Right Top:
	mVertices[0].push_back({ Vector3{  0.0f,  0.5f,  0.0f }, Colors::LightBlue });
	mVertices[0].push_back({ Vector3{ 0.35f,  0.9f,  0.0f }, Colors::White });
	mVertices[0].push_back({ Vector3{  0.7f,  0.5f,  0.0f }, Colors::LightBlue });

	// Bottom:
	mVertices[0].push_back({ Vector3{  0.0f, -0.9f,  0.0f }, Colors::White });
	mVertices[0].push_back({ Vector3{ -0.7f,  0.5f,  0.0f }, Colors::LightBlue });
	mVertices[0].push_back({ Vector3{  0.7f,  0.5f,  0.0f }, Colors::LightBlue });
	//**************************************************************************

	//*************************** Triforce *************************************
	//Top
	mVertices[1].push_back({ Vector3{   0.0f, 0.7f, 0.0f }, Colors::Gold });
	mVertices[1].push_back({ Vector3{   0.4f, 0.0f, 0.0f }, Colors::Gold });
	mVertices[1].push_back({ Vector3{  -0.4f, 0.0f, 0.0f }, Colors::Gold });

	//Left
	mVertices[1].push_back({ Vector3{  -0.8f, -0.7f, 0.0f }, Colors::Gold });
	mVertices[1].push_back({ Vector3{  -0.4f,  0.0f, 0.0f }, Colors::Gold });
	mVertices[1].push_back({ Vector3{   0.0f, -0.7f, 0.0f }, Colors::Gold });

	//Right
	mVertices[1].push_back({ Vector3{  0.4f,  0.0f, 0.0f }, Colors::Gold });
	mVertices[1].push_back({ Vector3{  0.8f, -0.7f, 0.0f }, Colors::Gold });
	mVertices[1].push_back({ Vector3{  0.0f, -0.7f, 0.0f }, Colors::Gold });
	//**************************************************************************

	//*************************** Fancy ****************************************

	SetFancyVertex();

	//**************************************************************************

	for (size_t i = 0; i < std::size(mVertexBuffer); i++)
		mVertexBuffer[i].Initialize(mVertices[i].data(), sizeof(VertexPC), (uint32_t)mVertices[i].size());

	mVertexShader.Initialize(L"../../Assets/Shaders/DoSomething.fx", VertexPC::Format);
	mPixelShader.Initialize(L"../../Assets/Shaders/DoSomething.fx");
}

void GameState::Terminate()
{
	for (size_t i = 0; i < std::size(mVertexBuffer); i++)
		mVertexBuffer[i].Terminate();

	mVertexShader.Terminate();
	mPixelShader.Terminate();
}

void GameState::Update(float deltaTime)
{
	if (SWAGE::Input::InputSystem::Get()->IsKeyPressed(SWAGE::Input::KeyCode::ONE))
		vertexBufferSwitcher = 0;
	else if (SWAGE::Input::InputSystem::Get()->IsKeyPressed(SWAGE::Input::KeyCode::TWO))
		vertexBufferSwitcher = 1;
	else if (SWAGE::Input::InputSystem::Get()->IsKeyPressed(SWAGE::Input::KeyCode::THREE))
		vertexBufferSwitcher = 2;
}

void GameState::Render()
{
	mVertexShader.Bind();
	mPixelShader.Bind();
	mVertexBuffer[vertexBufferSwitcher].Render();
}

// Device interface - used for VRAM allocation/resource creation
// Context interface - used to issue draw commands

void GameState::SetFancyVertex()
{
	// Grass
	mVertices[2].push_back({ Vector3{ -0.2f, 0.6f, 0.0f }, Colors::Green });
	mVertices[2].push_back({ Vector3{  0.0f, 0.7f, 0.0f }, Colors::Green });
	mVertices[2].push_back({ Vector3{  0.1f, 0.4f, 0.0f }, Colors::Green });

	mVertices[2].push_back({ Vector3{ -0.1f, 0.4f, 0.0f }, Colors::Green });
	mVertices[2].push_back({ Vector3{ -0.2f, 0.6f, 0.0f }, Colors::Green });
	mVertices[2].push_back({ Vector3{  0.1f, 0.4f, 0.0f }, Colors::Green });

	// Body
	//***** Mid Top face
	mVertices[2].push_back({ Vector3{  -0.1f, 0.4f, 0.0f }, Colors::Orange });
	mVertices[2].push_back({ Vector3{   0.1f, 0.4f, 0.0f }, Colors::Orange });
	mVertices[2].push_back({ Vector3{   0.1f, 0.0f, 0.0f }, Colors::Orange });

	mVertices[2].push_back({ Vector3{  -0.1f,  0.0f, 0.0f }, Colors::Orange });
	mVertices[2].push_back({ Vector3{  -0.1f,  0.4f, 0.0f }, Colors::Orange });
	mVertices[2].push_back({ Vector3{   0.1f, -0.0f, 0.0f }, Colors::Orange });

//*****
	mVertices[2].push_back({ Vector3{  -0.1f, -0.2f, 0.0f }, Colors::Orange });
	mVertices[2].push_back({ Vector3{  -0.1f,  0.0f, 0.0f }, Colors::Orange });
	mVertices[2].push_back({ Vector3{   0.0f, -0.2f, 0.0f }, Colors::Orange });

	mVertices[2].push_back({ Vector3{  0.1f,  0.0f, 0.0f }, Colors::Orange });
	mVertices[2].push_back({ Vector3{  0.1f, -0.2f, 0.0f }, Colors::Orange });
	mVertices[2].push_back({ Vector3{  0.0f, -0.2f, 0.0f }, Colors::Orange });

//***** Left face
	mVertices[2].push_back({ Vector3{  -0.1f, 0.3f, 0.0f }, Colors::Orange });
	mVertices[2].push_back({ Vector3{  -0.1f, 0.1f, 0.0f }, Colors::Orange });
	mVertices[2].push_back({ Vector3{  -0.2f, 0.3f, 0.0f }, Colors::Orange });

	mVertices[2].push_back({ Vector3{  -0.2f, 0.3f, 0.0f }, Colors::Orange });
	mVertices[2].push_back({ Vector3{  -0.3f, 0.1f, 0.0f }, Colors::Orange });
	mVertices[2].push_back({ Vector3{  -0.3f, 0.3f, 0.0f }, Colors::Orange });

	mVertices[2].push_back({ Vector3{  -0.1f, 0.4f, 0.0f }, Colors::Orange });
	mVertices[2].push_back({ Vector3{  -0.1f, 0.3f, 0.0f }, Colors::Orange });
	mVertices[2].push_back({ Vector3{  -0.3f, 0.3f, 0.0f }, Colors::Orange });

	mVertices[2].push_back({ Vector3{  -0.4f, 0.1f, 0.0f }, Colors::Orange });
	mVertices[2].push_back({ Vector3{  -0.3f, 0.3f, 0.0f }, Colors::Orange });
	mVertices[2].push_back({ Vector3{  -0.3f, 0.1f, 0.0f }, Colors::Orange });

//*****
	mVertices[2].push_back({ Vector3{  -0.4f,  0.1f, 0.0f }, Colors::Orange });
	mVertices[2].push_back({ Vector3{  -0.1f,  0.1f, 0.0f }, Colors::Orange });
	mVertices[2].push_back({ Vector3{  -0.4f, -0.2f, 0.0f }, Colors::Orange });

	mVertices[2].push_back({ Vector3{  -0.1f,  0.1f, 0.0f }, Colors::Orange });
	mVertices[2].push_back({ Vector3{  -0.1f, -0.2f, 0.0f }, Colors::Orange });
	mVertices[2].push_back({ Vector3{  -0.4f, -0.2f, 0.0f }, Colors::Orange });



//***** Right face
	mVertices[2].push_back({ Vector3{  0.1f,  0.1f, 0.0f }, Colors::Orange });
	mVertices[2].push_back({ Vector3{  0.1f,  0.3f, 0.0f }, Colors::Orange });
	mVertices[2].push_back({ Vector3{  0.2f,  0.3f, 0.0f }, Colors::Orange });

	mVertices[2].push_back({ Vector3{  0.3f,  0.1f, 0.0f }, Colors::Orange });
	mVertices[2].push_back({ Vector3{  0.2f,  0.3f, 0.0f }, Colors::Orange });
	mVertices[2].push_back({ Vector3{  0.3f,  0.3f, 0.0f }, Colors::Orange });

	mVertices[2].push_back({ Vector3{  0.1f,  0.3f, 0.0f }, Colors::Orange });
	mVertices[2].push_back({ Vector3{  0.1f,  0.4f, 0.0f }, Colors::Orange });
	mVertices[2].push_back({ Vector3{  0.3f,  0.3f, 0.0f }, Colors::Orange });

	mVertices[2].push_back({ Vector3{  0.3f,  0.3f, 0.0f }, Colors::Orange });
	mVertices[2].push_back({ Vector3{  0.4f,  0.1f, 0.0f }, Colors::Orange });
	mVertices[2].push_back({ Vector3{  0.3f,  0.1f, 0.0f }, Colors::Orange });

//*****
	mVertices[2].push_back({ Vector3{  0.1f,  0.1f, 0.0f }, Colors::Orange });
	mVertices[2].push_back({ Vector3{  0.4f,  0.1f, 0.0f }, Colors::Orange });
	mVertices[2].push_back({ Vector3{  0.4f, -0.2f, 0.0f }, Colors::Orange });

	mVertices[2].push_back({ Vector3{  0.1f,  -0.2f, 0.0f }, Colors::Orange });
	mVertices[2].push_back({ Vector3{  0.1f,  0.1f, 0.0f }, Colors::Orange });
	mVertices[2].push_back({ Vector3{  0.4f, -0.2f, 0.0f }, Colors::Orange });


//***** Bottom face
	mVertices[2].push_back({ Vector3{  -0.4f, -0.2f, 0.0f }, Colors::Orange });
	mVertices[2].push_back({ Vector3{  -0.3f, -0.2f, 0.0f }, Colors::Orange });
	mVertices[2].push_back({ Vector3{  -0.3f, -0.4f, 0.0f }, Colors::Orange });

	mVertices[2].push_back({ Vector3{  -0.3f, -0.3f, 0.0f }, Colors::Orange });
	mVertices[2].push_back({ Vector3{  -0.2f, -0.4f, 0.0f }, Colors::Orange });
	mVertices[2].push_back({ Vector3{  -0.3f, -0.4f, 0.0f }, Colors::Orange });

	mVertices[2].push_back({ Vector3{  0.3f, -0.2f, 0.0f }, Colors::Orange });
	mVertices[2].push_back({ Vector3{  0.4f, -0.2f, 0.0f }, Colors::Orange });
	mVertices[2].push_back({ Vector3{  0.3f, -0.4f, 0.0f }, Colors::Orange });

	mVertices[2].push_back({ Vector3{  0.3f, -0.3f, 0.0f }, Colors::Orange });
	mVertices[2].push_back({ Vector3{  0.3f, -0.4f, 0.0f }, Colors::Orange });
	mVertices[2].push_back({ Vector3{  0.2f, -0.4f, 0.0f }, Colors::Orange });


//*****
	mVertices[2].push_back({ Vector3{  -0.3f, -0.3f, 0.0f }, Colors::Orange });
	mVertices[2].push_back({ Vector3{  -0.3f, -0.2f, 0.0f }, Colors::Orange });
	mVertices[2].push_back({ Vector3{   0.3f, -0.3f, 0.0f }, Colors::Orange });

	mVertices[2].push_back({ Vector3{  0.3f, -0.2f, 0.0f }, Colors::Orange });
	mVertices[2].push_back({ Vector3{  0.3f, -0.3f, 0.0f }, Colors::Orange });
	mVertices[2].push_back({ Vector3{ -0.3f, -0.2f, 0.0f }, Colors::Orange });

	mVertices[2].push_back({ Vector3{  -0.2f, -0.5f, 0.0f }, Colors::Orange });
	mVertices[2].push_back({ Vector3{  -0.3f, -0.4f, 0.0f }, Colors::Orange });
	mVertices[2].push_back({ Vector3{   0.3f, -0.4f, 0.0f }, Colors::Orange });

	mVertices[2].push_back({ Vector3{  0.3f, -0.4f, 0.0f }, Colors::Orange });
	mVertices[2].push_back({ Vector3{  0.2f, -0.5f, 0.0f }, Colors::Orange });
	mVertices[2].push_back({ Vector3{ -0.2f, -0.5f, 0.0f }, Colors::Orange });

//***** Tooth
	mVertices[2].push_back({ Vector3{  0.0f, -0.4f, 0.0f }, Colors::Orange });
	mVertices[2].push_back({ Vector3{ -0.2f, -0.4f, 0.0f }, Colors::Orange });
	mVertices[2].push_back({ Vector3{ -0.1f, -0.34f, 0.0f }, Colors::Orange });

	mVertices[2].push_back({ Vector3{ 0.2f, -0.4f, 0.0f }, Colors::Orange });
	mVertices[2].push_back({ Vector3{ 0.0f, -0.4f, 0.0f }, Colors::Orange });
	mVertices[2].push_back({ Vector3{ 0.1f, -0.34f, 0.0f }, Colors::Orange });
}
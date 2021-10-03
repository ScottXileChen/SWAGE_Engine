#include "GameState.h"

using namespace SWAGE::Graphics;
using namespace SWAGE::Input;
using namespace SWAGE::Math;

namespace
{
	int vertexBufferSwitcher = 0;
}

void GameState::Initialize()
{
	// TODO:
	// - Create data for vertex buffer and index buffer for a cube
	//
	// Cube
	//          +-----------------+
	//         /|                /|
	//   1.0  +-----------------+ |
	//	      | |               | |
	//	      | |               | |
	//	      | |               | |
	//	      | +---------------|-+ 1.0
	//	      |/                |/
	//	-1.0  +-----------------+ -1.0
	//      -1.0               1.0
	//
	//
	// 	 i.e.
	//		std::vector<PCEngine::Graphics::VertexPC> vertices;
	//		std::vector<uint32_t> indices;
	//
	// - Initialize MeshBuffer using the new Initialize overload

	mCubeMesh = MeshBuilder::CreateCubePC();
	mCubeVertexBuffer.Initialize(mCubeMesh);

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

	mVertexShader.Initialize(L"../../Assets/Shaders/DoTransform.fx", VertexPC::Format);
	mPixelShader.Initialize(L"../../Assets/Shaders/DoTransform.fx");

	// Create constant buffer
	mConstantBuffer.Initialize();

	mPosition.z = 5.0f;
}

void GameState::Terminate()
{
	for (size_t i = 0; i < std::size(mVertexBuffer); i++)
		mVertexBuffer[i].Terminate();

	mVertexShader.Terminate();
	mPixelShader.Terminate();
	mCubeVertexBuffer.Terminate();
	mConstantBuffer.Terminate();
}

void GameState::Update(float deltaTime)
{
	if (SWAGE::Input::InputSystem::Get()->IsKeyPressed(SWAGE::Input::KeyCode::ONE))
		vertexBufferSwitcher = 0;
	else if (SWAGE::Input::InputSystem::Get()->IsKeyPressed(SWAGE::Input::KeyCode::TWO))
		vertexBufferSwitcher = 1;
	else if (SWAGE::Input::InputSystem::Get()->IsKeyPressed(SWAGE::Input::KeyCode::THREE))
		vertexBufferSwitcher = 2;

	if (SWAGE::Input::InputSystem::Get()->IsKeyDown(SWAGE::Input::KeyCode::LEFT))
		mRoataion.y += deltaTime;
	if (SWAGE::Input::InputSystem::Get()->IsKeyDown(SWAGE::Input::KeyCode::RIGHT))
		mRoataion.y -= deltaTime;

	if (SWAGE::Input::InputSystem::Get()->IsKeyDown(SWAGE::Input::KeyCode::UP))
		mRoataion.x += deltaTime;
	if (SWAGE::Input::InputSystem::Get()->IsKeyDown(SWAGE::Input::KeyCode::DOWN))
		mRoataion.x -= deltaTime;

	const float moveSpeed = 10.0f;
	const float turnSpeed = 10.0f * Constants::DegToRad;
	if (SWAGE::Input::InputSystem::Get()->IsKeyDown(SWAGE::Input::KeyCode::W))
		mCamera.Walk(moveSpeed * deltaTime);
	if (SWAGE::Input::InputSystem::Get()->IsKeyDown(SWAGE::Input::KeyCode::S))
		mCamera.Walk(-moveSpeed * deltaTime);
	if (SWAGE::Input::InputSystem::Get()->IsKeyDown(SWAGE::Input::KeyCode::D))
		mCamera.Strafe(moveSpeed * deltaTime);
	if (SWAGE::Input::InputSystem::Get()->IsKeyDown(SWAGE::Input::KeyCode::A))
		mCamera.Strafe(-moveSpeed * deltaTime);
	if (SWAGE::Input::InputSystem::Get()->IsMouseDown(SWAGE::Input::MouseButton::RBUTTON))
	{
		mCamera.Yaw(SWAGE::Input::InputSystem::Get()->GetMouseMoveX() * turnSpeed * deltaTime);
		mCamera.Pitch(SWAGE::Input::InputSystem::Get()->GetMouseMoveY() * turnSpeed * deltaTime);
	}
}

void GameState::Render()
{
	SWAGE::Math::Matrix4 matWorld = SWAGE::Math::Matrix4::RotationX(mRoataion.x) * Matrix4::RotationY(mRoataion.y) * Matrix4::Translation(mPosition);
	SWAGE::Math::Matrix4 matView = mCamera.GetViewMatrix();
	SWAGE::Math::Matrix4 matProj = mCamera.GetProjectionMatrix();

	TransformData transformData;
	transformData.wvp = SWAGE::Math::Transpose(matWorld * matView * matProj);

	// Download constant data to VRAM
	mConstantBuffer.Update(transformData);

	// Attach buffer to graphics pipeline
	mConstantBuffer.BindVS(0);

	mVertexShader.Bind();
	mPixelShader.Bind();
	//mVertexBuffer[vertexBufferSwitcher].Render();
	mCubeVertexBuffer.Render();


	matWorld = SWAGE::Math::Matrix4::RotationX(mRoataion.x) * Matrix4::RotationY(mRoataion.y) * Matrix4::Translation(mPosition + Vector3(3,0,0));
	transformData.wvp = SWAGE::Math::Transpose(matWorld * matView * matProj);
	mConstantBuffer.Update(transformData);
	mCubeVertexBuffer.Render();
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
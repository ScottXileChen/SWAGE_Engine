#include "GameState.h"

using namespace SWAGE::Graphics;
using namespace SWAGE::Input;
using namespace SWAGE::Math;

void GameState::Initialize()
{

	mCubeMesh = MeshBuilder::CreateCubePX();
	mCubeVertexBuffer.Initialize(mCubeMesh);

	mPlaneMesh = MeshBuilder::CreatePlanePX(10, 10, 1);
	mPlaneVertexBuffer.Initialize(mPlaneMesh);

	mCylinderMesh = MeshBuilder::CreateCylinderPX(10, 10, 2, 1);
	mCylinderVertexBuffer.Initialize(mCylinderMesh);

	mVertexShader.Initialize(L"../../Assets/Shaders/DoTexturing.fx", VertexPX::Format);
	mPixelShader.Initialize(L"../../Assets/Shaders/DoTexturing.fx");

	mSamplers[0].Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
	mSamplers[1].Initialize(Sampler::Filter::Anisotropic, Sampler::AddressMode::Wrap);
	mSamplers[2].Initialize(Sampler::Filter::Point, Sampler::AddressMode::Wrap);

	mTexture.Initialize("../../Assets/Images/WaterTurtle.png");

	// Create constant buffer
	mConstantBuffer.Initialize();

	mPosition.z = 5.0f;
}

void GameState::Terminate()
{
	mVertexShader.Terminate();
	mPixelShader.Terminate();
	mCubeVertexBuffer.Terminate();
	mConstantBuffer.Terminate();
	for (size_t i = 0; i < std::size(mSamplers); i++)
	{
		mSamplers[i].Terminate();
	}
	mTexture.Terminate();
	mPlaneVertexBuffer.Terminate();
	mCylinderVertexBuffer.Terminate();
}

void GameState::Update(float deltaTime)
{
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
	if (SWAGE::Input::InputSystem::Get()->IsKeyDown(SWAGE::Input::KeyCode::Q))
		mCamera.Rise(moveSpeed * deltaTime);
	if (SWAGE::Input::InputSystem::Get()->IsKeyDown(SWAGE::Input::KeyCode::E))
		mCamera.Rise(-moveSpeed * deltaTime);
	if (SWAGE::Input::InputSystem::Get()->IsMouseDown(SWAGE::Input::MouseButton::RBUTTON))
	{
		mCamera.Yaw(SWAGE::Input::InputSystem::Get()->GetMouseMoveX() * turnSpeed * deltaTime);
		mCamera.Pitch(SWAGE::Input::InputSystem::Get()->GetMouseMoveY() * turnSpeed * deltaTime);
	}

	mFPS = 1.0f / deltaTime;
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
	mTexture.BindPS(0);
	mSamplers[0].BindPS(0);

	mVertexShader.Bind();
	mPixelShader.Bind();
	mCubeVertexBuffer.Render();


	mSamplers[1].BindPS(0);
	matWorld = SWAGE::Math::Matrix4::RotationX(mRoataion.x) * Matrix4::RotationY(mRoataion.y) * Matrix4::Translation(mPosition + Vector3(3,0,0));
	transformData.wvp = SWAGE::Math::Transpose(matWorld * matView * matProj);
	mConstantBuffer.Update(transformData);
	mCubeVertexBuffer.Render();


	mSamplers[2].BindPS(0);
	matWorld = SWAGE::Math::Matrix4::RotationX(mRoataion.x) * Matrix4::RotationY(mRoataion.y) * Matrix4::Translation(mPosition - Vector3(3, 0, 0));
	transformData.wvp = SWAGE::Math::Transpose(matWorld * matView * matProj);
	mConstantBuffer.Update(transformData);
	mCubeVertexBuffer.Render();

	mPlaneVertexBuffer.Render();

	mCylinderVertexBuffer.Render();
}

void GameState::DebugUI()
{
	ImGui::Begin("Debug Info", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

	ImGui::Text("FPS: %f", mFPS);
	ImGui::DragFloat3("Rotation", (float*)&mRoataion, 0.01f);

	ImGui::End();
}

// Device interface - used for VRAM allocation/resource creation
// Context interface - used to issue draw commands
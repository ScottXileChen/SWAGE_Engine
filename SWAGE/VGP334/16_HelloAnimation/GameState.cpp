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

	mAnimation = AnimationBuilder()
		.SetTime(0.0f)
		.AddPositionKey({ 0,0,0 })
		.AddScaleKey({ 5,5,5 })
		//.AddRotationKey(SWAGE::Math::Quaternion::RotationAxis(SWAGE::Math::Vector3::XAxis, 60))
		.AdvanceTime(3.0f)
		.AddPositionKey({ 5,2,5 })
		//.AddRotationKey(SWAGE::Math::Quaternion::RotationAxis(SWAGE::Math::Vector3::YAxis, 60))
		.AddScaleKey({ 0,0,0 })
		.AdvanceTime(3.0f)
		//.AddRotationKey(SWAGE::Math::Quaternion::RotationAxis(SWAGE::Math::Vector3::XAxis, 60))
		.AddPositionKey({ 0,0,3 })
		.AddScaleKey({ 0.2f,0.2f,0.2f })
		.SetLooping(true)
		.Get();

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
	auto inputSystem = SWAGE::Input::InputSystem::Get();
	if (inputSystem->IsKeyDown(SWAGE::Input::KeyCode::LEFT))
		mRoataion.y += deltaTime;
	if (inputSystem->IsKeyDown(SWAGE::Input::KeyCode::RIGHT))
		mRoataion.y -= deltaTime;

	if (inputSystem->IsKeyDown(SWAGE::Input::KeyCode::UP))
		mRoataion.x += deltaTime;
	if (inputSystem->IsKeyDown(SWAGE::Input::KeyCode::DOWN))
		mRoataion.x -= deltaTime;

	const float moveSpeed = 10.0f;
	const float turnSpeed = 10.0f * Constants::DegToRad;
	if (inputSystem->IsKeyDown(SWAGE::Input::KeyCode::W))
		mCamera.Walk(moveSpeed * deltaTime);
	if (inputSystem->IsKeyDown(SWAGE::Input::KeyCode::S))
		mCamera.Walk(-moveSpeed * deltaTime);
	if (inputSystem->IsKeyDown(SWAGE::Input::KeyCode::D))
		mCamera.Strafe(moveSpeed * deltaTime);
	if (inputSystem->IsKeyDown(SWAGE::Input::KeyCode::A))
		mCamera.Strafe(-moveSpeed * deltaTime);
	if (inputSystem->IsKeyDown(SWAGE::Input::KeyCode::Q))
		mCamera.Rise(moveSpeed * deltaTime);
	if (inputSystem->IsKeyDown(SWAGE::Input::KeyCode::E))
		mCamera.Rise(-moveSpeed * deltaTime);
	if (inputSystem->IsMouseDown(SWAGE::Input::MouseButton::RBUTTON))
	{
		mCamera.Yaw(inputSystem->GetMouseMoveX() * turnSpeed * deltaTime);
		mCamera.Pitch(inputSystem->GetMouseMoveY() * turnSpeed * deltaTime);
	}
	//CameraUtil::UpdateFPSCamera(mCamera, inputSystem, moveSpeed, turnSpeed);

	mFPS = 1.0f / deltaTime;

	mAnimationTimer += deltaTime;
}

void GameState::Render()
{
    //SWAGE::Math::Matrix4 matWorld = SWAGE::Math::Matrix4::RotationX(mRoataion.x) * Matrix4::RotationY(mRoataion.y) * Matrix4::Translation(mPosition);
	SWAGE::Math::Matrix4 matView = mCamera.GetViewMatrix();
	SWAGE::Math::Matrix4 matProj = mCamera.GetProjectionMatrix();

	const auto pos = mAnimation.GetPosition(mAnimationTimer);
	//const auto rot = mAnimation.GetRotation(mAnimationTimer);
	const auto scale = mAnimation.GetScale(mAnimationTimer);
	const auto matWorld = Matrix4::Scaling(scale)/** Matrix4::RotationQuaternion(rot)*/ * Matrix4::Translation(pos);

	TransformData transformData;
	transformData.wvp = SWAGE::Math::Transpose(matWorld * matView * matProj);

	// Download constant data to VRAM
	mConstantBuffer.Update(transformData);

	// Attach buffer to graphics pipeline
	mConstantBuffer.BindVS(0);
	mTexture.BindPS(0);

	mVertexShader.Bind();
	mPixelShader.Bind();

	mSamplers[2].BindPS(0);


	mCylinderVertexBuffer.Render();
}

void GameState::DebugUI()
{
	ImGui::Begin("Debug Info", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

	ImGui::Text("FPS: %f", mFPS);
	ImGui::Text("Time: %f", mAnimationTimer);
	ImGui::DragFloat3("Rotation", (float*)&mRoataion, 0.01f);

	ImGui::End();
}

// Device interface - used for VRAM allocation/resource creation
// Context interface - used to issue draw commands
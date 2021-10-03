#include "GameState.h"

using namespace SWAGE::Graphics;
using namespace SWAGE::Input;
using namespace SWAGE::Math;

namespace
{

}

void GameState::Initialize()
{
	GraphicsSystem::Get()->SetClearColor(Colors::Black);

	mCamera.SetPosition({ 0.0f, 0.0f, -12.0f });

	//mFireMesh = MeshBuilder::CreateSpherePX(50, 50, 1);
	//mFireMesh = MeshBuilder::CreatePlanePX(50, 50, 1);
	mFireMesh = MeshBuilder::CreateFire();
	mFireMeshBuffer.Initialize(mFireMesh);

	mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
	mSampler2.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Clamp);
	mFireTexture.Initialize(L"../../Assets//Images/AnyConv.com__fire01.png");
	mNoiseTexture.Initialize(L"../../Assets//Images/AnyConv.com__noise01.png");
	mAlphaTexture.Initialize(L"../../Assets//Images/AnyConv.com__alpha01.png");

	mFireVertexShader.Initialize(L"../../Assets/Shaders/Fire.fx", VertexPX::Format);
	mFirePixelShader.Initialize(L"../../Assets/Shaders/Fire.fx");

	mNoiseBufferTypeBuffer.Initialize();
	mTransformDataBuffer.Initialize();
	mDistortionBufferTypeBuffer.Initialize();

	mNoise.scrollSpeeds = Vector3(1.3f, 2.1f, 2.3f);
	mNoise.scales = Vector3(1.0f, 2.0f, 3.0f);

	mDistortion.distortion1 = Vector2(0.1f, 0.2f);
	mDistortion.distortion2 = Vector2(0.1f, 0.3f);
	mDistortion.distortion3 = Vector2(0.1f, 0.1f);
	mDistortion.distortionBias = -0.8f;
	mDistortion.distortionScale = -8.34f;

	mBlendState.Initialize(SWAGE::Graphics::BlendState::Mode::Additive);
}

void GameState::Terminate()
{
	mTransformDataBuffer.Terminate();
	mNoiseBufferTypeBuffer.Terminate();
	mDistortionBufferTypeBuffer.Terminate();
	mFireMeshBuffer.Terminate();
	mFireVertexShader.Terminate();
	mFirePixelShader.Terminate();
	mFireTexture.Terminate();
	mAlphaTexture.Terminate();
	mNoiseTexture.Terminate();
	mSampler.Terminate();
	mSampler2.Terminate();
	mBlendState.Terminate();
}

void GameState::Update(float deltaTime)
{
	mFPS = 1.0f / deltaTime;

	auto inputSystem = InputSystem::Get();

	//if (inputSystem->IsKeyDown(KeyCode::LEFT))
	//	mRotation.y += deltaTime;
	//if (inputSystem->IsKeyDown(KeyCode::RIGHT))
	//	mRotation.y -= deltaTime;

	//if (inputSystem->IsKeyDown(KeyCode::UP))
	//	mRotation.x += deltaTime;
	//if (inputSystem->IsKeyDown(KeyCode::DOWN))
	//	mRotation.x -= deltaTime;

	const float moveSpeed = 10.0f;
	const float turnSpeed = 6.0f * Constants::DegToRad;
	if (inputSystem->IsKeyDown(KeyCode::W))
		mCamera.Walk(moveSpeed * deltaTime);
	if (inputSystem->IsKeyDown(KeyCode::S))
		mCamera.Walk(-moveSpeed * deltaTime);
	if (inputSystem->IsKeyDown(KeyCode::D))
		mCamera.Strafe(moveSpeed * deltaTime);
	if (inputSystem->IsKeyDown(KeyCode::A))
		mCamera.Strafe(-moveSpeed * deltaTime);
	if (inputSystem->IsMouseDown(MouseButton::RBUTTON))
	{
		mCamera.Yaw(inputSystem->GetMouseMoveX() * turnSpeed * deltaTime);
		mRotation.y += inputSystem->GetMouseMoveX() * turnSpeed * deltaTime;
		mCamera.Pitch(inputSystem->GetMouseMoveY() * turnSpeed * deltaTime);
	}
}

void GameState::Render()
{
	RenderScene();

	PostProcess();
}

void GameState::DebugUI()
{
	ImGui::Begin("Hello");
	ImGui::DragFloat("frameTime", &mNoise.frameTime);
	ImGui::DragFloat3("scales", &mNoise.scales.x);
	ImGui::DragFloat3("scrollSpeeds", &mNoise.scrollSpeeds.x);\

	ImGui::DragFloat2("distortion1", &mDistortion.distortion1.x);
	ImGui::DragFloat2("distortion2", &mDistortion.distortion2.x);
	ImGui::DragFloat2("distortion3", &mDistortion.distortion3.x);
	ImGui::DragFloat("distortionBias", &mDistortion.distortionBias);
	ImGui::DragFloat("distortionScale", &mDistortion.distortionScale);

	ImGui::End();
}

void GameState::RenderScene()
{
	//mCamera.
	Matrix4 matWorld = Matrix4::RotationY(mRotation.y);
	Matrix4 matView = mCamera.GetViewMatrix();
	Matrix4 matProj = mCamera.GetProjectionMatrix();
	Matrix4 wvp = Transpose(matWorld * matView * matProj);
	TransformData transform;
	transform.wvp = wvp;
	mTransformDataBuffer.Update(transform);

	mTransformDataBuffer.BindVS(0);
	mTransformDataBuffer.BindPS(0);


	mNoise.frameTime += 0.01f;
	if (mNoise.frameTime > 1000.0f)
	{
		mNoise.frameTime = 0.0f;
	}
	mNoiseBufferTypeBuffer.Update(mNoise);

	mNoiseBufferTypeBuffer.BindVS(1);
	mNoiseBufferTypeBuffer.BindPS(1);

	mDistortionBufferTypeBuffer.Update(mDistortion);
	mDistortionBufferTypeBuffer.BindVS(2);
	mDistortionBufferTypeBuffer.BindPS(2);

	mSampler.BindVS(0);
	mSampler.BindPS(0);
	mSampler2.BindPS(1);
	mSampler2.BindPS(1);

	mFireTexture.BindPS(0);
	mNoiseTexture.BindPS(1);
	mAlphaTexture.BindPS(2);

	mFireVertexShader.Bind();
	mFirePixelShader.Bind();

	mBlendState.Set();
	mFireMeshBuffer.Render();
	SWAGE::Graphics::BlendState::ClearState();
}

void GameState::PostProcess()
{

}
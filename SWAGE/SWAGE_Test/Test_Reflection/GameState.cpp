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

	mCamera.SetPosition({ -1.904f, 4.823f, -2.636f });
	mCamera.SetDirection({ 0.411f, -0.884f, 0.218f });
	mCamera.SetNearPlane(0.001f);

	mCamera2.SetDirection(mCamera.GetDirection());
	Vector3 newCameraPosition = -mCamera2.GetDirection() * 10;
	mCamera2.SetPosition(newCameraPosition);

	mWaterMesh = MeshBuilder::CreatePlanePX(10, 10, 1);
	mWaterMeshBuffer.Initialize(mWaterMesh);

	mCubeMesh = MeshBuilder::CreateCubePX();
	mCubeMeshBuffer.Initialize(mCubeMesh);

	mCube2Mesh = MeshBuilder::CreatePlanePNX(10, 10, 1);
	mCube2MeshBuffer.Initialize(mCube2Mesh);

	mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
	mSampler2.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Clamp);

	mWaterTexture.Initialize(L"../../Assets/Images//blue01.png");
	mRefractionTexture.Initialize(L"../../Assets//Images/seafloor.png");
	mReflectionTexture.Initialize(L"../../Assets//Images/ground.png");

	mWaterVertexShader.Initialize(L"../../Assets/Shaders/Reflection.fx", VertexPX::Format);
	mWaterPixelShader.Initialize(L"../../Assets/Shaders/Reflection.fx");
	mRefractionVertexShader.Initialize(L"../../Assets/Shaders/Refraction.fx", VertexPNX::Format);
	mRefractionPixelShader.Initialize(L"../../Assets/Shaders/Refraction.fx");
	mTextureVertexShader.Initialize(L"../../Assets/Shaders/DoTexturing.fx", VertexPX::Format);
	mTexturePixelShader.Initialize(L"../../Assets/Shaders/DoTexturing.fx");

	mTransformDataBuffer.Initialize();
	mReflectionBuffer.Initialize();
	mWaterBuffer.Initialize();
	mClipPlaneBuffer.Initialize();
	mLightBuffer.Initialize();
	mTransformDataBuffer2.Initialize();

	mRefractionRenderTarget.Initialize(
		GraphicsSystem::Get()->GetBackBufferWidth(),
		GraphicsSystem::Get()->GetBackBufferHeight(),
		SWAGE::Graphics::Texture::Format::RGBA_F32
	);
	mReflectionRenderTarget.Initialize(
		GraphicsSystem::Get()->GetBackBufferWidth(),
		GraphicsSystem::Get()->GetBackBufferHeight(),
		SWAGE::Graphics::Texture::Format::RGBA_F32
	);


	lightBuffer.ambientColor = Vector4(0.367f, 0.367f, 0.367f, 1.0f);
	lightBuffer.diffuseColor = Vector4(1.0f, 1.0f, 0.999f, 1.0f);
	lightBuffer.lightDirection = Vector3(0.0f, -1.0f, 0.5f);

	clipPlaneBuffer.clipPlane = Vector4(0.0f, -1.0f, 0.0f, 1.1f);
	waterBuffer.reflectRefractScale = 0.5f;
}

void GameState::Terminate()
{
	mTransformDataBuffer.Terminate();
	mReflectionBuffer.Terminate();
	mWaterBuffer.Terminate();
	mClipPlaneBuffer.Terminate();
	mLightBuffer.Terminate();
	mWaterMeshBuffer.Terminate();
	mWaterVertexShader.Terminate();
	mWaterPixelShader.Terminate();
	mRefractionVertexShader.Terminate();
	mRefractionPixelShader.Terminate();
	mWaterTexture.Terminate();
	mSampler.Terminate();
	mSampler2.Terminate();
	mRefractionRenderTarget.Terminate();
	mRefractionTexture.Terminate();
	mCubeMeshBuffer.Terminate();
	mReflectionTexture.Terminate();
	mReflectionRenderTarget.Terminate();
	mTextureVertexShader.Terminate();
	mTexturePixelShader.Terminate();
	mTransformDataBuffer2.Terminate();
	mCube2MeshBuffer.Terminate();
}

void GameState::Update(float deltaTime)
{
	mFPS = 1.0f / deltaTime;

	auto inputSystem = InputSystem::Get();

	if (inputSystem->IsKeyDown(KeyCode::LEFT))
		mRotation.y += deltaTime;
	if (inputSystem->IsKeyDown(KeyCode::RIGHT))
		mRotation.y -= deltaTime;

	if (inputSystem->IsKeyDown(KeyCode::UP))
		mRotation.x += deltaTime;
	if (inputSystem->IsKeyDown(KeyCode::DOWN))
		mRotation.x -= deltaTime;

	const float moveSpeed = 10.0f;
	const float turnSpeed = 6.0f * Constants::DegToRad;
	if (inputSystem->IsKeyDown(KeyCode::W))
	{
		mCamera.Walk(moveSpeed * deltaTime);
		mCamera2.Walk(moveSpeed * deltaTime);
	}
	if (inputSystem->IsKeyDown(KeyCode::S))
	{
		mCamera.Walk(-moveSpeed * deltaTime);
		mCamera2.Walk(-moveSpeed * deltaTime);
	}
	if (inputSystem->IsKeyDown(KeyCode::D))
	{
		mCamera.Strafe(moveSpeed * deltaTime);
		mCamera2.Strafe(moveSpeed * deltaTime);
	}
	if (inputSystem->IsKeyDown(KeyCode::A))
	{
		mCamera.Strafe(-moveSpeed * deltaTime);
		mCamera2.Strafe(-moveSpeed * deltaTime);
	}
	if (SWAGE::Input::InputSystem::Get()->IsKeyDown(SWAGE::Input::KeyCode::Q))
	{
		mCamera.Rise(moveSpeed * deltaTime);
		mCamera2.Rise(moveSpeed * deltaTime);
	}
	if (SWAGE::Input::InputSystem::Get()->IsKeyDown(SWAGE::Input::KeyCode::E))
	{
		mCamera.Rise(-moveSpeed * deltaTime);
		mCamera2.Rise(-moveSpeed * deltaTime);
	}

	if (inputSystem->IsMouseDown(MouseButton::RBUTTON))
	{
		mCamera.Yaw(inputSystem->GetMouseMoveX() * turnSpeed * deltaTime);
		mCamera.Pitch(inputSystem->GetMouseMoveY() * turnSpeed * deltaTime);

		mCamera2.Yaw(inputSystem->GetMouseMoveX() * turnSpeed * deltaTime);
		mCamera2.Pitch(inputSystem->GetMouseMoveY() * turnSpeed * deltaTime);
	}
}

void GameState::Render()
{
	RenderReflection();

	RenderScene();

	//PostProcess();
}

void GameState::DebugUI()
{
}

void GameState::RenderReflection()
{
	mReflectionRenderTarget.BeginRender();

	mTextureVertexShader.Bind();
	mTexturePixelShader.Bind();

	TransformData2 transform;
	Matrix4 worldMatrix = Matrix4::Translation(Vector3(0, 2, 0));
	Matrix4 viewMatrix = mCamera2.GetViewMatrix();
	Matrix4 projectionMatrix = mCamera2.GetProjectionMatrix();
	transform.wvp = Transpose(viewMatrix * projectionMatrix);
	mTransformDataBuffer2.Update(transform);
	mTransformDataBuffer2.BindVS(0);
	mTransformDataBuffer2.BindPS(0);

	mSampler.BindVS(0);
	mSampler.BindPS(0);

	mReflectionTexture.BindPS(0);

	mCubeMeshBuffer.Render();

	mReflectionRenderTarget.EndRender();
}

void GameState::RenderScene()
{
	mWaterVertexShader.Bind();
	mWaterPixelShader.Bind();

	TransformData transform;
	Matrix4 worldMatrix = Matrix4::RotationX(mRotation.x) * Matrix4::RotationY(mRotation.y);
	Matrix4 viewMatrix = mCamera.GetViewMatrix();
	Matrix4 projectionMatrix = mCamera.GetProjectionMatrix();
	transform.wvp[0] = Transpose(worldMatrix * viewMatrix * projectionMatrix);
	transform.wvp[1] = Transpose(mCamera2.GetViewMatrix() * mCamera2.GetProjectionMatrix());
	transform.Rewvp = Transpose(GetReflectionViewMatrix(0.7f) * projectionMatrix * worldMatrix);
	mTransformDataBuffer.Update(transform);
	mTransformDataBuffer.BindVS(0);
	mTransformDataBuffer.BindPS(0);

	mSampler.BindVS(0);
	mSampler.BindPS(0);

	mWaterTexture.BindPS(0);
	mReflectionRenderTarget.BindPS(1);

	mWaterMeshBuffer.Render();
	Texture::UnbindPS(1);

	//..........
	mTextureVertexShader.Bind();
	mTexturePixelShader.Bind();
	TransformData2 transform2;
	worldMatrix = Matrix4::Translation(Vector3(0, 2, 0));
	viewMatrix = mCamera.GetViewMatrix();
	projectionMatrix = mCamera.GetProjectionMatrix();
	transform2.wvp = Transpose(worldMatrix * viewMatrix * projectionMatrix);
	mTransformDataBuffer2.Update(transform2);
	mTransformDataBuffer2.BindVS(0);
	mTransformDataBuffer2.BindPS(0);

	mSampler.BindVS(0);
	mSampler.BindPS(0);

	mReflectionTexture.BindPS(0);

	mCubeMeshBuffer.Render();
}

void GameState::PostProcess()
{

}

Matrix4 GameState::GetReflectionViewMatrix(float height)
{
	Vector3 up, position, lookAt;
	float radians;


	// Setup the vector that points upwards.
	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;

	// Setup the position of the camera in the world.
	// For planar reflection invert the Y position of the camera.
	position.x = mCamera.GetPosition().x;
	position.y = -mCamera.GetPosition().y + (height * 2.0f);
	position.z = mCamera.GetPosition().z;

	// Calculate the rotation in radians.
	radians = mRotation.y * 0.0174532925f;

	// Setup where the camera is looking.
	lookAt.x = sinf(radians) + mCamera.GetPosition().x;
	lookAt.y = position.y;
	lookAt.z = cosf(radians) + mCamera.GetPosition().z;


	Vector3 zaxis = SWAGE::Math::Normalize(lookAt - mCamera.GetPosition());
	Vector3 xaxis = SWAGE::Math::Normalize(SWAGE::Math::Cross(up, zaxis));
	Vector3 yaxis = SWAGE::Math::Cross(zaxis, xaxis);

	return
	{
		xaxis.x,           yaxis.x,           zaxis.x,          0,
		xaxis.y,           yaxis.y,           zaxis.y,          0,
		xaxis.z,           yaxis.z,           zaxis.z,          0,
		- SWAGE::Math::Dot(xaxis, mCamera.GetPosition()), -SWAGE::Math::Dot(yaxis, mCamera.GetPosition()), -SWAGE::Math::Dot(zaxis, mCamera.GetPosition()),  1
	};
}

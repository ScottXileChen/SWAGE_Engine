#include "GameState.h"

using namespace SWAGE::Graphics;
using namespace SWAGE::Input;
using namespace SWAGE::Math;

void GameState::Initialize()
{
	GraphicsSystem::Get()->SetClearColor(Colors::White);

	mDefaultCamera.SetPosition({ 0.0f, 0.0f, -12.0f });
	mDefaultCamera.SetNearPlane(0.001f);

	mLightCamera.SetNearPlane(1.0f);
	mLightCamera.SetFarPlane(200.0f);
	mLightCamera.SetAspectRatio(1.0f);

	mActiveCamera = &mDefaultCamera;

	constexpr uint32_t depthMapSize = 4096;
	mDepthRenderTarget.Initialize(depthMapSize, depthMapSize, Texture::Format::RGBA_F32);

	mBloomRenderTarget.Initialize(
		GraphicsSystem::Get()->GetBackBufferWidth(),
		GraphicsSystem::Get()->GetBackBufferHeight()
	);
	mBlurRenderTarget.Initialize(
		GraphicsSystem::Get()->GetBackBufferWidth(),
		GraphicsSystem::Get()->GetBackBufferHeight()
	);

	mGroundMesh = MeshBuilder::CreatePlane(10, 10, 1);
	mGroundMeshBuffer.Initialize(mGroundMesh);

	ModelLoader::LoadObj(L"../../Assets//Models/trident_a10/trident_a10.obj", 0.001f, mModelMesh);
	mModelMeshBuffer.Initialize(mModelMesh);

	mStandardVertexShader.Initialize(L"../../Assets/Shaders/Standard.fx", Vertex::Format);
	mStandardPixelShader.Initialize(L"../../Assets/Shaders/Standard.fx");

	mDepthMapVertexShader.Initialize(L"../../Assets/Shaders/DepthMap.fx", Vertex::Format);
	mDepthMapPixelShader.Initialize(L"../../Assets/Shaders/DepthMap.fx");

	mEarthVertexShader.Initialize(L"../../Assets/Shaders/Earth.fx", Vertex::Format);
	mEarthPixelShader.Initialize(L"../../Assets/Shaders/Earth.fx");

	mGaussianBlurVertexShader.Initialize(L"../../Assets/Shaders/GaussianBlur.fx", VertexPX::Format);
	mGaussianBlurXPixelShader.Initialize(L"../../Assets/Shaders/GaussianBlur.fx", "BlurXPS");
	mGaussianBlurYPixelShader.Initialize(L"../../Assets/Shaders/GaussianBlur.fx", "BlurYPS");

	mBloomVertexShader.Initialize(L"../../Assets/Shaders/Bloom.fx", VertexPX::Format);
	mBloomPixelShader.Initialize(L"../../Assets/Shaders/Bloom.fx");

	mDepthMapTransformBuffer.Initialize();
	mEarthTransformBuffer.Initialize();
	mTexturingTransformBuffer.Initialize();
	mBlurSettingsBuffer.Initialize();
	mLightBuffer.Initialize();
	mMaterialBuffer.Initialize();
	mSettingBuffer.Initialize();

	mDirectionalLight.direction = Normalize({ 1.0f, -1.0f, 1.0f });
	mDirectionalLight.ambient = { 0.2f, 0.2f, 0.2f, 1.0f };
	mDirectionalLight.diffuse = { 0.9f, 0.9f, 0.9f, 1.0f };
	mDirectionalLight.specular = { 0.5f, 0.5f, 0.5f, 1.0f };

	mMaterial.ambient = { 0.2f, 0.2f, 0.2f, 1.0f };
	mMaterial.diffuse = { 0.85f, 0.85f, 0.85f, 1.0f };
	mMaterial.specular = { 0.5f, 0.5f, 0.5f, 1.0f };
	mMaterial.power = 10.0f;

	mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
	mEarthDiffuseTexture.Initialize(L"../../Assets//Models/trident_a10/trident_decal_diffuse.tif");
	mGroundTexture.Initialize(L"../../Assets/Images/Green.png");
	mEarthSpecularTexture.Initialize(L"../../Assets//Models/trident_a10/trident_specular.tif");
	mEarthDisplacmentTexture.Initialize(L"../../Assets//Models/trident_a10/trident_bump.tif");
	//mEarthNormalTexture.Initialize(L"../../Assets/Images/earth_normal.jpg");

	//
	// (-1,+1)---------------(+1,+1)
	//    |          ^          |
	//    |          +->        |
	//    |                     |
	// (-1,-1)---------------(+1,-1)
	//
	mScreenMesh.vertices.push_back({ {-1.0f, -1.0f, 0.0f }, { 0.0f, 1.0f } });
	mScreenMesh.vertices.push_back({ {-1.0f, +1.0f, 0.0f }, { 0.0f, 0.0f } });
	mScreenMesh.vertices.push_back({ {+1.0f, +1.0f, 0.0f }, { 1.0f, 0.0f } });
	mScreenMesh.vertices.push_back({ {+1.0f, -1.0f, 0.0f }, { 1.0f, 1.0f } });

	mScreenMesh.indices.push_back(0);
	mScreenMesh.indices.push_back(1);
	mScreenMesh.indices.push_back(2);

	mScreenMesh.indices.push_back(0);
	mScreenMesh.indices.push_back(2);
	mScreenMesh.indices.push_back(3);

	mScreenMeshBuffer.Initialize(mScreenMesh);
}

void GameState::Terminate()
{
	mSettingBuffer.Terminate();
	mStandardVertexShader.Terminate();
	mStandardPixelShader.Terminate();
	mScreenMeshBuffer.Terminate();
	mGroundTexture.Terminate();
	//mEarthNormalTexture.Terminate();
	mEarthDisplacmentTexture.Terminate();
	mEarthSpecularTexture.Terminate();
	mEarthDiffuseTexture.Terminate();
	mSampler.Terminate();
	mMaterialBuffer.Terminate();
	mLightBuffer.Terminate();
	mBlurSettingsBuffer.Terminate();
	mDepthMapTransformBuffer.Terminate();
	mTexturingTransformBuffer.Terminate();
	mEarthTransformBuffer.Terminate();
	mBloomPixelShader.Terminate();
	mBloomVertexShader.Terminate();
	mGaussianBlurYPixelShader.Terminate();
	mGaussianBlurXPixelShader.Terminate();
	mGaussianBlurVertexShader.Terminate();
	mEarthPixelShader.Terminate();
	mEarthVertexShader.Terminate();
	mDepthMapVertexShader.Terminate();
	mDepthMapPixelShader.Terminate();
	mGroundMeshBuffer.Terminate();
	mModelMeshBuffer.Terminate();
	mBlurRenderTarget.Terminate();
	mBloomRenderTarget.Terminate();
	mDepthRenderTarget.Terminate();
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
		mActiveCamera->Walk(moveSpeed * deltaTime);
	if (inputSystem->IsKeyDown(KeyCode::S))
		mActiveCamera->Walk(-moveSpeed * deltaTime);
	if (inputSystem->IsKeyDown(KeyCode::D))
		mActiveCamera->Strafe(moveSpeed * deltaTime);
	if (inputSystem->IsKeyDown(KeyCode::A))
		mActiveCamera->Strafe(-moveSpeed * deltaTime);
	if (inputSystem->IsKeyDown(SWAGE::Input::KeyCode::Q))
		mActiveCamera->Rise(moveSpeed * deltaTime);
	if (inputSystem->IsKeyDown(SWAGE::Input::KeyCode::E))
		mActiveCamera->Rise(-moveSpeed * deltaTime);
	if (inputSystem->IsMouseDown(MouseButton::RBUTTON))
	{
		mActiveCamera->Yaw(inputSystem->GetMouseMoveX() * turnSpeed * deltaTime);
		mActiveCamera->Pitch(inputSystem->GetMouseMoveY() * turnSpeed * deltaTime);
	}

	if (inputSystem->IsKeyDown(SWAGE::Input::KeyCode::NUMPAD4))
		mTransformPosition.x -= deltaTime;
	if (inputSystem->IsKeyDown(SWAGE::Input::KeyCode::NUMPAD6))
		mTransformPosition.x += deltaTime;
	if (inputSystem->IsKeyDown(SWAGE::Input::KeyCode::NUMPAD7))
		mTransformPosition.y -= deltaTime;
	if (inputSystem->IsKeyDown(SWAGE::Input::KeyCode::NUMPAD9))
		mTransformPosition.y += deltaTime;
	if (inputSystem->IsKeyDown(SWAGE::Input::KeyCode::NUMPAD2))
		mTransformPosition.z -= deltaTime;
	if (inputSystem->IsKeyDown(SWAGE::Input::KeyCode::NUMPAD8))
		mTransformPosition.z += deltaTime;

	// Synchronize the light camera to the directional light (cannot look straight up or down!)
	mLightCamera.SetDirection(mDirectionalLight.direction);
	Vector3 newCameraPosition = -mLightCamera.GetDirection() * mLightCameraDistance;
	mLightCamera.SetPosition(newCameraPosition);
}

void GameState::Render()
{
	// Record scene depths from light source
	RenderDepthMap();

	// Capture a screen shot - 1st Pass
	// Render scene with shadow apply
	RenderScene();
}

void GameState::DebugUI()
{
	ImGui::Begin("Debug Info", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::Text("fps: %f", mFPS);

	if (ImGui::CollapsingHeader("Camera", ImGuiTreeNodeFlags_DefaultOpen))
	{
		bool useLightCamera = (mActiveCamera == &mLightCamera);
		if (ImGui::Checkbox("Use Light Camera", &useLightCamera))
		{
			mActiveCamera = useLightCamera ? &mLightCamera : &mDefaultCamera;
		}
		ImGui::DragFloat("Light Camera Distance", &mLightCameraDistance, 1.0f, 1.0f, 1000.0f);
	}

	if (ImGui::CollapsingHeader("Light", ImGuiTreeNodeFlags_DefaultOpen))
	{
		if (ImGui::DragFloat3("Light Direction", &mDirectionalLight.direction.x, 0.01f, -1.0f, 1.0f))
			mDirectionalLight.direction = Normalize(mDirectionalLight.direction);
		ImGui::ColorEdit3("Light Ambient", &mDirectionalLight.ambient.x);
		ImGui::ColorEdit3("Light Diffuse", &mDirectionalLight.diffuse.x);
		ImGui::ColorEdit3("Light Specular", &mDirectionalLight.specular.x);
	}

	if (ImGui::CollapsingHeader("Material", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::ColorEdit3("Material Ambient", &mMaterial.ambient.x);
		ImGui::ColorEdit3("Material Diffuse", &mMaterial.diffuse.x);
		ImGui::ColorEdit3("Material Specular", &mMaterial.specular.x);
		ImGui::DragFloat("Material Power", &mMaterial.power, 0.1f, 1.0f, 100.0f);
	}

	if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::DragFloat3("Rotation", (float*)&mRotation, 0.01f);
	}

	if (ImGui::CollapsingHeader("Bloom", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::DragInt("Blur Iterations", &mBlurIterations, 1, 0, 100);
		ImGui::DragFloat("Blur Saturation", &mBlurSaturation, 0.001f, 0.0f, 1.0f);
	}

	ImGui::Image(mDepthRenderTarget.GetRawData(), { 200.0f, 200.0f });
	ImGui::End();
}

void GameState::RenderDepthMap()
{
	mDepthRenderTarget.BeginRender(Colors::Black);

	// Draw all the shadow casters using the light camera
	Matrix4 matView = mLightCamera.GetViewMatrix();
	Matrix4 matProj = mLightCamera.GetProjectionMatrix();

	mDepthMapTransformBuffer.BindVS(0);

	mDepthMapVertexShader.Bind();
	mDepthMapPixelShader.Bind();
	
	mSampler.BindVS(0);

	Matrix4 matWorld = Matrix4::RotationX(mRotation.x) * Matrix4::RotationY(mRotation.y) * Matrix4::Translation(mTransformPosition.x, mTransformPosition.y, mTransformPosition.z);
	Matrix4 wvp = Transpose(matWorld * matView * matProj);
	mDepthMapTransformBuffer.Update(wvp);

	mEarthDisplacmentTexture.BindVS(0);

	mModelMeshBuffer.Render();

	mDepthRenderTarget.EndRender();
}

void GameState::RenderScene()
{
	Matrix4 matView = mActiveCamera->GetViewMatrix();
	Matrix4 matProj = mActiveCamera->GetProjectionMatrix();

	Matrix4 matViewLight = mLightCamera.GetViewMatrix();
	Matrix4 matProjLight = mLightCamera.GetProjectionMatrix();

	EarthTransformData earthTransformData;
	earthTransformData.viewPosition = mActiveCamera->GetPosition();
	mEarthTransformBuffer.BindVS(0);
	mEarthTransformBuffer.BindPS(0);

	mLightBuffer.Update(mDirectionalLight);
	mLightBuffer.BindVS(1);
	mLightBuffer.BindPS(1);

	mMaterialBuffer.Update(mMaterial);
	mMaterialBuffer.BindVS(2);
	mMaterialBuffer.BindPS(2);

	Matrix4 matWorld = Matrix4::RotationX(mRotation.x) * Matrix4::RotationY(mRotation.y) * Matrix4::Translation(mTransformPosition.x, mTransformPosition.y, mTransformPosition.z);
	earthTransformData.wvp[0] = Transpose(matWorld * matView * matProj);
	earthTransformData.wvp[1] = Transpose(matWorld * matViewLight * matProjLight);
	mEarthTransformBuffer.Update(earthTransformData);

	mStandardVertexShader.Bind();
	mStandardPixelShader.Bind();

	mSampler.BindVS(0);
	mSampler.BindPS(0);

	mEarthDiffuseTexture.BindPS(0);
	mEarthSpecularTexture.BindPS(1);
	mEarthDisplacmentTexture.BindVS(2);
	//mEarthNormalTexture.BindPS(3);
	mDepthRenderTarget.BindPS(4);

	StandSettingBuffer setting;
	setting.displacementWeight = 0.2f;
	setting.isNormalMapOn = 0;
	setting.isSpecularMapOn = 1;
	mSettingBuffer.Update(setting);
	mSettingBuffer.BindVS(3);
	mSettingBuffer.BindPS(3);

	mModelMeshBuffer.Render();

	earthTransformData.world = Transpose(Matrix4::Identity);
	earthTransformData.wvp[0] = Transpose(Matrix4::Translation(Vector3{ 0, 0, 0 }) * matView * matProj);
	earthTransformData.wvp[1] = Transpose(matViewLight * matProjLight);
	mEarthTransformBuffer.Update(earthTransformData);

	SWAGE::Graphics::DirectionalLight groundDirectionalLight;
	groundDirectionalLight.ambient = {0.5f};
	groundDirectionalLight.diffuse = {0.784f};
	groundDirectionalLight.specular = {0.858f};
	groundDirectionalLight.direction = mDirectionalLight.direction;

	SWAGE::Graphics::Material groundMaterial;
	groundMaterial.ambient = {0.5f};
	groundMaterial.diffuse = { 0.784f };
	groundMaterial.specular = { 0.39f };
	groundMaterial.power = mMaterial.power;

	mLightBuffer.Update(groundDirectionalLight);
	mMaterialBuffer.Update(groundMaterial);
	
	mGroundTexture.BindPS(0);
	Texture::UnbindPS(1);
	Texture::UnbindPS(2);
	Texture::UnbindPS(3);
	mGroundMeshBuffer.Render();

	Texture::UnbindPS(4);

	SimpleDraw::AddLine({ 0, 0, 0 }, { 1, 0, 0 }, Colors::Red);
	SimpleDraw::AddLine({ 0, 0, 0 }, { 0, 1, 0 }, Colors::Green);
	SimpleDraw::AddLine({ 0, 0, 0 }, { 0, 0, 1 }, Colors::Blue);
	SimpleDraw::Render(*mActiveCamera);
}

void GameState::PostProcess()
{
	mBloomVertexShader.Bind();
	mBloomPixelShader.Bind();

	mSampler.BindPS(0);

	mBloomRenderTarget.BindPS(1);

	mScreenMeshBuffer.Render();

	Texture::UnbindPS(0);
	Texture::UnbindPS(1);
}
#include "GameState.h"

using namespace SWAGE::Graphics;
using namespace SWAGE::Input;
using namespace SWAGE::Math;

void GameState::Initialize()
{
	auto graphicsSystem = GraphicsSystem::Get();
	graphicsSystem->SetClearColor(SWAGE::Graphics::Colors::Gray);

	mSphereMesh = MeshBuilder::CreateSpherePN(20,20,1);
	mSphereBuffer.Initialize(mSphereMesh);

	const wchar_t* shaderFileNames[] = 
	{
		L"../../Assets/Shaders/DoGouraudShading.fx"
		, L"../../Assets/Shaders/DoPhongShading.fx"
	};

	for (size_t i = 0; i < std::size(shaderFileNames); i++)
	{
		mVertexShader[i].Initialize(shaderFileNames[i], VertexPN::Format);
		mPixelShader[i].Initialize(shaderFileNames[i]);
	}

	// Create constant buffer
	mTransformBuffer.Initialize();
	mLightBuffer.Initialize();
	mMaterialBuffer.Initialize();

	mPosition.z = 5.0f;

	mDirectionalLight.direction = { 0.577f, -0.577f, 0.577f };
	mDirectionalLight.ambient = { 0.2f,0.2f,0.2f,1.0f };
	mDirectionalLight.diffuse = { 0.9f,0.9f,0.9f,1.0f };
	mDirectionalLight.specular = { 0.2f,0.2f,0.2f,1.0f };

	mMaterial.ambient = { 0.2f,0.2f,0.2f,1.0f };
	mMaterial.diffuse = { 0.95f,0.2f,0.2f,1.0f };
	mMaterial.specular = { 0.5f,0.5f,0.5f,1.0f };
	mMaterial.power = 10;
}

void GameState::Terminate()
{
	mSphereBuffer.Terminate();
	mTransformBuffer.Terminate();
	mLightBuffer.Terminate();
	mMaterialBuffer.Terminate();
	for (size_t i = 0; i < std::size(mVertexShader); i++)
		mVertexShader[i].Terminate();
	for (size_t i = 0; i < std::size(mPixelShader); i++)
		mPixelShader[i].Terminate();
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
	SWAGE::Math::Matrix4 matView = mCamera.GetViewMatrix();
	SWAGE::Math::Matrix4 matProj = mCamera.GetProjectionMatrix();
	
	TransformData transformData;
	transformData.viewPosition = mCamera.GetPosition();
	mTransformBuffer.BindVS(0);
	mTransformBuffer.BindPS(0);

	mLightBuffer.Update(mDirectionalLight);
	mLightBuffer.BindVS(1);
	mLightBuffer.BindPS(1);

	mMaterialBuffer.Update(mMaterial);
	mMaterialBuffer.BindVS(2);
	mMaterialBuffer.BindPS(2);

	const float xoffsets[] = { -2.0f, 2.0f };
	for (size_t i = 0; i < std::size(xoffsets); i++)
	{
		SWAGE::Math::Matrix4 matWorld = SWAGE::Math::Matrix4::RotationX(mRoataion.x) * Matrix4::RotationY(mRoataion.y) * Matrix4::Translation(mPosition) * Matrix4::Translation({xoffsets[i], 0.0f, 0.0f});
		transformData.world = SWAGE::Math::Transpose(matWorld);
		transformData.wvp = SWAGE::Math::Transpose(matWorld * matView * matProj);
		mTransformBuffer.Update(transformData);

		mVertexShader[i].Bind();
		mPixelShader[i].Bind();
		mSphereBuffer.Render();
	}
}

void GameState::DebugUI()
{
	ImGui::Begin("Debug Info", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::Text("FPS: %f", mFPS);

	const char* themeItems[] = { "Classic", "Dark","Light" };
	static int themeItemIndex = 0;
	if (ImGui::Combo("UI Theme", &themeItemIndex, themeItems, IM_ARRAYSIZE(themeItems)))
	{
		if (themeItemIndex == 0)
		{
			DebugUI::SetTheme(DebugUI::Theme::Classic);
		}
		else if (themeItemIndex == 1)
		{
			DebugUI::SetTheme(DebugUI::Theme::Dark);
		}
		else
		{
			DebugUI::SetTheme(DebugUI::Theme::Light);

		}
	}

	ImGui::DragFloat3("Light Direction",&mDirectionalLight.direction.x);
	ImGui::ColorEdit3("Light Ambient",&mDirectionalLight.ambient.x);
	ImGui::ColorEdit3("Light Diffuse",&mDirectionalLight.diffuse.x);
	ImGui::ColorEdit3("Light Specular",&mDirectionalLight.specular.x);

	ImGui::ColorEdit3("Material Ambient",&mMaterial.ambient.x);
	ImGui::ColorEdit3("Material Diffuse",&mMaterial.diffuse.x);
	ImGui::ColorEdit3("Material Specular",&mMaterial.specular.x);
	ImGui::DragFloat("Material Power",&mMaterial.power);

	ImGui::DragFloat3("Rotation", (float*)&mRoataion, 0.01f);

	ImGui::End();
}

// Device interface - used for VRAM allocation/resource creation
// Context interface - used to issue draw commands
#include "GameState.h"

using namespace SWAGE::Graphics;
using namespace SWAGE::Input;
using namespace SWAGE::Math;

namespace 
{
	std::unique_ptr<Planet> sun = std::make_unique<Planet>();
	float sunSelfRoataionSpeed = 0.05f;
	float earthSelfRoataionSpeed = 0.6f;
	float mercurySelfRoataionSpeed = 0.2f;
	float venusSelfRoataionSpeed = 0.1f;
	float marsSelfRoataionSpeed = 0.4f;
	float jupiterSelfRoataionSpeed = 1.4f;
	float saturnSelfRoataionSpeed = 1.2f;
	float uranusSelfRoataionSpeed = 0.8f;
	float neptuneSelfRoataionSpeed = 1.0f;

	float earthRevolvingSpeed = 0.9f;
	float mercuryRevolvingSpeed = 1.4f;
	float venusRevolvingSpeed = 1.1f;
	float marsRevolvingSpeed = 0.7f;
	float jupiterRevolvingSpeed = 0.4f;
	float saturnRevolvingSpeed = 0.3f;
	float uranusRevolvingSpeed = 0.2f;
	float neptuneRevolvingSpeed = 0.1f;
}

void GameState::Initialize()
{

	mSkyBoxMesh = MeshBuilder::CreateSkybox(500.0f, true);
	mSkyBoxBuffer.Initialize(mSkyBoxMesh);

	std::unique_ptr<Planet> earth = std::make_unique<Planet>();

	sun->Initialize(10.0f, "../../Assets/Images/sun_texture.jpg", {0,0,0});
	sun->SetSelfRotationSpeed(sunSelfRoataionSpeed);
	sun->SetName("Sun");

	earth->Initialize(1.0f, "../../Assets/Images/Earth_Texture.jpg", {0,0,-25});
	earth->SetSelfRotationSpeed(earthSelfRoataionSpeed);
	earth->SetRevolvingSpeed(earthRevolvingSpeed);
	earth->SetName("Earth");

	std::unique_ptr<Planet> mercury = std::make_unique<Planet>();

	mercury->Initialize(0.5f, "../../Assets/Images/mercury_texture.jpg", { 0,0,-15 });
	mercury->SetSelfRotationSpeed(mercurySelfRoataionSpeed);
	mercury->SetRevolvingSpeed(mercuryRevolvingSpeed);
	mercury->SetName("Mercury");

	std::unique_ptr<Planet> venus = std::make_unique<Planet>();

	venus->Initialize(0.9f, "../../Assets/Images/venus_texture.jpg", { 0,0,-20 });
	venus->SetSelfRotationSpeed(venusSelfRoataionSpeed);
	venus->SetRevolvingSpeed(venusRevolvingSpeed);
	venus->SetName("Venus");

	std::unique_ptr<Planet> mars = std::make_unique<Planet>();

	mars->Initialize(0.7f, "../../Assets/Images/2k_mars.jpg", { 0,0,-30 });
	mars->SetSelfRotationSpeed(marsSelfRoataionSpeed);
	mars->SetRevolvingSpeed(marsRevolvingSpeed);
	mars->SetName("Mars");

	std::unique_ptr<Planet> jupiter = std::make_unique<Planet>();

	jupiter->Initialize(1.4f, "../../Assets/Images/2k_jupiter.jpg", { 0,0,-35 });
	jupiter->SetSelfRotationSpeed(jupiterSelfRoataionSpeed);
	jupiter->SetRevolvingSpeed(jupiterRevolvingSpeed);
	jupiter->SetName("Jupiter");

	std::unique_ptr<Planet> saturn = std::make_unique<Planet>();

	saturn->Initialize(1.2f, "../../Assets/Images/2k_saturn.jpg", { 0,0,-40 });
	saturn->SetSelfRotationSpeed(saturnSelfRoataionSpeed);
	saturn->SetRevolvingSpeed(saturnRevolvingSpeed);
	saturn->SetName("Saturn");

	std::unique_ptr<Planet> uranus = std::make_unique<Planet>();

	uranus->Initialize(0.8f, "../../Assets/Images/2k_uranus.jpg", { 0,0,-45 });
	uranus->SetSelfRotationSpeed(uranusSelfRoataionSpeed);
	uranus->SetRevolvingSpeed(uranusRevolvingSpeed);
	uranus->SetName("Uranus");

	std::unique_ptr<Planet> neptune = std::make_unique<Planet>();

	neptune->Initialize(0.8f, "../../Assets/Images/2k_neptune.jpg", { 0,0,-50 });
	neptune->SetSelfRotationSpeed(neptuneSelfRoataionSpeed);
	neptune->SetRevolvingSpeed(neptuneRevolvingSpeed);
	neptune->SetName("Neptune");

	std::unique_ptr<Planet> moon = std::make_unique<Planet>();

	//moon->Initialize(2.0f, "../../Assets/Images/2k_moon.jpg", { 0,0,-27 });
	//moon->SetSelfRotationSpeed(0.5);
	//moon->SetRevolvingSpeed(0.5);
	//moon->SetName("Moon");
	//planets.emplace_back(std::move(moon));

	planets.emplace_back(std::move(sun));
	planets.emplace_back(std::move(mercury));
	planets.emplace_back(std::move(venus));
	planets.emplace_back(std::move(earth));
	planets.emplace_back(std::move(mars));
	planets.emplace_back(std::move(jupiter));
	planets.emplace_back(std::move(saturn));
	planets.emplace_back(std::move(uranus));
	planets.emplace_back(std::move(neptune));

	mVertexShader.Initialize(L"../../Assets/Shaders/DoTexturing.fx", VertexPX::Format);
	mPixelShader.Initialize(L"../../Assets/Shaders/DoTexturing.fx");

	mSamplers[0].Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
	mSamplers[1].Initialize(Sampler::Filter::Anisotropic, Sampler::AddressMode::Wrap);
	mSamplers[2].Initialize(Sampler::Filter::Point, Sampler::AddressMode::Wrap);

	mSkyBoxTexture.Initialize("../../Assets/Images/Space.png");

	// Create constant buffer
	mConstantBuffer.Initialize();

	mPosition.z = 5.0f;
}

void GameState::Terminate()
{
	mSkyBoxBuffer.Terminate();
	mVertexShader.Terminate();
	mPixelShader.Terminate();
	mConstantBuffer.Terminate();
	for (size_t i = 0; i < std::size(mSamplers); i++)
	{
		mSamplers[i].Terminate();
	}
	mSkyBoxTexture.Terminate();
	for (size_t i = 0; i < planets.size(); i++)
	{
		planets[i]->Terminate();
	}
}

void GameState::Update(float deltaTime)
{
	for (size_t i = 0; i < planets.size(); i++)
	{
		planets[i]->Update(deltaTime);
	}

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
	// Download constant data to VRAM

	// Attach buffer to graphics pipeline
	mConstantBuffer.BindVS(0);
	mSamplers[1].BindPS(0);

	mVertexShader.Bind();
	mPixelShader.Bind();

	SWAGE::Math::Matrix4 matWorld = Matrix4::Translation(mCamera.GetPosition()) * Matrix4::RotationX(20);
	SWAGE::Math::Matrix4 matView = mCamera.GetViewMatrix();
	SWAGE::Math::Matrix4 matProj = mCamera.GetProjectionMatrix();

	TransformData transformData;
	transformData.wvp = SWAGE::Math::Transpose(matWorld * matView * matProj);
	mConstantBuffer.Update(transformData);

	mSkyBoxTexture.BindPS(0);
	mSkyBoxBuffer.Render();

	for (size_t i = 0; i < planets.size(); i++)
	{
		matWorld = planets[i]->GetMatWorld() * SWAGE::Math::Matrix4::Translation({0.0f,-20.0f,75.0f }) * SWAGE::Math::Matrix4::RotationX(-0.35f) * SWAGE::Math::Matrix4::RotationZ(0.15f);
		transformData.wvp = SWAGE::Math::Transpose(matWorld * matView * matProj);
		mConstantBuffer.Update(transformData);
		planets[i]->Render();
	}
}

void GameState::DebugUI()
{
	ImGui::Begin("Debug Info", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

	ImGui::Text("FPS: %f", mFPS);

	for (auto& planet : planets)
	{
		if (strcmp(planet->GetName().c_str(), "Sun") == 0)
		{
			ImGui::PushID("sun");
			if (ImGui::CollapsingHeader("Sun"))
			{
				//ImGui::slider
				if (ImGui::SliderFloat("Self rotation speed", &sunSelfRoataionSpeed, -5, 5))
					planet->SetSelfRotationSpeed(sunSelfRoataionSpeed);
			}
			ImGui::PopID();
		}

		if (strcmp(planet->GetName().c_str(), "Mercury") == 0)
		{
			ImGui::PushID("mercury");
			if (ImGui::CollapsingHeader("Mercury"))
			{
				if (ImGui::SliderFloat("Self rotation speed", &mercurySelfRoataionSpeed, -5, 5))
					planet->SetSelfRotationSpeed(mercurySelfRoataionSpeed);
				if (ImGui::SliderFloat("Revolving speed", &mercuryRevolvingSpeed, -5, 5))
					planet->SetRevolvingSpeed(mercuryRevolvingSpeed);
			}
			ImGui::PopID();
		}

		if (strcmp(planet->GetName().c_str(), "Venus") == 0)
		{
			ImGui::PushID("venus");
			if (ImGui::CollapsingHeader("Venus"))
			{
				if (ImGui::SliderFloat("Self rotation speed", &venusSelfRoataionSpeed, -5, 5))
					planet->SetSelfRotationSpeed(venusSelfRoataionSpeed);
				if (ImGui::SliderFloat("Revolving speed", &venusRevolvingSpeed, -5, 5))
					planet->SetRevolvingSpeed(venusRevolvingSpeed);
			}
			ImGui::PopID();
		}

		if (strcmp(planet->GetName().c_str(), "Earth") == 0)
		{
			ImGui::PushID("earth");
			if (ImGui::CollapsingHeader("Earth"))
			{
				if (ImGui::SliderFloat("Self rotation speed", &earthSelfRoataionSpeed, -5, 5))
					planet->SetSelfRotationSpeed(earthSelfRoataionSpeed);
				if (ImGui::SliderFloat("Revolving speed", &earthRevolvingSpeed, -5, 5))
					planet->SetRevolvingSpeed(earthRevolvingSpeed);
			}
			ImGui::PopID();
		}

		if (strcmp(planet->GetName().c_str(), "Mars") == 0)
		{
			ImGui::PushID("mars");
			if (ImGui::CollapsingHeader("Mars"))
			{
				if (ImGui::SliderFloat("Self rotation speed", &marsSelfRoataionSpeed, -5, 5))
					planet->SetSelfRotationSpeed(marsSelfRoataionSpeed);
				if (ImGui::SliderFloat("Revolving speed", &marsRevolvingSpeed, -5, 5))
					planet->SetRevolvingSpeed(marsRevolvingSpeed);
			}
			ImGui::PopID();
		}

		if (strcmp(planet->GetName().c_str(), "Jupiter") == 0)
		{
			ImGui::PushID("jupiter");
			if (ImGui::CollapsingHeader("Jupiter"))
			{
				if (ImGui::SliderFloat("Self rotation speed", &jupiterSelfRoataionSpeed, -5, 5))
					planet->SetSelfRotationSpeed(jupiterSelfRoataionSpeed);
				if (ImGui::SliderFloat("Revolving speed", &jupiterRevolvingSpeed, -5, 5))
					planet->SetRevolvingSpeed(jupiterRevolvingSpeed);
			}
			ImGui::PopID();
		}

		if (strcmp(planet->GetName().c_str(), "Saturn") == 0)
		{
			ImGui::PushID("saturn");
			if (ImGui::CollapsingHeader("Saturn"))
			{
				if (ImGui::SliderFloat("Self rotation speed", &saturnSelfRoataionSpeed, -5, 5))
					planet->SetSelfRotationSpeed(saturnSelfRoataionSpeed);
				if (ImGui::SliderFloat("Revolving speed", &saturnRevolvingSpeed, -5, 5))
					planet->SetRevolvingSpeed(saturnRevolvingSpeed);
			}
			ImGui::PopID();
		}

		if (strcmp(planet->GetName().c_str(), "Uranus") == 0)
		{
			ImGui::PushID("uranus");
			if (ImGui::CollapsingHeader("Uranus"))
			{
				if (ImGui::SliderFloat("Self rotation speed", &uranusSelfRoataionSpeed, -5, 5))
					planet->SetSelfRotationSpeed(uranusSelfRoataionSpeed);
				if (ImGui::SliderFloat("Revolving speed", &uranusRevolvingSpeed, -5, 5))
					planet->SetRevolvingSpeed(uranusRevolvingSpeed);
			}
			ImGui::PopID();
		}

		if (strcmp(planet->GetName().c_str(), "Neptune") == 0)
		{
			ImGui::PushID("neptune");
			if (ImGui::CollapsingHeader("Neptune"))
			{
				if (ImGui::SliderFloat("Self rotation speed", &neptuneSelfRoataionSpeed, -5, 5))
					planet->SetSelfRotationSpeed(neptuneSelfRoataionSpeed);
				if (ImGui::SliderFloat("Revolving speed", &neptuneRevolvingSpeed, -5, 5))
					planet->SetRevolvingSpeed(neptuneRevolvingSpeed);
			}
			ImGui::PopID();
		}
	}
	

	ImGui::End();
}

// Device interface - used for VRAM allocation/resource creation
// Context interface - used to issue draw commands
#include "GameState.h"

using namespace SWAGE;
using namespace SWAGE::Graphics;
using namespace SWAGE::Input;
using namespace SWAGE::Math;

void GameState::Initialize()
{
	mPosition.z = 5.0f;

	mGameWorld.AddService<RenderService>();
	mGameWorld.Initialize(1000);
	auto scott = mGameWorld.CreateGameObject("../../Assets/Templates/test.json", "Scott");

	GameObject* gameObject = mGameWorld.FindGameObject("Scott");
	if (gameObject)
	{
		auto animatorComponent = gameObject->GetComponent<AnimatorComponent>();
		animatorComponent->GetAnimator().Play();
		animatorComponent->GetAnimator().SetLooping(true);
		auto modelComponent = gameObject->GetComponent<ModelComponent>();
	}
}

void GameState::Terminate()
{
	mGameWorld.Terminate();
}

void GameState::Update(float deltaTime)
{
	if (SWAGE::Input::InputSystem::Get()->IsKeyDown(SWAGE::Input::KeyCode::LEFT))
		mRotation.y += deltaTime;
	if (SWAGE::Input::InputSystem::Get()->IsKeyDown(SWAGE::Input::KeyCode::RIGHT))
		mRotation.y -= deltaTime;

	if (SWAGE::Input::InputSystem::Get()->IsKeyDown(SWAGE::Input::KeyCode::UP))
		mRotation.x += deltaTime;
	if (SWAGE::Input::InputSystem::Get()->IsKeyDown(SWAGE::Input::KeyCode::DOWN))
		mRotation.x -= deltaTime;

	auto inputSystem = InputSystem::Get();
	if (inputSystem->IsKeyPressed(KeyCode::SPACE))
	{
		auto newObject = mGameWorld.CreateGameObject("../../Assets/Templates/test.json", std::to_string(mNextId++));
		newObject->GetComponent<TransformComponent>()->SetPosition({ mNextPositionX, 0.0f,0.0f });
		newObject->GetComponent<AnimatorComponent>()->GetAnimator().Play();
		mNextPositionX += 1.0f;

		if (mNextId >= 5)
		{
			auto kill = mGameWorld.FindGameObject(std::to_string(mNextId - 5));
			mGameWorld.Destroy(kill->GetHandle());
		}
	}

	mFPS = 1.0f / deltaTime;
	mGameWorld.Update(deltaTime);
}

void GameState::Render()
{
	mGameWorld.Render();
}

void GameState::DebugUI()
{
	ImGui::Begin("Debug Info", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	if (ImGui::CollapsingHeader("Transform"))
	{
		ImGui::DragFloat3("Rotation", (float*)&mRotation, 0.01f);
	}
	ImGui::Text("FPS: %f", mFPS);
	ImGui::End();
	mGameWorld.DebugUI();
}

// Device interface - used for VRAM allocation/resource creation
// Context interface - used to issue draw commands
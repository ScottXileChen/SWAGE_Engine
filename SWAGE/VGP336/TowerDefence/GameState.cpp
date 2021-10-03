#include "GameState.h"

using namespace SWAGE;
using namespace SWAGE::Graphics;
using namespace SWAGE::Input;
using namespace SWAGE::Math;

void GameState::Initialize()
{
	mPosition.z = 5.0f;

	mGameWorld.AddService<RenderService>();
	mGameWorld.AddService<EnemyService>();
	mGameWorld.Initialize(1000);
	auto tower = mGameWorld.CreateGameObject("../../Assets/Templates/Tower.json", "Tower");
	auto test = mGameWorld.CreateGameObject("../../Assets/Templates/modelError.json", "Error");
	auto spawner1 = mGameWorld.CreateGameObject("../../Assets/Templates/MinionSpawner.json", "Spawner");
	auto Weaponspawner1 = mGameWorld.CreateGameObject("../../Assets/Templates/WeaponSpawner.json", "WeaponSpawner");
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

	mFPS = 1.0f / deltaTime;
	mGameWorld.Update(deltaTime);

	auto gameObject = mGameWorld.FindGameObject("Weapon0");
	if (gameObject)
	{
		auto tower = mGameWorld.FindGameObject("Tower");
		if (tower)
		{
			auto target = mGameWorld.GetService<EnemyService>()->GetCloestEnemy(tower->GetComponent<TransformComponent>()->GetPosition());
			if (target)
			{
				auto targetPos = target->GetOwner().GetComponent<TransformComponent>();
				gameObject->GetComponent<WeaponComponent>()->SetTarget(targetPos);
			}
		}
	}
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

	auto gameObject = mGameWorld.FindGameObject("Tower");
	if (gameObject)
	{
		gameObject->DebugUI();
	}

	auto gameObject2 = mGameWorld.FindGameObject("Weapon5");
	if (gameObject2)
	{
		gameObject2->DebugUI();
	}
}

// Device interface - used for VRAM allocation/resource creation
// Context interface - used to issue draw commands




// Spawner
// + Transform Component
// + Spawner Component

// Tower
// + Transform Component
// + Targeting Component > finds target
// + Weapon Component > spwan projectiles and assign target

// Projectile
// + Transform Component
// + Projectile Component > move to target
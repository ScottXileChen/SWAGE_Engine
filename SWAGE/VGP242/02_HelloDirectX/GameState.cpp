#include "GameState.h"

using namespace SWAGE::Graphics;
using namespace SWAGE::Input;

void GameState::Initialize()
{
	auto graphicsSystem = GraphicsSystem::Get();
	graphicsSystem->SetClearColor(SWAGE::Graphics::Colors::White);
}

void GameState::Update(float deltaTime)
{
	auto inputSystem = InputSystem::Get();
	auto graphicsSystem = GraphicsSystem::Get();

	// This should go somewhere else ...
	if (inputSystem->IsKeyPressed(KeyCode::ONE))
		graphicsSystem->SetClearColor(Colors::White);
	if (inputSystem->IsKeyPressed(KeyCode::TWO))
		graphicsSystem->SetClearColor(Colors::LightBlue);
	if (inputSystem->IsKeyPressed(KeyCode::THREE))
		graphicsSystem->SetClearColor(Colors::LightGreen);
}
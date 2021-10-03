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

	mTexture = SWAGE::Utils::GUIUtil::LoadTexture("../../Assets//Images/WaterTurtle.png");

	mPosition = Vector2(GraphicsSystem::Get()->GetBackBufferWidth() * 0.5f, GraphicsSystem::Get()->GetBackBufferHeight()* 0.5f);

}

void GameState::Terminate()
{
}

void GameState::GUI(float deltaTime)
{
	mFPS = 1.0f / deltaTime;

	auto inputSystem = InputSystem::Get();

	const float moveSpeed = 1000.0f;
	const float turnSpeed = 6.0f * Constants::DegToRad;
	if (inputSystem->IsKeyDown(KeyCode::W))
		mPosition.y -= moveSpeed * deltaTime;
	if (inputSystem->IsKeyDown(KeyCode::S))
		mPosition.y += moveSpeed * deltaTime;
	if (inputSystem->IsKeyDown(KeyCode::D))
		mPosition.x += moveSpeed * deltaTime;
	if (inputSystem->IsKeyDown(KeyCode::A))
		mPosition.x -= moveSpeed * deltaTime;

	SWAGE::Utils::GUIUtil::DrawSprite(mTexture, mPosition);
	SWAGE::Utils::GUIUtil::DrawScreenText("Hello Font", 200.0f, 200.0f, 32, Colors::White);
}


#pragma once

#include <SWAGE/Inc/SWAGE.h>

class GameState : public SWAGE::AppState
{
public:
	void Initialize() override;
	void Terminate() override;

	void Update(float deltaTime) override;
	void Render() override;
	void DebugUI() override;

private:
	SWAGE::Math::Vector3 mPosition;
	SWAGE::Math::Vector3 mRotation;

	float mFPS = 0.0f;

	SWAGE::GameWorld mGameWorld;
	SWAGE::GameObjectHandle mGameObjectHandle;

	int mNextId = 0;
	float mNextPositionX = 0.0f;
};
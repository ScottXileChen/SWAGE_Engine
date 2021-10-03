#pragma once

#include <SWAGE/Inc/SWAGE.h>

class GameState : public SWAGE::AppState
{
public:
	void Initialize() override;
	void Terminate() override;

	void GUI(float deltaTime) override;

private:
	SWAGE::Graphics::TextureId mTexture;

	SWAGE::Math::Vector2 mPosition;
	float mFPS = 0.0f;
};
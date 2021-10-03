#pragma once

#include <SWAGE/Inc/SWAGE.h>

class Background
{
public:
	void Load();

	void Update(float deltaTime);
	void Render();

private:
	SWAGE::Graphics::TextureId mTextureId;
	SWAGE::Math::Vector2 mPosition;
	SWAGE::Math::Vector2 mOffset;
};
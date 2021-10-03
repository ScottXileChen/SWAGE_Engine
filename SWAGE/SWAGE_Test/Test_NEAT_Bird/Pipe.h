#pragma once

#include <SWAGE/Inc/SWAGE.h>

class Pipe
{
public:
	void Load();

	void Update(float deltaTime);
	void Render();

	void Spawn(float gapSize);

	SWAGE::Math::Shapes::Rect GetTopRect() const;
	SWAGE::Math::Shapes::Rect GetBottomRect() const;

private:
	SWAGE::Graphics::TextureId mTextureId;
	SWAGE::Math::Vector2 mPosition;
	SWAGE::Math::Vector2 mVelocity;
	float mGapSize;
};
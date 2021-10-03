#include "Background.h"

void Background::Load()
{
	mTextureId = SWAGE::Utils::GUIUtil::LoadTexture("../../Assets//Images/FlappyBird/background.png");
	mOffset.x = (float)SWAGE::Utils::GUIUtil::GetSpriteWidth(mTextureId);
}

void Background::Update(float deltaTime)
{
	auto velocity = SWAGE::Math::Vector2{ -100.0f, 0.0f };
	mPosition += velocity * deltaTime;
	if (mPosition.x <= -mOffset.x)
		mPosition.x += mOffset.x;
}

void Background::Render()
{
	SWAGE::Utils::GUIUtil::DrawSprite(mTextureId, mPosition, 0.0f, SWAGE::Graphics::Pivot::TopLeft);
	SWAGE::Utils::GUIUtil::DrawSprite(mTextureId, mPosition + mOffset, 0.0f, SWAGE::Graphics::Pivot::TopLeft);
}
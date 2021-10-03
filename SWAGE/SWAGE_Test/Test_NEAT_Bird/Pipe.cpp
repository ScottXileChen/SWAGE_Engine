#include "Pipe.h"

void Pipe::Load()
{
	mTextureId = SWAGE::Utils::GUIUtil::LoadTexture("../../Assets//Images/FlappyBird/pipe.png");
}

void Pipe::Update(float deltaTime)
{
	mPosition += mVelocity * deltaTime;
}

void Pipe::Render()
{
	auto topRect = GetTopRect();
	auto bottomRect = GetBottomRect();

	SWAGE::Utils::GUIUtil::DrawSprite(mTextureId, { topRect.left, topRect.bottom }, 0.0f,SWAGE::Graphics::Pivot::BottomLeft, SWAGE::Graphics::Flip::Vertical);
	SWAGE::Utils::GUIUtil::DrawSprite(mTextureId, { bottomRect.left, bottomRect.top }, 0.0f, SWAGE::Graphics::Pivot::TopLeft);
}

void Pipe::Spawn(float gapSize)
{
	mGapSize = gapSize;
	mVelocity = SWAGE::Math::Vector2{ -100.0f, 0.0f };
	mPosition.x = (float)SWAGE::Graphics::GraphicsSystem().Get()->GetBackBufferWidth();
	mPosition.y = SWAGE::Math::RandomFloat(gapSize, SWAGE::Graphics::GraphicsSystem().Get()->GetBackBufferHeight() - gapSize);
}

SWAGE::Math::Shapes::Rect Pipe::GetTopRect() const
{
	return {
		mPosition.x,
		-FLT_MAX,
		mPosition.x + mGapSize,
		mPosition.y - mGapSize,
	};
}

SWAGE::Math::Shapes::Rect Pipe::GetBottomRect() const
{
	return {
		mPosition.x,
		mPosition.y + mGapSize,
		mPosition.x + mGapSize,
		FLT_MAX,
	};
}
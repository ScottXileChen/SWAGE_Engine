#pragma once

namespace SWAGE::Utils::GUIUtil
{
	SWAGE::Graphics::TextureId LoadTexture(const char* filePath);
	void DrawSprite(SWAGE::Graphics::TextureId textureId, const SWAGE::Math::Vector2& position, float rotation = 0.0f, SWAGE::Graphics::Pivot pivot = SWAGE::Graphics::Pivot::Center, SWAGE::Graphics::Flip flip = SWAGE::Graphics::Flip::None);
	void DrawSprite(SWAGE::Graphics::TextureId textureId, const SWAGE::Math::Shapes::Rect& sourceRect, const SWAGE::Math::Vector2& position, float rotation = 0.0f, SWAGE::Graphics::Pivot pivot = SWAGE::Graphics::Pivot::Center, SWAGE::Graphics::Flip flip = SWAGE::Graphics::Flip::None);
	uint32_t GetSpriteWidth(SWAGE::Graphics::TextureId textureId);
	uint32_t GetSpriteHeight(SWAGE::Graphics::TextureId textureId);
	void DrawScreenText(const char* str, float x, float y, float size, const SWAGE::Graphics::Color& color);
}
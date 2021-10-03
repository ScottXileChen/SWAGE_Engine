#include "Precompiled.h"
#include "GUIUtil.h"

using namespace SWAGE::Graphics;
using namespace SWAGE::Math;
using namespace SWAGE::Math::Shapes;

TextureId SWAGE::Utils::GUIUtil::LoadTexture(const char* filePath)
{
	return TextureManager::Get()->Load(filePath);
}

void  SWAGE::Utils::GUIUtil::DrawSprite(TextureId textureId, const Vector2& position, float rotation, Pivot pivot, Flip flip)
{
	SpriteRenderer::Get()->Draw(*TextureManager::Get()->GetTexture(textureId), position, rotation, pivot, flip);
}

void SWAGE::Utils::GUIUtil::DrawSprite(TextureId textureId, const Rect& sourceRect, const Vector2& position, float rotation, Pivot pivot, Flip flip)
{
	SpriteRenderer::Get()->Draw(*TextureManager::Get()->GetTexture(textureId), sourceRect, position, rotation, pivot, flip);
}

uint32_t SWAGE::Utils::GUIUtil::GetSpriteWidth(TextureId textureId)
{
	Texture* texture = TextureManager::Get()->GetTexture(textureId);
	return texture ? texture->GetWidth() : 0u;
}

uint32_t SWAGE::Utils::GUIUtil::GetSpriteHeight(TextureId textureId)
{
	Texture* texture = TextureManager::Get()->GetTexture(textureId);
	return texture ? texture->GetHeight() : 0u;
}

void SWAGE::Utils::GUIUtil::DrawScreenText(const char* str, float x, float y, float size, const Color& color)
{
	FontManager::Get()->AddText(str, size, x, y, color);
}
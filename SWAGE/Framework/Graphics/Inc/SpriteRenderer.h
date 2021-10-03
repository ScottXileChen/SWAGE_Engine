#pragma once

#include "Math/Inc/EngineMath.h"

namespace DirectX { class CommonStates; class SpriteBatch; }

namespace SWAGE::Graphics
{
	class Texture;

	enum class Pivot
	{
		TopLeft,
		Top,
		TopRight,
		Left,
		Center,
		Right,
		BottomLeft,
		Bottom,
		BottomRight
	};

	enum class Flip
	{
		None,
		Horizontal,
		Vertical,
		Both
	};

	class SpriteRenderer
	{
	public:
		static void StaticInitialize();
		static void StaticTerminate();
		static SpriteRenderer* Get();

	public:
		SpriteRenderer();
		~SpriteRenderer();

		SpriteRenderer(const SpriteRenderer&) = delete;
		SpriteRenderer& operator=(const SpriteRenderer&) = delete;

		void Initialize();
		void Terminate();

		void SetTransform(const Math::Matrix4& transform);

		void BeginRender();
		void EndRender();

		void Draw(const Texture& texture, const Math::Vector2& pos, float rotation = 0.0f, Pivot pivot = Pivot::Center, Flip flip = Flip::None);
		void Draw(const Texture& texture, const Math::Shapes::Rect& sourceRect, const Math::Vector2& pos, float rotation = 0.0f, Pivot pivot = Pivot::Center, Flip flip = Flip::None);

	private:
		friend class Font;

		DirectX::CommonStates* mCommonStates;
		DirectX::SpriteBatch* mSpriteBatch;

		Math::Matrix4 mTransform;
	};
}
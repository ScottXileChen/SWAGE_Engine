#pragma once

#include "Colors.h"

interface IFW1Factory;
interface IFW1FontWrapper;

namespace SWAGE::Graphics
{
	class Font
	{
	public:
		Font();
		~Font();

		void Initialize();
		void Terminate();

		float GetStringWidth(const wchar_t* str, float size) const;
		void Draw(const wchar_t* str, float x, float y, float size, const Color& color);

	private:
		inline uint32_t ToColor(const Color& color)
		{
			uint8_t r = (uint8_t)(color.r * 255);
			uint8_t g = (uint8_t)(color.g * 255);
			uint8_t b = (uint8_t)(color.b * 255);
			return 0xff000000 | (b << 16) | (g << 8) | r;
		}

	private:
		IFW1Factory* mFW1Factory;
		IFW1FontWrapper* mFontWrapper;
	};

}

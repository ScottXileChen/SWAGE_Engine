#pragma once

#include "Colors.h"

namespace SWAGE::Graphics
{
	struct Material
	{
		Color ambient;
		Color diffuse;
		Color specular;
		float power;
		float padding[3];
	};
}
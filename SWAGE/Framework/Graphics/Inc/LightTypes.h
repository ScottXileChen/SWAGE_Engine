#pragma once

#include "Colors.h"

namespace SWAGE::Graphics
{
	struct DirectionalLight
	{
		Math::Vector3 direction;
		float padding;
		Color ambient;
		Color diffuse;
		Color specular;
	};
}
#pragma once

#include "Common.h"

namespace SWAGE::Graphics
{
	template <class T>
	struct Keyframe
	{
		T key;
		float time = 0.0f;
	};

	template <class T>
	using Keyframes = std::vector<Keyframe<T>>;

	using PositionKeys = Keyframes<SWAGE::Math::Vector3>;
	using RotationKeys = Keyframes<SWAGE::Math::Quaternion>;
	using ScaleKeys = Keyframes<SWAGE::Math::Vector3>;
}
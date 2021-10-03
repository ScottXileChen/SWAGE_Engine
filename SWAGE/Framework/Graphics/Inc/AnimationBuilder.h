#pragma once

#include "Animation.h"

namespace SWAGE::Graphics
{
	class AnimationBuilder
	{
	public:
		AnimationBuilder& SetTime(float time);
		AnimationBuilder& AdvanceTime(float time);

		AnimationBuilder& AddPositionKey(const SWAGE::Math::Vector3& position);
		AnimationBuilder& AddPositionKey(const SWAGE::Math::Vector3& position, float time);
		AnimationBuilder& AddRotationKey(const SWAGE::Math::Quaternion& rotation);
		AnimationBuilder& AddRotationKey(const SWAGE::Math::Quaternion& rotation, float time);
		AnimationBuilder& AddScaleKey(const SWAGE::Math::Vector3& scale);
		AnimationBuilder& AddScaleKey(const SWAGE::Math::Vector3& scale, float time);

		AnimationBuilder& SetLooping(bool looping);

		Animation Get();

	private:
		Animation mTemp;
		float mTime = 0.0f;
	};
}
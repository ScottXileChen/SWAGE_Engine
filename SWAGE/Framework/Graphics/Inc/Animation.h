#pragma once

#include "Keyframe.h"

namespace SWAGE::Graphics
{
	class Animation
	{
	public:
		SWAGE::Math::Vector3 GetPosition(float time) const;
		SWAGE::Math::Quaternion GetRotation(float time) const;
		SWAGE::Math::Vector3 GetScale(float time) const;

		bool IsPositionKeyEmpty() const { return mPositionKeys.empty(); }
		bool IsRotationKeyEmpty() const { return mRotationKeys.empty(); }
		bool IsScaleKeyEmpty() const { return mScaleKeys.empty(); }

		void SetLooping(bool looping) { mLooping = looping; }

	private:
		friend class AnimationBuilder;
		friend class AnimationIO;

		PositionKeys mPositionKeys;
		RotationKeys mRotationKeys;
		ScaleKeys mScaleKeys;
		float mStartTime = 0.0f;
		float mEndTime = 0.0f;
		float mTotalDuration = 0.0f;
		bool mLooping = false;
	};
}
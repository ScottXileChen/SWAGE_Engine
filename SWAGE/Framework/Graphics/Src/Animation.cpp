#include "Precompiled.h"
#include "Animation.h"

using namespace SWAGE::Graphics;
using namespace SWAGE::Math;

Vector3 Animation::GetPosition(float time) const
{
	ASSERT(!mPositionKeys.empty(), "Position keys are emtpy!");

	if (mLooping && time > mPositionKeys.back().time)
		time -= static_cast<int>(time / mTotalDuration) * mTotalDuration;

	if (mPositionKeys.front().time > time)
		return mPositionKeys.front().key;

	if (mPositionKeys.back().time > time)
	{
		for (size_t i = 0; i < mPositionKeys.size(); ++i)
		{
			if (mPositionKeys[i].time > time)
			{
				size_t frameIndex2 = i;
				size_t frameIndex1 = i - 1;
				float duration = mPositionKeys[frameIndex2].time - mPositionKeys[frameIndex1].time;
				float t = (time - mPositionKeys[frameIndex1].time) / duration;
				return Lerp(mPositionKeys[frameIndex1].key, mPositionKeys[frameIndex2].key, t);
			}
		}
	}

	return mPositionKeys.back().key;
}

Quaternion Animation::GetRotation(float time) const
{
	ASSERT(!mRotationKeys.empty(), "Rotation keys are emtpy!");

	if (mLooping && time > mRotationKeys.back().time)
		time -= static_cast<int>(time / mTotalDuration) * mTotalDuration;

	if (mRotationKeys.front().time > time)
		return mRotationKeys.front().key;

	if (mRotationKeys.back().time > time)
	{
		for (size_t i = 0; i < mRotationKeys.size(); ++i)
		{
			if (mRotationKeys[i].time > time)
			{
				size_t frameIndex2 = i;
				size_t frameIndex1 = i - 1;
				float duration = mRotationKeys[frameIndex2].time - mRotationKeys[frameIndex1].time;
				float t = (time - mRotationKeys[frameIndex1].time) / duration;
				return Lerp(mRotationKeys[frameIndex1].key, mRotationKeys[frameIndex2].key, t);
			}
		}
	}

	return mRotationKeys.back().key;
}

Vector3 Animation::GetScale(float time) const
{
	ASSERT(!mScaleKeys.empty(), "Scale keys are emtpy!");

	if (mLooping && time > mScaleKeys.back().time)
		time -= static_cast<int>(time / mTotalDuration) * mTotalDuration;

	if (mScaleKeys.front().time > time)
		return mScaleKeys.front().key;

	if (mScaleKeys.back().time > time)
	{
		for (size_t i = 0; i < mScaleKeys.size(); ++i)
		{
			if (mScaleKeys[i].time > time)
			{
				size_t frameIndex2 = i;
				size_t frameIndex1 = i - 1;
				float duration = mScaleKeys[frameIndex2].time - mScaleKeys[frameIndex1].time;
				float t = (time - mScaleKeys[frameIndex1].time) / duration;
				return Lerp(mScaleKeys[frameIndex1].key, mScaleKeys[frameIndex2].key, t);
			}
		}
	}

	return mScaleKeys.back().key;
}

#include "Precompiled.h"
#include "AnimationBuilder.h"

using namespace SWAGE::Graphics;
using namespace SWAGE::Math;

AnimationBuilder & AnimationBuilder::SetTime(float time)
{
	mTemp.mStartTime = time;
	mTime = time;
	return *this;
}

AnimationBuilder & AnimationBuilder::AdvanceTime(float time)
{
	mTime += time;
	return *this;
}

AnimationBuilder & AnimationBuilder::AddPositionKey(const Vector3 & position)
{
	ASSERT(mTemp.mPositionKeys.empty() || mTemp.mPositionKeys.back().time < mTime, "PositionKey time is wrong!");
	mTemp.mPositionKeys.push_back({ position, mTime });
	return *this;
}

AnimationBuilder & AnimationBuilder::AddPositionKey(const SWAGE::Math::Vector3 & position, float time)
{
	ASSERT(mTemp.mPositionKeys.empty() || mTemp.mPositionKeys.back().time < time, "PositionKey time is wrong!");
	mTemp.mPositionKeys.push_back({ position, time });
	mTime = time;
	return *this;
}

AnimationBuilder & AnimationBuilder::AddRotationKey(const Quaternion & rotation)
{
	ASSERT(mTemp.mRotationKeys.empty() || mTemp.mRotationKeys.back().time < mTime, "RotationKeys time is wrong!");
	mTemp.mRotationKeys.push_back({ rotation, mTime });
	return *this;
}

AnimationBuilder & AnimationBuilder::AddRotationKey(const SWAGE::Math::Quaternion & rotation, float time)
{
	ASSERT(mTemp.mRotationKeys.empty() || mTemp.mRotationKeys.back().time < time, "RotationKeys time is wrong!");
	mTemp.mRotationKeys.push_back({ rotation, time });
	mTime = time;
	return *this;
}

AnimationBuilder & AnimationBuilder::AddScaleKey(const Vector3 & scale)
{
	ASSERT(mTemp.mScaleKeys.empty() || mTemp.mScaleKeys.back().time < mTime, "ScaleKeys time is wrong!");
	mTemp.mScaleKeys.push_back({ scale, mTime });
	return *this;
}

AnimationBuilder & AnimationBuilder::AddScaleKey(const SWAGE::Math::Vector3 & scale, float time)
{
	ASSERT(mTemp.mScaleKeys.empty() || mTemp.mScaleKeys.back().time < time, "ScaleKeys time is wrong!");
	mTemp.mScaleKeys.push_back({ scale, time });
	mTime = time;
	return *this;
}

AnimationBuilder & AnimationBuilder::SetLooping(bool looping)
{
	mTemp.mLooping = looping;
	return *this;
}

Animation AnimationBuilder::Get()
{
	mTemp.mEndTime = mTime;
	mTemp.mTotalDuration = mTemp.mEndTime - mTemp.mStartTime;
	mTime = 0.0f;
	return std::move(mTemp);
}

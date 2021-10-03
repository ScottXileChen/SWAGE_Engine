#include "Precompiled.h"
#include "WayPointPathComponent.h"

#include "GameObject.h"
#include "GameWorld.h"
#include "TransformComponent.h"

using namespace SWAGE;
using namespace SWAGE::Math;

MEMPOOL_DEFINE(WayPointPathComponent, 1000)

void WayPointPathComponent::Initialize()
{
	mTransformComponent = GetOwner().GetComponent<TransformComponent>();
	mLastDistance = FLT_MAX;
	mTempIndex = 0;
}

void WayPointPathComponent::Update(float deltaTime)
{
	Vector3 currentPos = mTransformComponent->GetPosition();
	float distance = Distance(mWayPointPath[mTempIndex], currentPos);

	if (distance > mLastDistance)
	{
		mTempIndex = (mTempIndex + 1) % mWayPointPath.size();
		mLastDistance = FLT_MAX;
	}
	else
	{
		mLastDistance = distance;
	}

	if (distance <= 0.001f)
	{
		mTempIndex = (mTempIndex + 1) % mWayPointPath.size();
		mLastDistance = FLT_MAX;
	}
}

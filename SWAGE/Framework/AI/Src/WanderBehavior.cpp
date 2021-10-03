#include "Precompiled.h"
#include "WanderBehavior.h"

#include "Agent.h"

using namespace SWAGE::AI;
using namespace SWAGE::AI::Steering;
using namespace SWAGE::AI::Steering::Wander;

SWAGE::Math::Vector2 WanderBehavior::Calculate(Agent & agent)
{
	SWAGE::Math::Vector2 randomForce = SWAGE::Math::RandomUnitCircle(false) * mWanderJitter;
	mLocalWanderTarget += randomForce;
	mLocalWanderTarget = SWAGE::Math::Normalize(mLocalWanderTarget) * mWanderRadius;
	SWAGE::Math::Vector2 projectedTarget = mLocalWanderTarget + SWAGE::Math::Vector2(0, mWanderDistance);
	SWAGE::Math::Vector2 worldWanderTarget = SWAGE::Math::TransformCoord(projectedTarget, agent.LocalToWorld());

	//if (ShowDebug())
	//{
	//	SWAGE::Math::Vector2 circleCenter = X::Math::TransformCoord(X::Math::Vector2(0, mWanderDistance), agent.LocalToWorld());
	//	SWAGE::DrawScreenCircle(circleCenter, mWanderRadius, X::Colors::Red);
	//	SWAGE::DrawScreenLine(agent.position, circleCenter, X::Colors::Cyan);
	//	SWAGE::DrawScreenLine(agent.position, worldWanderTarget, X::Colors::Yellow);
	//	SWAGE::DrawScreenCircle(worldWanderTarget, 5.0f, X::Colors::White);
	//}

	// Seek behavior
	auto toTarget = worldWanderTarget - agent.position;
	auto desiredVelocity = SWAGE::Math::Normalize(toTarget) * agent.maxSpeed;

	return desiredVelocity - agent.velocity;
}

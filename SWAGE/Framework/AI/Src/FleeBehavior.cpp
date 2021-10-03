#include "Precompiled.h"
#include "FleeBehavior.h"

#include "Agent.h"

using namespace SWAGE::AI;
using namespace SWAGE::AI::Steering;
using namespace SWAGE::AI::Steering::Flee;

SWAGE::Math::Vector2 FleeBehavior::Calculate(Agent & agent)
{
	const float distance = SWAGE::Math::DistanceSqr(agent.position, agent.destination);

	if (ShowDebug())
	{
		//SWAGE::DrawScreenCircle(agent.position, mPanicDistance, X::Colors::Yellow);
	}

	if (distance >= SWAGE::Math::Sqr(mPanicDistance))
		return SWAGE::Math::Vector2(0.0f, 0.0f);

	auto fleeTarget = agent.position - agent.destination;
	auto desiredVelocity = SWAGE::Math::Normalize(fleeTarget) * agent.maxSpeed;

	return desiredVelocity - agent.velocity;
}

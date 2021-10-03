#include "Precompiled.h"
#include "CohesionBehavior.h"

#include "Agent.h"

using namespace SWAGE::AI;
using namespace SWAGE::AI::Steering;
using namespace SWAGE::AI::Steering::GroupBehaviors;

SWAGE::Math::Vector2 CohesionBehavior::Calculate(Agent & agent)
{
	SWAGE::Math::Vector2 positionAverage;

	for (auto& neighbor : agent.neighbors)
	{
		auto neighborToAgent = agent.position - neighbor->position;
		auto lengthSqr = SWAGE::Math::MagnitudeSqr(neighborToAgent);

		if (lengthSqr <= 0.0f)
			continue;

		positionAverage += neighbor->position;
	}

	if (ShowDebug())
	{
	}

	if (agent.neighbors.size() > 1)
	{
		positionAverage /= static_cast<float>(agent.neighbors.size()) - 1;
		auto toTarget = positionAverage - agent.position;
		auto desiredVelocity = SWAGE::Math::Normalize(toTarget) * agent.maxSpeed;

		return desiredVelocity - agent.velocity;
	}
	else
		return SWAGE::Math::Vector2(0.0f, 0.0f);
}
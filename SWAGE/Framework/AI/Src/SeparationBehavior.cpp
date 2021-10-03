#include "Precompiled.h"
#include "SeparationBehavior.h"

#include "Agent.h"

using namespace SWAGE::AI;
using namespace SWAGE::AI::Steering;
using namespace SWAGE::AI::Steering::GroupBehaviors;

SWAGE::Math::Vector2 SeparationBehavior::Calculate(Agent & agent)
{
	SWAGE::Math::Vector2 separation;
	for (auto& neighbor : agent.neighbors)
	{
		auto neighborToAgent = agent.position - neighbor->position;
		auto lengthSqr = SWAGE::Math::MagnitudeSqr(neighborToAgent);

		if (lengthSqr <= 0.0f)
			continue;

		separation += neighborToAgent / lengthSqr;
	}

	if (ShowDebug())
	{
	}

	return separation;
}
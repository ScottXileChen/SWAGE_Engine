#include "Precompiled.h"
#include "AlignmentBehavior.h"

#include "Agent.h"

using namespace SWAGE::AI;
using namespace SWAGE::AI::Steering;
using namespace SWAGE::AI::Steering::GroupBehaviors;

SWAGE::Math::Vector2 AlignmentBehavior::Calculate(Agent & agent)
{
	SWAGE::Math::Vector2 headingAverage;

	for (auto& neighbor : agent.neighbors)
	{
		auto neighborToAgent = agent.position - neighbor->position;
		auto lengthSqr = SWAGE::Math::MagnitudeSqr(neighborToAgent);

		if (lengthSqr <= 0.0f)
			continue;

		headingAverage += neighbor->heading;
	}

	if (agent.neighbors.size() > 1)
		headingAverage /= static_cast<float>(agent.neighbors.size()) - 1;
	else
		headingAverage = agent.heading;

	if (ShowDebug())
	{
	}

	return headingAverage - agent.heading;
}
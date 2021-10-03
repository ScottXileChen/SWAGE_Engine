#include "Precompiled.h"
#include "ArriveBehavior.h"

#include "Agent.h"

using namespace SWAGE::AI;
using namespace SWAGE::AI::Steering;
using namespace SWAGE::AI::Steering::Arrive;

SWAGE::Math::Vector2 ArriveBehavior::Calculate(Agent & agent)
{
	auto toTarget = agent.destination - agent.position;
	const float distance = SWAGE::Math::Magnitude(toTarget);

	if (distance > 0)
	{
		//const float decelTweaker = 0.3f;
		//float speed = distance / ((float)decel * decelTweaker);
		float speed = distance / ((float)decel);

		speed = SWAGE::Math::Min(speed, agent.maxSpeed);
		auto desiredVelocity = toTarget * speed / distance;

		if (ShowDebug())
		{
			std::string decelString = DecelerationToString(decel);
			std::string result = "Deceleration: " + decelString;
			//SWAGE::DrawScreenText(result.c_str(), agent.position + desiredVelocity, 20.0f, X::Colors::Yellow);
		}

		return desiredVelocity - agent.velocity;
	}
	
	return SWAGE::Math::Vector2(0.0f, 0.0f);
}
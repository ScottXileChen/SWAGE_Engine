#include "Precompiled.h"
#include "SeekBehavior.h"

#include "Agent.h"

using namespace SWAGE::AI;
using namespace SWAGE::AI::Steering;
using namespace SWAGE::AI::Steering::Seek;

SWAGE::Math::Vector2 SeekBehavior::Calculate(Agent & agent)
{
	auto toTarget = agent.destination - agent.position;
	auto desiredVelocity = SWAGE::Math::Normalize(toTarget) * agent.maxSpeed;
	auto seekForce = desiredVelocity - agent.velocity;

	//if (ShowDebug())
	//{
	//	SWAGE::DrawScreenLine(agent.position, agent.position + desiredVelocity, SWAGE::Colors::Yellow);
	//	SWAGE::DrawScreenText("Desired", agent.position + desiredVelocity, 20.0f, SWAGE::Colors::Yellow);

	//	SWAGE::DrawScreenLine(agent.position, agent.position + agent.velocity, X::Colors::Green);
	//	SWAGE::DrawScreenText("Current", agent.position + agent.velocity, 20.0f, X::Colors::Green);

	//	SWAGE::DrawScreenLine(agent.position + agent.velocity, agent.position + agent.velocity + seekForce, X::Colors::Red);
	//}

	return desiredVelocity - agent.velocity;
}
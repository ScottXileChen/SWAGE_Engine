#include "Precompiled.h"
#include "SteeringModule.h"

using namespace SWAGE::AI;
using namespace SWAGE::AI::Steering;

SteeringModule::SteeringModule(Agent& agent)
	: mAgent(agent)
{}

SWAGE::Math::Vector2 SteeringModule::Calculate()
{
	SWAGE::Math::Vector2 totalForce;
	for (auto& behavior : mBehaviors)
	{
		if (behavior->IsActive())
		{
			totalForce += behavior->Calculate(mAgent) * behavior->GetWeight();
		}
	}

	return totalForce;
}
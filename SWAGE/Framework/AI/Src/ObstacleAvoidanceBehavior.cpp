#include "Precompiled.h"
#include "ObstacleAvoidanceBehavior.h"

#include "Agent.h"
#include "AIWorld.h"

using namespace SWAGE::AI;
using namespace SWAGE::AI::Steering;
using namespace SWAGE::AI::Steering::ObstacleAvoidance;

SWAGE::Math::Vector2 ObstacleAvoidanceBehavior::Calculate(Agent & agent)
{
	AI::AIWorld::Obstacles worldObstacles = agent.world.GetObstacles();

	float avoidanceDistance = mDetectionLength + (SWAGE::Math::Magnitude(agent.velocity / agent.maxSpeed) * 100.0f);

	AI::AIWorld::Obstacles localExpandedObstacles;

	SWAGE::Math::Matrix3 toWorld = agent.LocalToWorld();
	SWAGE::Math::Matrix3 toLocal = SWAGE::Math::Inverse(agent.LocalToWorld());

	for (auto wo : worldObstacles)
	{
		if (SWAGE::Math::DistanceSqr(agent.position, wo.center) > SWAGE::Math::Sqr(avoidanceDistance + wo.radius))
			continue;
		
		SWAGE::Math::Vector2 localCenter = SWAGE::Math::TransformCoord(wo.center, toLocal);
		if (localCenter.y < 0)
			continue;

		localExpandedObstacles.push_back(SWAGE::Math::Shapes::Circle(localCenter, wo.radius + agent.radius));
	}

	float closestY = FLT_MAX;
	SWAGE::Math::Shapes::Circle closestCircle;
	for (auto lo : localExpandedObstacles)
	{
		if (abs(lo.center.x) > lo.radius)
			continue;

		// y = +/- Sqrt(r^2 - h^2) + k
		float y1 = sqrt(lo.radius * lo.radius - lo.center.x * lo.center.x) + lo.center.y;
		float y2 = sqrt(lo.radius * lo.radius - lo.center.x * lo.center.x) * -1 + lo.center.y;

		if (y1 > y2 && closestY > y2)
		{
			closestY = y2;
			closestCircle = lo;
		}
		else if (y2 > y1 && closestY > y1)
		{
			closestY = y1;
			closestCircle = lo;
		}
	}

	//if (ShowDebug())
	//{
	//	SWAGE::Math::Vector2 avoidDistance = X::Math::TransformCoord({ 0.0f ,avoidanceDistance }, toWorld);
	//	SWAGE::Math::Vector2 bottomLeft = X::Math::TransformCoord({agent.radius ,0.0f }, toWorld);
	//	SWAGE::Math::Vector2 bottomRight = X::Math::TransformCoord({-agent.radius ,0.0f }, toWorld);
	//	SWAGE::Math::Vector2 topLeft = X::Math::TransformCoord({agent.radius ,avoidanceDistance }, toWorld);
	//	SWAGE::Math::Vector2 topRight = X::Math::TransformCoord({-agent.radius ,avoidanceDistance }, toWorld);

	//	SWAGE::DrawScreenLine(bottomLeft, topLeft, X::Colors::Yellow);
	//	SWAGE::DrawScreenLine(bottomRight, topRight, X::Colors::Yellow);
	//	SWAGE::DrawScreenLine(bottomLeft, bottomRight, X::Colors::Yellow);
	//	SWAGE::DrawScreenLine(topLeft, topRight, X::Colors::Yellow);
	//	SWAGE::DrawScreenText("Detection", topRight, 20.0f, X::Colors::Yellow);

	//	SWAGE::Math::Vector2 lateralForceToWorld = X::Math::TransformCoord({ mLateralForce ,0.0f }, toWorld);
	//	SWAGE::DrawScreenLine(agent.position, lateralForceToWorld, X::Colors::Blue);
	//	SWAGE::DrawScreenText("LateralForce", lateralForceToWorld, 20.0f, X::Colors::Blue);

	//	SWAGE::Math::Vector2 brakingForceToWorld = X::Math::TransformCoord({ 0.0f , -mBrakingForce }, toWorld);
	//	SWAGE::DrawScreenLine(agent.position, brakingForceToWorld, X::Colors::Cyan);
	//	SWAGE::DrawScreenText("BrakingForce", brakingForceToWorld, 20.0f, X::Colors::Cyan);
	//}

	if (closestY != FLT_MAX)
	{
		SWAGE::Math::Vector2 lateral;
		lateral.x = closestCircle.radius - abs(closestCircle.center.x);
		lateral *= mLateralForce;
		if (closestCircle.center.x > 0)
			lateral = -lateral;

		SWAGE::Math::Vector2 braking;
		braking.y = -(1 / abs(closestCircle.center.y)) * mBrakingForce;

		SWAGE::Math::Vector2 localAvoidanceForce = lateral + braking;
		return SWAGE::Math::TransformNormal(localAvoidanceForce, toWorld);
	}

	return SWAGE::Math::Vector2(0.f, 0.f);
}
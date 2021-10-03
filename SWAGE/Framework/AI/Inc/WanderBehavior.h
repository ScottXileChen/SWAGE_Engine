#pragma once
#include "SteeringBehavior.h"

namespace SWAGE::AI
{
	namespace Steering
	{
		namespace Wander
		{
			class WanderBehavior : public SWAGE::AI::Steering::SteeringBehavior
			{
			public:
				SWAGE::Math::Vector2 Calculate(Agent& agent) override;

				void SetWanderRadius(float radius) { mWanderRadius = radius; }
				void SetWanderDistance(float distance) { mWanderDistance = distance; }
				void SetWanderJitter(float jitter) { mWanderJitter = jitter; }

			private:
				float mWanderRadius = 30.0f;
				float mWanderDistance = 0.0f;
				float mWanderJitter = 3.0f;

				SWAGE::Math::Vector2 mLocalWanderTarget;
			};
		}
	}
}
#pragma once
#include "SteeringBehavior.h"

namespace SWAGE::AI
{
	namespace Steering
	{
		namespace ObstacleAvoidance
		{
			class ObstacleAvoidanceBehavior : public SWAGE::AI::Steering::SteeringBehavior
			{
			public:
				SWAGE::Math::Vector2 Calculate(Agent& agent) override;

				void SetBrakingForce(float force) { mBrakingForce = force; }
				void SetLateralForce(float force) { mLateralForce = force; }
				void SetDetectionLength(float length) { mDetectionLength = length; }
			private:
				float mDetectionLength = 0;;
				float mBrakingForce = 0;
				float mLateralForce = 0;
			};
		}
	}
}
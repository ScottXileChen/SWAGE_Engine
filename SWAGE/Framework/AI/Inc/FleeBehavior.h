#pragma once
#include "SteeringBehavior.h"

namespace SWAGE::AI
{
	namespace Steering
	{
		namespace Flee
		{
			class FleeBehavior : public SWAGE::AI::Steering::SteeringBehavior
			{
			public:
				SWAGE::Math::Vector2 Calculate(Agent& agent) override;
				void SetPanicDistance(float panicDistance) { mPanicDistance = panicDistance; }

			private:
				float mPanicDistance = FLT_MAX;
			};
		}
	}
}
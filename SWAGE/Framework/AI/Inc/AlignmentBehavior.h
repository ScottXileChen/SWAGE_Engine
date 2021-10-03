#pragma once
#include "SteeringBehavior.h"

namespace SWAGE::AI
{
	namespace Steering
	{
		namespace GroupBehaviors
		{
			class AlignmentBehavior : public SWAGE::AI::Steering::SteeringBehavior
			{
			public:
				SWAGE::Math::Vector2 Calculate(Agent& agent) override;
			};
		}
	}
}
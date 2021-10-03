#pragma once
#include "SteeringBehavior.h"

namespace SWAGE::AI
{
	namespace Steering
	{
		namespace Arrive
		{
			enum Deceleration { slow = 3, normal = 2, fast = 1 };

			class ArriveBehavior : public SWAGE::AI::Steering::SteeringBehavior
			{
			public:
				SWAGE::Math::Vector2 Calculate(Agent& agent) override;
				void SetDeceleration(Deceleration deceleration) { decel = deceleration; }

			private:
				Deceleration decel = Deceleration::normal;

				inline std::string DecelerationToString(Deceleration v)
				{
					switch (v)
					{
					case normal:   return "normal";
					case slow:   return "slow";
					case fast: return "fast";
					default:      return "[Unknown Deceleration]";
					}
				}
			};
		}
	}
}
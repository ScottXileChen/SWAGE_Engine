#pragma once

#include "Common.h"

namespace SWAGE::AI
{
	class Agent;

	namespace Steering
	{
		class SteeringBehavior
		{
		public:
			SteeringBehavior() = default;
			virtual ~SteeringBehavior() = default;

			virtual SWAGE::Math::Vector2 Calculate(Agent& agent) = 0;

			void SetWeight(float weight) { mWeight = weight; }
			float GetWeight()const { return mWeight; }

			void SetActive(bool active) { mActive = active; }
			bool IsActive() const { return mActive; }

			void EnableShowDebug(bool active) { mShowDebug = active; }
			bool ShowDebug() const { return mShowDebug; }

		private:
			float mWeight = 1.0f;
			bool mActive = false;
			bool mShowDebug = false;
		};
	}
}
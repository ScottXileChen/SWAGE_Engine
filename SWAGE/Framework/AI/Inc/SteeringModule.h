#pragma once

#include "SteeringBehavior.h"

namespace SWAGE::AI
{
	namespace Steering
	{
		class SteeringModule
		{
		public:
			SteeringModule(Agent& agent);

			template <class BehaviorType>
			BehaviorType* AddBehavior(std::string name);

			SWAGE::Math::Vector2 Calculate();
		private:
			using BehaviorMap = std::vector<std::unique_ptr<SteeringBehavior>>;

			Agent& mAgent;
			BehaviorMap mBehaviors;
		};

		template <class BehaviorType>
		BehaviorType* SteeringModule::AddBehavior(std::string name)
		{
			static_assert(std::is_base_of_v<SteeringBehavior, BehaviorType>,
				"BehaviorType is not a child class of AI::Steering::SteeringBehavior!");

			auto& newBehavior = mBehaviors.emplace_back(std::make_unique<BehaviorType>());
			return static_cast<BehaviorType*>(newBehavior.get());
		}
	}
}
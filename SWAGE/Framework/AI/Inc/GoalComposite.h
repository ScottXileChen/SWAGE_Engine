#pragma once

#include "Goal.h"

namespace SWAGE::AI::Decision
{
	template <class AgentType>
	class GoalComposite : public Goal<AgentType>
	{
	public:
		using Status = Goal<AgentType>::Status;

		GoalComposite(AgentType& agent)
			: Goal<AgentType>(agent)
		{}

		~GoalComposite() override
		{
			RemoveAllSubgoals();
		}

	protected:
		template <class GoalType>
		void AddSubgoal()
		{
			static_assert(std::is_base_of_v<Goal<AgentType>, GoalType>, "GoalType is not a child class of AI::Goal!");
			mSubgoals.push_front(std::make_unique<GoalType>());
		}

		void RemoveAllSubgoals()
		{
			for (auto& goal : mSubgoals)
				goal->Terminate();
			mSubgoals.clear();
		}

		Status ProcessSubgoals()
		{
			// Remove all completed goals
			while (!mSubgoals.empty())
			{
				auto goal = mSubgoals.front();
				if (goal->mStatus != Status::Completed && goal->mStatus != Status::Failed)
					break;

				goal->Terminate();
				mSubgoals.pop_front();
			}

			// If any Goals remain, continue to process
			if (!mSubgoals.empty())
			{
				Status status = mSubgoals.front()->Process();
				if (status == Status::Completed && !mSubgoals.empty())
					return Status::Active;
				else
					return status;
			}
			return Status::Completed;
		}

		std::list<std::unique_ptr<Goal<AgentType>>> mSubgoals;
	};
}
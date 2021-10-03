#pragma once

#include "MemoryRecord.h"

namespace SWAGE::AI::Perception
{
	class Agent;

	class Sensor
	{
	public:
		virtual ~Sensor() = default;

		virtual void Update(Agent& agent, MemoryRecords& memory, float deltaTime) = 0;
	};
}
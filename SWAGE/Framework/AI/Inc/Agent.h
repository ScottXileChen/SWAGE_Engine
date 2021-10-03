#pragma once

#include "Entity.h"

namespace SWAGE::AI
{
	class Agent;

	using Agents = std::vector<Agent*>;

	class Agent : public Entity
	{
	public:
		Agent(AIWorld& world, uint16_t typeId)
			: Entity(world, typeId)
		{}

		Agents neighbors;
		SWAGE::Math::Vector2 velocity = SWAGE::Math::Vector2::Zero;
		SWAGE::Math::Vector2 destination = SWAGE::Math::Vector2::Zero;
		float maxSpeed = 1.0f;
		float mass = 1.0f;
	};

}
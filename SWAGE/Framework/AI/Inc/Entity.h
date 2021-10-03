#pragma once
namespace SWAGE::AI
{
	class AIWorld;

	class Entity
	{
	public:
		Entity(AIWorld& world, uint16_t typeId);
		~Entity();

		Entity(const Entity&) = delete;
		Entity& operator=(const Entity&) = delete;

		Entity(Entity&&) = delete;
		Entity& operator=(Entity&&) = delete;

		SWAGE::Math::Matrix3 LocalToWorld() const;
		AIWorld& world;
		SWAGE::Math::Vector2 position = SWAGE::Math::Vector2::Zero;
		SWAGE::Math::Vector2 heading = SWAGE::Math::Vector2::YAxis;
		const int id = 0;
		float radius = 1.0f;
	};

	using Entities = std::vector<Entity*>;
}
#pragma once

#include "Agent.h"
#include "PartitionGrid.h"

namespace SWAGE::AI
{
	class AIWorld
	{
	public:
		using Obstacles = std::vector<SWAGE::Math::Shapes::Circle>;
		using Walls = std::vector<SWAGE::Math::Shapes::LineSegment>;

		void Initialize(const SWAGE::Math::Vector2& worldSize);
		void Update();

		void RegisterEntity(Entity*entity);
		void UnregisterEntity(Entity*entity);

		void AddObstacle(const SWAGE::Math::Shapes::Circle& obstacle) { mObstacles.push_back(obstacle); }
		void AddWall(const SWAGE::Math::Shapes::LineSegment& wall) { mWalls.push_back(wall); }

		Agents GetNeighborhood(const SWAGE::Math::Shapes::Circle& range, uint16_t typeId);
		Entities GetEntities(const SWAGE::Math::Shapes::Circle& range, uint16_t typeId);

		int GetNextId(uint16_t typeId);
		uint16_t GetType(int id) const;

		const Obstacles& GetObstacles() const { return mObstacles; }
		const Walls& GetWalls() const { return mWalls; }

	private:
		Entities mEntities;
		Obstacles mObstacles;
		Walls mWalls;
		AI::PartitionGrid::PartitionGrid<Entity> mGrid;
		int mNextId = 0;
	};
}
#pragma once

#include "GridBasedGraph.h"

namespace SWAGE::AI
{
	namespace Pathfinding
	{
		class AStar
		{
		public:
			bool Search(GridBasedGraph& graph, int startX, int startY, int endX, int endY,
				std::function<bool(int, int)> isBlocked,
				std::function<float(int, int, int, int)> getGCost,
				std::function<float(int, int, int, int)> getHCost);

			const std::list<GridBasedGraph::Node*>& GetClosedList() const { return mClosedList; }

		private:
			std::list<GridBasedGraph::Node*> mOpenList;
			std::list<GridBasedGraph::Node*> mClosedList;
		};
	}
}
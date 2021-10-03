#include "Precompiled.h"
#include "Dijkstra_Search.h"

using namespace SWAGE::AI::Pathfinding;

bool Dijkstra_Search::Search(GridBasedGraph & graph, int startX, int startY, int endX, int endY, std::function<bool(int, int)> isBlocked, std::function<float(int, int, int, int)> getGCost)
{
	graph.ResetSearchParams();

	auto node = graph.GetNode(startX, startY);
	mOpenList.push_back(node);
	node->opened = true;
	
	bool found = false;

	while (!found && !mOpenList.empty())
	{
		auto node = mOpenList.front();
		mOpenList.pop_front();

		if (node->column == endX && node->row == endY)
		{
			found = true;
		}
		else
		{
			for (auto neighbor : node->neighbors)
			{
				if (neighbor == nullptr || isBlocked(neighbor->column, neighbor->row))
					continue;

				//neighbor->g = getGCost(node->column, node->row, neighbor->column, neighbor->row);
				//neighbor->h = node->h + neighbor->g;
				float totalCost = node->g + getGCost(node->column, node->row, neighbor->column, neighbor->row);
				if (!neighbor->opened)
				{
					if (!mOpenList.empty())
					{
						bool isInserted = false;
						for (auto it = mOpenList.begin(); it != mOpenList.end(); ++it)
						{
							if (totalCost < (*it)->g)
							{
								neighbor->opened = true;
								neighbor->parent = node;
								neighbor->g = totalCost;
								mOpenList.insert(it, neighbor);
								isInserted = true;
								break;
							}
						}
						if (!isInserted)
						{
							neighbor->opened = true;
							neighbor->parent = node;
							neighbor->g = totalCost;
							mOpenList.push_back(neighbor);
						}
					}
					else
					{
						neighbor->opened = true;
						neighbor->parent = node;
						neighbor->g = totalCost;
						mOpenList.push_back(neighbor);
					}
				}
				else if (!neighbor->closed)
				{
					if (neighbor->g > totalCost)
					{
						auto sortFromSToL = [](GridBasedGraph::Node* a, GridBasedGraph::Node* b) {return a->g < b->g; };
						neighbor->g = totalCost;
						neighbor->parent = node;
						mOpenList.sort(sortFromSToL);
						//mOpenList.insert(mOpenList.begin(), neighbor);
						//mOpenList.pop_back();
					}
				}
			}
		}

		mClosedList.push_back(node);
		node->closed = true;
	}

	return found;
}
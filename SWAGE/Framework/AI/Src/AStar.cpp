#include "Precompiled.h"
#include "AStar.h"

using namespace SWAGE::AI::Pathfinding;

bool AStar::Search(GridBasedGraph & graph, int startX, int startY, int endX, int endY, std::function<bool(int, int)> isBlocked, std::function<float(int, int, int, int)> getGCost, std::function<float(int, int, int, int)> getHCost)
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

				//neighbor->g =  node->g + getGCost(neighbor->column, neighbor->row);
				float totalCost = node->g + getGCost(node->column, node->row ,neighbor->column, neighbor->row);;
				neighbor->h = getHCost(neighbor->column, neighbor->row, endX, endY);
				float f = neighbor->h + totalCost;

				if (!neighbor->opened)
				{
					if (!mOpenList.empty())
					{
						bool isInserted = false;
						for (auto it = mOpenList.begin(); it != mOpenList.end(); ++it) 
						{
							float f2 = (*it)->h + (*it)->g;
							if (f < f2)
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
					float f2 = neighbor->h + neighbor->g;
					if (f2 > f)
					{
						auto sortFromSToL = [](GridBasedGraph::Node* a, GridBasedGraph::Node* b) {return a->g + a->h < b->g + b->h; };
						neighbor->g = totalCost;
						neighbor->parent = node;
						mOpenList.sort(sortFromSToL);
		/*				mOpenList.insert(mOpenList.begin(), neighbor);
						mOpenList.remove(neighbor);*/
					}
				}
			}
		}

		mClosedList.push_back(node);
		node->closed = true;
	}

	return found;
}
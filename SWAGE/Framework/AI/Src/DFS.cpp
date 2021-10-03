#include "Precompiled.h"
#include "DFS.h"

using namespace SWAGE::AI::Pathfinding;

bool DFS::Search(GridBasedGraph & graph, int startX, int startY, int endX, int endY, std::function<bool(int, int)> isBlocked)
{
	graph.ResetSearchParams();
	auto node = graph.GetNode(startX, startY);
	mOpenList.push_front(node);
	node->opened = true;

	bool found = false;
	while (!found && !mOpenList.empty())
	{
		//Todo:
		//nextNode = get from open list
		//if(nextNode == end)
			//found = ture
		//otherwise
			//follow the lecture slide

		if (node == graph.GetNode(endX, endY))
		{
			found = true;
		}

		for (const auto &neighbor : node->neighbors)
		{
			if (neighbor != nullptr)
			{
				if (isBlocked(neighbor->column, neighbor->row))
					continue;
				if (neighbor->opened)
					continue;
				if (!neighbor->closed)
				{
					neighbor->opened = true;
					mOpenList.push_front(neighbor);
					neighbor->parent = node;
				}
			}
		}
		node->closed = true;
		mClosedList.push_back(node);
		if (!mOpenList.empty())
		{
			node = mOpenList.front();
			node->opened = true;
			mOpenList.pop_front();
		}
	}
	return found;
}
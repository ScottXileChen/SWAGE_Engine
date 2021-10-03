#include "Precompiled.h"
#include "BFS.h"

using namespace SWAGE::AI::Pathfinding;

bool BFS::Search(GridBasedGraph & graph, int startX, int startY, int endX, int endY, std::function<bool(int, int)> isBlocked)
{
	graph.ResetSearchParams();
	auto node = graph.GetNode(startX, startY);
	mOpenList.push_back(node);
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
			//mClosedList.push_back(node);
			found = true;
			//mOpenList.clear();
			//break;
		}

		for (const auto &neighbor : node->neighbors)
		{
			if (neighbor != nullptr)
			{
				//if (neighbor == graph.GetNode(endX, endY))
				//{
				//	//mOpenList.push_front(neighbor);
				//	mOpenList.push_back(neighbor);
				//	neighbor->parent = node;
				//	//break;
				//}
				if (isBlocked(neighbor->column, neighbor->row))
					continue;
				if (neighbor->opened)
					continue;
				if (!neighbor->closed)
				{
					neighbor->opened = true;
					mOpenList.push_back(neighbor);
					neighbor->parent = node;
				}
			}
		}
		node->closed = true;
		mClosedList.push_back(node);
		mOpenList.remove(node);
		if (!mOpenList.empty())
		{
			node = mOpenList.front();
			node->opened = true;
		}
	}
	return found;
}

// Peter Way
//bool BFS::Search(GridBasedGraph & graph, int startX, int startY, int endX, int endY, std::function<bool(int, int)> isBlocked)
//{
//	graph.ResetSearchParams();
//
//	auto node = graph.GetNode(startX, startY);
//	mOpenList.push_back(node);
//	node->opened = true;
//	
//	bool found = false;
//
//	while (!found && !mOpenList.empty())
//	{
//		auto node = mOpenList.front();
//		mOpenList.pop_front();
//
//		if (node->column == endX && node->row == endY)
//		{
//			found = true;
//		}
//		else
//		{
//			for (auto neighbor : node->neighbors)
//			{
//				if (neighbor == nullptr || isBlocked(neighbor->column, neighbor->row))
//					continue;
//
//				if (!neighbor->opened)
//				{
//					neighbor->opened = true;
//					mOpenList.push_back(neighbor);
//					neighbor->parent = node;
//				}
//			}
//		}
//
//		mClosedList.push_back(node);
//		node->closed = true;
//	}
//
//	return found;
//}
#include "Precompiled.h"
#include "GridBasedGraph.h"

using namespace SWAGE::AI::Pathfinding;

void GridBasedGraph::Initialize(int columns, int rows)
{
	//TODO:
	//crate nodes and assign neighbors
	mNodes.resize(columns * rows);//create nodes
	mColumns = columns;
	mRows = rows;
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < columns; ++j)
		{
			auto node = GetNode(j, i);
			for (int d = 0; d < 8; d++)
			{
				switch (d)
				{
				case 0:
					node->neighbors[d] = GetNode(j, i - 1);
					break;
				case 1:
					node->neighbors[d] = GetNode(j, i + 1);
					break;
				case 2:
					node->neighbors[d] = GetNode(j + 1, i);
					break;
				case 3:
					node->neighbors[d] = GetNode(j - 1, i);
					break;
				case 4:
					node->neighbors[d] = GetNode(j + 1, i - 1);
					break;
				case 5:
					node->neighbors[d] = GetNode(j - 1, i - 1);
					break;
				case 6:
					node->neighbors[d] = GetNode(j + 1, i + 1);
					break;
				case 7:
					node->neighbors[d] = GetNode(j - 1, i + 1);
					break;
				default:
					break;
				}
			}
			node->column = j;
			node->row = i;
		}
	}
}

void GridBasedGraph::ResetSearchParams()
{
	for (auto& node : mNodes)
	{
		node.parent = nullptr;
		node.g = 0.0f;
		node.h = 0.0f;
		node.opened = false;
		node.closed = false;
	}
}
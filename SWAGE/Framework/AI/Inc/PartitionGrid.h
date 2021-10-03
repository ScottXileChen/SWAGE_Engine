#pragma once

#include "Common.h"

namespace SWAGE::AI::PartitionGrid
{
	template <class T>
	class PartitionGrid
	{
	public:
		using Cell = std::vector<T*>;

		void Initialize(uint32_t columns, uint32_t rows)
		{
			mCells.resize(columns * rows);
			mColumns = columns;
			mRows = rows;
		}

		void ClearCells()
		{
			for (auto& cell : mCells)
				cell.clear();
		}

		Cell& GetCell(uint32_t column, uint32_t row)
		{
			ASSERT(column < mColumns && row < mRows, "[PartitionGrid] Invalid indices.");
			return mCells[column + (row* mColumns)];
		}

		uint32_t GetColumns() const { return mColumns; }
		uint32_t GetRows() const { return mRows; }

	private:
		std::vector<Cell> mCells;
		uint32_t mColumns;
		uint32_t mRows;
	};
}
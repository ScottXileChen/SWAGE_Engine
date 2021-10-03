#pragma once

#include "BlockAllocator.h"

namespace SWAGE::Core
{
	template <class DataType>
	class TypedAllocator final : private BlockAllocator
	{
	public:
		TypedAllocator(std::size_t capacity)
			: BlockAllocator(sizeof(DataType), capacity)
		{}

		DataType* New()
		{
			DataType* instance = static_cast<DataType*>(Allocate());
			if (instance != nullptr)
				new (instance) DataType();
			return instance;
		}

		void Delete(DataType* ptr)
		{
			if (ptr == nullptr)
				return;

			ptr->~DataType();
			Free(ptr);
		}
	};
}
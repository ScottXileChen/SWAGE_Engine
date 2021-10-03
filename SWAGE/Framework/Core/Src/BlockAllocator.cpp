#include "Precompiled.h"
#include "BlockAllocator.h"

#include "DebugUtil.h"

using namespace SWAGE::Core;

BlockAllocator::BlockAllocator(std::size_t blockSize, std::size_t capacity)
	:mBlockSize(blockSize), mCapacity(capacity)
{
	mData = std::malloc(mBlockSize * mCapacity);
	for (uint32_t i = 0; i < mCapacity; i++)
		mFreeSlots.push_back(i);
}

BlockAllocator::~BlockAllocator()
{
	std::free(mData);
}

void * BlockAllocator::Allocate()
{
	if (mFreeSlots.empty())
		return nullptr;

	size_t freeSlot = mFreeSlots.back();
	mFreeSlots.pop_back();
	return static_cast<uint8_t*>(mData) + mBlockSize * freeSlot;
}

void BlockAllocator::Free(void * ptr)
{
	size_t totalGap = (static_cast<uint8_t*>(ptr) - static_cast<uint8_t*>(mData));
	uint32_t recycledSlot = static_cast<uint32_t>(totalGap / mBlockSize);
	mFreeSlots.push_back((uint32_t)recycledSlot);
}

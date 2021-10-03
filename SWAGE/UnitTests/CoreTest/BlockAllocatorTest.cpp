#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace SWAGE::Core;

namespace CoreTest
{
	TEST_CLASS(BlockAllocatorTest)
	{
	public:
		
		TEST_METHOD(OneBlockTest)
		{
			BlockAllocator blockAllocator(16, 1);
			void* ptr = blockAllocator.Allocate();
			Assert::IsNotNull(ptr);
			void* ptr2 = blockAllocator.Allocate();
			Assert::IsNull(ptr2);
		}

		TEST_METHOD(TwoBlockTest)
		{
			BlockAllocator blockAllocator(16, 2);
			void* ptr = blockAllocator.Allocate();
			Assert::IsNotNull(ptr);
			void* ptr2 = blockAllocator.Allocate();
			Assert::IsNotNull(ptr2);
			Assert::IsTrue(ptr != ptr2);

			ptrdiff_t diff = static_cast<uint8_t*>(ptr) - static_cast<uint8_t*>(ptr2);
			Assert::IsTrue(abs(diff) == 16);

			void* ptr3 = blockAllocator.Allocate();
			Assert::IsNull(ptr3);
		}

		TEST_METHOD(FreeBlockTest)
		{
			BlockAllocator blockAllocator(16, 2);
			void* ptr = blockAllocator.Allocate();
			Assert::IsNotNull(ptr);
			void* ptr2 = blockAllocator.Allocate();
			Assert::IsNotNull(ptr2);
			Assert::IsTrue(ptr != ptr2);

			ptrdiff_t diff = static_cast<uint8_t*>(ptr) - static_cast<uint8_t*>(ptr2);
			Assert::IsTrue(abs(diff) == 16);

			void* ptr3 = blockAllocator.Allocate();
			Assert::IsNull(ptr3);

			blockAllocator.Free(ptr);

			ptr3 = blockAllocator.Allocate();
			Assert::IsNotNull(ptr3);

			Assert::IsTrue(ptr == ptr3);
		}
	};
}

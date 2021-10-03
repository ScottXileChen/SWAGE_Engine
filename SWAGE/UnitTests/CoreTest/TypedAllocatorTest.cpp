#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace SWAGE::Core;

namespace CoreTest
{
	TEST_CLASS(TypedAllocatorTest)
	{
	public:
		class TestClass
		{
		public:
			TestClass() : a(42), b(7) {}
			~TestClass() { a = b = 13; }
			int a, b;
		};

		TEST_METHOD(TestNew)
		{
			TypedAllocator<TestClass> typedAllocator(1);
			TestClass* ptr = typedAllocator.New();
			Assert::IsNotNull(ptr);
			Assert::AreEqual(ptr->a, 42);
			Assert::AreEqual(ptr->b, 7);

			TestClass* ptr2 = typedAllocator.New();
			Assert::IsNull(ptr2);
		}

		TEST_METHOD(TestDelete)
		{
			TypedAllocator<TestClass> typedAllocator(1);
			TestClass* ptr = typedAllocator.New();
			Assert::IsNotNull(ptr);
			Assert::AreEqual(ptr->a, 42);
			Assert::AreEqual(ptr->b, 7);

			typedAllocator.Delete(ptr);
			Assert::AreEqual(ptr->a, 13);
			Assert::AreEqual(ptr->b, 13);

			TestClass* ptr2 = typedAllocator.New();
			Assert::IsNotNull(ptr2);
			Assert::IsTrue(ptr2 == ptr);
		}
	};
}

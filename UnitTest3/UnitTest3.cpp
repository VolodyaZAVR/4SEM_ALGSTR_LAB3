#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab3/List.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest3
{
	TEST_CLASS(UnitTest3)
	{
	public:
		TEST_METHOD(push_test)
		{
			List<int> list;
			list.push_back(5);
			list.push_back(6);
			list.push_back(7);
			Assert::IsTrue(list[0] == 5);
			Assert::IsTrue(list[2] == 7);
			list.~List();
		}
		TEST_METHOD(pop_test)
		{
			List<int> list;
			list.push_back(5);
			list.push_back(6);
			list.push_back(7);
			Assert::IsTrue(5 == list.pop_front());
			Assert::IsTrue(list[0] == 6);
			list.~List();
		}
		TEST_METHOD(find_test)
		{
			List<int> list;
			list.push_back(5);
			list.push_back(6);
			list.push_back(7);
			Assert::IsTrue(list[list.find(5)] == 5);
			Assert::IsTrue(list[list.find(6)] == 6);
			Assert::IsTrue(list[list.find(7)] == 7);
			list.~List();
		}
		TEST_METHOD(clear_test)
		{
			List<int> list;
			list.push_back(5);
			list.push_back(6);
			list.push_back(7);
			list.clear();
			Assert::IsTrue(list.isEmpty());
			list.~List();
		}
	};
}

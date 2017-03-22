#include "stdafx.h"
#include"deque_test.h"
#include "deque.h"
#include <deque>
#include <cassert>
#include <string>
#include"algorithm.h"

namespace TinySTL
{
	namespace DequeTest {
		template<class T>
		using stdDQ = std::deque < T >;
		template<class T>
		using tsDQ = TinySTL::deque < T >;

		void testCase1()
		{
			stdDQ<int> dq1(10, 0);
			tsDQ<int> dq2(10, 0);
			assert(TinySTL::equal(dq1.begin(), dq1.end(),dq2.begin()));

			auto dq3(dq1);
			auto dq4(dq2);
			assert(TinySTL::equal(dq3.begin(), dq3.end(), dq4.begin()));

			auto dq5 = dq3;
			auto dq6 = dq4;
			assert(TinySTL::equal(dq5.begin(), dq5.end(), dq6.begin()));
		}
		void testCase2()
		{
			tsDQ<int> dq1;
			assert(dq1.empty());
			assert(dq1.size() == 0);

			tsDQ<int> dq2(10, 0);
			assert(!dq2.empty());
			assert(dq2.size() == 10);
		}
		void testCase3()
		{
			stdDQ<std::string> dq1(10, "10");
			tsDQ<std::string> dq2(10, "10");

			dq1[0] = "0"; dq1[9] = "9";
			dq2[0] = "0"; dq2[9] = "9";

			assert(dq1.front() == dq2.front());
			assert(dq1.back() == dq2.back());
		}
		void testCase4()
		{
			stdDQ<int> dq1;
			tsDQ<int> dq2;

			for (auto i = 0; i != 100; ++i) {
				dq1.push_back(i);
				dq2.push_back(i);
			}
			assert(TinySTL::equal(dq1.begin(), dq1.end(),dq2.begin()));

			for (auto i = 10; i != 100; ++i) {
				dq1.push_front(i);
				dq2.push_front(i);
			}
			assert(TinySTL::equal(dq1.begin(), dq1.end(), dq2.begin()));

			for (auto i = 0; i != 10; ++i) {
				dq1.pop_back();
				dq2.pop_back();
			}
			assert(TinySTL::equal(dq1.begin(), dq1.end(), dq2.begin()));

			for (auto i = 0; i != 20; ++i) {
				dq1.pop_front();
				dq2.pop_front();
			}
			assert(TinySTL::equal(dq1.begin(), dq1.end(), dq2.begin()));
		}
		void testCase5()
		{
			int arr[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
			tsDQ<int> foo{ 0,1,2 }, bar{ 3,4,5,6,7,8,9 };

			assert(foo.size() == 3 && bar.size() == 7);
			foo.swap(bar);
			assert(foo.size() == 7 && bar.size() == 3);
			TinySTL::swap(foo, bar);
			assert(foo.size() == 3 && bar.size() == 7);
		}
		void testCase6()
		{
			int arr[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
			tsDQ<int> foo1{ 0,1,2 }, bar{ 3,4,5,6,7,8,9 };

			assert(foo1 != bar);
			auto foo2 = bar;
			assert(foo2 == bar);
		}

		void testAllCases()
		{
			testCase1();
			testCase2();
			testCase3();
			testCase4();
			testCase5();
			testCase6();
		}
	}
}
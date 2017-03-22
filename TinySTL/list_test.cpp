#include "stdafx.h"
#include"deque_test.h"
#include "list.h"
#include <list>
#include <cassert>
#include <string>
#include"algorithm.h"
#include<random>
namespace TinySTL {
	namespace ListTest {
		template<class T>
		using stdL = std::list < T >;
		template<class T>
		using tsL = TinySTL::list < T >;

		void testCase1() 
		{
			stdL<int> l1(10, 0);
			tsL<int> l2(10, 0);
			assert(TinySTL::equal(l1.begin(),l1.end(),l2.begin()));

			auto l3(l1);
			auto l4(l2);
			assert(TinySTL::equal(l3.begin(), l3.end(), l4.begin()));

			auto l5 = l1;
			auto l6 = l2;
			assert(TinySTL::equal(l5.begin(), l5.end(), l6.begin()));
		}
		void testCase2()
		{
			tsL<std::string> l1;
			assert(l1.empty());
			assert(l1.size() == 0);

			std::string arr[] = { "1", "2", "3" };
			tsL<std::string> l2{ "1","2","3" };
			assert(!l2.empty());
			assert(l2.size() == 3);
		}
		void testCase3()
		{
			std::string arr[] = { "1", "2", "3" };
			tsL<std::string> l{ "1", "2", "3" };
			assert(l.back() == arr[2]);
			assert(l.front() == arr[0]);

			l.front() = "front";
			l.back() = "back";
			assert(l.back() == "back");
			assert(l.front() == "front");
		}
		void testCase4()
		{
			stdL<int> l1;
			tsL<int> l2;
			for (auto i = 0; i != 10; ++i) {
				l1.push_front(i);
				l2.push_front(i);
			}
			assert(std::equal(l1.begin(), l1.end(), l2.begin()));
			for (auto i = 0; i != 10; ++i) {
				l1.push_back(i);
				l2.push_back(i);
			}
			assert(std::equal(l1.begin(), l1.end(), l2.begin()));
			for (auto i = 0; i != 5; ++i) {
				l1.pop_back();
				l2.pop_back();
			}
			assert(std::equal(l1.begin(), l1.end(), l2.begin()));
			for (auto i = 0; i != 5; ++i) {
				l1.pop_front();
				l2.pop_front();
			}
			assert(std::equal(l1.begin(), l1.end(), l2.begin()));
		}
		void testCase5()
		{
			stdL<int> l1;
			tsL<int> l2;

			l1.insert(l1.end(), 10, -1);
			l2.insert(l2.end(), 10, -1);
			assert(std::equal(l1.begin(), l1.end(), l2.begin()));

			auto it1 = l1.begin();
			auto it2 = l2.begin();
			for (auto i = l1.size() / 2 + 1; i != 0; --i) {
				++it1;
				++it2;
			}
			l1.insert(it1, 1);
			l2.insert(it2, 1);
			assert(std::equal(l1.begin(), l1.end(), l2.begin()));
		}
		void testCase6()
		{
			stdL<int> l1;
			tsL<int> l2;
			for (auto i = 0; i != 100; ++i) {
				l1.push_back(i);
				l2.push_back(i);
			}

			l1.erase(l1.begin()); l1.erase(--l1.end());
			l2.erase(l2.begin()); l2.erase(--l2.end());
			assert(std::equal(l1.begin(), l1.end(), l2.begin()));

			l1.erase(l1.begin(), l1.end());
			l2.erase(l2.begin(), l2.end());
			assert(std::equal(l1.begin(), l1.end(), l2.begin()));
		}
		void testCase7()
		{
			tsL<int> l1, l2;
			l1.push_back(1); l1.push_back(1); l1.push_back(1);
			l2.push_back(2); l2.push_back(2);

			l1.swap(l2);
			assert(l1.size() == 2 && l2.size() == 3);
			TinySTL::swap(l1, l2);
			assert(l1.size() == 3 && l2.size() == 2);
		}


		void testAllCases()
		{
			testCase1();
			testCase2();
			testCase3();
			testCase4();
			testCase5();
			testCase6();
			testCase7();
		}
	}
}
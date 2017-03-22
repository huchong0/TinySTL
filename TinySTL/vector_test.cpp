#include "stdafx.h"
#include"vector_test.h"
#include<string>
#include<cassert>
#include<algorithm>
#include<vector>
#include"vector.h"
#include<iostream>


namespace TinySTL {
	namespace VectorTest {
		template<class T>
		using stdVec = std::vector < T >;

		template<class T>
		using tsVec = TinySTL::vector < T >;

		void testCase1() {
			stdVec<std::string>v1(10,"zxh");
			tsVec<std::string> v2(10,"zxh");
			assert(std::equal(v1.begin(),v1.end(),v2.begin()));

			stdVec<std::string> v3(10);
			tsVec<std::string> v4(10);
			assert(std::equal(v1.begin(), v1.end(), v2.begin()));


		}
		void testCase2() {
			stdVec<int> temp1(10, 0);
			tsVec<int> temp2(10, 0);

			auto v1(temp1);
			auto v2(temp2);
			assert(std::equal(v1.begin(), v1.end(), v2.begin()));

			auto v3(std::move(temp1));
			auto v4(std::move(temp2));
			assert(std::equal(v3.begin(), v3.end(), v4.begin()));

			auto v5 = v1;
			auto v6 = v2;
			assert(std::equal(v5.begin(), v5.end(), v6.begin()));
		}
		void testCase3() {
			tsVec<int> v1, v2;
			for (int i = 0; i != 100; ++i) {
				v1.push_back(i);
				v2.push_back(i);
			}

			assert(v1 == v2);
			assert(!(v1 != v2));
		}
		void testCase4() {
			tsVec<int> myvector;
			for (int i = 1; i <= 5; i++) myvector.push_back(i);

			auto i = 1;
			for (tsVec<int>::iterator it = myvector.begin(); it != myvector.end(); ++it, ++i) {
				assert(*it == i);
			}


		}
		void testCase5() {
			tsVec<int> v(11, 0);
			assert(v.size() == 11);

			v.resize(5);
			assert(v.size() == 5);

			v.resize(20);
			assert(v.size() == 20);
		}
		void testCase6() {
			tsVec<int> v;
			v.reserve(20);
			assert(v.capacity() == 20);
		}
		void testCase7() {
			stdVec<int> v1(10);
			tsVec<int> v2(10);
			for (unsigned i = 0; i < 10; i++) {
				v1[i] = i;
				v2[i] = i;
			}
			assert(std::equal(v1.begin(), v1.end(), v2.begin()));
			v1.front() = 99;
			v2.front() = 99;
			v1.back() = 100;
			v2.back() = 100;
			assert(std::equal(v1.begin(), v1.end(), v2.begin()));
		}
		void testCase8() {
			tsVec<int> foo(3, 100);   // three ints with a value of 100
			tsVec<int> bar(2, 200);   // five ints with a value of 200


			assert(std::equal(foo.begin(),foo.end(), stdVec < int > { 100, 100, 100 }.begin()));
			assert(std::equal(bar.begin(), bar.end(), stdVec < int > { 200, 200 }.begin()));



			foo.swap(bar);
			assert(std::equal(foo.begin(), foo.end(), stdVec < int > { 200, 200 }.begin()));
			assert(std::equal(bar.begin(), bar.end(), stdVec < int > { 100,100,100 }.begin()));
		}
		void testCase9() {
			stdVec<std::string> v1;
			tsVec<std::string> v2;

			v1.push_back("hello "); v1.push_back("world");
			v2.push_back("hello "); v2.push_back("world");
			assert(std::equal(v1.begin(), v1.end(), v2.begin()));

			v1.pop_back();
			v2.pop_back();
			assert(std::equal(v1.begin(), v1.end(), v2.begin()));
		}
		void testCase10() {
			stdVec<int> v1;
			tsVec<int> v2;

			v1.insert(v1.begin(), 0);
			v2.insert(v2.begin(), 0);
			assert(std::equal(v1.begin(), v1.end(), v2.begin()));

			v1.insert(v1.end(), 1);
			v2.insert(v2.end(), 1);
			assert(std::equal(v1.begin(), v1.end(), v2.begin()));
		}
		void testCase11() {
			stdVec<int> v1;
			tsVec<int> v2;
			for (int i = 1; i <= 10; i++) {
				v1.push_back(i);
				v2.push_back(i);
			}
			v1.erase(v1.begin() + 5);
			v2.erase(v2.begin() + 5);
			assert(std::equal(v1.begin(), v1.end(), v2.begin()));

			v1.erase(v1.begin(), v1.begin() + 3);
			v2.erase(v2.begin(), v2.begin() + 3);
			assert(std::equal(v1.begin(), v1.end(), v2.begin()));
		}
		void testCase12() {
			tsVec<int> foo(3, 100);
			tsVec<int> bar(2, 200);

			assert(!(foo == bar));
			assert(foo != bar);
		}



		void testAllCases() {
			testCase1();
			testCase2();
			testCase3();
			testCase4();
			testCase5();
			testCase6();
			testCase7();
			testCase8();
			testCase9();
			testCase10();
			testCase11();
			testCase12();
		}
	}
}

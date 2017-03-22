#include "stdafx.h"
#include <set>
#include "set.h"
#include <cassert>
#include <string>
#include"algorithm.h"
#include"set_test.h"

namespace TinySTL {
	namespace SetTest {
		template<class T>
		using stdS = std::set < T >;
		template<class T>
		using tsS = TinySTL::set < T >;
		template<class T>
		using stdMS = std::multiset < T >;
		template<class T>
		using tsMS = TinySTL::multiset < T >;

		void testCase1()
		{
			stdS<int> s1{1243,53,25,36,7,91,643,74,8};
			tsS<int>   s2{1243,53,25,36,7,91,643,74,8 };
			assert(TinySTL::equal(s1.begin(), s1.end(), s2.begin()));

			auto s3(s1);
			auto s4(s2);
			assert(TinySTL::equal(s3.begin(), s3.end(), s4.begin()));

			auto s5 = s1;
			auto s6 = s2;
			assert(TinySTL::equal(s5.begin(), s5.end(), s6.begin()));
		}
		void testCase2()
		{
			tsS<std::string> s1;
			assert(s1.empty());
			assert(s1.size() == 0);

			std::string arr[] = { "1", "2", "3" };
			tsS<std::string> s2{ "1","2","3" };
			assert(!s2.empty());
			assert(s2.size() == 3);
		}
		void testCase3()
		{
			std::string arr[] = { "1", "2", "3" };
			tsS<std::string> s{ "1", "2", "3" };
			assert(*s.begin() == arr[0]);
			assert(*(--s.end()) == arr[2]);
		}
		void testCase4()
		{
			stdS<char> s1;
			tsS<char> s2;
			std::string str{"f23euiorjf923if920tf3y45 wgstjs"};
			for (auto ch : str)
			{
				s1.insert(ch);
				s2.insert(ch);
			}
			assert(*s1.find('f') == *s2.find('f'));
			assert(*s1.upper_bound('2') == *s2.upper_bound('2'));
			assert(*s1.lower_bound(' ') == *s2.lower_bound(' '));
			assert(s1.count('e') == s2.count('e'));
			s1.insert('Y'); s2.insert('Y');
			assert(s1.count('Y') == s2.count('Y'));
			s2.erase('s');
			assert(s2.find('s') == s2.end());
		}
		void testCase5()
		{
			stdS<int> s1;
			tsS<int> s2;
			for (auto i = 0; i != 100; ++i) {
				s1.insert(i);
				s2.insert(i);
			}

			s1.erase(s1.begin()); s1.erase(--s1.end());
			s2.erase(s2.begin()); s2.erase(--s2.end());
			assert(std::equal(s1.begin(), s1.end(), s2.begin()));

		}
		void testCase6()
		{
			stdMS<int> s1{ 1243,53,25,36,7,91,643,74,8 };
			tsMS<int>   s2{ 1243,53,25,36,7,91,643,74,8 };
			assert(TinySTL::equal(s1.begin(), s1.end(), s2.begin()));

			auto s3(s1);
			auto s4(s2);
			assert(TinySTL::equal(s3.begin(), s3.end(), s4.begin()));

			auto s5 = s1;
			auto s6 = s2;
			assert(TinySTL::equal(s5.begin(), s5.end(), s6.begin()));
		}
		void testCase7()
		{
			tsMS<std::string> s1;
			assert(s1.empty());
			assert(s1.size() == 0);

			std::string arr[] = { "1", "2", "3" };
			tsMS<std::string> s2{ "1","2","3" };
			assert(!s2.empty());
			assert(s2.size() == 3);
		}
		void testCase8()
		{
			std::string arr[] = { "1", "2", "3" };
			tsMS<std::string> s{ "1", "2", "3" };
			assert(*s.begin() == arr[0]);
			assert(*(--s.end()) == arr[2]);
		}
		void testCase9()
		{
			stdMS<char> s1;
			tsMS<char> s2;
			std::string str{ "f23euiorjfe923ife920tf3y45 wegstjs" };
			for (auto ch : str)
			{
				s1.insert(ch);
				s2.insert(ch);
			}
			assert(*s1.find('f') == *s2.find('f'));
			assert(*s1.upper_bound('2') == *s2.upper_bound('2'));
			assert(*s1.lower_bound(' ') == *s2.lower_bound(' '));
			assert(s1.count('e') == s2.count('e'));
			s1.insert('Y'); s2.insert('Y');
			assert(s1.count('Y') == s2.count('Y'));
			s2.erase('Y');
			assert(s2.find('Y') == s2.end());

		}
		void testCase10()
		{
			stdMS<int> s1;
			tsMS<int> s2;
			for (auto i = 0; i != 100; ++i) {
				s1.insert(i);
				s2.insert(i);
			}
			for (auto i = 0; i != 100; ++i) {
				s1.insert(i);
				s2.insert(i);
			}

			s1.erase(s1.begin()); s1.erase(--s1.end());
			s2.erase(s2.begin()); s2.erase(--s2.end());
			assert(std::equal(s1.begin(), s1.end(), s2.begin()));

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
			testCase8();
			testCase9();
			testCase10();
		}
	}
}
#include "stdafx.h"
#include <unordered_map>
#include "unordered_map.h"
#include <cassert>
#include <string>
#include"algorithm.h"
#include"set_test.h"

namespace TinySTL
{
	namespace Unordered_Map_Test
	{
		template<class T, class X>
		using stdS = std::unordered_map < T, X >;
		template<class T, class X>
		using tsS = TinySTL::unordered_map < T, X >;
		template<class T, class X>
		using stdMS = std::unordered_multimap < T, X >;
		template<class T, class X>
		using tsMS = TinySTL::unordered_multimap < T, X >;
		void testCase1()
		{
			stdS<int, int> s1;
			tsS<int, int>   s2;
			for (int i = 0; i < 10; ++i)
			{
				s1.insert(std::make_pair(i, i));
				s2.insert(std::make_pair(i, i));
			}
			for (int i = 0; i < 10; ++i)
			{
				assert(s1[i] == s2[i]);
			}
		}
		void testCase2()
		{
			tsS<int, int>   s;
			for (int i = 0; i < 10; ++i)
			{
				s[i] = 0;
			}
			assert(s.find(10) == s.end());
			s.insert(99);
			assert(s.find(99)->first == 99);
			s.erase(5);
			assert(s.find(99)->first == 99);
			assert(s.find(5) == s.end());
		}
		void testCase3()
		{
			stdS<char, int> s1;
			tsS  <char, int> s2;
			std::string str{ "sjedofwenc24t5u53672esd fssd fsbgfsd n" };
			for (auto ch : str)
			{
				++s1[ch];
				++s2[ch];
			}
			for (auto mov = s1.begin(); mov != s1.end(); ++mov)
			{
				assert(s1[mov->first] == s2[mov->first]);
			}
			for (auto mov = s2.begin(); mov != s2.end(); ++mov)
			{
				assert(s2[mov->first] == s1[mov->first]);
			}
		}
		void testCase4()
		{
			stdMS<int, int> s1;
			tsMS<int, int>   s2;
			for (int i = 0; i < 10; ++i)
			{
				s1.insert(std::make_pair(i,int()));
				s2.insert(i);
			}
			for (int i = 5; i < 15; ++i)
			{
				s1.insert(std::make_pair(i, int()));
				s2.insert(i);
			}
			for (int i = 0; i < 10; ++i)
			{
				assert(s1.count(i) == s2.count(i));
			}
		}
		void testCase5()
		{
			tsMS<int, int>   s{ 1,2,3,4,5,6,7,8,8,6,3,3,2,62,4323,9,1,2,3,9 };
			assert(s.find(10) == s.end());
			s.insert(99);
			assert(s.find(99)->first == 99);
			s.erase(5);
			assert(s.find(99)->first == 99);
			assert(s.find(5) == s.end());
		}
		void testCase6()
		{
			stdMS<char, int> s1;
			tsMS  <char, int> s2;
			std::string str{ "sjedofwenc24t5svergt435yushb gsd su53672esd fssd fsbgfsd n" };
			for (int i = 0; i < str.size(); ++i)
			{
				s1.insert(std::make_pair(str[i], i));
				s2.insert(std::make_pair(str[i], i));
			}
			for (auto mov = s1.begin(); mov != s1.end(); ++mov)
			{
				assert(s1.count(mov->first) == s2.count(mov->first));
			}
			for (auto mov = s2.begin(); mov != s2.end(); ++mov)
			{
				assert(s2.count(mov->first) == s1.count(mov->first));
			}
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
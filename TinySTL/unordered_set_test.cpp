#include "stdafx.h"
#include <unordered_set>
#include "unordered_set.h"
#include <cassert>
#include <string>
#include"algorithm.h"
#include"set_test.h"

namespace TinySTL
{
	namespace Unordered_Set_Test
	{
		template<class T>
		using stdS = std::unordered_set < T >;
		template<class T>
		using tsS = TinySTL::unordered_set < T >;
		template<class T>
		using stdMS = std::unordered_multiset < T >;
		template<class T>
		using tsMS = TinySTL::unordered_multiset < T >;
		void testCase1()
		{
			stdS<int> s1 ;
			tsS<int>   s2 ;
			for (int i = 0; i < 10; ++i)
			{
				s1.insert(i);
				s2.insert(i);
			}
			for (int i = 0; i < 10; ++i)
			{
				assert(s1.count(i) == s2.count(i));
			}
			stdS<int> s3=s1;
			tsS<int>   s4=s2;
			for (auto mov = s3.begin(); mov != s3.end(); ++mov)
			{
				auto x = s3.count(*mov);
				auto y = s4.count(*mov);
				assert(s3.count(*mov) == s4.count(*mov));
			}
			stdS<int> s5;
			tsS<int>   s6;
			s5 = s3;
			s6 = s4;
			for (auto mov = s6.begin(); mov != s6.end(); ++mov)
			{
				assert(s5.count(*mov) == s6.count(*mov));
			}
		}
		void testCase2()
		{
			tsS<int>   s{ 1,2,3,4,5,6,7,8,9 };
			assert(s.find(10) == s.end());
			s.insert(99);
			assert(*s.find(99) == 99);
			s.erase(5);
			assert(*s.find(99) == 99);
			assert(s.find(5) == s.end());
		}
		void testCase3()
		{
			stdS<char> s1;
			tsS  <char> s2;
			std::string str { "sjedofwenc24t5u53672esd fssd fsbgfsd n" };
			for (auto ch : str)
			{
				s1.insert(ch);
				s2.insert(ch);
			}
			for (auto mov = s1.begin(); mov != s1.end(); ++mov)
			{
				assert(s1.count(*mov) == s2.count(*mov));
			}
			for (auto mov = s2.begin(); mov != s2.end(); ++mov)
			{
				assert(s2.count(*mov) == s1.count(*mov));
			}
		}
		void testCase4()
		{
			stdMS<int> s1;
			tsMS<int>   s2;
			for (int i = 0; i < 10; ++i)
			{
				s1.insert(i);
				s2.insert(i);
			}
			for (int i = 5; i < 15; ++i)
			{
				s1.insert(i);
				s2.insert(i);
			}
			for (int i = 0; i < 10; ++i)
			{
				assert(s1.count(i) == s2.count(i));
			}
			stdMS<int> s3 = s1;
			tsMS<int>   s4 = s2;
			for (auto mov = s3.begin(); mov != s3.end(); ++mov)
			{
				assert(s3.count(*mov) == s4.count(*mov));
			}
			stdMS<int> s5;
			tsMS<int>   s6;
			s5 = s3;
			s6 = s4;
			for (auto mov = s6.begin(); mov != s6.end(); ++mov)
			{
				assert(s5.count(*mov) == s6.count(*mov));
			}
		}
		void testCase5()
		{
			tsMS<int>   s{ 1,2,3,4,5,6,7,8,8,6,3,3,2,62,4323,9,1,2,3,9 };
			assert(s.find(10) == s.end());
			s.insert(99);
			assert(*s.find(99) == 99);
			s.erase(5);
			assert(*s.find(99) == 99);
			assert(s.find(5) == s.end());
		}
		void testCase6()
		{
			stdMS<char> s1;
			tsMS  <char> s2;
			std::string str{ "sjedofwenc24t5svergt435yushb gsd su53672esd fssd fsbgfsd n" };
			for (auto ch : str)
			{
				s1.insert(ch);
				s2.insert(ch);
			}
			for (auto mov = s1.begin(); mov != s1.end(); ++mov)
			{
				assert(s1.count(*mov) == s2.count(*mov));
			}
			for (auto mov = s2.begin(); mov != s2.end(); ++mov)
			{
				assert(s2.count(*mov) == s1.count(*mov));
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
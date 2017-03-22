#include "stdafx.h"
#include <map>
#include "map.h"
#include <cassert>
#include <string>
#include"algorithm.h"
#include"map_test.h"





namespace TinySTL {
	namespace MapTest {
		template<class T, class Z>
		using stdL = std::map < T , Z >;
		template<class T, class Z>
		using tsL = TinySTL::map < T , Z >;

		void testCase1()
		{
			stdL<int,int> m1;
			tsL<int,int> m2;
			assert(m2.empty());
			assert(m2.size() == 0);
			for (int i = 0; i < 100; ++i)
			{
				m1[i] = i;
				m2[i] = i;
			}
			for (int i = 0; i < 110; ++i)
			{
				assert(m1[i] == m2[i]);
			}
		}
		void testCase2()
		{
			stdL<char, int> m1;
			tsL<char, int> m2;
			std::string str = { "198fhg23tpfjmewa0r19h" };
			for (auto ch : str)
			{
				++m1[ch];
				++m2[ch];
			}




			assert((static_cast<std::pair<const char,int>>(*m2.lower_bound('b'))) == *m1.lower_bound('b'));
			assert((static_cast<std::pair<const char, int>>(*m2.upper_bound('4'))) == *m1.upper_bound('4'));
			assert((static_cast<std::pair<const char, int>>(*m2.find('8'))) == *m1.find('8'));
			assert(m1['a'] == m2['a']);
		}
		void testCase3()
		{
			tsL<char, int> m1;
			for (auto ch : "aer8923 r023-91 sf")
			{
				++m1[ch];
			}
			m1.insert(std::make_pair('S', 9));
			assert(m1['S'] == 9);
			m1.erase('9');
			assert(m1.find('9') == m1.end());
		}
		void testCase4()
		{
			std::multimap<char, int> mm1;
			TinySTL::multimap<char, int>mm2;
			std::string str{ "jf92 u3890fsd923r g4wg2 3yj" };
			for (int i = 0; i < str.size(); ++i)
			{
				mm1.insert(std::make_pair(str[i], i));
				mm2.insert(std::make_pair(str[i], i));
			}

			mm1.insert(std::make_pair('S', 999));
			mm2.insert(std::make_pair('S', 999));
			assert(mm1.find('S')->second == mm2.find('S')->second);
		}


		void testAllCases()
		{
			testCase1();
			testCase2();
			testCase3();
			testCase4();
		}
	}
}
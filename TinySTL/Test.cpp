#include "stdafx.h"
#include <iostream>
#include<string>
#include<unordered_map>
#include<vector>

#include"deque.h"
#include"vector.h"
#include"list.h"
#include"stack.h"
#include"queue.h"
#include"heap.h"
#include"RBtree.h"
#include"set.h"
#include"map.h"
#include"unordered_set.h"
#include"unordered_map.h"
#include"algorithm.h"

namespace TinySTL
{
	template<class T>
	void _print(const T& item)
	{
		for (auto mov = item.begin(); mov != item.end(); ++mov)
		{
			std::cout << *mov << " ";
		}
		std::cout << std::endl;
	}

	void dequeTest()
	{
		deque<int> a;
		deque<int> b{ 707,727,760,777,737 };

		for (int i = 0; i < 1000; ++i)
		{
			a.push_front(i);
		}
		_print(a);
		for (int i = 0; i < 900; ++i)
		{
			a.pop_back();
		}
		_print(a);



	}
	void listTest()
	{
		list<std::string> strs = { "3412341341" };
		//for (int i = 0; i < 200000; ++i)
		//{
		//	strs.push_back("hahahahaha");
		//}
		//for (int i = 0; i < 200000; ++i)
		//{
		//	strs.pop_front();
		//}

		list<int> fuck = { 1,2,3,4,5,6,7,8 };
		list<int> wokao = fuck;
		fuck = { 1,2,3,4,643,745,745,235,74,324,8,6 };
		_print(fuck);
		_print(wokao);


		strs.clear();






	}
	void vectorTest()
	{
		//ctor_test
		vector<int> one_nine = { 1,2,3,4,5,6,7,8,9 };
		vector<int> all_nine(99, 9);
		vector<std::string>strs;

		auto copy1 = one_nine;
		vector<int> copy2(all_nine);

		if (one_nine.back() != 9)
		{
			std::cout << "vectorTest 24 line" << std::endl;
		}

		if (one_nine[5] != 6)
		{
			std::cout << one_nine[5] << std::endl;
		}

		all_nine[98] = 98;
		if (all_nine[98] != 98)
		{
			std::cout << "vectorTest 29 line" << std::endl;
		}


		one_nine.insert(41, one_nine.begin());
		one_nine.insert(43, one_nine.begin());
		one_nine.insert(44, one_nine.begin());
		one_nine.insert(45, one_nine.begin());
		one_nine.insert(46, one_nine.end());
		one_nine.insert(47, one_nine.end());
		one_nine.insert(48, one_nine.begin() + 3);
		one_nine.insert(48, one_nine.begin() + 3);
		one_nine.insert(48, one_nine.begin() + 3);
		one_nine.insert(48, one_nine.begin() + 3);

		one_nine.insert(48, one_nine.begin() + 3);

		one_nine.insert(48, one_nine.begin() + 3);

		one_nine.insert(48, one_nine.begin() + 3);

		for (int i = 0; i < 100; ++i)
		{
			all_nine.push_back(123);
		}


		one_nine.erase(one_nine.begin());
		one_nine.erase(one_nine.begin() + 5);


		one_nine.erase(one_nine.begin(), one_nine.begin() + 3);
		int i = one_nine.back();
		one_nine.back() = 9;
		i = one_nine.back();

		strs.push_back("1231425");
		strs.push_back("12fewwf");
		strs.push_back("1sdfare425");
		strs.push_back("12EDFEQFsdvfw425");
		strs.push_back("fdvwe25");
		strs.push_back("1EW3124Y&&*25");

		strs.clear();
		one_nine.clear();

		for (int i = 0; i < 10000000; ++i)
		{

		}
		system("pause");






	}
	void stackTest()
	{
		stack<int> stk;
		for (int i = 0; i < 100; ++i)
		{
			stk.push(i);
		}
		for (int i = 0; i < 100; ++i)
		{
			std::cout << stk.top() << " ";
			stk.pop();
		}
		std::cout << std::endl;
	}
	void queueTest()
	{
		queue<int> que;
		for (int i = 0; i < 100; ++i)
		{
			que.push(i);
		}
		for (int i = 0; i < 100; ++i)
		{
			std::cout << que.front() << " ";
			std::cout << que.back() << " ";
			que.pop();
		}
		std::cout << std::endl;
	}
	void heapTest()
	{
		heap<int>fuck;
		fuck.push(23);
		fuck.push(1);
		fuck.push(643);
		fuck.push(563);
		fuck.push(243);
		fuck.push(22);
		fuck.push(9);
		fuck.push(5643);
		fuck.push(90);
		fuck.push(231);
		fuck.push(5473);

		while (!fuck.empty())
		{
			std::cout << fuck.top() << " ";
			fuck.pop();
		}
		std::cout << std::endl;
		
	}
	void RBtreeTest()
	{
		RBtree<int> fuck = {1,2,3,4,5,6,7,8,9,0};
		for (int i = 2; i < 5; ++i)
		{
			fuck.insert(i * 3);
		}
		fuck.erase(4);
		fuck.print(0);
		std::cout << std::endl;
		RBtree<int> wokao = fuck;
		wokao.print(0);
		std::cout << std::endl;
		RBtree<int> sabi;
		sabi = wokao;
		sabi.print(0);
		std::cout << std::endl;
		for(int i=0;i<10;++i)
		fuck.insert(10);
		for (auto mov = fuck.begin(); mov != fuck.end(); ++mov)
		{
			std::cout << *mov << " ";
		}

	}
	void setTest()
	{
		set<int> fuck;
		multiset<int> wokao;
		for (int i = 0; i < 100; ++i)
		{
			fuck.insert(i);
			wokao.insert(i);
		}
		for (int i = 0; i < 10; ++i)
		{
			fuck.insert(i);
			fuck.insert(i);
			fuck.insert(i);
			wokao.insert(i);
			wokao.insert(i);
			wokao.insert(i);
			wokao.insert(i);
		}

		for (auto mov = fuck.begin(); mov != fuck.end(); ++mov)
		{
			std::cout << *mov << " ";
		}
		std::cout << "\n\n\n";
		std::cout << *fuck.lower_bound(3) << " " << *fuck.upper_bound(3) << *fuck.find(5);
		std::cout << "\n\n\n";
		for (auto mov = wokao.begin(); mov != wokao.end(); ++mov)
		{
			std::cout << *mov << " ";
		}
		std::cout << "\n\n\n";
		std::cout << *wokao.lower_bound(3) << " " << *wokao.upper_bound(3)<<*wokao.find(5);

		
	}
	void mapTest()
	{
		map<char, int> fuck;
		std::unordered_map<char,int> wokao;
		std::string sentence = "fj239r8u329qr y239r89230ru10ur094ut9wyhtgospei34r9-20u3ytugsfj02q3u5r23qutgodht";
		for (auto item : sentence)
		{
			++fuck[item];
			++wokao[item];
		}
		fuck.insert(std::make_pair('P', 99));
		for (auto mov = fuck.begin(); mov != fuck.end(); ++mov)
		{
			std::cout << (*mov).first << "  " << (*mov).second<<"    "<<wokao[(*mov).first] << "\n";
		}
		auto nima = fuck;
		nima['P'] = 234;
		for (auto mov = nima.begin(); mov != nima.end(); ++mov)
		{
			std::cout << (*mov).first << "  " << (*mov).second << "    " << wokao[(*mov).first] << "\n";
		}

	}
	void unordered_setTest()
	{
		unordered_set<int> fuck;
		unordered_multiset<int> wokao;
		for (int i = 0; i < 20; ++i)
		{
			fuck.insert(i);
		}
		for (int i = 10; i < 15; ++i)
		{
			fuck.insert(i);
		}
		for (int i = 0; i < 20; ++i)
		{
			std::cout << i << "  " << fuck.count(i)<<std::endl;
		}
		std::cout << "\n\n";
		for (int i = 0; i < 20; ++i)
		{
			wokao.insert(i);
		}
		for (int i = 10; i < 15; ++i)
		{
			wokao.insert(i);
		}
		for (int i = 1; i < 20; ++i)
		{
			std::cout << i << "  " << wokao.count(i) << std::endl;
		}

	}
	void unordered_mapTest()
	{
		unordered_map<char, int> fuck;
		std::string str = {"fsioefjpeifmjo319 8r203qti-32uar9uqroawufeo kzmf, r fjweo 23dsf w23 y"};
		for (auto item : str)
		{
			++fuck[item];
		}
		fuck.erase('2');
		for (auto mov = fuck.begin(); mov != fuck.end(); ++mov)
		{
			std::cout << mov->first << "    " << mov->second << "\n";
		}
		std::cout << "\n\n\n";
		unordered_multimap<char, int> wokao;
		wokao.insert(std::make_pair('r', 10));
		wokao.insert(std::make_pair('r', 2));
		wokao.insert(std::make_pair('r', 3));
		wokao.insert(std::make_pair('r', 4));
		wokao.insert(std::make_pair('r', 5));
		for (auto item : str)
		{
			wokao.insert(std::make_pair(item, 9));
		}
		wokao.erase('3');
		wokao.erase('3');
		wokao.erase('3');
		for (auto mov = wokao.begin(); mov != wokao.end(); ++mov)
		{
			std::cout << mov->first << "    " << mov->second << "\n";
		}

	}
	void for_eachTest()
	{
		std::vector<int> fuck{1,2,3,4,5,6,7,8,89,90};
		for_each(fuck.begin(), fuck.end(), [](int& i) {i = i * 2; });
		for (auto i : fuck)std::cout << i << "  ";
	}
	void minmax_element()
	{
		std::vector<int> fuck{ 1,2,3,4,5,6,-7,8,89,90,4325,-25,23623,-745,12,635,74,-236,35745,9,99,-32 };
		auto item = minmax_element(fuck.begin(), fuck.end());
		auto absCmp = [](int x, int y) {return std::abs(x) < std::abs(y); };

		std::cout << *min_element(fuck.begin(),fuck.end()) << "  " << *max_element(fuck.begin(), fuck.end()) << "\n";

		std::cout << *item.first << "  " << *item.second<<"\n";

		item= minmax_element(fuck.begin(), fuck.end(),absCmp);

		std::cout << *min_element(fuck.begin(), fuck.end(),absCmp) << "  " << *max_element(fuck.begin(), fuck.end(), absCmp) << "\n";

		std::cout << *item.first << "  " << *item.second << "\n";
	}

	
}


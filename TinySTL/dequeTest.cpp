#include "stdafx.h"
#include <iostream>
#include<string>
#include"deque.h"
#include"vector.h"
#include"list.h"

using namespace std;
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
}

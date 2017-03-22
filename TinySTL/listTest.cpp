#include "stdafx.h"
#include <iostream>
#include<string>
#include"listTest.h"
#include "list.h"






using namespace TinySTL;
namespace TinySTL
{
	template<class T>
	void printList(const T& item)
	{
		for (auto mov = item.begin(); mov != item.end(); ++mov)
		{
			std::cout << *mov << " ";
		}
		std::cout << std::endl;
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

		list<int> fuck = {1,2,3,4,5,6,7,8};
		list<int> wokao = fuck;
		fuck = {1,2,3,4,643,745,745,235,74,324,8,6};
		printList(fuck);
		printList(wokao);
		

		strs.clear();






	}

}
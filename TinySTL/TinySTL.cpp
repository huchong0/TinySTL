// TinySTL.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<algorithm>


#include"allocator.h"
#include"iterator.h"
#include"vector.h"
#include"deque_test.h"
#include"list_test.h"
#include"map_test.h"
#include"set_test.h"
#include"unordered_set_test.h"
#include"unordered_map_test.h"
#include"vector_test.h"
using namespace std;




int main()
{
	
	TinySTL::DequeTest::testAllCases();
	TinySTL::ListTest::testAllCases();
	TinySTL::MapTest::testAllCases();
	TinySTL::SetTest::testAllCases();
	TinySTL::Unordered_Set_Test::testAllCases();
	TinySTL::Unordered_Map_Test::testAllCases();
	TinySTL::VectorTest::testAllCases();
	

	system("pause");
    return 0;
}


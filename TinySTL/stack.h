#pragma once
#ifndef  STACK
#define STACK
#include"deque.h"

namespace TinySTL
{
	template <class T>
	class stack
	{
		deque<T> buffer;

	public:
		void push(const T& value)
		{
			buffer.push_back(value);
		}
		void pop()
		{
			buffer.pop_back();
		}
		T		top()
		{
			return buffer.back();
		}
		void clear()
		{
			buffer.clear();
		}
		bool empty()
		{
			return buffer.empty();
		}
		size_t size()
		{
			return buffer.size();
		}
	};
}




#endif // ! STACK


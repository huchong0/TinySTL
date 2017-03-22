#pragma once
#ifndef QUEUE
#define QUEUE
#include "list.h"

namespace TinySTL
{
	template<class T>
	class queue
	{
		list<T> buffer;
	public:
		void push(const T& item)
		{
			buffer.push_back(item);
		}
		void pop()
		{
			buffer.pop_front();
		}
		T      back()
		{
			return buffer.back();
		}
		T		front()
		{
			return buffer.front();
		}
		void size()
		{
			return buffer.size();
		}
		void clear()
		{
			buffer.clear();
		}

	};
}
#endif // !QUEUE

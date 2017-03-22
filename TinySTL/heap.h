#pragma once
#ifndef  HEAP
#define HEAP

#include"vector.h"

namespace TinySTL
{
	template<class T>
	class heap
	{
		vector<T> buffer;
		size_t start;
		size_t finish;
		size_t parent(size_t item)
		{
			return item / 2;
		}
		size_t left(size_t item)
		{
			size_t res = item * 2;
			if (res >= finish)return 0;
			return res;
		}
		size_t right(size_t item)
		{
			size_t res = item * 2+1;
			if (res >= finish)return 0;
			return res;
		}
		void swap(size_t a, size_t b)
		{
			T temp = buffer[a];
			buffer[a] = buffer[b];
			buffer[b] = temp;
		}
		void trace_up(size_t item)
		{
			while (1)
			{
				if (item == 1)break;
				size_t pa = parent(item);
				if (buffer[pa] >= buffer[item])break;
				swap(item, pa);
				item = pa;
			}
		}
		void trace_down(size_t item)
		{
			while (1)
			{
				if (item > finish/2)break;
				size_t le =left(item);
				size_t ri = right(item);
				if (ri == 0)
				{
					if (le == 0)
					{
						break;
					}
					else
					{
						if (buffer[le] > buffer[item])
						{
							swap(le, item);
						}
					}
					break;
				}
				else
				{
					if (buffer[le] > buffer[ri])
					{
						if (buffer[le] > buffer[item])
						{
							swap(le, item);
							item = le;
						}
						else break;
					}
					else
					{
						if (buffer[ri] > buffer[item])
						{
							swap(ri, item);
							item = ri;
						}
						else break;
					}
				}
			}
		}

	public:
		heap() :start(1), finish(1) { buffer.push_back(T()); }
		heap(std::initializer_list<T> list)
		{
			for (auto mov = list.begin(); mov != list.end(); ++mov)
			{
				push(item);
			}
		}
		void push(const T& item)
		{
			buffer.push_back(item);
			trace_up(finish++);
		}
		void pop()
		{
			swap(start, --finish);
			buffer.pop_back();
			trace_down(1);
		}
		T		top()
		{
			return buffer[start];
		}
		size_t size() { return buffer.size(); }
		bool empty() { return buffer.size()==1; }

	};
}




#endif // ! HEAP


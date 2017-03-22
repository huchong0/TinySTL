#pragma once
#ifndef VECTOR
#define VECTOR

#include<memory>

#include"allocator.h"

namespace TinySTL
{
	template<class T>
	class vector
	{
	public:
		typedef			T				value_type;
		typedef			T*				pointer;
		typedef			T*				iterator;
		typedef			T&			refrence;
		typedef			size_t		size_type;
		typedef			ptrdiff_t	difference_type;
		typedef			vector<T> self;
	private:
		iterator start, finish, endOfStorage;
		
		allocator<T> alloc;



		void fill_initialize(size_type n,const T& item)
		{
			start = alloc.allocate(n * 2);
			std::uninitialized_fill_n(start, n, item);
			endOfStorage = start + 2 * n;
			finish = start + n;
		}


	public:
		vector() :start(0), finish(0), endOfStorage(0) {}
		explicit vector(size_type n)
		{
			fill_initialize(n, T());
		}
		vector(size_type n, const T& item)
		{
			fill_initialize(n, item);
		}
		vector(const vector<value_type>& item)
		{
			size_type n = item.size();
			start = alloc.allocate(n * 2);
			std::uninitialized_copy(item.begin(), item.end(), start);
			finish = start + n;
			endOfStorage = start + 2 * n;
		}
		vector<value_type>& operator= (vector<value_type> item)
		{
			alloc.destroy(start, finish);
			alloc.deallocate(start);
			size_type n = item.size();
			start = alloc.allocate(n * 2);
			std::uninitialized_copy(item.begin(), item.end(), start);
			finish = start + n;
			endOfStorage = start + 2 * n;
			return *this;
		}
		vector(std::initializer_list<value_type> items)
		{
			size_type n = items.size();
			start = alloc.allocate(n * 2);
			auto consPtr = start;
			for (auto mov = items.begin(); mov != items.end(); ++mov,++consPtr)
			{
				alloc.construct(consPtr, *mov);
			}
			finish = start + n;
			endOfStorage = start + 2 * n;
		}
		~vector()
		{
			alloc.destroy(start, finish);
			alloc.deallocate(start);
		}
		
		refrence operator[](size_type n)
		{
			if (n >= size())
			{
				std::cerr << "out of array";
				std::abort();
			}
			return *(start + n);
		}
		bool       operator==(const self& item)
		{
			for (auto mov1 = begin(), mov2 = item.begin();;)
			{
				if (mov1 == end())
				{
					if (mov2 == item.end())return true;
					else return false;
				}
				if (mov2 == item.end())
				{
					return false;
				}
				if (*mov1 != *mov2)return false;
				++mov1;
				++mov2;
			}
			return true;
		}
		bool		  operator!=(const self& item)
		{
			return !operator==(item);
		}
		size_type size()const { return (size_type)(finish - start); }
		size_type capacity()const { return (size_type)(endOfStorage - start); }
		iterator begin()const { return start; }
		iterator end()const { return finish; }
		void reserve(size_type n)
		{
			if (n <= capacity()) return;
			int size = finish-start;
			iterator temp = alloc.allocate(n);
			
			std::uninitialized_copy(start, finish, temp);
			alloc.deallocate(start);
			start = temp;
			finish = start + size;
			endOfStorage = start + n;
		}
		iterator erase(iterator pos)
		{
			if (pos >= finish)return finish;
			alloc.destroy(pos);
			if (pos == finish - 1)--finish;
			else
			{
				std::copy(pos+1,finish,pos);
				--finish;
			}
			return pos;
		}
		iterator erase(iterator beg, iterator end)
		{
			alloc.destroy(beg, end);
			if (end == finish)
			{
				finish -= end - beg;
			}
			else
			{
				std::copy(end,finish,beg);
				finish -= end - beg;
			}
			return beg;
		}
		refrence back()
		{
			return *(finish - 1);
		}
		refrence front()
		{
			return *(start);
		}
		void push_back(const value_type& item)
		{
			if (finish==endOfStorage)
			{
				reserve(2 * capacity()+1);
				alloc.construct(finish, item);
			}
			else alloc.construct(finish, item);
			++finish;
		}
		void pop_back()
		{
			--finish;
			alloc.destroy(finish);
		}
		void insert(iterator pos, const value_type& item)
		{
			if (finish == endOfStorage)
			{
				int index = pos - start;
				reserve(2 * capacity()+1);
				insert(start + index, item);
				return;
			}
			std::copy(pos, finish, pos + 1);
			alloc.construct(pos, item);
			++finish;
		}
		void clear()
		{
			alloc.destroy(start, finish);
			alloc.deallocate(start);
			start = 0; finish = 0;
		}
		bool empty()
		{
			return start == finish;
		}
		void swap(vector<T>& item)
		{
			iterator temp = item.start;
			item.start = start;
			start = temp;

			temp = item.finish;
			item.finish = finish;
			finish = temp;

			temp = item.endOfStorage;
			item.endOfStorage = endOfStorage;
			endOfStorage = temp;
		}
		void resize(size_t new_size)
		{
			if (new_size > capacity())
			{
				reserve(new_size * 2);
				size_t gap = new_size - size();
				std::uninitialized_fill_n(finish, gap, T());
				finish += gap;
				return;
			}
			if (new_size > size())
			{
				size_t gap = new_size - size();
				std::uninitialized_fill_n(finish, gap, T());
				finish += gap;
				return;
			}
			else
			{
				size_t gap = size() - new_size;
				alloc.destroy(finish - gap, finish);
				finish -= gap;
				return;
			}

		}

	};

}

#endif // !VECTOR


#ifndef DEQUE
#define DEQUE
#include"allocator.h"
#include"iterator.h"
#include"vector.h"

#include<algorithm>
#include<iostream>
#include<iterator>
//#include<type_traits>

namespace TinySTL
{
	template <class T> class deque;
	template <class T> class _bidirectional_vector;

	template<class T>
	class _deque_iterator :public std::iterator<std::random_access_iterator_tag,T>
	{
	public:
		friend class deque<T>;
		typedef _deque_iterator<T> self;
		//typedef T**							 map_pointer;
		

	private:
		T* cur;
		T* first;
		T* last;
		size_t node;
		size_t sizeOfBuffer;
		_bidirectional_vector<T*> *map;

	public:
		//_deque_iterator():cur(0),first(0),last(0),node(0) {}
		_deque_iterator(size_t SizeOfBuffer) :cur(0), first(0), last(0), node(0), sizeOfBuffer(SizeOfBuffer){}
		_deque_iterator(T*Cur,T*First,T*Last, size_t Node, size_t SizeOfBuffer, _bidirectional_vector<T*> *Map) :cur(Cur), first(First), last(Last), node(Node), sizeOfBuffer(SizeOfBuffer), map(Map) {}


		bool			operator==(const self& item)const
		{
			return cur == item.cur;
		}
		bool			operator!=(const self& item)const
		{
			return cur != item.cur;
		}
		bool			operator>(const self& item)const
		{
			if (node == item.node)
			{
				return cur > item.cur;
			}
			else return node > item.node;
		}
		bool			operator>=(const self& item)const
		{
			if (node == item.node)
			{
				return cur >= item.cur;
			}
			else return node >= item.node;
		}
		bool			operator<(const self& item)const
		{
			if (node == item.node)
			{
				return cur < item.cur;
			}
			else return node < item.node;
		}
		bool			operator<=(const self& item)const
		{
			if (node == item.node)
			{
				return cur <= item.cur;
			}
			else return node <= item.node;
		}

		reference operator*()const
		{
			return *cur;
		}
		pointer    operator->()const
		{
			return &(*cur)
		}
		self&		operator+=(ptrdiff_t n)
		{
			if (n < 0)return operator-=(-n);
			ptrdiff_t least = last - cur;
			if (n > least)
			{
				ptrdiff_t S = n - least-1;
				ptrdiff_t nodeS = S / sizeOfBuffer+1;
				ptrdiff_t bufferS = S%sizeOfBuffer;
				node += nodeS;
				first = (*map)[node];
				last = (*map)[node] + sizeOfBuffer - 1;
				cur = first + bufferS;
			}
			else
			{
				cur += n;
				return *this;
			}
		}
		self&		operator-=(ptrdiff_t n)
		{
			if (n < 0)return operator+=(-n);

			ptrdiff_t least = cur - first;
			if (n > least)
			{
				ptrdiff_t S = n - least+1;
				ptrdiff_t nodeS = S / sizeOfBuffer+1;
				ptrdiff_t bufferS = S%sizeOfBuffer;
				node -= nodeS;
				first = (*map)[node];
				last = (*map)[node] + sizeOfBuffer - 1;
				cur = last - bufferS;
			}
			else
			{
				cur -= n;
				return *this;
			}

		}
		self&		operator++()
		{
			if (cur == last)
			{
				++node;
				first = (*map)[node];
				last = first + sizeOfBuffer-1;
				cur = first;
			}
			else ++cur;
			return *this;
		}
		self&		operator--()
		{
			if (cur == first)
			{
				--node;
				first = (*map)[node];
				last = (*map)[node] + sizeOfBuffer-1;
				cur = last;
			}
			else --cur;
			return *this;
		}
		self			operator++(int)
		{
			auto temp = *this;
			operator++();
			return temp;
		}
		self			operator--(int)
		{
			auto temp = *this;
			operator--();
			return temp;
		}
		ptrdiff_t  operator-(const self& item)const
		{
			ptrdiff_t l = cur-first+node*sizeOfBuffer;
			ptrdiff_t r = item.cur-item.first+item.node*sizeOfBuffer;
			ptrdiff_t res = l-r;
			return res;

		}
		self			operator+(ptrdiff_t n)const
		{
			self temp = *this;
			temp += n;
			return temp;
		}
		self			operator-(ptrdiff_t n)const
		{
			self temp = *this;
			temp -= n;
			return temp;
		}



	};

	template<class T>
	class _bidirectional_vector
	{
	public:
		typedef			T				value_type;
		typedef			T*				pointer;
		typedef			T*				iterator;
		typedef			T&			refrence;
		typedef			size_t		size_type;
		typedef			ptrdiff_t	difference_type;
	private:
		iterator start, finish,begOfStorage, endOfStorage;

		allocator<T> alloc;



		void fill_initialize(size_type n, const T& item)
		{
			begOfStorage = alloc.allocate(n * 2);
			std::uninitialized_fill_n(begOfStorage, n, item);
			endOfStorage = begOfStorage + 2 * n;
			start = begOfStorage + n / 4;
			finish = start + n;
		}


	public:
		_bidirectional_vector() :begOfStorage(0),start(0), finish(0), endOfStorage(0) {}
		explicit _bidirectional_vector(size_type n)
		{
			fill_initialize(n, T());
		}
		~_bidirectional_vector()
		{
			alloc.destroy(start, finish);
			alloc.deallocate(begOfStorage);
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
		size_type size()const { return (size_type)(finish - start); }
		size_type capacity()const { return (size_type)(endOfStorage - begOfStorage); }
		iterator begin()const { return start; }
		iterator end()const { return finish; }
		void reserve(size_type n)
		{
			if (n <= capacity()) return;
			int size = finish - start;
			iterator temp = alloc.allocate(n);

			std::uninitialized_copy(start, finish, temp + n / 4);
			alloc.deallocate(begOfStorage);
			begOfStorage = temp;
			start = temp + n / 4;
			finish = start + size;
			endOfStorage = begOfStorage + n;
		}
		iterator erase(iterator pos)
		{
			if (pos >= finish)return finish;
			alloc.destroy(pos);
			if (pos == finish - 1)--finish;
			else
			{
				std::copy(pos + 1, finish, pos);
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
				std::copy(end, finish, beg);
				finish -= end - beg;
			}
			return beg;
		}
		refrence back()
		{
			return *(finish - 1);
		}
		void push_back(const value_type& item)
		{
			if (finish == endOfStorage)
			{
				reserve(2 * capacity() + 4);
				alloc.construct(finish, item);
			}
			else alloc.construct(finish, item);
			++finish;
		}
		void push_front(const value_type& item)
		{
			if (start == begOfStorage)
			{
				reserve(2 * capacity() + 4);
				alloc.construct(--start, item);
			}
			else alloc.construct(--start, item);
		}
		void pop_back()
		{
			alloc.destroy(--finish);
		}
		void pop_front()
		{
			alloc.destroy(start++);
		}
		void clear()
		{
			alloc.destroy(start, finish);
			alloc.deallocate(begOfStorage);
			start = 0; finish = 0; begOfStorage = 0; endOfStorage = 0;
		}

	};
	
	template<class T>
	class deque
	{
	public:
		typedef _deque_iterator<T> iterator;
	private:
		typedef deque<T> self;
		iterator start;
		iterator finish;
		allocator<T> alloc;
		size_t sizeOfBuffer;
		_bidirectional_vector<T*>map;
		void add_Finish()	//在尾端新开一个缓冲区
		{
				T* temp = alloc.allocate(sizeOfBuffer);
				map.push_back(temp);
				finish = iterator(map.back(), map.back(), map.back() + sizeOfBuffer - 1, map.size() - 1, sizeOfBuffer,&map);
		}



	public:
		deque():start(8), finish(8),sizeOfBuffer(8){}
		deque(size_t n,const T& val=T()):start(8), finish(8), sizeOfBuffer(8)
		{
			if (n == 0)return;
			while (n > sizeOfBuffer)
			{
				T*temp=alloc.allocate(sizeOfBuffer);
				std::uninitialized_fill_n(temp, sizeOfBuffer, val);
				map.push_back(temp);
				n -= sizeOfBuffer;
			}
			T*temp = alloc.allocate(sizeOfBuffer);
			std::uninitialized_fill_n(temp, n, val);
			map.push_back(temp);
			start = iterator(*map.begin(), *map.begin(),*map.begin() + sizeOfBuffer - 1,0, sizeOfBuffer,&map);
			finish = iterator(map.back() + n, map.back(), map.back() + sizeOfBuffer - 1, map.size() - 1, sizeOfBuffer, &map);

		}
		deque(const std::initializer_list<T>& list):start(8), finish(8), sizeOfBuffer(8)
		{
			for (auto mov = list.begin(); mov != list.end(); ++mov)
			{
				push_back(*mov);
			}
		}
		deque(const self& item) :start(item.sizeOfBuffer), finish(item.sizeOfBuffer), sizeOfBuffer(item.sizeOfBuffer)
		{
			for (iterator mov = item.begin(); mov != item.end(); ++mov)
			{
				push_back(*mov);
			}
		}

		//template<class input_iterator>
		//deque(input_iterator beg, input_iterator end ) :start(8), finish(8), sizeOfBuffer(8)
		//{
		//	for (auto mov=beg; mov != end; ++mov)
		//	{
		//		push_back(*mov);
		//	}
		//}

		self& operator=(const self& item)
		{
			clear();
			for (iterator mov = item.begin(); mov != item.end();++mov)
			{
				push_back(*mov);
			}
			return *this;
		}
		bool  operator==(const self& item)const
		{
			return std::equal(begin(), end(), item.begin());
		}
		bool  operator!=(const self& item)const
		{
			return !std::equal(begin(), end(), item.begin());
		}
		iterator begin()const
		{
			return start;
		}
		iterator end()const
		{
			return finish;
		}
		size_t size()const
		{
			return finish - start;
		}
		T& operator[](size_t n)const
		{
			return *(start + n);
		}
		
		void push_back(const T& val)
		{
			if (start == finish)
			{
				T*temp = alloc.allocate(sizeOfBuffer);
				map.push_back(temp);
				start = iterator(*map.begin(), *map.begin(),*map.begin() + sizeOfBuffer - 1, 0, sizeOfBuffer, &map);
				finish = start + 1;
				if (finish.cur == finish.last)add_Finish();
				alloc.construct(start.cur, val);
				return;
			}
			else
			{
				alloc.construct(finish.cur, val);
				if(finish.cur==finish.last && finish.node==map.size()-1)add_Finish();
				else ++finish;
			}

		}
		void pop_back()
		{
			--finish;
			alloc.destroy(finish.cur);
		}
		void push_front(const T& val)
		{
			if (start == finish)
			{
				T*temp = alloc.allocate(sizeOfBuffer);
				map.push_back(temp);
				start = iterator(*map.begin(), *map.begin(), *map.begin() + sizeOfBuffer - 1, 0, sizeOfBuffer, &map);
				finish = start + 1;
				if (finish.cur == finish.last)add_Finish();
				alloc.construct(start.cur, val);
				return;
			}
			else
			{
				if (start.cur == start.first&&start.node==0)
				{
					size_t SIZE= size();
					T*temp = alloc.allocate(sizeOfBuffer);
					map.push_front(temp);
					start = iterator(*map.begin()+sizeOfBuffer-1, *map.begin(), *map.begin() + sizeOfBuffer - 1, 0, sizeOfBuffer, &map);
					finish = start + SIZE + 1;
					alloc.construct(start.cur,val);
					return;
				}
				else
				{
					--start;
					alloc.construct(start.cur,val);
				}
			}
		}
		void pop_front()
		{
			iterator temp = start;
			++start;
			alloc.destroy(temp.cur);
		}
		bool empty()const
		{
			return start == finish;
		}
		T&	back()
		{
			iterator temp = finish - 1;
			return *temp;
		}
		T&	front()
		{
			return *start;
		}
		void swap(self& item)
		{
			std::swap(*this, item);
		}
		void clear()
		{
			for (auto mov = start; mov != finish; ++mov)
			{
				alloc.destroy(mov.cur);
			}

			for (int i = 1; i < map.size(); ++i)
			{
				alloc.deallocate(map[i]);
			}
			start = iterator(sizeOfBuffer);
			finish = iterator(sizeOfBuffer);
			map.clear();
		}

		iterator erase(const iterator& pos)
		{
			if (pos == start)
			{
				pop_front();
				return start;
			}
			if (pos == finish)
			{
				pop_back();
				return finish;
			}
			size_t index = pos - start;
			if (index < size()/2)
			{
				std::copy_backward(start, pos, pos +1);
				pop_front();
			}
			else
			{
				std::copy(pos + 1, finish, pos);
				pop_back();
			}
			return start + index;
		}
		iterator erase(const iterator& head, const iterator& tail)
		{
			if (head == start && tail == finish)
			{
				clear();
				return start;
			}
			if (head >= tail)
			{
				std::abort();
			}
			size_t index = head - start;
			size_t count = tail - head;
			
			if (index < size()/2)
			{
				iterator new_start = start + count;
				std::copy_backward(start, head, tail);
				for (iterator mov = start; mov != new_start; ++mov)
				{
					alloc.destroy(mov.cur);
				}
				start = new_start;
			}
			else
			{
				iterator new_finish = finish - count;
				std::copy(tail, finish, head);
				for (iterator mov = new_finish; mov != finish; ++mov)
				{
					alloc.destroy(mov.cur);
				}
				finish = new_finish;
			}
			return start + index;
		}
		iterator insert(iterator pos,const T& value)
		{
			if (pos == start)
			{
				push_front(value);
				return start;
			}
			if (pos == finish)
			{
				push_back(value);
				return finish;
			}
			size_t index = pos - start;
			if (index < size()/2)
			{
				push_front(T());
				iterator new_item_pos = pos - 1;
				std::copy(start+1, pos, start);
				alloc.construct(new_item_pos.cur, value);
			}
			else
			{
				push_back(T());
				iterator new_item_pos = pos;
				std::copy_backward(pos, finish-1, finish);
				alloc.construct(new_item_pos.cur, value);
			}
			return start + index;
		}
		iterator insert(iterator pos, const iterator& head, const iterator& tail)
		{
			if (pos == start)
			{
				for (auto mov = tail-1; mov != head; --mov)
				{
					push_front(*mov);
				}
				push_front(*head);
				return start;
			}
			if (pos == finish)
			{
				for (auto mov = head; mov != tail; ++mov)
				{
					push_back(*mov);
				}
				return finish;
			}
			size_t index = pos - start;
			size_t count = tail - head;
			if (index < size()/2)
			{
				
				for(size_t i=0;i<count;++i) push_front(T());
				iterator old_start = start+count;
				pos = old_start + index;
				iterator new_item_beg = pos - count;
				std::copy(old_start, pos, start);
				std::copy(head, tail, new_item_beg);
			}
			else
			{
				
				for (size_t i = 0; i<count; ++i) push_back(T());
				iterator old_finish = finish-count;
				pos = start + index;
				iterator new_item_end = pos+count;
				std::copy_backward(pos, old_finish, finish);
				std::copy(head, tail, pos);
			}
			return start + index;
		}

		~deque()
		{
			clear();
		}
	};
}

#endif // !DEQUE


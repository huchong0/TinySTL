#pragma once
#ifndef  LIST
#define LIST

#include"allocator.h"
#include"iterator.h"
#include<iostream>


namespace TinySTL
{
	template<class T>class list;

	template<class T>
	struct _list_node
	{
		typedef T								value_type;
		value_type data;
		_list_node<value_type> * next;
		_list_node<value_type> * pre;
		_list_node():next(0),pre(0) {}
		_list_node(value_type Date) :data(Date), next(0), pre(0) {}
	};

	template<class T>
	class _list_iterator:public std::iterator<std::bidirectional_iterator_tag,T>
	{
	
	public:
		friend class list<T>;
		typedef _list_node<T> node;
	private:
		node* ptr;
	public:
		

		_list_iterator():ptr(0)
		{

		}
		_list_iterator(node* P) :ptr(P) {}

		reference operator*()const
		{
			return ptr->data;
		}
		pointer operator->()const
		{
			return &(operator*());
		}
		bool operator==(const _list_iterator& item)const
		{
			return item.ptr == this->ptr;
		}
		bool operator!=(const _list_iterator& item)const
		{
			return item.ptr != this->ptr;
		}
		_list_iterator<T>& operator++()
		{
			ptr = ptr->next;
			return *this;
		}
		_list_iterator<T> operator++(int)
		{
			_list_iterator<T> res = *this;
			operator++();
			return res;
		}
		_list_iterator<T>& operator--()
		{
			ptr = ptr->pre;
			return *this;
		}
		_list_iterator<T> operator--(int)
		{
			_list_iterator<T> res = *this;
			operator--();
			return res;
		}


		
	};

	template<class T>
	class list
	{
	public:
		typedef T								value_type;
		typedef T&							reference;
		typedef _list_iterator<T>		iterator;
		typedef _list_node<T>			node;
		typedef size_t						size_type;
		typedef ptrdiff_t					difference_type;


	private:
		iterator start;
		iterator finish;
		allocator<node>		alloc;
		size_t count;
	public:
		list()
		{
			auto temp = alloc.allocate(1);
			alloc.construct(temp, T());
			finish = temp;
			start = finish;
		}
		list(size_t n,value_type item=value_type())
		{
			node* temp = alloc.allocate(1);
			alloc.construct(temp, item);
			start.ptr = temp;

			node* Pre = temp;
			count = n;
			while (--n)
			{
				temp = alloc.allocate(1);
				alloc.construct(temp, item);
				Pre->next = temp;
				temp->pre = Pre;
				Pre = temp;
			}
			// Pre is the last one
			temp = alloc.allocate(1);
			alloc.construct(temp, T());
			Pre->next = temp;
			temp->pre = Pre;
			finish = temp;
		}
		list(std::initializer_list<value_type> initial_list)
		{
			if (initial_list.size() == 0)
			{
				auto temp = alloc.allocate(1);
				alloc.construct(temp,T());
				finish = temp;
				start = finish;
				count = 0;
			}
			else
			{
				node*temp=alloc.allocate(1);
				alloc.construct(temp, *initial_list.begin());
				start.ptr = temp;

				node* Pre = temp;
				for (auto mov = initial_list.begin()+1; mov != initial_list.end(); ++mov)
				{
					temp = alloc.allocate(1);
					alloc.construct(temp, *mov);
					Pre->next = temp;
					temp->pre = Pre;
					Pre = temp;
				}

				temp = alloc.allocate(1);
				alloc.construct(temp, T());
				Pre->next = temp;
				temp->pre = Pre;
				finish = temp;
			}
			count = initial_list.size();
		}
		list(const list<T>& item) :start(0), finish(0), count(0)
		{
			
			auto temp = alloc.allocate(1);
			alloc.construct(temp, T());
			finish = temp;
			start = finish;

			for (iterator mov = item.begin(); mov != item.end(); ++mov)
			{
				push_back(*mov);
			}
		}
		list<T>& operator=(const list<T>& item)
		{
			clear();
			for (auto mov = item.begin(); mov != item.end(); ++mov)
			{
				push_back(*mov);
			}
			return *this;
		}

		bool empty()const
		{
			return count == 0;
		}
		size_type size()const
		{
			return count;
		}
		iterator begin()const
		{
			return start;
		}
		iterator end()const
		{
			return finish;
		}
		reference back()const 
		{
			auto temp = finish;
			return *(--temp);
		}
		reference front()const
		{
			return *start;
		}
		reference operator[](size_t n)const
		{
			if (n > count)
			{
				std::cerr << "list access out of range" << std::endl;
				std::abort;
			}
			node* mov = start.ptr;
			while (n--)
			{
				mov = mov->next;
			}
			return mov->data;
		}


		void push_back(const value_type& item)
		{
			++count;
			if (start == finish)//list is empty
			{
				start.ptr=alloc.allocate(1);
				alloc.construct(start.ptr, item);
				start.ptr->next = finish.ptr;
				finish.ptr->pre = start.ptr;
				return;
			}
			node* temp = alloc.allocate(1);
			alloc.construct(temp, value_type());
			*finish = item;
			finish.ptr->next = temp;
			temp->pre = finish.ptr;
			finish = temp;
		}
		void push_front(const value_type& item)
		{
			if (start == finish)//list is void
			{
				start.ptr = alloc.allocate(1);
				alloc.construct(start.ptr, item);
				start.ptr->next = finish.ptr;
				finish.ptr->pre = start.ptr;
				return;
			}
			node* temp = alloc.allocate(1);
			alloc.construct(temp, item);
			temp->next = start.ptr;
			start.ptr->pre = temp;
			start.ptr = temp;
			++count;
		}

		void pop_back()
		{
			--count;
			node* temp = finish.ptr->pre;
			alloc.destroy(finish.ptr);
			alloc.deallocate(finish.ptr);
			finish = temp;
			temp = finish.ptr->pre;
			alloc.destroy(finish.ptr);
			alloc.construct(finish.ptr, value_type());
			finish.ptr->pre = temp;
		}
		void pop_front()
		{
			node* temp = start.ptr->next;
			if(start.ptr->next)
			start.ptr->next->pre = finish.ptr;
			alloc.destroy(start.ptr);
			alloc.deallocate(start.ptr);
			start.ptr = temp;
			--count;
		}

		iterator insert(iterator pos, const value_type& item)
		{
			++count;
			if (pos.ptr == finish.ptr)
			{
				push_back(item);
				return finish;
			}
			else
			{
				if (pos == start)
				{
					push_front(item);
					return start;
				}
				node* temp = alloc.allocate(1);
				alloc.construct(temp,item);
				node* Pre = pos.ptr->pre;
				node* Next = pos.ptr;
				Pre->next = temp;
				Next->pre = temp;
				temp->pre = Pre;
				temp->next = Next;

				return iterator(Next);

			}

		}
		iterator insert(iterator pos, iterator beg, iterator last)
		{
			if (pos == finish)
			{
				while (beg != last)
				{
					push_back(*beg);
					++beg;
				}
				return finish;
			}
			iterator res = ++pos;
			while (beg != last)
			{
				insert(pos, *beg);
				++beg;
			}
			return res;
		}
		iterator insert(iterator pos, size_t num, const T& item)
		{
			if (pos == finish)
			{
				for (int i = 0; i < num; ++i)
				{
					push_back(item);
				}
				return finish;
			}
			iterator res = ++pos;
			for (int i = 0; i < num; ++i)
			{
				insert(pos, item);
			}
			return res;
		}



		iterator erase(iterator pos)
		{
			if (pos == start)
			{
				pop_front();
				return start;
			}
			node*Pre = pos.ptr->pre;
			node*Next = pos.ptr->next;
			Pre->next = Next;
			Next->pre = Pre;
			alloc.destroy(pos.ptr);
			alloc.deallocate(pos.ptr);
			iterator res(Next);
			--count;
			return res;

		}
		iterator erase(iterator beg, iterator last)
		{
			size_t Count = 0;
			if (last == finish && beg==start)
			{
				clear();
				return finish;
			}
			if (last == finish)
			{
				node* Pre = beg.ptr->pre;
				Pre->next = finish.ptr;
				node* Next = beg.ptr->next;
				node* mov = beg.ptr;
				while (mov != 0)
				{
					alloc.destroy(mov);
					alloc.deallocate(mov);
					mov = Next;
					Next = mov->next;
					++Count;
				}
				count -= Count;
				return finish;
			}
			if (beg == start)
			{
				last.ptr->pre = 0;
				start = last;

				node* Next = beg.ptr->next;
				node* mov = beg.ptr;
				while (mov != start.ptr)
				{
					alloc.destroy(mov);
					alloc.deallocate(mov);
					mov = Next;
					Next = mov->next;
					++Count;
				}
				count -= Count;
				return start;
			}

			node* Pre = beg.ptr->pre;
			node* Next = last.ptr;
			Pre->next = Next;
			Next->pre = Pre;

			Next = beg.ptr->next;
			node* mov = beg.ptr;
			while (mov != last.ptr)
			{
				alloc.destroy(mov);
				alloc.deallocate(mov);
				mov = Next;
				Next = mov->next;
				++Count;
			}
			count -= Count;
			return last;


		}

		void swap(list<T>& item)
		{
			std::swap(*this, item);
		}
		void clear()
		{
			node* mov = start.ptr;
			node* next;
			while (mov != finish.ptr)
			{
				next = mov->next;
				alloc.destroy(mov);
				alloc.deallocate(mov);
				mov = next;
			}
			start = finish;
			count = 0;
		}
		
		~list()
		{
			clear();
			alloc.destroy(finish.ptr);
			alloc.deallocate(finish.ptr);
		}

		


	};
}




#endif // ! LIST

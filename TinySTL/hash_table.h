#pragma once
#ifndef HASHTABLE
#define HASHTABLE
#include "vector.h"
#include"allocator.h"

namespace TinySTL
{
	template<class T, class _hash_func = _default_hash<T> >
	class _hash_table;

	template <class T>
	class _hash_table_node
	{
	public:
		T data;
		_hash_table_node* next;
		_hash_table_node(const T &item, _hash_table_node* Next=0) :data(item), next(Next) {}
		_hash_table_node(_hash_table_node* Next=0) :next(Next) {}
	};

	template<class T>
	class _default_hash
	{
	public:
		size_t operator() (const T& item, size_t size)
		{
			size_t temp = static_cast<size_t>(item);
			return temp%size;
		}
	};


	template<class T, class _hash_func = _default_hash<T>>
	class _hash_iterator:public std::iterator<std::forward_iterator_tag,T>
	{
		
		typedef _hash_table_node<T>		node;
		typedef _hash_func							hasher;
		typedef _hash_table<T,hasher>		table;
		typedef _hash_iterator	<T, hasher> self;

		node* pos;
		table* container;
		size_t table_index;

	public:
		_hash_iterator(node* pos, table* container, size_t table_index) :pos(pos), container(container), table_index(table_index) {}
		self& operator++()
		{
			if(pos!=0)pos = pos->next;
			while (pos == 0)
			{
				++table_index;
				pos = container->table[table_index];
			}
			return *this;
		}
		self    operator++(int)
		{
			self temp = *this;
			return ++temp;
		}
		const T&	  operator*()
		{
			return *(&(pos->data));
		}
		T*		  operator->()
		{
			return &(pos->data);
		}
		bool   operator==(const _hash_iterator& item)const
		{
			return pos == item.pos;
		}
		bool   operator!=(const _hash_iterator& item)const
		{
			return pos != item.pos;
		}
		
	};

	template<class T,class _hash_func= _default_hash<T> >
	class _hash_table
	{
		friend class _hash_iterator<T, _hash_func>;
		typedef _hash_table_node<T>		node;
		typedef _hash_iterator	<T, _hash_func> iterator;
		typedef _hash_table<T, _hash_func> self;

		size_t num;
		_hash_func		hasher;
		vector<node*> table;
		allocator<node> alloc;
		size_t hash(const T& item)
		{
			return hasher(item, table.size() - 1);				//×¢ÒâÅÅ³ýÎ²²¿ÉÚ±ø
		}
		size_t hash(const T& item,size_t num)
		{
			return hasher(item, num);
		}
		void search_erase(const T& item)
		{
			size_t index = hash(item);
			node* p = table[index];
			node*mov = p;
			if (table[index] != 0 && table[index]->data == item)
			{
				node* temp = table[index]->next;
				alloc.deallocate(table[index]);

				table[index] = temp;
				return;
			}
			while (mov != 0)
			{
				if (mov->data == item)
				{
					p->next = mov->next;
					alloc.deallocate(mov);
					break;
				}
				else
				{
					p = mov;
					mov = mov->next;
				}
			}
		}
	public:
		void rehash()
		{
			if (num >= table.size() / 2)return;
			vector<node*> new_table(table.size() * 2, 0);
			size_t new_size = new_table.size();
			for (size_t i = 0; i < table.size() - 1; ++i)
			{
				node* mov = table[i];
				while (mov != 0)
				{
					size_t index = hash(mov->data, new_size);
					node* temp = mov->next;
					mov->next = new_table[index];
					new_table[index] = mov;
					mov = temp;
				}
			}
			new_table.push_back(alloc.allocate(1));
			table.swap(new_table);
		}
		_hash_table() :num(0) ,table(25,0)
		{ 
			table.push_back(alloc.allocate(1));
		}		//Î²²¿Ôö¼ÓÉÚ±ø
		_hash_table( self& item)
		{
			for (auto mov = item.begin(); mov != item.end(); ++mov)insert(*mov);
		}
		self& operator=( self& item)
		{
			for (auto mov = item.begin(); mov != item.end(); ++mov)insert(*mov);
			return *this;
		}
		size_t size() { return num; }
		void insert(const T& item)
		{
			node* temp = alloc.allocate(1);
			alloc.construct(temp, node(item));
			size_t index = hasher(item, table.size()-1);			
			temp->next = table[index];
			table[index] = temp;
			++num;
			if (num > table.size() / 2)rehash();
		}
		void erase(const T& item)
		{
			search_erase(item);
		}
		void erase(const iterator& iter)
		{
			erase(*iter);
		}
		iterator find(const T& item)
		{
			size_t index = hash(item);
			node* p = table[index];
			node*mov = p;
			while (mov != 0)
			{
				if (mov->data == item)
				{
					return iterator(mov, this, index);
				}
				mov = mov->next;
			}
			return end();
		}
		iterator end()
		{
			return iterator(table.back(), this, table.size());
		}
		iterator begin()
		{
			iterator temp(*table.begin(), this, 0);
			if (table[0] == 0)++temp;
			return temp;
		}
		size_t count(const T& item)
		{
			size_t index = hash(item);
			node* mov = table[index];
			size_t	res = 0;
			while (mov != 0)
			{
				if (mov->data == item)++res;
				mov = mov->next;
			}
			return res;
		}
		void clear()
		{
			for (int i = 0; i < table.size()-1; ++i) //ÈÆ¿ªÉÚ±ø
			{
				node* mov = table[i];
				while (mov != 0)
				{
					node* temp = mov->next;
					alloc.destroy(mov);
					alloc.deallocate(mov);
					mov = temp;
				}
				table[i] = 0;
			}
		}
		~_hash_table()
		{
			clear();
		}
		



	};
}


#endif // !HASHTABLE


#pragma once
#ifndef UNORDEREDSET
#define UNORDEREDSET
#include "hash_table.h"

namespace TinySTL
{
	template <class T, class _hash_func = _default_hash<T>>
	class _unordered_set_iterator
	{
		typedef _hash_iterator<T>									base;
		typedef _hash_func												hasher;
		typedef _unordered_set_iterator	<T, hasher>		self;
		base pos;
	public:
		_unordered_set_iterator(const base& item):pos(item) {}
		self& operator++()
		{
			++pos;
			return *this;
		}
		self    operator++(int)
		{
			self temp = *this;
			return ++temp;
		}
		const T&	  operator*()
		{
			return *(pos);
		}
		T*		  operator->()
		{
			return &(*(pos));
		}
		bool  operator== (const self& item)
		{
			return pos == item.pos;
		}
		bool  operator!= (const self& item)
		{
			return pos != item.pos;
		}
	};

	template <class T, class _hash_func = _default_hash<T>>
	class unordered_set
	{
	public:
		typedef  _unordered_set_iterator< T,  _hash_func>  iterator;
		
	private:
		_hash_table<T, _hash_func> table;

		
	public:
		unordered_set() {}
		unordered_set(std::initializer_list<T> list)
		{
			for (auto mov = list.begin(); mov != list.end();++mov)table.insert(*mov);
		}
		unordered_set( unordered_set<T>& item)
		{
			table = item.table;
		}
		unordered_set<T>& operator=( unordered_set<T>& item)
		{
			clear();
			table = item.table;
			return *this;
		}
		void insert(const T& item)
		{
			if(!count(item))table.insert(item);
		}
		void erase(const T& item)
		{
			table.erase(item);
		}
		void erase(const iterator& iter)
		{
			table.erase(*iter)
		}
		iterator find(const T& item)
		{
			return iterator(table.find(item));
		}
		iterator begin()
		{
			return iterator(table.begin());
		}
		iterator end()
		{
			return iterator(table.end());
		}
		size_t count(const T& item)
		{
			return table.count(item);
		}
		void clear() { table.clear(); }
	};

	template <class T, class _hash_func = _default_hash<T>>
	class unordered_multiset
	{
	public:
		typedef  _unordered_set_iterator< T,  _hash_func>  iterator;

	private:
		_hash_table<T, _hash_func> table;


	public:
		unordered_multiset() {}
		unordered_multiset(std::initializer_list<T> list)
		{
			for (auto mov = list.begin(); mov != list.end();++mov)table.insert(*mov);
		}
		unordered_multiset(unordered_multiset<T>& item)
		{
			table = item.table;
		}
		unordered_multiset<T>& operator=(unordered_multiset<T>& item)
		{
			clear();
			table = item.table;
			return *this;
		}
		void insert(const T& item)
		{
			table.insert(item);
		}
		void erase(const T& item)
		{
			table.erase(item);
		}
		void erase(const iterator& iter)
		{
			table.erase(*iter)
		}
		iterator find(const T& item)
		{
			return iterator(table.find(item));
		}
		iterator begin()
		{
			return iterator(table.begin());
		}
		iterator end()
		{
			return iterator(table.end());
		}
		size_t count(const T& item)
		{
			return table.count(item);
		}
		void clear() { table.clear(); }
	};
}


#endif // !UNORDEREDSET


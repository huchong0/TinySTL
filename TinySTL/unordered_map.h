#pragma once
#ifndef UNORDEREDMAP
#define  UNORDEREDMAP
#include "hash_table.h"
namespace TinySTL
{
	template<class T, class Z>
	class hash_pair
	{
	public:
		const T first;
		Z second;
		hash_pair(T first, Z second) :first(first), second(second) {}
		hash_pair(std::pair<T, Z> item) :first(item.first), second(item.second) {}
		hash_pair() :first(T()) {}

		bool operator==(const hash_pair<T, Z>& item)const { return first == item.first; }
		bool operator!=(const hash_pair<T, Z>& item)const { return first != item.first; }

		operator std::pair<T, Z>()
		{
			return std::pair<T, Z>(first, second);
		}
	};

	template <class F, class S, class _hash_func = _default_hash<F>>
	class _default_map_hash
	{
		_hash_func hasher;
	public:
		size_t operator()(const hash_pair<F, S>& item,const size_t size)
		{
			return hasher(item.first,size);
		}
	};

	template <class F, class S, class _hash_func = _default_map_hash<F, S, _default_hash<F>>>
	class _unordered_map_iterator
	{
		typedef hash_pair<F, S>										obj;
		typedef _hash_iterator<obj, _hash_func>								base;
		typedef _hash_func												hasher;
		typedef _unordered_map_iterator	<F, S, hasher>		self;
		base pos;
	public:
		_unordered_map_iterator(const base& item) :pos(item) {}
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
		obj&	  operator*()
		{
			return *(pos);
		}
		const obj*		  operator->()
		{
			return &(*pos);
		}
		bool  operator==(const self& item)const
		{
			return pos == item.pos;
		}
		bool  operator!=(const self& item)const
		{
			return pos != item.pos;
		}
	};

	template <class F, class S, class _hash_func = _default_hash<F>>
	class unordered_map
	{
		friend class _unordered_map_iterator< F, S, _hash_func>;
	public:
		typedef    _default_map_hash<F, S, _hash_func>		hasher;
		typedef  _unordered_map_iterator< F, S, hasher> iterator;
		typedef		hash_pair< F, S>										obj;
	private:
		_hash_table<obj, hasher> table;


	public:
		unordered_map() {}
		unordered_map(std::initializer_list<F> list)
		{
			for (auto mov = list.begin(); mov != list.end())
			{
				table.insert(obj(*mov, S()));
			}
		}
		void insert(const obj& item)
		{
			if (!table.count(item))table.insert(item);
		}
		void insert(const F& item)
		{
			obj temp(item, S());
			if (!table.count(temp)) table.insert(temp);
		}
		void erase(const F& item)
		{
			table.erase(obj(item, S()));
		}
		S&   operator[](const F& item)
		{
			obj temp(item, S());
			if (!table.count(temp)) table.insert(temp);
			return table.find(temp)->second;
		}
		size_t count(const F& item)
		{
			return table.count(obj(item, S()));
		}
		iterator find(const F& item)
		{
			return iterator(table.find(obj(item, S())));
		}
		iterator begin()
		{
			return iterator(table.begin());
		}
		iterator end()
		{
			iterator temp(table.end());
			return temp;
		}
		void clear()
		{
			table.clear();
		}
	};

	template <class F, class S, class _hash_func = _default_hash<F>>
	class unordered_multimap
	{
		friend class _unordered_map_iterator< F, S, _hash_func >;
	public:
		typedef  _default_map_hash<F, S, _hash_func>					hasher;
		typedef  _unordered_map_iterator< F, S, hasher>    iterator;
		typedef  hash_pair<F, S>													obj;
	private:
		_hash_table<obj, hasher> table;


	public:
		unordered_multimap() {}
		unordered_multimap(std::initializer_list<F> list)
		{
			for (auto mov = list.begin(); mov != list.end();++mov)
			{
				table.insert(obj(*mov, S()));
			}
		}
		void insert(const obj& item)
		{
			table.insert(item);
		}
		void insert(const F& item)
		{
			obj temp(item, S());
			table.insert(temp);
		}
		void erase(const F& item)
		{
			table.erase(obj(item, S()));
		}
		void erase(const iterator& item)
		{
			table.erase(item->base);
		}
		iterator find(const F& item)
		{
			return iterator(table.find(obj(item, S())));
		}
		size_t count(const F& item)
		{
			return table.count(obj(item, S()));
		}
		iterator begin()
		{
			return iterator(table.begin());
		}
		iterator end()
		{
			return iterator(table.end());
		}
		void clear()
		{
			table.clear();
		}
	};

}

#endif // !UNORDEREDMAP


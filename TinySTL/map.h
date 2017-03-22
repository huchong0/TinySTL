#pragma once
#ifndef MAP
#define MAP
#include "RBtree.h"
namespace TinySTL
{
	template<class T, class Z>class map;
	template<class T,class Z>
	class map_pair
	{
	public:
		T first;
		Z second;
		map_pair(T first, Z second):first(first),second(second){}
		map_pair(std::pair<T, Z> item) :first(item.first), second(item.second) {}
		map_pair():first(T()){}

		bool operator==(const map_pair<T,Z>& item)const { return first == item.first; }
		bool operator!=(const map_pair<T, Z>& item)const { return first != item.first; }
		bool operator>(const map_pair<T, Z>&  item)const { return first > item.first; }
		bool operator<(const map_pair<T, Z>& item)const { return first < item.first; }
		bool operator>=(const map_pair<T, Z>& item)const { return first >= item.first; }
		bool operator<=(const map_pair<T, Z>& item)const { return first <= item.first; }
		explicit operator std::pair<const T,Z>()const 
		{
			return std::pair<const T, Z>(first, second);
		}
	};


	template<class T, class Z>
	class map_iterator :public std::iterator<std::bidirectional_iterator_tag, map_pair<T,Z>>
	{
		friend class map<T,Z>;
		typedef map_iterator<T,Z>  self;
		typedef map_pair<T, Z> pair;
		RBtree_iterator<pair>  ptr;

	public:
		map_iterator() {}
		map_iterator(const RBtree_iterator<pair>& ptr) :ptr(ptr) {}
		self& operator++()
		{
			++ptr;
			return *this;
		}
		self    operator++(int)
		{
			self temp = *this;
			++temp;
			return temp;
		}
		self& operator--()
		{
			--ptr;
			return *this;
		}
		self    operator--(int)
		{
			self temp = *this;
			--temp;
			return temp;
		}
		bool  operator==(const self& item)
		{
			return ptr == item.ptr;
		}
		bool  operator!=(const self& item)
		{
			return ptr != item.ptr;
		}
		const map_pair< T,Z>&     operator*()
		{
			return *ptr;
		}
		const map_pair<T, Z>&     operator*() const
		{
			return *ptr;
		}

		map_pair<T, Z>*	operator->()
		{
			return &(*ptr);
		}
	};
	
	template<class T,class Z>
	class map
	{
	public:
		typedef map_iterator<T,Z> iterator;
	private:
		RBtree<map_pair<T, Z>> tree;
	public:
		map() {}

		void insert(const std::pair<T, Z>& item)
		{
			map_pair<T, Z> temp(item.first, item.second);
			if (tree.find(temp) == tree.end())tree.insert(temp);
		}
		void erase(const T& item)
		{
			map_pair<T, Z> temp(item, Z());
			auto pos = tree.find(temp);
			if (pos != tree.end())tree.erase(pos);
		}
		void erase(const iterator& iter)
		{
			tree.erase(iter->ptr);
		}
		size_t size() { return tree.size(); }
		bool empty() { return tree.empty(); }
		iterator lower_bound(const T& item)
		{
			map_pair<T, Z> temp(item, Z());
			return tree.lower_bound(temp);
		}
		iterator upper_bound(const T& item)
		{
			map_pair<T, Z> temp(item, Z());
			return tree.upper_bound(temp);
		}
		iterator find(const T& item)
		{
			map_pair<T, Z> temp(item, Z());
			return tree.find(temp);
		}
		Z& operator[](const T& item)
		{
			map_pair<T, Z> temp(item, Z());
			iterator pos = tree.find(temp);
			if (pos == tree.end())
			{
				tree.insert(temp);
				pos = tree.find(temp);
			}
			return  *(&pos->second);
		}
		iterator begin()
		{
			return iterator(tree.begin());
		}
		iterator end()
		{
			return iterator(tree.end());
		}
		void clear()
		{
			tree.clear();
		}

	};

	template<class T, class Z>
	class multimap
	{
	public:
		typedef map_iterator<T,Z> iterator;
	private:
		RBtree<map_pair<T, Z>> tree;
	public:
		void insert(const std::pair<T, Z>& item)
		{
			map_pair<T, Z> temp(item.first, item.second);
			tree.insert(temp);
		}
		void erase(const T& item)
		{
			map_pair<T, Z> temp(item, Z());
			auto pos = tree.find(temp);
			if (pos != tree.end())tree.erase(pos);
		}
		void erase(const iterator& iter)
		{
			tree.erase(iter->ptr);
		}
		size_t size() { return tree.size(); }
		bool empty() { return tree.empty(); }
		iterator lower_bound(const T& item)const
		{
			map_pair<T, Z> temp(item, Z());
			return tree.lower_bound(temp);
		}
		iterator upper_bound(const T& item)const
		{
			map_pair<T, Z> temp(item, Z());
			return tree.upper_bound(temp);
		}
		iterator find(const T& item)
		{
			map_pair<T, Z> temp(item, Z());
			return tree.find(temp);
		}
		iterator begin()
		{
			return iterator(tree.begin());
		}
		iterator end()
		{
			return iterator(tree.end());
		}
		void clear()
		{
			tree.clear();
		}

	};
}




#endif // !MAP


#pragma once
#ifndef SET
#define SET
#include "RBtree.h"


namespace TinySTL
{
	template<class T> 
	class set_iterator;

	template <class T>  
	class set
	{
	public:
		typedef set_iterator<T> iterator;
		typedef RBtree_iterator<T> iterator_base;

	private:
		RBtree<T> tree;
	public:
		set() {}
		set(std::initializer_list<T>list)
		{
			for (auto mov = list.begin(); mov != list.end(); ++mov)
			{
				insert(*mov);
			}
		}
		set( set<T>& item)
		{
			for (iterator mov = item.begin(); mov != item.end(); ++mov)
			{
				insert(*mov);
			}
		}
		set<T>& operator=(const set<T>& item)
		{
			clear();
			for (auto mov = item.begin(); mov != item.end(); ++item)
			{
				insert(*mov);
			}
		}
		void insert(const T& item)
		{
			if (tree.find(item) == tree.end())tree.insert(item);
		}
		void erase(const T& item)
		{
			auto pos = tree.find(item);
			if (pos != tree.end())tree.erase(pos);
		}
		void erase(const iterator& item)
		{
			tree.erase(item.ptr);
		}
		size_t size() { return tree.size(); }
		size_t count(const T& item)
		{
			return tree.count(item);
		}
		bool empty() { return tree.empty(); }
		iterator lower_bound(const T& item)
		{
			return iterator((tree.lower_bound(item)));
		}
		iterator upper_bound(const T& item)
		{
			return iterator((tree.upper_bound(item)));
		}
		iterator find(const T& item)
		{
			return iterator((tree.find(item)));
		}
		iterator begin() { return iterator((tree.begin())); }
		iterator end() { return iterator((tree.end())); }

		void clear() { tree.clear(); }
	};

	template <class T>
	class multiset
	{
	public:
		typedef set_iterator<T>  iterator;
		typedef RBtree_iterator<T> iterator_base;
	private:
		RBtree<T> tree;
	public:
		multiset() {}
		multiset(std::initializer_list<T>list)
		{
			for (auto mov = list.begin(); mov != list.end(); ++mov)
			{
				insert(*mov);
			}
		}
		void insert(const T& item)
		{
			tree.insert(item);
		}
		void erase(const T& item)
		{
			tree.erase(item);
		}
		void erase(const iterator& item)
		{
			tree.erase(item.ptr);
		}
		size_t size() { return tree.size(); }
		bool empty() { return tree.empty(); }
		iterator lower_bound(const T& item)
		{
			return iterator((tree.lower_bound(item)));
		}
		iterator upper_bound(const T& item)
		{
			return iterator((tree.upper_bound(item)));
		}
		iterator find(const T& item)
		{
			return iterator((tree.find(item)));
		}
		size_t	count(const T& item)
		{
			return tree.count(item);
		}
		iterator begin() { return iterator((tree.begin())); }
		iterator end() { return iterator((tree.end())); }
		void clear()
		{
			tree.clear();
		}

	};

	template <class T>
	class set_iterator:public std::iterator<std::bidirectional_iterator_tag,T>
	{
		friend class set<T>;
		friend class multiset<T>;
		typedef set_iterator<T> self;
		RBtree_iterator<T> ptr;

	public:
		set_iterator() {}
		set_iterator(const RBtree_iterator<T>& ptr):ptr(ptr) {}
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
		const T&     operator*()
		{
			return *ptr;
		}
		const T*		  operator->()
		{
			return &ptr;
		}
	};
}
#endif // !SET


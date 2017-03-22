#pragma once
#ifndef ITERATOR
#define ITERATOR

#include <memory>//for ptrdiff_t

namespace TinySTL
{

	class input_iterator_tag
	{

	};

	class output_iterator_tag
	{

	};

	class forward_iterator_tag
	{

	};

	class bidirectional_iterator_tag :public forward_iterator_tag
	{

	};

	class random_access_iterator_tag :public bidirectional_iterator_tag
	{

	};

	template
		<
		class T,
		class Category,
		class Pointer = T*,
		class Reference = T&,
		class Distance = ptrdiff_t
		>
		class iterator
	{
	public:
		typedef T						value_type;
		typedef Category			iterator_category;
		typedef Pointer			pointer;
		typedef Reference		reference;
		typedef Distance			differece_type;
	};

	template<class T>
	class iterator_traits
	{
		typedef	typename T::value_type			value_type;
		typedef	typename T::pointer					pointer;
		typedef	typename T::reference				reference;
		typedef	typename T::difference_type	difference_type;
		typedef	typename	T::category				iterator_category;
	};

	template<class T>
	class iterator_traits<T*>
	{
		typedef	typename T								value_type;
		typedef	typename T*							pointer;
		typedef	typename T&							reference;
		typedef	typename ptrdiff_t					difference_type;
		typedef	typename	random_access_iterator_tag iterator_category;
	};

	template<class T>
	class iterator_traits<const T*>
	{
		typedef	typename T								value_type;
		typedef	typename const T*							pointer;
		typedef	typename const T&							reference;
		typedef	typename ptrdiff_t					difference_type;
		typedef	typename	random_access_iterator_tag iterator_category;
	};

	template<class InputIterator, class Distance>
	void _advance(InputIterator iter, Distance n, input_iterator_tag)
	{
		while (n--)++iter;
	}

	template<class ForwardIterator, class Distance>
	void _advance(ForwardIterator iter, Distance n, forward_iterator_tag)
	{
		while (n--)++iter;
	}

	template<class BidirectionalIterator, class Distance>
	void _advance(BidirectionalIterator iter, Distance n, bidirectional_iterator_tag)
	{
		if (n > 0) while (n--)++iter;
		else while (n++)--iter;
	}
	
	template<class RandomAccessIterator, class Distance>
	void _advance(RandomAccessIterator iter, Distance n, random_access_iterator_tag)
	{
		iter += n;
	}

}
#endif // !ITERATOR


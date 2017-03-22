#pragma once
#ifndef ALLOCATOR
#define ALLOCATOR

#include<new.h>
#include<iostream>
#include<memory>//for fill


namespace TinySTL
{
	template<class T>
	inline T* _allocate(size_t n,T*)
	{
		set_new_handler(0);
		T* res = (T*)operator new((size_t)(sizeof(T)*n));
		if (res == 0)
		{
			std::cerr << "not enough memory";
			exit(0);
		}
		return res;
	}

	template<class T>
	inline void _deallocate(T* buffer)
	{
		operator delete(buffer);
	}

	template<class T1,class T2>
	inline void _construct(T1* ptr, T2 value)
	{
		new(ptr) T1(value);
	}

	template<class T>
	inline void _destroy(T* ptr)
	{
		ptr->~T();
	}



	template<class T>
	class allocator
	{
	public:
		typedef		T					value_type;
		typedef		T*					pointer;
		typedef		const T*		const_pointer;
		typedef		T&				reference;
		typedef		const T&		const_reference;
		typedef		size_t			size_type;
		typedef		ptrdiff_t			difference_type;

		pointer allocate(size_type n)
		{
			return _allocate(n, (pointer)0);
		}

		void deallocate(pointer buffer)
		{
			_deallocate(buffer);
		}

		void construct(pointer p, const value_type& value)
		{
			_construct(p, value);
		}

		void destroy(pointer p)
		{
			_destroy(p);
		}
		
		void destroy(pointer beg, pointer end)
		{
			for (; beg != end; ++beg)
			{
				_destroy(beg);
			}
		}

	};



}

#endif // !ALLOCATOR


#pragma once
#ifndef ALGORITHM
#define ALGORITHM
#include <iterator>
namespace TinySTL
{
	template <class T>
	T min(const T& x, const T& y)
	{
		if (x < y)return x;
		else return y;
	}

	template <class T,class op>
	T min(const T& x, const T& y, const op& cmp)
	{
		if (cmp(x,y))return x;
		else return y;
	}

	template <class T>
	T max(const T& x, const T& y)
	{
		if (x < y)return y;
		else return x;
	}

	template <class T, class op>
	T max(const T& x, const T& y, const op& cmp)
	{
		if (cmp(y, x))return x;
		else return y;
	}

	template<class T>
	void swap(T& x, T& y)
	{
		T temp = x;
		x = y;
		y = temp;
	}

	template <class ITER,class OP>
	void for_each(const ITER&  beg,const ITER& end,const OP &op)
	{
		auto mov = beg;
		for (; mov != end; ++mov)
		{
			op(*mov);
		}
	}

	template <class ITER, class VAL>
	void count(const ITER&  beg, const ITER& end, const VAL &value)
	{
		auto mov = beg;
		size_t res = 0;
		for (; mov != end; ++mov)
		{
			if (*mov == value)++res;
		}
		return res;
	}

	template <class ITER, class OP>
	void count_if(const ITER&  beg, const ITER& end, const OP &op)
	{
		auto mov = beg;
		size_t res = 0;
		for (; mov != end; ++mov)
		{
			if (op(*mov))++res;
		}
		return res;
	}

	template <class ITER>
	ITER min_element(const ITER&  beg, const ITER& end)
	{
		auto mov = beg;
		++mov;
		auto res = beg;
		for (; mov != end; ++mov)
		{
			if (*mov<*res)res = mov;
		}
		return res;
	}
	template <class ITER, class OP>
	ITER min_element(const ITER&  beg, const ITER& end, const OP &cmp)
	{
		auto mov = beg;
		++mov;
		auto res = beg;
		for (; mov != end; ++mov)
		{
			if (cmp(*mov, *res))res = mov;
		}
		return res;
	}

	template <class ITER>
	ITER max_element(const ITER&  beg, const ITER& end)
	{
		auto mov = beg;
		++mov;
		auto res = beg;
		for (; mov != end; ++mov)
		{
			if (*res < *mov)res = mov;
		}
		return res;
	}
	template <class ITER, class OP>
	ITER max_element(const ITER&  beg, const ITER& end, const OP &cmp)
	{
		auto mov = beg;
		++mov;
		auto res = beg;
		for (; mov != end; ++mov)
		{
			if (cmp(*res, *mov))res = mov;
		}
		return res;
	}

	template<class ITER>
	std::pair<ITER, ITER> minmax_element(const ITER&  beg, const ITER& end)
	{
		std::pair<ITER, ITER> res(beg,beg);
		auto mov = beg;
		for (mov ;mov!=end;++mov)
		{
			typename std::iterator_traits<ITER>::value_type Tmin, Tmax;
			auto next =mov;
			++next;
			if (next == end)
			{
				break;
			}
			if (*mov < *next)
			{
				if (*mov < *res.first)res.first = mov;
				if (*res.second < *next)res.second = next;
			}
			else
			{
				if (*next < *res.first)res.first = next;
				if (*res.second < *mov)res.second = mov;
			}
			++mov;
		}
		if (mov != end)
		{
			if (*mov > *res.second)res.second = mov;
			else if (*mov < *res.first)res.first = mov;
		}
		return res;
	}
	template<class ITER, class OP>
	std::pair<ITER, ITER> minmax_element(const ITER&  beg, const ITER& end, const OP& cmp)
	{
		std::pair<ITER, ITER> res(beg, beg);
		auto mov = beg;
		for ( mov ; mov != end; ++mov)
		{
			typename std::iterator_traits<ITER>::value_type Tmin, Tmax;
			auto next = mov;
			++next;
			if (next == end)
			{
				break;
			}
			if (cmp(*mov , *next))
			{
				if (cmp(*mov , *res.first))res.first = mov;
				if (cmp(*res.second , *next))res.second = next;
			}
			else
			{
				if (cmp(*next , *res.first))res.first = next;
				if (cmp(*res.second , *mov))res.second = mov;
			}
			++mov;
		}
		if (mov != end)
		{
			if (cmp(*mov , *res.second))res.second = mov;
			else if (cmp(*mov , *res.first))res.first = mov;
		}
		return res;
	}

	template <class ITER,class T>
	ITER find(const ITER&  beg, const ITER& end, const T& val)
	{
		for (auto mov = beg; mov != end; ++mov)
		{
			if (*mov == val)return mov;
		}
		return end;
	}

	template <class ITER, class OP>
	ITER find_if(const ITER&  beg, const ITER& end, const OP& cmp)
	{
		for (auto mov = beg; mov != end; ++mov)
		{
			if (cmp(*mov))return mov;
		}
		return end;
	}

	template <class ITER, class OP>
	ITER find_if_not(const ITER&  beg, const ITER& end, const OP& ncmp)
	{
		for (auto mov = beg; mov != end; ++mov)
		{
			if (!ncmp(*mov))return mov;
		}
		return end;
	}

	template <class ITER, class T>
	ITER search_n(const ITER&  beg, const ITER& end, size_t count, const T& val)
	{
		for (auto mov = beg; mov != end;++mov)
		{
			if (*mov == val)
			{
				size_t num = count-1;
				auto i = ++mov;
				for ( i ; mov != end; ++i)
				{
					if (*i == val)--count;
					else break;
					if (num == 0)return mov;
				}
				mov = i;
				if (mov == end)break;
			}
		}
		return end;
	}
	template <class ITER,class T, class BINARY_FUNC>
	ITER search_n(const ITER&  beg, const ITER& end, size_t count, const T& val, const BINARY_FUNC& op)
	{
		for (auto mov = beg; mov != end; ++mov)
		{
			if (op(*mov,val))
			{
				size_t num = count - 1;
				auto i = ++mov;
				for (i; mov != end; ++i)
				{
					if (op(*i,val))--count;
					else break;
					if (num == 0)return mov;
				}
				mov = i;
				if (mov == end)break;
			}
		}
		return end;
	}

	template <class ITER1, class ITER2>
	ITER1 search(const ITER1&  beg, const ITER1& end, const ITER2&  search_beg, const ITER2& search_end)
	{
		for (auto mov = beg; mov != end; ++mov)
		{
			auto temp = mov;
			for (auto i = search_beg; i != search_end; ++i)
			{
				if (temp == end)return end;
				if (*temp != *i)break;
				++temp;
			}
			return mov;
		}
		return end;
	}
	template <class ITER1, class ITER2,class OP>
	ITER1 search(const ITER1&  beg, const ITER1& end, const ITER2&  search_beg, const ITER2& search_end, const OP& cmp)
	{
		for (auto mov = beg; mov != end; ++mov)
		{
			auto temp = mov;
			for (auto i = search_beg; i != search_end; ++i)
			{
				if (temp == end)return end;
				if (!cmp(*temp , *i))break;
				++temp;
			}
			return mov;
		}
		return end;
	}

	template <class ITER1, class ITER2>
	ITER1 find_end(const ITER1&  beg, const ITER1& end, const ITER2&  search_beg, const ITER2& search_end)
	{
		auto res = end;
		for (auto mov = beg; mov != end; ++mov)
		{
			auto temp = mov;
			for (auto i = search_beg; i != search_end; ++i)
			{
				if (temp == end)return end;
				if (*temp != *i)break;
				++temp;
			}
			res = mov;
		}
		return res;
	}
	template <class ITER1, class ITER2, class OP>
	ITER1 find_end(const ITER1&  beg, const ITER1& end, const ITER2&  search_beg, const ITER2& search_end, const OP& cmp)
	{
		auto res = end;
		for (auto mov = beg; mov != end; ++mov)
		{
			auto temp = mov;
			for (auto i = search_beg; i != search_end; ++i)
			{
				if (temp == end)return end;
				if (!cmp(*temp, *i))break;
				++temp;
			}
			res = mov;
		}
		return res;
	}

	template <class ITER1, class ITER2>
	ITER1 find_first_of(const ITER1&  beg, const ITER1& end, const ITER2&  search_beg, const ITER2& search_end)
	{
		for (auto mov = beg; mov != end; ++mov)
		{
			for (auto i = search_beg; i != search_end; ++i)
			{
				if (*mov == *i)return mov;
			}
		}
		return end;
	}
	template <class ITER1, class ITER2,class OP>
	ITER1 find_first_of(const ITER1&  beg, const ITER1& end, const ITER2&  search_beg, const ITER2& search_end, const OP& cmp)
	{
		for (auto mov = beg; mov != end; ++mov)
		{
			for (auto i = search_beg; i != search_end; ++i)
			{
				if (cmp(*mov , *i))return mov;
			}
		}
		return end;
	}

	template <class ITER>
	ITER adjacent_find(const ITER&  beg, const ITER& end)
	{
		for (auto mov = beg; mov != end; ++mov)
		{
			auto next = mov;
			++next;
			if (next == end)return;
			if (*next == *mov)return mov;
		}
		return end;
	}
	template <class ITER,class OP>
	ITER adjacent_find(const ITER&  beg, const ITER& end, const OP& cmp)
	{
		for (auto mov = beg; mov != end; ++mov)
		{
			auto next = mov;
			++next;
			if (next == end)return;
			if (cmp(*next , *mov))return mov;
		}
		return end;
	}

	template <class ITER1, class ITER2>
	bool equal(const ITER1&  beg, const ITER1& end, const ITER2&  cmp_beg)
	{
		auto cmp_mov = cmp_beg;
		for (auto mov = beg; mov != end; ++mov)
		{
			if (*cmp_mov != *mov)return false;
			++cmp_mov;
		}
		return true;
	}
	template <class ITER1, class ITER2,class OP>
	bool equal(const ITER1&  beg, const ITER1& end, const ITER2&  cmp_beg, const OP& cmp)
	{
		auto cmp_mov = cmp_beg;
		for (auto mov = beg; mov != end; ++mov)
		{
			if (cmp(*mov , *cmp_beg))return false;
			++cmp_mov;
		}
		return true;
	}

	template<class ITER1, class ITER2>
	bool is_permutation(const ITER1&  beg, const ITER1& end, const ITER2&  cmp_beg)
	{
		auto start = mismatch(beg, end, cmp_beg);
		auto start1 = start.first;
		auto start2 = start.second;
		auto end1 = end;
		auto end2 = start2;
		advance(end2, distance(beg, end));
		for (auto mov = start1; mov != end1; ++mov)
		{
			if (find(start1, mov, *mov) == mov)
			{
				size_t n = count(start2, end2,*mov);
				if (n == 0 || count(mov, end1,*mov) != n)return false;
			}
		}
		return true;
	}
	template<class ITER1, class ITER2, class OP>
	bool is_permutation(const ITER1&  beg, const ITER1& end, const ITER2&  cmp_beg,const OP& cmp)
	{
		auto start = mismatch(beg, end, cmp_beg, cmp);
		auto start1 = start.first;
		auto start2 = start.second;
		auto end1 = end;
		auto end2 = start2;
		advance(end2, distance(beg, end));
		for (auto mov = start1; mov != end1; ++mov)
		{
			if (find_if(start1, mov, *mov, cmp) == mov)
			{
				size_t n = count_if(start2, end2, cmp);
				if (n == 0 || count_if(mov, end1, cmp) != n)return false;
			}
		}
		return true;
	}

	template<class ITER1, class ITER2>
	std::pair<ITER1, ITER2> mismatch(const ITER1&  beg, const ITER1& end, const ITER2&  cmp_beg)
	{
		auto mov2 = cmp_beg;
		for (auto mov1 = beg; beg != end; ++mov1,++mov2)
		{
			if (*mov1 != *mov2)
			{
				return make_pair(mov1, mov2);
			}
		}
		return make_pair(end, mov2);
	}
	template<class ITER1, class ITER2, class OP>
	std::pair<ITER1, ITER2> mismatch(const ITER1&  beg, const ITER1& end, const ITER2&  cmp_beg,const OP& cmp)
	{
		auto mov2 = cmp_beg;
		for (auto mov1 = beg; beg != end; ++mov1, ++mov2)
		{
			if (!cmp(*mov1 , *mov2))
			{
				return make_pair(mov1, mov2);
			}
		}
		return make_pair(end, mov2);
	}

	template<class ITER>
	ptrdiff_t distance(const ITER&  beg, const ITER& end)
	{
		return _distance(beg, end,typename std::iterator_traits<ITER>::iterator_category());
	}
	template<class ITER>
	ptrdiff_t _distance(const ITER&  beg, const ITER& end, std::random_access_iterator_tag)
	{
		return end - beg;
	}
	template<class ITER>
	ptrdiff_t _distance(const ITER&  beg, const ITER& end, std::forward_iterator_tag)
	{
		ptrdiff_t res=0;
		for (auto mov = beg; mov != end; ++mov)
		{
			++res;
		}
		return res;
	}

	template<class ITER>
	ITER advance( ITER&  beg, ptrdiff_t length)
	{
		return _advance(beg, end, typename std::iterator_traits<ITER>::iterator_category());
	}
	template<class ITER>
	ITER _advance( ITER&  beg, ptrdiff_t length, std::random_access_iterator_tag)
	{
		return beg += length;
	}
	template<class ITER>
	ITER _advance( ITER&  beg, ptrdiff_t length, std::forward_iterator_tag)
	{
		for (ptrdiff_t i = 0; i < length; ++i)
		{
			++beg;
		}
		return beg;
	}
	template<class ITER>
	ITER _advance(ITER&  beg, ptrdiff_t length, std::bidirectional_iterator_tag)
	{
		if (length > 0)
		{
			for (ptrdiff_t i = 0; i < length; ++i)
			{
				++beg;
			}
		}
		else
		{
			for (ptrdiff_t i = 0; i < length; ++i)
			{
				--beg;
			}
		}
		return beg;
	}

	template <class ITER1, class ITER2>
	bool lexicographical_compare(const ITER1&  beg1, const ITER1& end1, const ITER2&  beg2, const ITER2&  end2)
	{
		auto mov1 = beg1;
		auto mov2 = beg2;
		for (mov1; mov1 != end1; ++mov1,++mov2)
		{
			if (mov2 == end2)return false;
			if (*mov1 < *mov2)return true;
			if (*mov2 < *mov1)return false;
		}
		if (mov2 == end2)return false;
		return true;
	}
	template <class ITER1, class ITER2, class OP>
	bool lexicographical_compare(const ITER1&  beg1, const ITER1& end1, const ITER2&  beg2, const ITER2&  end2,const OP& cmp)
	{
		auto mov1 = beg1;
		auto mov2 = beg2;
		for (mov1; mov1 != end1; ++mov1, ++mov2)
		{
			if (mov2 == end2)return false;
			if (cmp(*mov1 , *mov2))return true;
			if (cmp(*mov2 , *mov1))return false;
		}
		if (mov2 == end2)return false;
		return true;
	}

	template<class ITER>
	bool is_sorted(ITER  beg, ITER end)
	{
		if (beg == end)return true;
		auto next = beg;
		++next;
		for (; next != end; ++beg, ++next)
		{
			if (*next < *beg)return false;
		}
		return true;
	}
	template<class ITER,class OP>
	bool is_sorted(ITER  beg, ITER end,const OP& cmp)
	{
		if (beg == end)return true;
		auto next = beg;
		++next;
		for (; next != end; ++beg, ++next)
		{
			if (cmp(*next , *beg))return false;
		}
		return true;
	}

	template<class ITER>
	ITER is_sorted_until(ITER  beg, ITER end)
	{
		if (beg == end)return true;
		auto next = beg;
		++next;
		for (; next != end; ++beg, ++next)
		{
			if (*next < *beg)return next;
		}
		return end;
	}
	template<class ITER, class OP>
	ITER is_sorted_until(ITER  beg, ITER end, const OP& cmp)
	{
		if (beg == end)return true;
		auto next = beg;
		++next;
		for (; next != end; ++beg, ++next)
		{
			if (cmp(*next , *beg))return next;
		}
		return end;
	}

	template<class ITER,class OP>
	bool is_partitioned(ITER  beg, ITER end, const OP& cmp)
	{
		if (beg == end)return true;
		auto next = beg;
		++next;
		bool res = false;
		for (next; next != end; ++beg, ++next)
		{
			if (!res)
			{
				if (cmp(*beg, *next))res = true;
			}
			else
			{
				if (cmp(*next, *beg))return false;
			}
		}
		return res;
	}

	template<class ITER, class OP>
	ITER _partition_point(ITER  beg, ITER end, const OP& cmp)
	{
		if (beg == end)return end;
		auto next = beg;
		++next;
		for (next; next != end; ++beg, ++next)
		{
			if (cmp(*beg, *next))return next;
		}
		return res;
	}

	template<class ITER>
	bool is_heap(ITER  beg, ITER end)
	{
		size_t length = end - beg;
		for (size_t i = i; i < length;++i)
		{
			if (*(beg + i) < *(beg + (i - 1) / 2))return false;
		}
		return true;
	}
	template<class ITER, class OP>
	bool is_heap(ITER  beg, ITER end,const OP& cmp)
	{
		size_t length = end - beg;
		for (size_t i = i; i < length; ++i)
		{
			if (cmp(*(beg + i) < *(beg + (i - 1) / 2)))return false;
		}
		return true;
	}

	template<class ITER>
	ITER is_heap_until(ITER  beg, ITER end)
	{
		size_t length = end - beg;
		for (size_t i = i; i < length; ++i)
		{
			if (*(beg + i) < *(beg + (i - 1) / 2))return beg+i;
		}
		return end;
	}
	template<class ITER,class OP>
	ITER is_heap_until(ITER  beg, ITER end,const OP& cmp)
	{
		size_t length = end - beg;
		for (size_t i = i; i < length; ++i)
		{
			if (cmp(*(beg + i) , *(beg + (i - 1) / 2)))return beg + i;
		}
		return end;
	}

	template<class ITER, class OP>
	bool all_of(ITER  beg, ITER end,const OP& cmp)
	{
		for (beg; beg != end; ++beg)
		{
			if (!cmp(*beg))return false;
		}
		return true;
	}

	template<class ITER, class OP>
	bool any_of(ITER  beg, ITER end, const OP& cmp)
	{
		for (beg; beg != end; ++beg)
		{
			if (cmp(*beg))return true;
		}
		return false;
	}

	template<class ITER, class OP>
	bool none_of(ITER  beg, ITER end, const OP& cmp)
	{
		for (beg; beg != end; ++beg)
		{
			if (cmp(*beg))return false;
		}
		return true;
	}

	template<class input_ITER,class output_ITER>
	output_ITER copy(input_ITER  beg, input_ITER end, output_ITER destBeg)
	{
		for (beg; beg != end; ++beg, ++destBeg)
		{
			*destBeg = *beg;
		}
		return destBeg;
	}
	 
	template<class input_ITER, class output_ITER>
	output_ITER copy_n(input_ITER  beg, size_t num, output_ITER destBeg)
	{
		for (size_t i = 0; i < num; ++i, ++beg, ++destBeg)
		{
			*destBeg = *beg;
		}
		return destBeg;
	}

	template<class input_ITER, class output_ITER,class OP>
	output_ITER copy_if(input_ITER  beg, size_t num, output_ITER destBeg,const OP& cmp)
	{
		for (beg; beg != end; ++beg)
		{
			if (cmp(*beg))
			{
				*destBeg = *beg;
				++destBeg;
			}
		}
		return destBeg;
	}

	template<class bidirectional_ITER1, class bidirectional_ITER2>
	bidirectional_ITER2 copy_backward(bidirectional_ITER1  beg, bidirectional_ITER1 end, bidirectional_ITER2 destEnd)
	{
		--end;
		--destEnd;
		for (end; end != beg; --end,--destEnd)
		{
			*destEnd = *end;
		}
		*destEnd = *end;
		return --destEnd;
	}

	template<class input_ITER, class output_ITER>
	output_ITER move(input_ITER  beg, input_ITER end, output_ITER destBeg)
	{
		for (beg; beg != end; ++beg, ++destBeg)
		{
			*destBeg = std::move(*beg);
		}
		return destBeg;
	}

	template<class bidirectional_ITER1, class bidirectional_ITER2>
	bidirectional_ITER2 move_backward(bidirectional_ITER1  beg, bidirectional_ITER1 end, bidirectional_ITER2 destEnd)
	{
		--end;
		--destEnd;
		for (end; end != beg; --end, --destEnd)
		{
			*destEnd = std::move(*end);
		}
		*destEnd = std::move(*end);
		return --destEnd;
	}

	template<class input_ITER, class output_ITER,class UNARY_OP>
	output_ITER transform(input_ITER  beg, input_ITER end, output_ITER destBeg,const UNARY_OP& op)
	{
		for (beg; beg != end; ++beg, ++destBeg)
		{
			*destBeg = op(*beg);
		}
		return destBeg;
	}
	template<class input_ITER1,class input_ITER2, class output_ITER, class BINARY_OP>
	output_ITER transform(input_ITER1  beg1, input_ITER1 end1, input_ITER2 beg2, output_ITER destBeg, const BINARY_OP& op)
	{
		for (beg1; beg1 != end1; ++beg1,++beg2, ++destBeg)
		{
			*destBeg = op(*beg1,*beg2);
		}
		return destBeg;
	}

	template<class forward_ITER1, class forward_ITER2>
	forward_ITER2 swap_ranges(forward_ITER1 beg1, forward_ITER1 end1, forward_ITER2 beg2)
	{
		for (beg1; beg1 != end1; ++beg1, ++beg2)
		{
			auto temp = *beg1;
			*beg1 = *beg2;
			*beg2 = temp;
		}
		return beg2;
	}

	template<class forward_ITER,class T>
	void fill(forward_ITER beg, forward_ITER end, const T& val)
	{
		for (beg; beg != end; ++beg)
		{
			*beg = val;
		}
	}

	template<class forward_ITER, class T>
	void fill_n(forward_ITER beg, size_t num, const T& val)
	{
		for (size_t i = 0; i < num; ++i)
		{
			*(beg + i) = val;
		}
	}

	template<class forward_ITER, class func>
	void generate(forward_ITER beg, forward_ITER end, const func& op)
	{
		for (beg; beg != end; ++beg)
		{
			*beg = op();
		}
	}

	template<class forward_ITER, class func>
	void generate_n(forward_ITER beg, size_t num, const func& op)
	{
		for (size_t i = 0; i < num; ++i)
		{
			*(beg + i) = op();
		}
	}

	template<class forward_ITER, class T>
	void iota(forward_ITER beg, forward_ITER end, T val)
	{
		for (beg; beg != end; ++beg)
		{
			*beg = val++;
		}
	}

	template<class forward_ITER,class T>
	void replace(forward_ITER beg, forward_ITER end, const T& old_value, const T& new_value)
	{
		for (beg; beg != end; ++beg)
		{
			if (*beg == old_value)*beg = new_value;
		}
	}

	template<class forward_ITER, class T,class UNARY_FUNC>
	void replace_if(forward_ITER beg, forward_ITER end, const UNARY_FUNC& op, const T& new_value)
	{
		for (beg; beg != end; ++beg)
		{
			if (op(*beg))*beg = new_value;
		}
	}

	template<class input_ITER1, class output_ITER2, class T>
	void replace_copy(input_ITER1 beg, input_ITER1 end, output_ITER2 dest_beg, const T& old_val, const T& new_val)
	{
		for (beg; beg != end; ++beg, ++dest_beg)
		{
			if (*beg == old_val)*dest_beg = new_val;
			else *dest_beg = *beg;
		}
	}

	template<class input_ITER1, class output_ITER2, class UNARY_FUNC, class T>
	void replace_copy_if(input_ITER1 beg, input_ITER1 end, output_ITER2 dest_beg, const UNARY_FUNC& op, const T& new_val)
	{
		for (beg; beg != end; ++beg, ++dest_beg)
		{
			if (op(*beg))*dest_beg = new_val;
			else *dest_beg = *beg;
		}
	}

	template<class forward_ITER,class T>
	void remove(forward_ITER beg, forward_ITER end, const T& val)
	{
		auto start = find(beg, end, val);
		for (auto mov = start; mov != end; ++mov)
		{
			if (*start != val)
			{
				*start = *mov;
				++start;
			}
		}
		return start;
	}

	template<class forward_ITER, class UNARY_FUNC>
	void remove_if(forward_ITER beg, forward_ITER end, const UNARY_FUNC& op)
	{
		auto start = find_if(beg, end, op);
		for (auto mov = start; mov != end; ++mov)
		{
			if (op(*start))
			{
				*start = *mov;
				++start;
			}
		}
		return start;
	}

	template<class input_ITER, class output_ITER, class T>
	output_ITER remove_copy(input_ITER beg, input_ITER end, output_ITER dest_beg, const T& val)
	{
		auto start = find(beg, end, val);
		for (auto mov = start; mov != end; ++mov)
		{
			if (*start != val)
			{
				*start = *mov;
				++start;
			}
			else
			{
				*dest_beg = *mov;
				++dest_beg;
			}
		}
		return start;
	}

	template<class input_ITER, class output_ITER, class UNARY_FUNC>
	output_ITER remove_copy_if(input_ITER beg, input_ITER end, output_ITER dest_beg, const UNARY_FUNC& op)
	{
		auto start = find_if(beg, end, op);
		for (auto mov = start; mov != end; ++mov)
		{
			if (op(*start))
			{
				*start = *mov;
				++start;
			}
			else
			{
				*dest_beg = *mov;
				++dest_beg;
			}
		}
		return start;
	}

	template<class forward_ITER>
	forward_ITER unique(forward_ITER beg, forward_ITER end)
	{
		if (beg == end)return end;
		auto temp = *beg;
		++beg;
		for (beg; beg != end; ++beg)
		{
			if (*beg == temp)break;
			temp = *beg;
		}
		auto start = beg;
		for (beg; beg != end; ++beg)
		{
			if (*beg != temp)
			{
				*start = *beg;
				temp = *start;
				++start;
			}
		}
		return start;
	}
	template<class forward_ITER, class BINARY_FUNC>
	forward_ITER unique(forward_ITER beg, forward_ITER end,const BINARY_FUNC& op)
	{
		if (beg == end)return end;
		auto temp = *beg;
		++beg;
		for (beg; beg != end; ++beg)
		{
			if (op(*beg , temp))break;
			temp = *beg;
		}
		auto start = beg;
		for (beg; beg != end; ++beg)
		{
			if (!op(*beg, temp))
			{
				*start = *beg;
				temp = *start;
				++start;
			}
		}
		return start;
	}

	template<class forward_ITER1,class forward_ITER2,class output_ITER>
	output_ITER unique_copy(forward_ITER1 beg, forward_ITER2 end, output_ITER dest_beg)
	{
		if (beg == end)return end;
		auto temp = *beg;
		++beg;
		for (beg; beg != end; ++beg)
		{
			if (*beg != temp)
			{
				*dest_beg = *beg;
				temp = *beg;
				++dest_beg;
			}
		}
		return dest_beg;
	}
	template<class forward_ITER1, class forward_ITER2, class output_ITER, class BINARY_FUNC>
	output_ITER unique_copy(forward_ITER1 beg, forward_ITER2 end, output_ITER dest_beg,const BINARY_FUNC&op)
	{
		if (beg == end)return end;
		auto temp = *beg;
		++beg;
		for (beg; beg != end; ++beg)
		{
			if (!op(*beg , temp))
			{
				*dest_beg = *beg;
				temp = *beg;
				++dest_beg;
			}
		}
		return dest_beg;
	}

	template<class bidirectional_ITER>
	void reverse(bidirectional_ITER beg, bidirectional_ITER end)
	{
		--end;
		for (;;)
		{
			if (beg == end)break;
			auto temp = *beg;
			*beg = *end;
			*end = temp;
			auto next = beg;
			if (++beg == end)break;
			--end;
		}
	}

	template<class bidirectional_ITER1,class output_ITER>
	output_ITER reverse_copy(bidirectional_ITER1 beg, bidirectional_ITER1 end, output_ITER dest_beg)
	{
		--end;
		for (; end != beg; --end, ++dest_beg)
		{
			*dest_beg = *end;
		}
		*dest_beg = *end;
		return ++dest_beg;
	}

	template<class forward_ITER>
	void rotate(forward_ITER beg, forward_ITER new_beg, forward_ITER end)
	{
		reverse(beg, new_beg);
		reverse(new_beg, end);
		reverse(beg, end);
	}

	template<class forward_ITER,class output_ITER>
	void rotate(forward_ITER beg, forward_ITER new_beg, forward_ITER end, output_ITER dest_beg)
	{
		copy(new_beg, end, dest_beg);
		copy(beg, new_beg, dest_beg);
	}

	template<class binary_ITER>
	bool next_permutation(binary_ITER beg, binary_ITER end)
	{
		if (beg == end)return false;
		auto back = end;
		--back;
		for (auto mov = back; mov != beg; --mov)
		{
			auto pre = mov; 
			--pre;
			if (*pre < *mov)
			{
				for (auto mov2 = back; mov2 != pre; --mov2)
				{
					if (*pre < *mov2)
					{
						auto temp = *pre;
						*pre = *mov2;
						*mov2 = temp;
						break;
					}
				}
				reverse(mov, end);
				return true;
			}
		}
		return false;
	}
	template<class binary_ITER,class BINARY_OP>
	bool next_permutation(binary_ITER beg, binary_ITER end, const BINARY_OP& op)
	{
		if (beg == end)return false;
		auto back = end;
		--back;
		for (auto mov = back; mov != beg; --mov)
		{
			auto pre = mov;
			--pre;
			if (op(*pre , *mov))
			{
				for (auto mov2 = back; mov2 != pre; --mov2)
				{
					if (op(*pre , *mov2))
					{
						auto temp = *pre;
						*pre = *mov2;
						*mov2 = temp;
						break;
					}
				}
				reverse(mov, end);
				return true;
			}
		}
		return false;
	}

	template<class binary_ITER>
	bool prev_permutation(binary_ITER beg, binary_ITER end)
	{
		if (beg == end)return false;
		auto back = end;
		--back;
		for (auto mov = back; mov != beg; --mov)
		{
			auto pre = mov;
			--pre;
			if (*mov < *pre)
			{
				for (auto mov2 = back; mov2 != pre; --mov2)
				{
					if (*mov2 < *pre)
					{
						auto temp = *pre;
						*pre = *mov2;
						*mov2 = temp;
						break;
					}
				}
				reverse(mov, end);
				return true;
			}
		}
		return false;
	}
	template<class binary_ITER, class BINARY_OP>
	bool prev_permutation(binary_ITER beg, binary_ITER end, const BINARY_OP& op)
	{
		if (beg == end)return false;
		auto back = end;
		--back;
		for (auto mov = back; mov != beg; --mov)
		{
			auto pre = mov;
			--pre;
			if (op(*mov, *pre))
			{
				for (auto mov2 = back; mov2 != pre; --mov2)
				{
					if (op(*mov2, *pre))
					{
						auto temp = *pre;
						*pre = *mov2;
						*mov2 = temp;
						break;
					}
				}
				reverse(mov, end);
				return true;
			}
		}
		return false;
	}

	template<class random_ITER>
	void sort(random_ITER beg, random_ITER end)
	{
		if (beg >= end)return;
		auto key = *(end - 1);
		auto mid_pos = beg;
		for (auto mov = beg; mov != end; ++mov)
		{
			if (*mov < key)
			{
				swap(*mov, *mid_pos);
				++mid_pos;
			}
		}
		swap(*(end - 1), *mid_pos);
		sort(beg, mid_pos);
		sort(mid_pos + 1, end);
	}
	template<class random_ITER,class BINARY_FUNC>
	void sort(random_ITER beg, random_ITER end,const BINARY_FUNC& op)
	{
		if (beg >= end)return;
		auto key = *(end - 1);
		auto mid_pos = beg;
		for (auto mov = beg; mov != end; ++mov)
		{
			if (op(*mov , key))
			{
				swap(*mov, *mid_pos);
				++mid_pos;
			}
		}
		swap(*(end - 1), *mid_pos);
		sort(beg, mid_pos, op);
		sort(mid_pos + 1, end, op);
	}

	template<class random_ITER>
	void nth_element(random_ITER beg, random_ITER nth, random_ITER end)
	{
		if (beg >= end)return;
		auto key = *(end - 1);
		auto n = nth - beg;
		auto mid_pos = beg;
		for (auto mov = beg; mov != end; ++mov)
		{
			if (*mov < key)
			{
				swap(*mov, *mid_pos);
				++mid_pos;
			}
		}
		swap(*(end - 1), *mid_pos);
		ptrdiff_t mid = mid_pos - beg;
		if (mid == n)return;
		if (mid > n)
		{
			nth_element(beg, n, mid_pos);
		}
		else
		{
			nth_element(mid_pos, n - mid, end);
		}
	}
	template<class random_ITER, class BINARY_FUNC>
	void nth_element(random_ITER beg, random_ITER nth, random_ITER end, const BINARY_FUNC& op)
	{
		if (beg >= end)return;
		auto key = *(end - 1);
		auto n = nth - beg;
		auto mid_pos = beg;
		for (auto mov = beg; mov != end; ++mov)
		{
			if (op(*mov , key))
			{
				swap(*mov, *mid_pos);
				++mid_pos;
			}
		}
		swap(*(end - 1), *mid_pos);
		ptrdiff_t mid = mid_pos - beg;
		if (mid == n)return;
		if (mid > n)
		{
			nth_element(beg, n, mid_pos);
		}
		else
		{
			nth_element(mid_pos, n - mid, end);
		}
	}




}
#endif // !ALGORITHM


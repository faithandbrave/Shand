#ifndef SHAND_COUNTING_INCLUDE
#define SHAND_COUNTING_INCLUDE

//------------------------------------------------------------------//
//																	//
//	関 数 名 : count_range(int first, int last), zero_to(int last)	//
//	用    途 : foreach文用インデックス番号生成						//
//																	//
// Version : 1.00 2007/10/29 作成									//
//			 1.01 2007/11/02 STLアルゴリズムにも適用可にした		//
//																	//
//				Programmed By Akira.T								//
//		Copyright(C) 2007 Akira.T All rights reserved				//
//------------------------------------------------------------------//


#include <iterator>

namespace shand {

template <class Incrementable>
class counting_iterator {
	Incrementable value_;
public:
	typedef std::random_access_iterator_tag iterator_category;
	typedef Incrementable					value_type;
	typedef Incrementable					difference_type;
	typedef Incrementable					pointer;
	typedef Incrementable					reference;

	counting_iterator(Incrementable value): value_(value) {}
	counting_iterator& operator++ () { ++value_; return *this; }
	counting_iterator operator++ (int) { ++value_; return counting_iterator(value_-1); }
	Incrementable operator* () const { return value_; }
	bool operator== (const counting_iterator& rhs) const { return value_ == rhs.value_; }
	bool operator!= (const counting_iterator& rhs) const { return value_ != rhs.value_; }
};

template <class Type>
bool operator<(const counting_iterator<Type>& lhs, const counting_iterator<Type>& rhs)
{
	return *lhs < *rhs;
}


template <class Incrementable>
inline counting_iterator<Incrementable> make_counting_iterator(Incrementable count)
{
	return counting_iterator<Incrementable>(count);
}


template <class Incrementable>
class count_range_t {
	counting_iterator<Incrementable> first_;
	counting_iterator<Incrementable> last_;
public:
	typedef counting_iterator<Incrementable> iterator;
	typedef Incrementable reference;

	count_range_t(Incrementable first, Incrementable last)
		: first_(first), last_(last) {}

	iterator		begin()			{ return first_; }
	iterator		end()			{ return last_; }
	const iterator	begin() const	{ return first_; }
	const iterator	end()	const	{ return last_; }
};


template <class Incrementable>
inline count_range_t<Incrementable> zero_to(Incrementable last)
{
	return count_range_t<Incrementable>(0, last);
}

template <class Incrementable>
inline count_range_t<Incrementable> count_range(Incrementable first, Incrementable last)
{
	return count_range_t<Incrementable>(first, last);
}


} // namespace shand


//----------------------------------------------------------//
// Sample													//
//----------------------------------------------------------//
// vector<int> v;											//
//															//
// // generate 0～9											//
// foreach (int index, zero_to(10)) // count_range(0, 10)	//
//     v.push_back(index);									//
//															//
//----------------------------------------------------------//

#endif // SHAND_COUNTING_INCLUDE


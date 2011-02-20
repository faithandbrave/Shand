#ifndef SHAND_ALGORITHM_INCLUDE
#define SHAND_ALGORITHM_INCLUDE

//------------------------------------------------------//
// Name : アルゴリズム									//
//														//
// Version : 1.00 2007/05/17 作成, mem_find				//
//           1.01 2007/05/24 mem_find(メンバ関数版)作成	//
//			 1.02 2007/09/19 いろいろ + is_sorted追加	//
//			 1.03 2007/10/03 SFINAE版アルゴリズム追加	//
//			 1.04 2007/11/02 erase_if追加				//
//			 1.05 2007/11/22 SFINAEの余計な処理削除		//
//														//
//				Programmed By Akira.T					//
//		Copyright(C) 2007 Akira.T All rights reserved	//
//														//
//------------------------------------------------------//

#include <vector>
#include <string>
#include <iterator>
#include <algorithm>
#include <functional>
#include <utility>


// SFINAEをサポートしているコンパイラか
#if !defined(_MSC_VER) || (_MSC_VER > 1300)  // 1300 == VC++ 7.0
	#define SHAND_SUPPORT_SFINAE
#endif


namespace shand {

//------------------------------------------//
// 名称 : mem_find()						//
// 用途 : メンバ変数の検索					//
// 引数 : first		: 先頭イテレータ		//
//		  last		: 最後尾イテレータ		//
//		  target	: 検索する値			//
//		  member	: メンバ変数へのポインタ//
// 戻値 : 該当イテレータ					//
//------------------------------------------//
template <class Iterator, class Target, class Type, class ClassName>
inline Iterator mem_find(Iterator first, Iterator last, const Target& target, Type ClassName::*member)
{
	while (first != last) {
		if ((*first).*member == target)
			break;
		++first;
	}

	return first;
}


#ifdef SHAND_SUPPORT_SFINAE

template <class ArrayType, int Size, class Target, class Type, class ClassName>
inline ArrayType*
mem_find(ArrayType (&ar)[Size], const Target& target, Type ClassName::*member)
{
	return mem_find(ar, ar + Size, target, member);
}

template <class Container, class Target, class Type, class ClassName>
inline typename Container::iterator
mem_find(Container& container, const Target& target, Type ClassName::*member)
{
	return mem_find(container.begin(), container.end(), target, member);
}

template <class Container, class Target, class Type, class ClassName>
inline typename Container::const_iterator
mem_find(const Container& container, const Target& target, Type ClassName::*member)
{
	return mem_find(container.begin(), container.end(), target, member);
}

#endif // SHAND_SUPPORT_SFINAE

//--------------------------------------------------------------------------//
// sample																	//
//==========================================================================//
// struct hoge {															//
//   string name_;															//
//																			//
//   hoge(const string& name="") : name_(name) {}							//
// };																		//
//																			//
// int main()																//
// {																		//
//   vector<hoge> v;														//
//																			//
//   v.push_back(hoge("Akira"));											//
//   v.push_back(hoge("Johnny"));											//
//   v.push_back(hoge("Sum"));												//
//																			//
//   if (mem_find(v.begin(), v.end(), "Akira", &hoge::name_) != v.end())	//
//     cout << "該当あり" << endl;											//
//   else																	//
//     cout << "該当なし" << endl;											//
//																			//
//   return 0;																//
// }																		//
//--------------------------------------------------------------------------//



//------------------------------------------------------//
// 名称 : mem_find()									//
// 用途 : メンバ変数の検索(メンバ関数版, 非公開メンバ用)//
// 引数 : first		: 先頭イテレータ					//
//		  last		: 最後尾イテレータ					//
//		  target	: 検索する値						//
//		  member	: メンバ変数取得ゲッターへのポインタ//
// 戻値 : 該当イテレータ								//
//------------------------------------------------------//
template <class Iterator, class Target, class Type, class ClassName>
inline Iterator mem_find(Iterator first, Iterator last, const Target& target, Type (ClassName::*member)())
{
	while (first != last) {
		if (((*first).*member)() == target)
			break;
		++first;
	}

	return first;
}

template <class Iterator, class Target, class Type, class ClassName>
inline Iterator mem_find(Iterator first, Iterator last, const Target& target, Type (ClassName::*member)() const)
{
	while (first != last) {
		if (((*first).*member)() == target)
			break;
		++first;
	}

	return first;
}


#ifdef SHAND_SUPPORT_SFINAE

// mem_find...ゲッター版...type getter()
template <class ArrayType, int Size, class Target, class Type, class ClassName>
inline ArrayType*
mem_find(ArrayType (&ar)[Size], const Target& target, Type (ClassName::*member)())
{
	return mem_find(ar, ar + Size, target, member);
}

template <class Container, class Target, class Type, class ClassName>
inline typename Container::iterator
mem_find(Container& container, const Target& target, Type (ClassName::*member)())
{
	return mem_find(container.begin(), container.end(), target, member);
}

template <class Container, class Target, class Type, class ClassName>
inline typename Container::const_iterator
mem_find(const Container& container, const Target& target, Type (ClassName::*member)())
{
	return mem_find(container.begin(), container.end(), target, member);
}

// mem_find...ゲッター版...type getter() const
template <class ArrayType, int Size, class Target, class Type, class ClassName>
inline ArrayType*
mem_find(ArrayType (&ar)[Size], const Target& target, Type (ClassName::*member)() const)
{
	return mem_find(ar, ar + Size, target, member);
}

template <class Container, class Target, class Type, class ClassName>
inline typename Container::iterator
mem_find(Container& container, const Target& target, Type (ClassName::*member)() const)
{
	return mem_find(container.begin(), container.end(), target, member);
}

template <class Container, class Target, class Type, class ClassName>
inline typename Container::const_iterator
mem_find(const Container& container, const Target& target, Type (ClassName::*member)() const)
{
	return mem_find(container.begin(), container.end(), target, member);
}

#endif // SHAND_SUPPORT_SFINAE


//--------------------------------------------------------------------------//
// sample																	//
//==========================================================================//
// class hoge {																//
//   string name_;															//
// public:																	//
//   hoge(const string& name="") : name_(name) {}							//
//   string get_name() const { return name_; }								//
// };																		//
//																			//
// int main()																//
// {																		//
//   vector<hoge> v;														//
//																			//
//   v.push_back(hoge("Akira"));											//
//   v.push_back(hoge("Johnny"));											//
//   v.push_back(hoge("Sum"));												//
//																			//
//   if (mem_find(v.begin(), v.end(), "Akira", &hoge::get_name) != v.end())	//
//     cout << "該当あり" << endl;											//
//   else																	//
//     cout << "該当なし" << endl;											//
//																			//
//   return 0;																//
// }																		//
//--------------------------------------------------------------------------//


//----------------------------------------------//
// 名称 : chain_count()							//
// 用途 : 同じ要素が連続している個数を数える	//
// 引数 : first : 検索対象の先頭イテレータ		//
//		  last  : 検索対象の最後尾イテレータ	//
//		  value : 検索する要素					//
// 戻値 : 連続した個数							//
//----------------------------------------------//
template<class FwdIter, class Type>
inline int chain_count(FwdIter first, FwdIter last, const Type& value)
{
	int count = 0;
	for (; first != last; ++first) {
		if (*first == value)
			count++;
		else {
			if (count != 0)
				break;
		}
	}

	return count;
}

#ifdef SHAND_SUPPORT_SFINAE

template <class ArrayType, int Size, class Type>
inline int chain_count(ArrayType (&ar)[Size], const Type& value)
{
	return chain_count(ar, ar + Size, value);
}

template <class Container, class Type>
inline int chain_count(const Container& contaier, const Type& value)
{
	return chain_count(contaier.begin(), contaier.end(), value);
}

#endif // SHAND_SUPPORT_SFINAE


//----------------------------------------------------------//
// sample													//
//==========================================================//
// int main()												//
// {														//
//     string s("a  b   c");								//
//     int count = chain_count(s.begin(), s.end(), ' ');	//
//															//
//     return 0;											//
// }														//
//----------------------------------------------------------//
// Exclution												//
//==========================================================//
// 2														//
//															//
//----------------------------------------------------------//


//----------------------------------------------//
// 名称 : size_split()							//
// 用途 : 文字列を指定された文字数で分割		//
// 引数 : target : 対象文字列					//
//		  size   : 分割サイズ					//
// 戻値 : 分割された文字列						//
//----------------------------------------------//
template <class TString>
inline std::vector<TString> size_split(const TString& target, int size)
{
	std::vector<TString> splitter;
	TString work;

	for (size_t index = 0; index < target.length(); ++index) {
		work += target[index];

		if ((index + 1) % size == 0 || index >= target.length() -1) {
			splitter.push_back(work);
			work = TString();
		}
	}

	return splitter;
}


//----------------------------------------------//
// 名称 : unique_count()						//
// 用途 : 重複してない数取得					//
// 引数 : first : 先頭要素へのイテレータ		//
//		  last  : 最後尾要素へのイテレータ		//
//		  pred  : 条件関数(オブジェクト)		//
// 戻値 : 重複数								//
// 注意 : ソート済みコンテナである必要がある	//
//----------------------------------------------//
template <class FwdIter>
inline size_t unique_count(FwdIter first, FwdIter last)
{
	std::vector<typename FwdIter::difference_type> uni;

	std::unique_copy(first, last, std::back_inserter(uni));

	return uni.size();
}

template <class FwdIter, class Pred>
inline size_t unique_count(FwdIter first, FwdIter last, Pred pred)
{
	std::vector<typename FwdIter::difference_type> uni;

	std::unique_copy(first, last, std::back_inserter(uni), pred);

	return uni.size();
}


#ifdef SHAND_SUPPORT_SFINAE

template <class Type, int Size>
inline size_t unique_count(Type (&ar)[Size])
{
	return unique_count(ar, ar + Size);
}

template <class Type, int Size, class Pred>
inline size_t unique_count(Type (&ar)[Size], Pred pred)
{
	return unique_count(ar, ar + Size, pred);
}

template <class Container>
inline size_t unique_count(const Container& container)
{
	return unique_count(container.begin(), container.end());
}

template <class Container, class Pred>
inline size_t unique_count(const Container& container, Pred pred)
{
	return unique_count(container.begin(), container.end(), pred);
}

#endif // SHAND_SUPPORT_SFINAE


//----------------------------------------------//
// 名称 : overlap_count()						//
// 用途 : 重複数取得							//
// 引数 : first : 先頭要素へのイテレータ		//
//		  last  : 最後尾要素へのイテレータ		//
//		  pred  : 条件関数(オブジェクト)		//
// 戻値 : 重複数								//
// 注意 : ソート済みコンテナである必要がある	//
//----------------------------------------------//
template <class FwdIter>
inline size_t overlap_count(FwdIter first, FwdIter last)
{
	return std::distance(first, last) - unique_count(first, last);
}

template <class FwdIter, class Pred>
inline size_t overlap_count(FwdIter first, FwdIter last, Pred pred)
{
	return std::distance(first, last) - unique_count(first, last, pred);
}


#ifdef SHAND_SUPPORT_SFINAE

template <class Type, int Size>
inline size_t overlap_count(Type (&ar)[Size])
{
	return overlap_count(ar, ar + Size);
}

template <class Type, int Size, class Pred>
inline size_t overlap_count(Type (&ar)[Size], Pred pred)
{
	return overlap_count(ar, ar + Size, pred);
}

template <class Container>
inline size_t overlap_count(const Container& container)
{
	return overlap_count(container.begin(), container.end());
}

template <class Container, class Pred>
inline size_t overlap_count(const Container& container, Pred pred)
{
	return overlap_count(container.begin(), container.end(), pred);
}

#endif // SHAND_SUPPORT_SFINAE


//--------------------------------------------------//
// 名称 : is_sorted()								//
// 用途 : 範囲がソート済みか調べる					//
// 引数 : first : 先頭要素へのイテレータ			//
//		  last  : 最後尾要素へのイテレータ			//
//		  pred  : 条件関数							//
// 戻値 : true:ソート済み false:ソート済みではない	//
//--------------------------------------------------//
template <class FwdIter, class Pred>
inline bool is_sorted(FwdIter first, FwdIter last, Pred pred)
{
	FwdIter it(first);
    return std::equal(++first, last, it, std::not2(pred));
}

template <class FwdIter>
inline bool is_sorted(FwdIter first, FwdIter last)
{
    typedef typename std::iterator_traits<FwdIter>::value_type value_type;
    return is_sorted(first, last, std::less<value_type>());
}


#ifdef SHAND_SUPPORT_SFINAE

template <class Type, int Size>
inline bool is_sorted(Type (&ar)[Size])
{
	return is_sorted(ar, ar + Size);
}

template <class Type, int Size, class Pred>
inline bool is_sorted(Type (&ar)[Size], Pred pred)
{
	return is_sorted(ar, ar + Size, pred);
}

template <class Container>
inline bool is_sorted(const Container& container)
{
	return is_sorted(container.begin(), container.end());
}

template <class Container, class Pred>
inline bool is_sorted(const Container& container, Pred pred)
{
	return is_sorted(container.begin(), container.end(), pred);
}

#endif // SHAND_SUPPORT_SFINAE


//--------------------------------------------------------------//
// 名称 : erase_if()											//
// 用途 : ***.erase(remove_if(begin, end, pred), end);の簡略版	//
// 引数 : predで条件指定された要素を削除						//
// 戻値 : なし													//
//--------------------------------------------------------------//
template<class Container, class Pred>
inline void erase_if(Container& container, Pred pred)
{
    container.erase(std::remove_if(container.begin(), container.end(), pred), container.end());
}



#ifdef SHAND_SUPPORT_SFINAE
//--------------------------------------------------//
// 以下 SFINAE版STLアルゴリズム						//
//													//
// vector<int> v;									//
// sort(v);											//
//													//
// int ar[] = {3, 1, 4};							//
// sort(ar);										//
//--------------------------------------------------//
// for_each
template <class Type, int Size, class Predicate>
inline Predicate for_each(Type (&ar)[Size], Predicate pred)
{
	return std::for_each(ar, ar + Size, pred);
}

template <class Container, class Predicate>
inline Predicate for_each(const Container& container, Predicate pred)
{
	return std::for_each(container.begin(), container.end(), pred);
}


// find
template <class Type, int Size, class Target>
inline Type* find(Type (&ar)[Size], const Target& value)
{
	return std::find(ar, ar + Size, value);
}

template <class Container, class Target>
inline typename Container::iterator find(Container& container, const Target& value)
{
	return std::find(container.begin(), container.end(), value);
}

template <class Container, class Target>
inline typename Container::const_iterator find(const Container& container, const Target& value)
{
	return std::find(container.begin(), container.end(), value);
}


// find_if
template <class Type, int Size, class Predicate>
inline Type* find_if(Type (&ar)[Size], Predicate pred)
{
	return std::find_if(ar, ar + Size, pred);
}

template <class Container, class Predicate>
inline typename Container::iterator find_if(Container& container, Predicate pred)
{
	return std::find_if(container.begin(), container.end(), pred);
}

template <class Container, class Predicate>
inline typename Container::const_iterator find_if(const Container& container, Predicate pred)
{
	return std::find_if(container.begin(), container.end(), pred);
}


// find_first_of
template <class LType, int LSize, class RType, int RSize>
inline LType* find_first_of(LType (&lhs)[LSize], RType (&rhs)[RSize])
{
	return std::find_first_of(lhs, lhs + LSize, rhs, rhs + RSize);
}

template <class LType, int LSize, class RType, int RSize, class Predicate>
inline LType* find_first_of(LType (&lhs)[LSize], RType (&rhs)[RSize], Predicate pred)
{
	return std::find_first_of(lhs, lhs + LSize, rhs, rhs + RSize, pred);
}

template <class LContainer, class RContainer>
inline typename LContainer::iterator find_first_of(LContainer &lhs, RContainer &rhs)
{
	return std::find_first_of(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <class LContainer, class RContainer, class Predicate>
inline typename LContainer::iterator find_first_of(LContainer &lhs, RContainer &rhs, Predicate pred)
{
	return std::find_first_of(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <class LContainer, class RContainer>
inline typename LContainer::const_iterator find_first_of(const LContainer& lhs, const RContainer& rhs)
{
	return std::find_first_of(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <class LContainer, class RContainer, class Predicate>
inline typename LContainer::const_iterator find_first_of(const LContainer& lhs, const RContainer& rhs, Predicate pred)
{
	return std::find_first_of(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), pred);
}


// find_end
template <class LType, int LSize, class RType, int RSize>
inline LType*
find_end(LType (&lhs)[LSize], RType (&rhs)[RSize])
{
	return std::find_end(lhs, lhs + LSize, rhs, rhs + RSize);
}

template <class LType, int LSize, class RType, int RSize, class Predicate>
inline LType* find_end(LType (&lhs)[LSize], RType (&rhs)[RSize], Predicate pred)
{
	return std::find_end(lhs, lhs + LSize, rhs, rhs + RSize, pred);
}

template <class LContainer, class RContainer>
inline typename LContainer::iterator find_end(LContainer &lhs, RContainer &rhs)
{
	return std::find_end(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <class LContainer, class RContainer, class Predicate>
inline typename LContainer::iterator find_end(LContainer &lhs, RContainer &rhs, Predicate pred)
{
	return std::find_end(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <class LContainer, class RContainer>
inline typename LContainer::const_iterator find_end(const LContainer& lhs, const RContainer& rhs)
{
	return std::find_end(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <class LContainer, class RContainer, class Predicate>
inline typename LContainer::const_iterator find_end(const LContainer& lhs, const RContainer& rhs, Predicate pred)
{
	return std::find_end(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), pred);
}


// adjacent_find
template <class Type, int Size>
inline Type* adjacent_find(Type (&ar)[Size])
{
	return std::adjacent_find(ar, ar + Size);
}

template <class Type, int Size, class Predicate>
inline Type* adjacent_find(Type (&ar)[Size], Predicate pred)
{
	return std::adjacent_find(ar, ar + Size, pred);
}

template <class Container>
inline typename Container::iterator adjacent_find(Container& container)
{
	return std::adjacent_find(container.begin(), container.end());
}

template <class Container>
inline typename Container::const_iterator adjacent_find(const Container& container)
{
	return std::adjacent_find(container.begin(), container.end());
}

template <class Container, class Predicate>
inline typename Container::iterator adjacent_find(Container& container, Predicate pred)
{
	return std::adjacent_find(container.begin(), container.end(), pred);
}

template <class Container, class Predicate>
inline typename Container::const_iterator adjacent_find(const Container& container, Predicate pred)
{
	return std::adjacent_find(container.begin(), container.end(), pred);
}


// count
template <class Type, int Size, class Target>
inline Type count(Type (&ar)[Size], const Target& value)
{
	return std::count(ar, ar + Size, value);
}

template <class Container, class Target>
inline typename Container::difference_type count(const Container& container, const Target& value)
{
	return std::count(container.begin(), container.end(), value);
}


// count_if
template <class Type, int Size, class Predicate>
inline Type count_if(Type (&ar)[Size], Predicate pred)
{
	return std::count_if(ar, ar + Size, pred);
}

template <class Container, class Predicate>
inline typename Container::difference_type count_if(const Container& container, Predicate pred)
{
	return std::count_if(container.begin(), container.end(), pred);
}


// mismatch
template <class Type, int Size, class InputIterator>
inline std::pair<Type*, InputIterator> mismatch(Type (&ar)[Size], InputIterator first)
{
	return std::mismatch(ar, ar + Size, first);
}

template <class Type, int Size, class InputIterator, class Predicate>
inline std::pair<Type*, InputIterator> mismatch(Type (&ar)[Size], InputIterator first, Predicate pred)
{
	return std::mismatch(ar, ar + Size, first, pred);
}

template <class Container, class InputIterator>
inline std::pair<typename Container::iterator, InputIterator>
mismatch(Container& container, InputIterator first)
{
	return std::mismatch(container.begin(), container.end(), first);
}

template <class Container, class InputIterator, class Predicate>
inline std::pair<typename Container::iterator, InputIterator>
mismatch(Container& container, InputIterator first, Predicate pred)
{
	return std::mismatch(container.begin(), container.end(), first, pred);
}

template <class Container, class InputIterator>
inline std::pair<typename Container::const_iterator, InputIterator>
mismatch(const Container& container, InputIterator first)
{
	return std::mismatch(container.begin(), container.end(), first);
}

template <class Container, class InputIterator, class Predicate>
inline std::pair<typename Container::const_iterator, InputIterator>
mismatch(const Container& container, InputIterator first, Predicate pred)
{
	return std::mismatch(container.begin(), container.end(), first, pred);
}

// equal
template <class Type, int Size, class InputIterator>
inline bool equal(Type (&ar)[Size], InputIterator first)
{
	return std::equal(ar, ar + Size, first);
}

template <class Type, int Size, class InputIterator, class Predicate>
inline bool equal(Type (&ar)[Size], InputIterator first, Predicate pred)
{
	return std::equal(ar, ar + Size, first, pred);
}

template <class Container, class InputIterator>
inline bool equal(const Container& container, InputIterator first)
{
	return std::equal(container.begin(), container.end(), first);
}

template <class Container, class InputIterator, class Predicate>
inline bool equal(const Container& container, InputIterator first, Predicate pred)
{
	return std::equal(container.begin(), container.end(), first, pred);
}

// search
template <class LType, int LSize, class RType, int RSize>
inline LType* search(LType (&lhs)[LSize], RType (&rhs)[RSize])
{
	return std::search(lhs, lhs + LSize, rhs, rhs + RSize);
}

template <class LType, int LSize, class RType, int RSize, class BynaryPredicate>
inline LType* search(LType (&lhs)[LSize], RType (&rhs)[RSize], BynaryPredicate pred)
{
	return std::search(lhs, lhs + LSize, rhs, rhs + RSize, pred);
}

template <class LContainer, class RContainer>
inline typename LContainer::iterator search(LContainer& lhs, RContainer& rhs)
{
	return std::search(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <class LContainer, class RContainer, class BynaryPredicate>
inline typename LContainer::iterator search(LContainer& lhs, RContainer& rhs, BynaryPredicate pred)
{
	return std::search(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), pred);
}

template <class LContainer, class RContainer>
inline typename LContainer::const_iterator search(const LContainer& lhs, const RContainer& rhs)
{
	return std::search(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <class LContainer, class RContainer, class BynaryPredicate>
inline typename LContainer::const_iterator search(const LContainer& lhs, const RContainer& rhs, BynaryPredicate pred)
{
	return std::search(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), pred);
}

// copy
template <class Type, int Size, class OutputIterator>
inline OutputIterator copy(Type (&ar)[Size], OutputIterator result)
{
	return std::copy(ar, ar + Size, result);
}

template <class Container, class OutputIterator>
inline OutputIterator copy(const Container& container, OutputIterator result)
{
	return std::copy(container.begin(), container.end(), result);
}


// copy_backward
template <class Type, int Size, class BidirectionalIterator>
inline BidirectionalIterator copy_backward(Type (&ar)[Size], BidirectionalIterator result)
{
	return std::copy_backward(ar, ar + Size, result);
}

template <class Container, class BidirectionalIterator>
inline BidirectionalIterator copy_backward(const Container& container, BidirectionalIterator result)
{
	return std::copy_backward(container.begin(), container.end(), result);
}


// transform
template <class Type, int Size, class OutputIterator, class UnaryOperation>
inline OutputIterator transform(Type (&ar)[Size], OutputIterator result, UnaryOperation op)
{
	return std::transform(ar, ar + Size, result, op);
}

template <class Type, int Size, class InputIterator, class OutputIterator, class BynaryOperation>
inline OutputIterator transform(Type (&ar)[Size], InputIterator first, OutputIterator result, BynaryOperation op)
{
	return std::transform(ar, ar + Size, first, result, op);
}

template <class Container, class OutputIterator, class UnaryOperation>
inline OutputIterator transform(const Container& container, OutputIterator result, UnaryOperation op)
{
	return std::transform(container.begin(), container.end(), result, op);
}

template <class Container, class InputIterator, class OutputIterator, class BynaryOperation>
inline OutputIterator transform(const Container& container, InputIterator first, OutputIterator result, BynaryOperation op)
{
	return std::transform(container.begin(), container.end(), first, result, op);
}


// replace
template <class Type, int Size, class Target>
inline void replace(Type (&ar)[Size], const Target& old_value, const Target& new_value)
{
	std::replace(ar, ar + Size, old_value, new_value);
}

template <class Container, class Target>
inline void replace(Container& container, const Target& old_value, const Target& new_value)
{
	std::replace(container.begin(), container.end(), old_value, new_value);
}


// replace_if
template <class Type, int Size, class Predicate, class Target>
inline void replace_if(Type (&ar)[Size], Predicate pred, const Target& new_value)
{
	std::replace_if(ar, ar + Size, pred, new_value);
}

template <class Container, class Predicate, class Target>
inline void replace_if(Container& container, Predicate pred, const Target& new_value)
{
	std::replace_if(container.begin(), container.end(), pred, new_value);
}


// replace_copy
template <class Type, int Size, class OutputIterator, class Target>
inline OutputIterator
replace_copy(Type (&ar)[Size], OutputIterator result, const Target& old_value, const Target& new_value)
{
	return std::replace_copy(ar, ar + Size, result, old_value, new_value);
}

template <class Container, class OutputIterator, class Target>
inline OutputIterator
replace_copy(const Container& container, OutputIterator result, const Target& old_value, const Target& new_value)
{
	return std::replace_copy(container.begin(), container.end(), result, old_value, new_value);
}


// replace_copy_if
template <class Type, int Size, class OutputIterator, class Predicate, class Target>
inline OutputIterator
replace_copy_if(Type (&ar)[Size], OutputIterator result, Predicate pred, const Target& new_value)
{
	return std::replace_copy_if(ar, ar + Size, result, pred, new_value);
}

template <class Container, class OutputIterator, class Predicate, class Target>
inline OutputIterator
replace_copy_if(const Container& container, OutputIterator result, Predicate pred, const Target& new_value)
{
	return std::replace_copy_if(container.begin(), container.end(), result, pred, new_value);
}


// fill
template <class Type, int Size, class Target>
inline void fill(Type (&ar)[Size], const Target& value)
{
	std::fill(ar, ar + Size, value);
}

template <class Container, class Target>
inline void fill(Container& container, const Target& value)
{
	std::fill(container.begin(), container.end(), value);
}


// generate
template <class Type, int Size, class Generator>
inline void generate(Type (&ar)[Size], Generator gen)
{
	return std::generate(ar, ar + Size, gen);
}

template <class Container, class Generator>
inline void generate(Container &container, Generator gen)
{
	return std::generate(container.begin(), container.end(), gen);
}


// remove
template <class Type, int Size, class Target>
inline Type* remove(Type (&ar)[Size], const Target& value)
{
	return std::remove(ar, ar + Size, value);
}

template <class Container, class Target>
inline typename Container::iterator remove(Container& container, const Target& value)
{
	return std::remove(container.begin(), container.end(), value);
}

// remove_if
template <class Type, int Size, class Predicate>
inline Type* remove_if(Type (&ar)[Size], Predicate pred)
{
	return std::remove_if(ar, ar + Size, pred);
}

template <class Container, class Predicate>
inline typename Container::iterator remove_if(Container& container, Predicate pred)
{
	return std::remove_if(container.begin(), container.end(), pred);
}

// remove_copy
template <class Type, int Size, class OutputIterator, class Target>
inline OutputIterator remove_copy(Type (&ar)[Size], OutputIterator result, const Target& value)
{
	return std::remove_copy(ar, ar + Size, result, value);
}

template <class Container, class OutputIterator, class Target>
inline OutputIterator remove_copy(const Container& container, OutputIterator result, const Target& value)
{
	return std::remove_copy(container.begin(), container.end(), result, value);
}

// remove_copy_if
template <class Type, int Size, class OutputIterator, class Predicate>
inline OutputIterator remove_copy_if(Type (&ar)[Size], OutputIterator result, Predicate pred)
{
	return std::remove_copy_if(ar, ar + Size, result, pred);
}

template <class Container, class OutputIterator, class Predicate>
inline OutputIterator remove_copy_if(const Container& container, OutputIterator result, Predicate pred)
{
	return std::remove_copy_if(container.begin(), container.end(), result, pred);
}

// unique
template <class Type, int Size>
inline Type* unique(Type (&ar)[Size])
{
	return std::unique(ar, ar + Size);
}

template <class Type, int Size, class BynaryPredicate>
inline Type* unique(Type (&ar)[Size], BynaryPredicate pred)
{
	return std::unique(ar, ar + Size, pred);
}

template <class Container>
inline typename Container::iterator unique(Container& container)
{
	return std::unique(container.begin(), container.end());
}

template <class Container, class BynaryPredicate>
inline typename Container::iterator unique(Container& container, BynaryPredicate pred)
{
	return std::unique(container.begin(), container.end(), pred);
}

// unique_copy
template <class Type, int Size, class OutputIterator>
inline OutputIterator unique_copy(Type (&ar)[Size], OutputIterator result)
{
	return std::unique_copy(ar, ar + Size, result);
}

template <class Type, int Size, class OutputIterator, class BynaryPredicate>
inline OutputIterator unique_copy(Type (&ar)[Size], OutputIterator result, BynaryPredicate pred)
{
	return std::unique_copy(ar, ar + Size, result, pred);
}

template <class Container, class OutputIterator>
inline OutputIterator unique_copy(const Container& container, OutputIterator result)
{
	return std::unique_copy(container.begin(), container.end(), result);
}

template <class Container, class OutputIterator, class BynaryPredicate>
inline OutputIterator unique_copy(const Container& container, OutputIterator result, BynaryPredicate pred)
{
	return std::unique_copy(container.begin(), container.end(), result, pred);
}

// reverse
template <class Type, int Size>
inline void reverse(Type (&ar)[Size])
{
	std::reverse(ar, ar + Size);
}

template <class Container>
inline void reverse(Container& container)
{
	std::reverse(container.begin(), container.end());
}

// reverse_copy
template <class Type, int Size, class OutputIterator>
inline OutputIterator reverse_copy(Type (&ar)[Size], OutputIterator result)
{
	return std::reverse_copy(ar, ar + Size, result);
}

template <class Container, class OutputIterator>
inline OutputIterator reverse_copy(Container& container, OutputIterator result)
{
	return std::reverse_copy(container.begin(), container.end(), result);
}

// random_shuffle
template <class Type, int Size>
inline void random_shuffle(Type (&ar)[Size])
{
	std::random_shuffle(ar, ar + Size);
}

template <class Type, int Size, class RandomNumberGenerator>
inline void random_shuffle(Type (&ar)[Size], RandomNumberGenerator& gen)
{
	std::random_shuffle(ar, ar + Size, gen);
}

template <class Container>
inline void random_shuffle(Container &container)
{
	std::random_shuffle(container.begin(), container.end());
}

template <class Container, class RandomNumberGenerator>
inline void random_shuffle(Container &container, RandomNumberGenerator& gen)
{
	std::random_shuffle(container.begin(), container.end(), gen);
}

// partition
template <class Type, int Size, class Predicate>
inline Type* partition(Type (&ar)[Size], Predicate pred)
{
	return std::partition(ar, ar + Size, pred);
}

template <class Container, class Predicate>
inline typename Container::iterator partition(Container& container, Predicate pred)
{
	return std::partition(container.begin(), container.end(), pred);
}

// stable_partition
template <class Type, int Size, class Predicate>
inline Type* stable_partition(Type (&ar)[Size], Predicate pred)
{
	return std::stable_partition(ar, ar + Size, pred);
}

template <class Container, class Predicate>
inline typename Container::iterator stable_partition(Container& container, Predicate pred)
{
	return std::stable_partition(container.begin(), container.end(), pred);
}

// sort
template <class Type, int Size>
inline void sort(Type (&ar)[Size])
{
	std::sort(ar, ar + Size);
}

template <class Type, int Size, class Compare>
inline void sort(Type (&ar)[Size], Compare comp)
{
	std::sort(ar, ar + Size, comp);
}

template <class Container>
inline void sort(Container &container)
{
	std::sort(container.begin(), container.end());
}

template <class Container, class Compare>
inline void sort(Container &container, Compare comp)
{
	std::sort(container.begin(), container.end(), comp);
}

// stable_sort
template <class Type, int Size>
inline void stable_sort(Type (&ar)[Size])
{
	std::stable_sort(ar, ar + Size);
}

template <class Type, int Size, class Compare>
inline void stable_sort(Type (&ar)[Size], Compare comp)
{
	std::stable_sort(ar, ar + Size, comp);
}

template <class Container>
inline void stable_sort(Container &container)
{
	std::stable_sort(container.begin(), container.end());
}

template <class Container, class Compare>
inline void stable_sort(Container &container, Compare comp)
{
	std::stable_sort(container.begin(), container.end(), comp);
}

// lower_bound
template <class Type, int Size, class Target>
inline Type* lower_bound(Type (&ar)[Size], const Target& value)
{
	return std::lower_bound(ar, ar + Size, value);
}

template <class Type, int Size, class Target, class Compare>
inline Type* lower_bound(Type (&ar)[Size], const Target& value, Compare comp)
{
	return std::lower_bound(ar, ar + Size, value, comp);
}

template <class Container, class Target>
inline typename Container::iterator lower_bound(Container& container, const Target& value)
{
	return std::lower_bound(container.begin(), container.end(), value);
}

template <class Container, class Target, class Compare>
inline typename Container::iterator lower_bound(Container& container, const Target& value, Compare comp)
{
	return std::lower_bound(container.begin(), container.end(), value, comp);
}

template <class Container, class Target>
inline typename Container::const_iterator lower_bound(const Container& container, const Target& value)
{
	return std::lower_bound(container.begin(), container.end(), value);
}

template <class Container, class Target, class Compare>
inline typename Container::const_iterator lower_bound(const Container& container, const Target& value, Compare comp)
{
	return std::lower_bound(container.begin(), container.end(), value, comp);
}

// upper_bound
template <class Type, int Size, class Target>
inline Type* upper_bound(Type (&ar)[Size], const Target& value)
{
	return std::upper_bound(ar, ar + Size, value);
}

template <class Type, int Size, class Target, class Compare>
inline Type* upper_bound(Type (&ar)[Size], const Target& value, Compare comp)
{
	return std::upper_bound(ar, ar + Size, value, comp);
}

template <class Container, class Target>
inline typename Container::iterator upper_bound(Container& container, const Target& value)
{
	return std::upper_bound(container.begin(), container.end(), value);
}

template <class Container, class Target, class Compare>
inline typename Container::iterator upper_bound(Container& container, const Target& value, Compare comp)
{
	return std::upper_bound(container.begin(), container.end(), value, comp);
}

template <class Container, class Target>
inline typename Container::const_iterator upper_bound(const Container& container, const Target& value)
{
	return std::upper_bound(container.begin(), container.end(), value);
}

template <class Container, class Target, class Compare>
inline typename Container::const_iterator upper_bound(const Container& container, const Target& value, Compare comp)
{
	return std::upper_bound(container.begin(), container.end(), value, comp);
}

// binary_search
template <class Type, int Size, class Target>
inline bool binary_search(Type (&ar)[Size], const Target& value)
{
	return std::binary_search(ar, ar + Size, value);
}

template <class Type, int Size, class Target, class Compare>
inline bool binary_search(Type (&ar)[Size], const Target& value, Compare comp)
{
	return std::binary_search(ar, ar + Size, value, comp);
}

template <class Container, class Target>
inline bool binary_search(const Container& container, const Target& value)
{
	return std::binary_search(container.begin(), container.end(), value);
}

template <class Container, class Target, class Compare>
inline bool binary_search(const Container& container, const Target& value, Compare comp)
{
	return std::binary_search(container.begin(), container.end(), value, comp);
}

// merge
template <class LType, int LSize, class RType, int RSize, class OutputIterator>
inline OutputIterator merge(LType (&lhs)[LSize], RType (&rhs)[RSize], OutputIterator result)
{
	return std::merge(lhs, lhs + LSize, rhs, rhs + RSize, result);
}

template <class LType, int LSize, class RType, int RSize, class OutputIterator, class Compare>
inline OutputIterator merge(LType (&lhs)[LSize], RType (&rhs)[RSize], OutputIterator result, Compare comp)
{
	return std::merge(lhs, lhs + LSize, rhs, rhs + RSize, result, comp);
}

template <class LContainer, class RContainer, class OutputIterator>
inline OutputIterator merge(const LContainer& lhs, const RContainer& rhs, OutputIterator result)
{
	return std::merge(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), result);
}

template <class LContainer, class RContainer, class OutputIterator, class Compare>
inline OutputIterator merge(const LContainer& lhs, const RContainer& rhs, OutputIterator result, Compare comp)
{
	return std::merge(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), result, comp);
}

// includes
template <class LType, int LSize, class RType, int RSize>
inline bool includes(LType (&lhs)[LSize], RType (&rhs)[RSize])
{
	return std::includes(lhs, lhs + LSize, rhs, rhs + RSize);
}

template <class LType, int LSize, class RType, int RSize, class Compare>
inline bool includes(LType (&lhs)[LSize], RType (&rhs)[RSize], Compare comp)
{
	return std::includes(lhs, lhs + LSize, rhs, rhs + RSize, comp);
}

template <class LContainer, class RContainer>
inline bool includes(const LContainer& lhs, const RContainer& rhs)
{
	return std::includes(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <class LContainer, class RContainer, class Compare>
inline bool includes(const LContainer& lhs, const RContainer& rhs, Compare comp)
{
	return std::includes(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), comp);
}

// set_union
template <class LType, int LSize, class RType, int RSize, class OutputIterator>
inline OutputIterator set_union(LType (&lhs)[LSize], RType (&rhs)[RSize], OutputIterator result)
{
	return std::set_union(lhs, lhs + LSize, rhs, rhs + RSize, result);
}

template <class LType, int LSize, class RType, int RSize, class OutputIterator, class Compare>
inline OutputIterator set_union(LType (&lhs)[LSize], RType (&rhs)[RSize], OutputIterator result, Compare comp)
{
	return std::set_union(lhs, lhs + LSize, rhs, rhs + RSize, result, comp);
}

template <class LContainer, class RContainer, class OutputIterator>
inline OutputIterator set_union(const LContainer& lhs, const RContainer& rhs, OutputIterator result)
{
	return std::set_union(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), result);
}

template <class LContainer, class RContainer, class OutputIterator, class Compare>
inline OutputIterator set_union(const LContainer& lhs, const RContainer& rhs, OutputIterator result, Compare comp)
{
	return std::set_union(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), result, comp);
}

// set_intersection
template <class LType, int LSize, class RType, int RSize, class OutputIterator>
inline OutputIterator set_intersection(LType (&lhs)[LSize], RType (&rhs)[RSize], OutputIterator result)
{
	return std::set_intersection(lhs, lhs + LSize, rhs, rhs + RSize, result);
}

template <class LType, int LSize, class RType, int RSize, class OutputIterator, class Compare>
inline OutputIterator set_intersection(LType (&lhs)[LSize], RType (&rhs)[RSize], OutputIterator result, Compare comp)
{
	return std::set_intersection(lhs, lhs + LSize, rhs, rhs + RSize, result, comp);
}

template <class LContainer, class RContainer, class OutputIterator>
inline OutputIterator set_intersection(const LContainer& lhs, const RContainer& rhs, OutputIterator result)
{
	return std::set_intersection(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), result);
}

template <class LContainer, class RContainer, class OutputIterator, class Compare>
inline OutputIterator set_intersection(const LContainer& lhs, const RContainer& rhs, OutputIterator result, Compare comp)
{
	return std::set_intersection(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), result, comp);
}

// set_difference
template <class LType, int LSize, class RType, int RSize, class OutputIterator>
inline OutputIterator set_difference(LType (&lhs)[LSize], RType (&rhs)[RSize], OutputIterator result)
{
	return std::set_difference(lhs, lhs + LSize, rhs, rhs + RSize, result);
}

template <class LType, int LSize, class RType, int RSize, class OutputIterator, class Compare>
inline OutputIterator set_difference(LType (&lhs)[LSize], RType (&rhs)[RSize], OutputIterator result, Compare comp)
{
	return std::set_difference(lhs, lhs + LSize, rhs, rhs + RSize, result, comp);
}

template <class LContainer, class RContainer, class OutputIterator>
inline OutputIterator set_difference(const LContainer& lhs, const RContainer& rhs, OutputIterator result)
{
	return std::set_difference(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), result);
}

template <class LContainer, class RContainer, class OutputIterator, class Compare>
inline OutputIterator set_difference(const LContainer& lhs, const RContainer& rhs, OutputIterator result, Compare comp)
{
	return std::set_difference(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), result, comp);
}

// set_symmetric_difference
template <class LType, int LSize, class RType, int RSize, class OutputIterator>
inline OutputIterator set_symmetric_difference(LType (&lhs)[LSize], RType (&rhs)[RSize], OutputIterator result)
{
	return std::set_symmetric_difference(lhs, lhs + LSize, rhs, rhs + RSize, result);
}

template <class LType, int LSize, class RType, int RSize, class OutputIterator, class Compare>
inline OutputIterator set_symmetric_difference(LType (&lhs)[LSize], RType (&rhs)[RSize], OutputIterator result, Compare comp)
{
	return std::set_symmetric_difference(lhs, lhs + LSize, rhs, rhs + RSize, result, comp);
}

template <class LContainer, class RContainer, class OutputIterator>
inline OutputIterator set_symmetric_difference(const LContainer& lhs, const RContainer& rhs, OutputIterator result)
{
	return std::set_symmetric_difference(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), result);
}

template <class LContainer, class RContainer, class OutputIterator, class Compare>
inline OutputIterator set_symmetric_difference(const LContainer& lhs, const RContainer& rhs, OutputIterator result, Compare comp)
{
	return std::set_symmetric_difference(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), result, comp);
}

// push_heap
template <class Type, int Size>
inline void push_heap(Type (&ar)[Size])
{
	std::push_heap(ar, ar + Size);
}

template <class Type, int Size, class Compare>
inline void push_heap(Type (&ar)[Size], Compare comp)
{
	std::push_heap(ar, ar + Size, comp);
}

template <class Container>
inline void push_heap(Container& container)
{
	std::push_heap(container.begin(), container.end());
}

template <class Container, class Compare>
inline void push_heap(Container& container, Compare comp)
{
	std::push_heap(container.begin(), container.end(), comp);
}

// pop_heap
template <class Type, int Size>
inline void pop_heap(Type (&ar)[Size])
{
	std::pop_heap(ar, ar + Size);
}

template <class Type, int Size, class Compare>
inline void pop_heap(Type (&ar)[Size], Compare comp)
{
	std::pop_heap(ar, ar + Size, comp);
}

template <class Container>
inline void pop_heap(Container& container)
{
	std::pop_heap(container.begin(), container.end());
}

template <class Container, class Compare>
inline void pop_heap(Container& container, Compare comp)
{
	std::pop_heap(container.begin(), container.end(), comp);
}

// make_heap
template <class Type, int Size>
inline void make_heap(Type (&ar)[Size])
{
	std::make_heap(ar, ar + Size);
}

template <class Type, int Size, class Compare>
inline void make_heap(Type (&ar)[Size], Compare comp)
{
	std::make_heap(ar, ar + Size, comp);
}

template <class Container>
inline void make_heap(Container& container)
{
	std::make_heap(container.begin(), container.end());
}

template <class Container, class Compare>
inline void make_heap(Container& container, Compare comp)
{
	std::make_heap(container.begin(), container.end(), comp);
}

// sort_heap
template <class Type, int Size>
inline void sort_heap(Type (&ar)[Size])
{
	std::sort_heap(ar, ar + Size);
}

template <class Type, int Size, class Compare>
inline void sort_heap(Type (&ar)[Size], Compare comp)
{
	std::sort_heap(ar, ar + Size, comp);
}

template <class Container>
inline void sort_heap(Container& container)
{
	std::sort_heap(container.begin(), container.end());
}

template <class Container, class Compare>
inline void sort_heap(Container& container, Compare comp)
{
	std::sort_heap(container.begin(), container.end(), comp);
}

// min_element
template <class Type, int Size>
inline Type* min_element(Type (&ar)[Size])
{
	return std::min_element(ar, ar + Size);
}

template <class Type, int Size, class Compare>
inline Type* min_element(Type (&ar)[Size], Compare comp)
{
	return std::min_element(ar, ar + Size, comp);
}

template <class Container>
inline typename Container::iterator min_element(Container& container)
{
	return std::min_element(container.begin(), container.end());
}

template <class Container, class Compare>
inline typename Container::iterator min_element(Container& container, Compare comp)
{
	return std::min_element(container.begin(), container.end(), comp);
}

template <class Container>
inline typename Container::const_iterator min_element(const Container& container)
{
	return std::min_element(container.begin(), container.end());
}

template <class Container, class Compare>
inline typename Container::const_iterator min_element(const Container& container, Compare comp)
{
	return std::min_element(container.begin(), container.end(), comp);
}

// max_element
template <class Type, int Size>
inline Type* max_element(Type (&ar)[Size])
{
	return std::max_element(ar, ar + Size);
}

template <class Type, int Size, class Compare>
inline Type* max_element(Type (&ar)[Size], Compare comp)
{
	return std::max_element(ar, ar + Size, comp);
}

template <class Container>
inline typename Container::iterator max_element(Container& container)
{
	return std::max_element(container.begin(), container.end());
}

template <class Container, class Compare>
inline typename Container::iterator max_element(Container& container, Compare comp)
{
	return std::max_element(container.begin(), container.end(), comp);
}

template <class Container>
inline typename Container::const_iterator max_element(const Container& container)
{
	return std::max_element(container.begin(), container.end());
}

template <class Container, class Compare>
inline typename Container::const_iterator max_element(const Container& container, Compare comp)
{
	return std::max_element(container.begin(), container.end(), comp);
}

// lexicographical_compare
template <class LType, int LSize, class RType, int RSize>
inline bool lexicographical_compare(LType (&lhs)[LSize], RType (&rhs)[RSize])
{
	return std::lexicographical_compare(lhs, lhs + LSize, rhs, rhs + RSize);
}

template <class LType, int LSize, class RType, int RSize, class Compare>
inline bool lexicographical_compare(LType (&lhs)[LSize], RType (&rhs)[RSize], Compare comp)
{
	return std::lexicographical_compare(lhs, lhs + LSize, rhs, rhs + RSize, comp);
}

template <class LContainer, class RContainer>
inline bool lexicographical_compare(const LContainer& lhs, const RContainer& rhs)
{
	return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <class LContainer, class RContainer, class Compare>
inline bool lexicographical_compare(const LContainer& lhs, const RContainer& rhs, Compare comp)
{
	return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), comp);
}

// next_permutation
template <class Type, int Size>
inline bool next_permutation(Type (&ar)[Size])
{
	return std::next_permutation(ar, ar + Size);
}

template <class Type, int Size, class Compare>
inline bool next_permutation(Type (&ar)[Size], Compare comp)
{
	return std::next_permutation(ar, ar + Size, comp);
}

template <class Container>
inline bool next_permutation(const Container& container)
{
	return std::next_permutation(container.begin(), container.end());
}

template <class Container, class Compare>
inline bool next_permutation(const Container& container, Compare comp)
{
	return std::next_permutation(container.begin(), container.end(), comp);
}

// prev_permutation
template <class Type, int Size>
inline bool prev_permutation(Type (&ar)[Size])
{
	return std::prev_permutation(ar, ar + Size);
}

template <class Type, int Size, class Compare>
inline bool prev_permutation(Type (&ar)[Size], Compare comp)
{
	return std::prev_permutation(ar, ar + Size, comp);
}

template <class Container>
inline bool prev_permutation(const Container& container)
{
	return std::prev_permutation(container.begin(), container.end());
}

template <class Container, class Compare>
inline bool prev_permutation(const Container& container, Compare comp)
{
	return std::prev_permutation(container.begin(), container.end(), comp);
}


#endif // SHAND_SUPPORT_SFINAE


} // namespace shand

#undef SHAND_SUPPORT_SFINAE

#endif // SHAND_ALGORITHM_INCLUDE



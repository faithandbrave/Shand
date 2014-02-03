#ifndef SHAND_ALGORITHM_INCLUDE
#define SHAND_ALGORITHM_INCLUDE

// Copyright Akira Takahashi 2007
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//----------------------------------------------------------------------//
// Name : アルゴリズム                                                  //
//                                                                      //
// Version : 1.00 2007/05/17 作成, mem_find                             //
//           1.01 2007/05/24 mem_find(メンバ関数版)作成                 //
//           1.02 2007/09/19 いろいろ + is_sorted追加                   //
//           1.03 2007/10/03 SFINAE版アルゴリズム追加                   //
//           1.04 2007/11/02 erase_if追加                               //
//           1.05 2007/11/22 SFINAEの余計な処理削除                     //
//           1.06 2007/11/27 SFINAE版アルゴリズムをBoost.Range風に変更  //
//                                                                      //
//----------------------------------------------------------------------//

#include <algorithm>
#include <vector>
#include <string>
#include <iterator>
#include <functional>
#include <utility>


// SFINAEをサポートしているコンパイラか
#if !defined(_MSC_VER) || (_MSC_VER > 1300)  // 1300 == VC++ 7.0
    #define SHAND_SUPPORT_SFINAE
#endif


#include <algorithm>

namespace shand {

#ifdef SHAND_SUPPORT_SFINAE

// 反復子の型取得
template <class Container>
struct range_iterator {
    typedef typename Container::iterator type;
};

template <class Container>
struct range_iterator< const Container > {
    typedef typename Container::const_iterator type;
};

template <class Type, int Size>
struct range_iterator< Type[Size] > {
    typedef Type* type;
};

template <class Type, int Size>
struct range_iterator< const Type[Size] > {
    typedef const Type* type;
};

template<>
struct range_iterator< char* >
{
    typedef char* type;
};

// 配列 - 先頭要素へのポインタ取得
template <class Type, int Size>
inline Type* begin(Type (&ar)[Size])
{
    return ar;
}

// 配列 - 最後尾要素へのポインタ取得
template <class Type, int Size>
inline Type* end(Type (&ar)[Size])
{
    return ar + Size;
}

// コンテナ - 先頭イテレータ取得
template <class Container>
inline typename Container::iterator begin(Container& c)
{
    return c.begin();
}

template <class Container>
inline typename Container::const_iterator begin(const Container& c)
{
    return c.begin();
}

// コンテナ - 最後尾イテレータ取得
template <class Container>
inline typename Container::iterator end(Container& c)
{
    return c.end();
}

template <class Container>
inline typename Container::const_iterator end(const Container& c)
{
    return c.end();
}

// std::pair
template <class Iterator>
inline Iterator begin(const std::pair<Iterator, Iterator>& p)
{
    return p.first;
}

template <class Iterator>
inline Iterator end(const std::pair<Iterator, Iterator>& p)
{
    return p.second;
}

#define SHAND_RANGE_ITERATOR    typename range_iterator<Container>::type
#define SHAND_RANGE_CITERATOR   typename range_iterator<const Container>::type

#endif // SHAND_SUPPORT_SFINAE



//------------------------------------------//
// 名称 : mem_find()                        //
// 用途 : メンバ変数の検索                  //
// 引数 : first     : 先頭イテレータ        //
//        last      : 最後尾イテレータ      //
//        target    : 検索する値            //
//        member    : メンバ変数へのポインタ//
// 戻値 : 該当イテレータ                    //
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
template <class Container, class Target, class Type, class ClassName>
inline SHAND_RANGE_ITERATOR mem_find(Container& c, const Target& value, Type ClassName::*member)
{
    return mem_find(begin(c), end(c), value, member);
}

template <class Container, class Target, class Type, class ClassName>
inline SHAND_RANGE_CITERATOR mem_find(const Container& c, const Target& value, Type ClassName::*member)
{
    return mem_find(begin(c), end(c), value, member);
}
#endif // SHAND_SUPPORT_SFINAE

//--------------------------------------------------------------------------//
// sample                                                                   //
//==========================================================================//
// struct hoge {                                                            //
//   string name;                                                           //
//                                                                          //
//   hoge(const string& name="") : name(name) {}                            //
// };                                                                       //
//                                                                          //
// int main()                                                               //
// {                                                                        //
//   vector<hoge> v;                                                        //
//                                                                          //
//   v.push_back(hoge("Akira"));                                            //
//   v.push_back(hoge("Johnny"));                                           //
//   v.push_back(hoge("Sum"));                                              //
//                                                                          //
//   if (mem_find(v.begin(), v.end(), "Akira", &hoge::name) != v.end())     //
//     cout << "found" << endl;                                             //
//   else                                                                   //
//     cout << "not found" << endl;                                         //
//                                                                          //
//   return 0;                                                              //
// }                                                                        //
//--------------------------------------------------------------------------//



//------------------------------------------------------//
// 名称 : mem_find()                                    //
// 用途 : メンバ変数の検索(メンバ関数版, 非公開メンバ用)//
// 引数 : first     : 先頭イテレータ                    //
//        last      : 最後尾イテレータ                  //
//        target    : 検索する値                        //
//        member    : メンバ変数取得ゲッターへのポインタ//
// 戻値 : 該当イテレータ                                //
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
template <class Container, class Target, class Type, class ClassName>
inline SHAND_RANGE_ITERATOR mem_find(Container& c, const Target& target, Type (ClassName::*member)())
{
    return mem_find(begin(c), end(c), target, member);
}

template <class Container, class Target, class Type, class ClassName>
inline SHAND_RANGE_CITERATOR mem_find(const Container& c, const Target& target, Type (ClassName::*member)())
{
    return mem_find(begin(c), end(c), target, member);
}

template <class Container, class Target, class Type, class ClassName>
inline SHAND_RANGE_ITERATOR mem_find(Container& c, const Target& target, Type (ClassName::*member)() const)
{
    return mem_find(begin(c), end(c), target, member);
}

template <class Container, class Target, class Type, class ClassName>
inline SHAND_RANGE_CITERATOR mem_find(const Container& c, const Target& target, Type (ClassName::*member)() const)
{
    return mem_find(begin(c), end(c), target, member);
}
#endif // SHAND_SUPPORT_SFINAE

//--------------------------------------------------------------------------//
// sample                                                                   //
//==========================================================================//
// class hoge {                                                             //
//   string name_;                                                          //
// public:                                                                  //
//   hoge(const string& name="") : name_(name) {}                           //
//   string get_name() const { return name_; }                              //
// };                                                                       //
//                                                                          //
// int main()                                                               //
// {                                                                        //
//   vector<hoge> v;                                                        //
//                                                                          //
//   v.push_back(hoge("Akira"));                                            //
//   v.push_back(hoge("Johnny"));                                           //
//   v.push_back(hoge("Sum"));                                              //
//                                                                          //
//   if (mem_find(v.begin(), v.end(), "Akira", &hoge::get_name) != v.end()) //
//     cout << "該当あり" << endl;                                          //
//   else                                                                   //
//     cout << "該当なし" << endl;                                          //
//                                                                          //
//   return 0;                                                              //
// }                                                                        //
//--------------------------------------------------------------------------//


//----------------------------------------------//
// 名称 : chain_count()                         //
// 用途 : 同じ要素が連続している個数を数える    //
// 引数 : first : 検索対象の先頭イテレータ      //
//        last  : 検索対象の最後尾イテレータ    //
//        value : 検索する要素                  //
// 戻値 : 連続した個数                          //
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
template <class Container, class Type>
inline int chain_count(const Container& c, const Type& value)
{
    return chain_count(begin(c), end(c), value);
}
#endif // SHAND_SUPPORT_SFINAE

//--------------------------------------------------------------//
// sample                                                       //
//==============================================================//
// int main()                                                   //
// {                                                            //
//     string s("a  b   c");                                    //
//     int count = chain_count(s.begin(), s.end(), ' '); // 2   //
//                                                              //
//     return 0;                                                //
// }                                                            //
//--------------------------------------------------------------//


//----------------------------------------------//
// 名称 : size_split()                          //
// 用途 : 文字列を指定された文字数で分割        //
// 引数 : target : 対象文字列                   //
//        size   : 分割サイズ                   //
// 戻値 : 分割された文字列                      //
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
// 名称 : unique_count()                        //
// 用途 : 重複してない数取得                    //
// 引数 : first : 先頭要素へのイテレータ        //
//        last  : 最後尾要素へのイテレータ      //
//        pred  : 条件関数(オブジェクト)        //
// 戻値 : 重複数                                //
// 注意 : ソート済みコンテナである必要がある    //
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
template <class Container>
inline size_t unique_count(const Container& c)
{
    return unique_count(begin(c), end(c));
}

template <class Container, class Pred>
inline size_t unique_count(const Container& c, Pred pred)
{
    return unique_count(begin(c), end(c), pred);
}
#endif // SHAND_SUPPORT_SFINAE


//----------------------------------------------//
// 名称 : overlap_count()                       //
// 用途 : 重複数取得                            //
// 引数 : first : 先頭要素へのイテレータ        //
//        last  : 最後尾要素へのイテレータ      //
//        pred  : 条件関数(オブジェクト)        //
// 戻値 : 重複数                                //
// 注意 : ソート済みコンテナである必要がある    //
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
template <class Container>
inline size_t overlap_count(const Container& c)
{
    return overlap_count(begin(c), end(c));
}

template <class Container, class Pred>
inline size_t overlap_count(const Container& c, Pred pred)
{
    return overlap_count(begin(c), end(c), pred);
}
#endif // SHAND_SUPPORT_SFINAE


//--------------------------------------------------//
// 名称 : is_sorted()                               //
// 用途 : 範囲がソート済みか調べる                  //
// 引数 : first : 先頭要素へのイテレータ            //
//        last  : 最後尾要素へのイテレータ          //
//        pred  : 条件関数                          //
// 戻値 : true:ソート済み false:ソート済みではない  //
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
template <class Container>
inline bool is_sorted(const Container& c)
{
    return is_sorted(begin(c), end(c));
}

template <class Container, class Pred>
inline bool is_sorted(const Container& c, Pred pred)
{
    return is_sorted(begin(c), end(c), pred);
}
#endif // SHAND_SUPPORT_SFINAE


//--------------------------------------------------------------//
// 名称 : erase_if()                                            //
// 用途 : ***.erase(remove_if(begin, end, pred), end);の簡略版  //
// 引数 : predで条件指定された要素を削除                        //
// 戻値 : なし                                                  //
//--------------------------------------------------------------//
template<class Container, class Pred>
inline void erase_if(Container& c, Pred pred)
{
    c.erase(std::remove_if(c.begin(), c.end(), pred), c.end());
}



// SFINAE版STLアルゴリズム -----------------------------
#ifdef SHAND_SUPPORT_SFINAE

// for_each
template <class Container, class Pred>
inline Pred for_each(const Container& c, Pred pred)
{
    return std::for_each(begin(c), end(c), pred);
}

// find
template <class Container, class Target>
inline SHAND_RANGE_ITERATOR find(Container& c, const Target& value)
{
    return std::find(begin(c), end(c), value);
}

template <class Container, class Target>
inline SHAND_RANGE_CITERATOR find(const Container& c, const Target& value)
{
    return std::find(begin(c), end(c), value);
}

// find_if
template <class Container, class Pred>
inline SHAND_RANGE_ITERATOR find_if(Container& c, Pred pred)
{
    return std::find_if(begin(c), end(c), pred);
}

template <class Container, class Pred>
inline SHAND_RANGE_CITERATOR find_if(const Container& c, Pred pred)
{
    return std::find_if(begin(c), end(c), pred);
}

// find_first_of
template <class LContainer, class RContainer>
inline typename range_iterator<LContainer>::type find_first_of(LContainer &lhs, RContainer &rhs)
{
    return std::find_first_of(begin(lhs), end(lhs), begin(rhs), end(rhs));
}

template <class LContainer, class RContainer, class Pred>
inline typename range_iterator<LContainer>::type find_first_of(LContainer &lhs, RContainer &rhs, Pred pred)
{
    return std::find_first_of(begin(lhs), end(lhs), begin(rhs), end(rhs), pred);
}

template <class LContainer, class RContainer>
inline typename range_iterator<const LContainer>::type find_first_of(const LContainer& lhs, const RContainer& rhs)
{
    return std::find_first_of(begin(lhs), end(lhs), begin(rhs), end(rhs));
}

template <class LContainer, class RContainer, class Pred>
inline typename range_iterator<const LContainer>::type find_first_of(const LContainer& lhs, const RContainer& rhs, Pred pred)
{
    return std::find_first_of(begin(lhs), end(lhs), begin(rhs), end(rhs), pred);
}

// find_end
template <class LContainer, class RContainer>
inline typename range_iterator<LContainer>::type find_end(LContainer &lhs, RContainer &rhs)
{
    return std::find_end(begin(lhs), end(lhs), begin(rhs), end(rhs));
}

template <class LContainer, class RContainer, class Pred>
inline typename range_iterator<LContainer>::type find_end(LContainer &lhs, RContainer &rhs, Pred pred)
{
    return std::find_end(begin(lhs), end(lhs), begin(rhs), end(rhs), pred);
}

template <class LContainer, class RContainer>
inline typename range_iterator<const LContainer>::type find_end(const LContainer& lhs, const RContainer& rhs)
{
    return std::find_end(begin(lhs), end(lhs), begin(rhs), end(rhs));
}

template <class LContainer, class RContainer, class Pred>
inline typename range_iterator<const LContainer>::type find_end(const LContainer& lhs, const RContainer& rhs, Pred pred)
{
    return std::find_end(begin(lhs), end(lhs), begin(rhs), end(rhs), pred);
}

// adjacent_find
template <class Container>
inline SHAND_RANGE_ITERATOR adjacent_find(Container& c)
{
    return std::adjacent_find(begin(c), end(c));
}

template <class Container>
inline SHAND_RANGE_CITERATOR adjacent_find(const Container& c)
{
    return std::adjacent_find(begin(c), end(c));
}

template <class Container, class Pred>
inline SHAND_RANGE_ITERATOR adjacent_find(Container& c, Pred pred)
{
    return std::adjacent_find(begin(c), end(c), pred);
}

template <class Container, class Pred>
inline SHAND_RANGE_CITERATOR adjacent_find(const Container& c, Pred pred)
{
    return std::adjacent_find(begin(c), end(c), pred);
}

// count
template <class Container, class Target>
inline size_t count(const Container& c, const Target& value)
{
    return std::count(begin(c), end(c), value);
}

// count_if
template <class Container, class Pred>
inline typename size_t count_if(const Container& c, Pred pred)
{
    return std::count_if(begin(c), end(c), pred);
}

// mismatch
template <class Container, class InputIterator>
inline std::pair<SHAND_RANGE_ITERATOR, InputIterator> mismatch(Container& c, InputIterator first)
{
    return std::mismatch(begin(c), end(c), first);
}

template <class Container, class InputIterator, class Pred>
inline std::pair<SHAND_RANGE_ITERATOR, InputIterator> mismatch(Container& c, InputIterator first, Pred pred)
{
    return std::mismatch(begin(c), end(c), first, pred);
}

template <class Container, class InputIterator>
inline std::pair<SHAND_RANGE_CITERATOR, InputIterator> mismatch(const Container& c, InputIterator first)
{
    return std::mismatch(begin(c), end(c), first);
}

template <class Container, class InputIterator, class Pred>
inline std::pair<SHAND_RANGE_CITERATOR, InputIterator> mismatch(const Container& c, InputIterator first, Pred pred)
{
    return std::mismatch(begin(c), end(c), first, pred);
}

// equal
template <class Container, class InputIterator>
inline bool equal(const Container& c, InputIterator first)
{
    return std::equal(begin(c), end(c), first);
}

template <class Container, class InputIterator, class Pred>
inline bool equal(const Container& c, InputIterator first, Pred pred)
{
    return std::equal(begin(c), end(c), first, pred);
}

// search
template <class LContainer, class RContainer>
inline typename range_iterator<LContainer>::type search(LContainer& lhs, RContainer& rhs)
{
    return std::search(begin(lhs), end(lhs), begin(rhs), end(rhs));
}

template <class LContainer, class RContainer, class BynaryPred>
inline typename range_iterator<LContainer>::type search(LContainer& lhs, RContainer& rhs, BynaryPred pred)
{
    return std::search(begin(lhs), end(lhs), begin(rhs), end(rhs), pred);
}

template <class LContainer, class RContainer>
inline typename range_iterator<const LContainer>::type search(const LContainer& lhs, const RContainer& rhs)
{
    return std::search(begin(lhs), end(lhs), begin(rhs), end(rhs));
}

template <class LContainer, class RContainer, class BynaryPred>
inline typename range_iterator<const LContainer>::type search(const LContainer& lhs, const RContainer& rhs, BynaryPred pred)
{
    return std::search(begin(lhs), end(lhs), begin(rhs), end(rhs), pred);
}

// copy
template <class Container, class OutputIterator>
inline OutputIterator copy(const Container& c, OutputIterator result)
{
    return std::copy(begin(c), end(c), result);
}

// copy_backward
template <class Container, class BidirectionalIterator>
inline BidirectionalIterator copy_backward(const Container& c, BidirectionalIterator result)
{
    return std::copy_backward(begin(c), end(c), result);
}

// transform
template <class Container, class OutputIterator, class UnaryOperation>
inline OutputIterator transform(const Container& c, OutputIterator result, UnaryOperation op)
{
    return std::transform(begin(c), end(c), result, op);
}

template <class Container, class InputIterator, class OutputIterator, class BynaryOperation>
inline OutputIterator transform(const Container& c, InputIterator first, OutputIterator result, BynaryOperation op)
{
    return std::transform(begin(c), end(c), first, result, op);
}

// replace
template <class Container, class Target>
inline void replace(Container& c, const Target& old_value, const Target& new_value)
{
    std::replace(begin(c), end(c), old_value, new_value);
}

// replace_if
template <class Container, class Predicate, class Target>
inline void replace_if(Container& c, Predicate pred, const Target& new_value)
{
    std::replace_if(begin(c), end(c), pred, new_value);
}

// replace_copy
template <class Container, class OutputIterator, class Target>
inline OutputIterator replace_copy(const Container& c, OutputIterator result, const Target& old_value, const Target& new_value)
{
    return std::replace_copy(begin(c), end(c), result, old_value, new_value);
}

// replace_copy_if
template <class Container, class OutputIterator, class Predicate, class Target>
inline OutputIterator replace_copy_if(const Container& c, OutputIterator result, Predicate pred, const Target& new_value)
{
    return std::replace_copy_if(begin(c), end(c), result, pred, new_value);
}

// fill
template <class Container, class Target>
inline void fill(Container& c, const Target& value)
{
    std::fill(begin(c), end(c), value);
}

// generate
template <class Container, class Generator>
inline void generate(Container& c, Generator gen)
{
    return std::generate(begin(c), end(c), gen);
}

// remove
template <class Container, class Target>
inline SHAND_RANGE_ITERATOR remove(Container& c, const Target& value)
{
    return std::remove(begin(c), end(c), value);
}

// remove_if
template <class Container, class Pred>
inline SHAND_RANGE_ITERATOR remove_if(Container& c, Pred pred)
{
    return std::remove_if(begin(c), end(c), pred);
}

// remove_copy
template <class Container, class OutputIterator, class Target>
inline OutputIterator remove_copy(const Container& c, OutputIterator result, const Target& value)
{
    return std::remove_copy(begin(c), end(c), result, value);
}

// remove_copy_if
template <class Container, class OutputIterator, class Pred>
inline OutputIterator remove_copy_if(const Container& c, OutputIterator result, Pred pred)
{
    return std::remove_copy_if(begin(c), end(c), result, pred);
}

// unique
template <class Container>
inline SHAND_RANGE_ITERATOR unique(Container& c)
{
    return std::unique(begin(c), end(c));
}

template <class Container, class BynaryPred>
inline SHAND_RANGE_ITERATOR unique(Container& c, BynaryPred pred)
{
    return std::unique(begin(c), end(c), pred);
}

// unique_copy
template <class Container, class OutputIterator>
inline OutputIterator unique_copy(const Container& c, OutputIterator result)
{
    return std::unique_copy(begin(c), end(c), result);
}

template <class Container, class OutputIterator, class BynaryPred>
inline OutputIterator unique_copy(const Container& c, OutputIterator result, BynaryPred pred)
{
    return std::unique_copy(begin(c), end(c), result, pred);
}

// reverse
template <class Container>
inline void reverse(Container& c)
{
    std::reverse(begin(c), end(c));
}

// reverse_copy
template <class Container, class OutputIterator>
inline OutputIterator reverse_copy(Container& c, OutputIterator result)
{
    return std::reverse_copy(begin(c), end(c), result);
}

// random_shuffle
template <class Container>
inline void random_shuffle(Container& c)
{
    std::random_shuffle(begin(c), end(c));
}

template <class Container, class RandomNumberGenerator>
inline void random_shuffle(Container& c, RandomNumberGenerator& gen)
{
    std::random_shuffle(begin(c), end(c), gen);
}

// partition
template <class Container, class Pred>
inline SHAND_RANGE_ITERATOR partition(Container& c, Pred pred)
{
    return std::partition(begin(c), end(c), pred);
}

// stable_partition
template <class Container, class Pred>
inline SHAND_RANGE_ITERATOR stable_partition(Container& c, Pred pred)
{
    return std::stable_partition(begin(c), end(c), pred);
}

// sort
template <class Container>
inline void sort(Container& c)
{
    std::sort(begin(c), end(c));
}

template <class Container, class Compare>
inline void sort(Container& c, Compare comp)
{
    std::sort(begin(c), end(c), comp);
}

// stable_sort
template <class Container>
inline void stable_sort(Container& c)
{
    std::stable_sort(begin(c), end(c));
}

template <class Container, class Compare>
inline void stable_sort(Container& c, Compare comp)
{
    std::stable_sort(begin(c), end(c), comp);
}

// lower_bound
template <class Container, class Target>
inline SHAND_RANGE_ITERATOR lower_bound(Container& c, const Target& value)
{
    return std::lower_bound(begin(c), end(c), value);
}

template <class Container, class Target, class Compare>
inline SHAND_RANGE_ITERATOR lower_bound(Container& c, const Target& value, Compare comp)
{
    return std::lower_bound(begin(c), end(c), value, comp);
}

template <class Container, class Target>
inline SHAND_RANGE_CITERATOR lower_bound(const Container& c, const Target& value)
{
    return std::lower_bound(begin(c), end(c), value);
}

template <class Container, class Target, class Compare>
inline SHAND_RANGE_CITERATOR lower_bound(const Container& c, const Target& value, Compare comp)
{
    return std::lower_bound(begin(c), end(c), value, comp);
}

// upper_bound
template <class Container, class Target>
inline SHAND_RANGE_ITERATOR upper_bound(Container& c, const Target& value)
{
    return std::upper_bound(begin(c), end(c), value);
}

template <class Container, class Target, class Compare>
inline SHAND_RANGE_ITERATOR upper_bound(Container& c, const Target& value, Compare comp)
{
    return std::upper_bound(begin(c), end(c), value, comp);
}

template <class Container, class Target>
inline SHAND_RANGE_CITERATOR upper_bound(const Container& c, const Target& value)
{
    return std::upper_bound(begin(c), end(c), value);
}

template <class Container, class Target, class Compare>
inline SHAND_RANGE_CITERATOR upper_bound(const Container& c, const Target& value, Compare comp)
{
    return std::upper_bound(begin(c), end(c), value, comp);
}

// binary_search
template <class Container, class Target>
inline bool binary_search(const Container& c, const Target& value)
{
    return std::binary_search(begin(c), end(c), value);
}

template <class Container, class Target, class Compare>
inline bool binary_search(const Container& c, const Target& value, Compare comp)
{
    return std::binary_search(begin(c), end(c), value, comp);
}

// merge
template <class LContainer, class RContainer, class OutputIterator>
inline OutputIterator merge(const LContainer& lhs, const RContainer& rhs, OutputIterator result)
{
    return std::merge(begin(lhs), end(lhs), begin(rhs), end(rhs), result);
}

template <class LContainer, class RContainer, class OutputIterator, class Compare>
inline OutputIterator merge(const LContainer& lhs, const RContainer& rhs, OutputIterator result, Compare comp)
{
    return std::merge(begin(lhs), end(lhs), begin(rhs), end(rhs), result, comp);
}

// includes
template <class LContainer, class RContainer>
inline bool includes(const LContainer& lhs, const RContainer& rhs)
{
    return std::includes(begin(lhs), end(lhs), begin(rhs), end(rhs));
}

template <class LContainer, class RContainer, class Compare>
inline bool includes(const LContainer& lhs, const RContainer& rhs, Compare comp)
{
    return std::includes(begin(lhs), end(lhs), begin(rhs), end(rhs), comp);
}

// set_union
template <class LContainer, class RContainer, class OutputIterator>
inline OutputIterator set_union(const LContainer& lhs, const RContainer& rhs, OutputIterator result)
{
    return std::set_union(begin(lhs), end(lhs), begin(rhs), end(rhs), result);
}

template <class LContainer, class RContainer, class OutputIterator, class Compare>
inline OutputIterator set_union(const LContainer& lhs, const RContainer& rhs, OutputIterator result, Compare comp)
{
    return std::set_union(begin(lhs), end(lhs), begin(rhs), end(rhs), result, comp);
}

// set_intersection
template <class LContainer, class RContainer, class OutputIterator>
inline OutputIterator set_intersection(const LContainer& lhs, const RContainer& rhs, OutputIterator result)
{
    return std::set_intersection(begin(lhs), end(lhs), begin(rhs), end(rhs), result);
}

template <class LContainer, class RContainer, class OutputIterator, class Compare>
inline OutputIterator set_intersection(const LContainer& lhs, const RContainer& rhs, OutputIterator result, Compare comp)
{
    return std::set_intersection(begin(lhs), end(lhs), begin(rhs), end(rhs), result, comp);
}

// set_difference
template <class LContainer, class RContainer, class OutputIterator>
inline OutputIterator set_difference(const LContainer& lhs, const RContainer& rhs, OutputIterator result)
{
    return std::set_difference(begin(lhs), end(lhs), begin(rhs), end(rhs), result);
}

template <class LContainer, class RContainer, class OutputIterator, class Compare>
inline OutputIterator set_difference(const LContainer& lhs, const RContainer& rhs, OutputIterator result, Compare comp)
{
    return std::set_difference(begin(lhs), end(lhs), begin(rhs), end(rhs), result, comp);
}

// set_symmetric_difference
template <class LContainer, class RContainer, class OutputIterator>
inline OutputIterator set_symmetric_difference(const LContainer& lhs, const RContainer& rhs, OutputIterator result)
{
    return std::set_symmetric_difference(begin(lhs), end(lhs), begin(rhs), end(rhs), result);
}

template <class LContainer, class RContainer, class OutputIterator, class Compare>
inline OutputIterator set_symmetric_difference(const LContainer& lhs, const RContainer& rhs, OutputIterator result, Compare comp)
{
    return std::set_symmetric_difference(begin(lhs), end(lhs), begin(rhs), end(rhs), result, comp);
}

// push_heap
template <class Container>
inline void push_heap(Container& c)
{
    std::push_heap(begin(c), end(c));
}

template <class Container, class Compare>
inline void push_heap(Container& c, Compare comp)
{
    std::push_heap(begin(c), end(c), comp);
}

// pop_heap
template <class Container>
inline void pop_heap(Container& c)
{
    std::pop_heap(begin(c), end(c));
}

template <class Container, class Compare>
inline void pop_heap(Container& c, Compare comp)
{
    std::pop_heap(begin(c), end(c), comp);
}

// make_heap
template <class Container>
inline void make_heap(Container& c)
{
    std::make_heap(begin(c), end(c));
}

template <class Container, class Compare>
inline void make_heap(Container& c, Compare comp)
{
    std::make_heap(begin(c), end(c), comp);
}

// sort_heap
template <class Container>
inline void sort_heap(Container& c)
{
    std::sort_heap(begin(c), end(c));
}

template <class Container, class Compare>
inline void sort_heap(Container& c, Compare comp)
{
    std::sort_heap(begin(c), end(c), comp);
}

// min_element
template <class Container>
inline SHAND_RANGE_ITERATOR min_element(Container& c)
{
    return std::min_element(begin(c), end(c));
}

template <class Container, class Compare>
inline SHAND_RANGE_ITERATOR min_element(Container& c, Compare comp)
{
    return std::min_element(begin(c), end(c), comp);
}

template <class Container>
inline SHAND_RANGE_CITERATOR min_element(const Container& c)
{
    return std::min_element(begin(c), end(c));
}

template <class Container, class Compare>
inline SHAND_RANGE_CITERATOR min_element(const Container& c, Compare comp)
{
    return std::min_element(begin(c), end(c), comp);
}

// max_element
template <class Container>
inline SHAND_RANGE_ITERATOR max_element(Container& c)
{
    return std::max_element(begin(c), end(c));
}

template <class Container, class Compare>
inline SHAND_RANGE_ITERATOR max_element(Container& c, Compare comp)
{
    return std::max_element(begin(c), end(c), comp);
}

template <class Container>
inline SHAND_RANGE_CITERATOR max_element(const Container& c)
{
    return std::max_element(begin(c), end(c));
}

template <class Container, class Compare>
inline SHAND_RANGE_CITERATOR max_element(const Container& c, Compare comp)
{
    return std::max_element(begin(c), end(c), comp);
}

// lexicographical_compare
template <class LContainer, class RContainer>
inline bool lexicographical_compare(const LContainer& lhs, const RContainer& rhs)
{
    return std::lexicographical_compare(begin(lhs), end(lhs), begin(rhs), end(rhs));
}

template <class LContainer, class RContainer, class Compare>
inline bool lexicographical_compare(const LContainer& lhs, const RContainer& rhs, Compare comp)
{
    return std::lexicographical_compare(begin(lhs), end(lhs), begin(rhs), end(rhs), comp);
}

// next_permutation
template <class Container>
inline bool next_permutation(Container& c)
{
    return std::next_permutation(begin(c), end(c));
}

template <class Container, class Compare>
inline bool next_permutation(Container& c, Compare comp)
{
    return std::next_permutation(begin(c), end(c), comp);
}

// prev_permutation
template <class Container>
inline bool prev_permutation(Container& c)
{
    return std::prev_permutation(begin(c), end(c));
}

template <class Container, class Compare>
inline bool prev_permutation(Container& c, Compare comp)
{
    return std::prev_permutation(begin(c), end(c), comp);
}
#endif SHAND_SUPPORT_SFINAE

} // namespace shand


// delete macro
#undef SHAND_RANGE_ITERATOR
#undef SHAND_RANGE_CITERATOR
#undef SHAND_SUPPORT_SFINAE


#endif // SHAND_ALGORITHM_INCLUDE


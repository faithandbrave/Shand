#ifndef SHAND_JOIN_INCLUDE
#define SHAND_JOIN_INCLUDE

// Copyright Akira Takahashi 2007
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <iterator>
#include <vector>
#include <algorithm>

namespace shand {

    namespace join_detail {
        // range begin, end
        template <class Type, int Size>
        inline Type* begin(Type (&ar)[Size]) { return ar; }

        template <class Type, int Size>
        inline Type* end(Type (&ar)[Size]) { return ar + Size; }

        template <class Container>
        inline typename Container::iterator begin(Container& c) { return c.begin(); }

        template <class Container>
        inline typename Container::const_iterator begin(const Container& c) { return c.begin(); }

        template <class Container>
        inline typename Container::iterator end(Container& c) { return c.end(); }

        template <class Container>
        inline typename Container::const_iterator end(const Container& c) { return c.end(); }

        // range_value
        template <class Container>
        struct range_value {
            typedef typename Container::value_type type;
        };

        template <class Type, int Size>
        struct range_value< Type[Size] > {
            typedef Type type;
        };

        template <class Type, int Size>
        struct range_value< const Type[Size] > {
            typedef Type type;
        };

    } // namespace shand::join_detail

template <class Type>
class jointer {
    std::vector<Type> elements_;

public:
    typedef Type                                        value_type;
    typedef Type                                        difference_type;
    typedef Type&                                       reference;
    typedef typename std::vector<Type>::iterator        iterator;
    typedef typename std::vector<Type>::const_iterator  const_iterator;

    template<class Iterator>
    jointer(Iterator first, Iterator last) : elements_(first, last) {}

    iterator        begin()         { return elements_.begin(); }
    const_iterator  begin() const   { return elements_.begin(); }
    iterator        end()           { return elements_.end(); }
    const_iterator  end() const     { return elements_.end(); }

    template <class Iterator>
    void push(Iterator first, Iterator last) { std::copy(first, last, std::back_inserter(elements_)); }
};

template <class T0, class T1>
inline jointer<T0> operator|(const jointer<T0>& lhs, const jointer<T1>& rhs)
{
    jointer<T0> c(join_detail::begin(lhs), join_detail::end(lhs));
    c.push(join_detail::begin(rhs), join_detail::end(rhs));
    return c;
}

template <class Container>
inline jointer<typename join_detail::range_value<Container>::type> join(const Container& c)
{
    return jointer<typename join_detail::range_value<Container>::type>(join_detail::begin(c), join_detail::end(c));
}


// variadic join
template <class T0, class T1>
inline jointer<typename join_detail::range_value<T0>::type> join(const T0& t0, const T1& t1)
{
    return join(t0)|join(t1);
}

template <class T0, class T1, class T2>
inline jointer<typename join_detail::range_value<T0>::type> join(const T0& t0, const T1& t1, const T2& t2)
{
    return join(t0, t1)|join(t2);
}

template <class T0, class T1, class T2, class T3>
inline jointer<typename join_detail::range_value<T0>::type> join(const T0& t0, const T1& t1, const T2& t2, const T3& t3)
{
    return join(t0, t1, t2)|join(t3);
}

template <class T0, class T1, class T2, class T3, class T4>
inline jointer<typename join_detail::range_value<T0>::type> join(const T0& t0, const T1& t1, const T2& t2, const T3& t3,
                                                                 const T4& t4)
{
    return join(t0, t1, t2, t3)|join(t4);
}

template <class T0, class T1, class T2, class T3, class T4, class T5>
inline jointer<typename join_detail::range_value<T0>::type> join(const T0& t0, const T1& t1, const T2& t2, const T3& t3,
                                                                 const T4& t4, const T5& t5)
{
    return join(t0, t1, t2, t3, t4)|join(t5);
}

template <class T0, class T1, class T2, class T3, class T4, class T5, class T6>
inline jointer<typename join_detail::range_value<T0>::type> join(const T0& t0, const T1& t1, const T2& t2, const T3& t3,
                                                                 const T4& t4, const T5& t5, const T6& t6)
{
    return join(t0, t1, t2, t3, t4, t5)|join(t6);
}

template <class T0, class T1, class T2, class T3, class T4, class T5, class T6, class T7>
inline jointer<typename join_detail::range_value<T0>::type> join(const T0& t0, const T1& t1, const T2& t2, const T3& t3,
                                                                 const T4& t4, const T5& t5, const T6& t6, const T7& t7)
{
    return join(t0, t1, t2, t3, t4, t5, t6)|join(t7);
}

template <class T0, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
inline jointer<typename join_detail::range_value<T0>::type> join(const T0& t0, const T1& t1, const T2& t2, const T3& t3,
                                                                 const T4& t4, const T5& t5, const T6& t6, const T7& t7,
                                                                 const T8& t8)
{
    return join(t0, t1, t2, t3, t4, t5, t6, t7)|join(t8);
}

template <class T0, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9>
inline jointer<typename join_detail::range_value<T0>::type> join(const T0& t0, const T1& t1, const T2& t2, const T3& t3,
                                                                 const T4& t4, const T5& t5, const T6& t6, const T7& t7,
                                                                 const T8& t8, const T9& t9)
{
    return join(t0, t1, t2, t3, t4, t5, t6, t7, t8)|join(t9);
}


} // namespace shand

#endif // SHAND_JOIN_INCLUDE


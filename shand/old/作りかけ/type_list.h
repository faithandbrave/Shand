#ifndef _SHAND_TYPE_LIST_H_
#define _SHAND_TYPE_LIST_H_

struct nil {};

template <class Car, class Cdr>
struct cons {
    typedef Car car;
    typedef Cdr cdr;
};


#define TYPELIST1(T0)                                     cons<T0, nil>
#define TYPELIST2(T0, T1)                                 cons<T0, TYPELIST1(T1) >
#define TYPELIST3(T0, T1, T2)                             cons<T0, TYPELIST2(T1, T2) >
#define TYPELIST4(T0, T1, T2, T3)                         cons<T0, TYPELIST3(T1, T2, T3) >
#define TYPELIST5(T0, T1, T2, T3, T4)                     cons<T0, TYPELIST4(T1, T2, T3, T4) >
#define TYPELIST6(T0, T1, T2, T3, T4, T5)                 cons<T0, TYPELIST5(T1, T2, T3, T4, T5) >
#define TYPELIST7(T0, T1, T2, T3, T4, T5, T6)             cons<T0, TYPELIST6(T1, T2, T3, T4, T5, T6) >
#define TYPELIST8(T0, T1, T2, T3, T4, T5, T6, T7)         cons<T0, TYPELIST7(T1, T2, T3, T4, T5, T6, T7) >
#define TYPELIST9(T0, T1, T2, T3, T4, T5, T6, T7, T8)     cons<T0, TYPELIST8(T1, T2, T3, T4, T5, T6, T7, T8) >
#define TYPELIST10(T0,T1, T2, T3, T4, T5, T6, T7, T8, T9) cons<T0, TYPELIST9(T1, T2, T3, T4, T5, T6, T7, T8, T9) >




/*
template <class T0>
using type_list1 = cons<T0, nil>;

template <class T0, class T1>
using type_list2 = cons<T0, type_list1<T1>>;

template <class T0, class T1, class T2>
using type_list3 = cons<T0, type_list2<T1, T2>>;

template <class T0, class T1, class T2, class T3>
using type_list4 = cons<T0, type_list3<T1, T2, T3>>;

template <class T0, class T1, class T2, class T3, class T4>
using type_list5 = cons<T0, type_list4<T1, T2, T3, T4>>;

template <class T0, class T1, class T2, class T3, class T4, class T5>
using type_list6 = cons<T0, type_list5<T1, T2, T3, T4, T5>>;

template <class T0, class T1, class T2, class T3, class T4, class T5, class T6>
using type_list7 = cons<T0, type_list6<T1, T2, T3, T4, T5, T6>>;

template <class T0, class T1, class T2, class T3, class T4, class T5, class T6, class T7>
using type_list8 = cons<T0, type_list7<T1, T2, T3, T4, T5, T6, T7>>;

template <class T0, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
using type_list9 = cons<T0, type_list8<T1, T2, T3, T4, T5, T6, T7, T8>>;

template <class T0, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9>
using type_list10 = cons<T0, type_list9<T1, T2, T3, T4, T5, T6, T7, T8, T9>>;
*/


template <class TypeList, int N>
struct nth {
    typedef typename nth<typename TypeList::cdr, N-1>::type type;
};

template <class TypeList>
struct nth<TypeList, 0> {
    typedef typename TypeList::car type;
};

template <class TypeList>
struct length {
    static const int value = length<typename TypeList::cdr>::value + 1;
};

template <>
struct length<nil> {
    static const int value = 0;
};


#endif // _SHAND_TYPE_LIST_H_


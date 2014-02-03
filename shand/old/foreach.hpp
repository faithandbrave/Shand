#ifndef SHAND_FOREACH_INCLUDE
#define SHAND_FOREACH_INCLUDE

// Copyright 2004 Eric Niebler.
// Copyright Akira Takahashi 2007
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

namespace shand { namespace foreach_detail {

struct static_any_base {
    operator bool() const { return false; }
};

template <class Type>
struct static_any : static_any_base {
    static_any(const Type& item) : item_(item) {}
    mutable Type item_;
};

typedef const static_any_base& static_any_t;


template <class Type>
inline Type& static_any_cast(static_any_t value)
{
    return static_cast<const static_any<Type>&>(value).item_;
}

template <class Type>
struct contain_type {
    typedef Type type;
};

template <class Type>
contain_type<Type>* encode_type(Type&)
{
    return 0;
}

#define SHAND_FOREACH_TYPEOF(COL) \
    (true ? 0 : shand::foreach_detail::encode_type(COL))


template <class Type>
inline static_any<Type> contain(const Type& col) // rvalue
{
    return col;
}

template <class Type>
inline static_any<Type> contain(Type& col) // lvalue
{
    return col;
}

template <class Type, int Size>
inline static_any<Type*> contain(Type (&col)[Size]) // lvalue
{
    return col;
}


// Array
template <class Type, int Size>
inline static_any<Type*> begin(static_any_t cur, contain_type<Type[Size]>*)
{
    return static_any_cast<Type*>(cur);
}

template <class Type, int Size>
inline static_any<Type*> end(static_any_t cur, contain_type<Type[Size]>*)
{
    return static_any_cast<Type*>(cur) + Size;
}

template <class Type, int Size>
inline void next(static_any_t cur, contain_type<Type[Size]>*)
{
    ++static_any_cast<Type*>(cur);
}

template <class Type, int Size>
inline Type& extract(static_any_t cur, contain_type<Type[Size]>*)
{
    return *static_any_cast<Type*>(cur);
}


template <class Type, int Size>
inline bool done(static_any_t cur, static_any_t end, contain_type<Type[Size]>*)
{
    return static_any_cast<Type*>(cur) == static_any_cast<Type*>(end);
}

// Container
template <class Type>
inline static_any<typename Type::iterator> begin(static_any_t cur, contain_type<Type>*)
{
    return static_any_cast<Type>(cur).begin();
}

template <class Type>
inline static_any<typename Type::const_iterator> begin(static_any_t cur, contain_type<const Type>*)
{
    return static_any_cast<Type>(cur).begin();
}

template <class Type>
inline static_any<typename Type::iterator> end(static_any_t cur, contain_type<Type>*)
{
    return static_any_cast<Type>(cur).end();
}

template <class Type>
inline static_any<typename Type::const_iterator> end(static_any_t cur, contain_type<const Type>*)
{
    return static_any_cast<Type>(cur).end();
}

template <class Type>
inline void next(static_any_t cur, contain_type<Type>*)
{
    ++static_any_cast<typename Type::iterator>(cur);
}

template <class Type>
inline typename Type::reference extract(static_any_t cur, contain_type<Type>*)
{
    return *static_any_cast<typename Type::iterator>(cur);
}

template <class Type>
inline bool done(static_any_t cur, static_any_t end, contain_type<Type>*)
{
    typedef typename Type::iterator Iter;
    return static_any_cast<Iter>(cur) == static_any_cast<Iter>(end);
}

// pair
template <class Type>
inline static_any<Type> begin(static_any_t cur, contain_type<std::pair<Type, Type> >*)
{
    return static_any_cast<std::pair<Type, Type> >(cur).first;
}

template <class Type>
inline static_any<Type> end(static_any_t cur, contain_type<std::pair<Type, Type> >*)
{
    return static_any_cast<std::pair<Type, Type> >(cur).second;
}

template <class Type>
inline void next(static_any_t cur, contain_type<std::pair<Type, Type> >*)
{
    ++static_any_cast<Type>(cur);
}

template <class Type>
inline typename Type::reference extract(static_any_t cur, contain_type<std::pair<Type, Type> >*)
{
    return *static_any_cast<Type>(cur);
}

template <class Type>
inline bool done(static_any_t cur, static_any_t end, contain_type<std::pair<Type, Type> >*)
{
    return static_any_cast<Type>(cur) == static_any_cast<Type>(end);
}


#define SHAND_FOREACH_CONTAIN(COL) \
    shand::foreach_detail::contain(COL)

#define SHAND_FOREACH_BEGIN(COL) \
    shand::foreach_detail::begin(_contain, SHAND_FOREACH_TYPEOF(COL))

#define SHAND_FOREACH_END(COL) \
    shand::foreach_detail::end(_contain, SHAND_FOREACH_TYPEOF(COL))

#define SHAND_FOREACH_DONE(COL) \
    shand::foreach_detail::done(_cur, _end, SHAND_FOREACH_TYPEOF(COL))

#define SHAND_FOREACH_NEXT(COL) \
    shand::foreach_detail::next(_cur, SHAND_FOREACH_TYPEOF(COL))

#define SHAND_FOREACH_EXTRACT(COL) \
    shand::foreach_detail::extract(_cur, SHAND_FOREACH_TYPEOF(COL))

// foreach macro
#define SHAND_FOREACH(VAR, COL)                                                                 \
        if       (shand::foreach_detail::static_any_t _contain = SHAND_FOREACH_CONTAIN(COL)) {} \
        else if  (shand::foreach_detail::static_any_t _cur     = SHAND_FOREACH_BEGIN(COL))   {} \
        else if  (shand::foreach_detail::static_any_t _end     = SHAND_FOREACH_END(COL))     {} \
        else for (bool _continue = true;                                                        \
                  _continue && !SHAND_FOREACH_DONE(COL);                                        \
                  _continue ? SHAND_FOREACH_NEXT(COL) : (void)0)                                \
                 if      ((_continue = false) == true) {}                                       \
                 else for (VAR = SHAND_FOREACH_EXTRACT(COL); !_continue; _continue = true)

#define foreach SHAND_FOREACH


//--------------------------------------------//
//              How to use                    //
//============================================//
// int ar[] = {3, 1, 4};                      //
// foreach (int value, ar) {                  //
//     cout << value << endl;                 //
// }                                          //
//                                            //
// vector<int> v;                             //
// foreach (int value, v) ...                 //
//                                            //
// foreach (int& value, v) {                  //
//     ++value;                               //
//--------------------------------------------//


}} // namespace shand::foreach_detail

#endif // SHAND_FOREACH_INCLUDE


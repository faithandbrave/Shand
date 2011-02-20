#ifndef SHAND_ENABLE_IF_INCLUDE
#define SHAND_ENABLE_IF_INCLUDE

namespace shand {

// enable_if
template <bool, class Type = void>
struct enable_if_c {
    typedef Type type;
};

template <class Type>
struct enable_if_c<false, Type> {};

template <class Cond, class Type = void> 
struct enable_if : public enable_if_c<Cond::value, Type> {};


// disable_if
template <bool, class Type = void>
struct disable_if_c {
    typedef Type type;
};

template <class Type>
struct disable_if_c<true, Type> {};

template <class Cond, class Type = void> 
struct disable_if : public disable_if_c<Cond::value, Type> {};

} // namespace shand

#endif // SHAND_ENABLE_IF_INCLUDE

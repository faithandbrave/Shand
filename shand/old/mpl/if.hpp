#ifndef SHAND_MPL_IF_INCLUDE
#define SHAND_MPL_IF_INCLUDE

namespace shand { namespace mpl {

// if_c
template <bool Cond, class Then, class Else>
struct if_c;

template <class Then, class Else>
struct if_c<true, Then, Else> {
    typedef Then type;
};

template <class Then, class Else>
struct if_c<false, Then, Else> {
    typedef Else type;
};


// if_
template <class Cond, class Then, class Else>
struct if_ {
    typedef typename if_c<Cond::value, Then, Else>::type type;
};

} } // namespace shand::mpl

#endif // SHAND_MPL_IF_INCLUDE


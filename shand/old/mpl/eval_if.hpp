#ifndef SHAND_MPL_EVAL_IF_INCLUDE
#define SHAND_MPL_EVAL_IF_INCLUDE

namespace shand { namespace mpl {

// eval_if_c
template <bool Cond, class Then, class Else>
struct eval_if_c;

template <class Then, class Else>
struct eval_if_c<true, Then, Else> {
    typedef typename Then::type type;
};

template <class Then, class Else>
struct eval_if_c<false, Then, Else> {
    typedef typename Else::type type;
};


// eval_if
template <class Cond, class Then, class Else>
struct eval_if {
    typedef typename eval_if_c<Cond::value, Then, Else>::type type;
};


}} // namespace shand::mpl

#endif // SHAND_MPL_EVAL_IF_INCLUDE


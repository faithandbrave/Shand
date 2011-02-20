#ifndef SHAND_MPL_TO_STRING_INCLUDE
#define SHAND_MPL_TO_STRING_INCLUDE

#include <boost/mpl/string.hpp>

namespace shand { namespace mpl {

namespace to_mpl_string_detail {

// digit : Œ…”‚ğŒvZ
template <int N, int Digit>
struct digit_impl {
    static const int value = digit_impl<N / 10, Digit + 1>::value;
};

template <int Digit>
struct digit_impl<0, Digit> {
    static const int value = Digit;
};

template <>
struct digit_impl<0, 0> {
    static const int value = 1;
};

template <int N>
struct digit {
    static const int value = digit_impl<N, 0>::value;
};


// digit_number : X‚ÌNŒ…–Ú‚ğæ“¾
template <int N, int X>
struct digit_pow {
    static const int value = digit_pow<N - 1, X>::value * X;
};

template <int X>
struct digit_pow<1, X> {
    static const int value = 1;
};

template <int X>
struct digit_pow<0, X> {
    static const int value = 1;
};

template <int X, int Digit>
struct digit_number {
    static const int value = X / digit_pow<Digit, 10>::value % 10;
};


// to_mpl_string : ®”‚ğmpl::string‚É•ÏŠ·
template <class String, int X, int Digit>
struct to_mpl_string_impl {
    typedef
        typename to_mpl_string_impl<
            typename boost::mpl::push_back<
                String,
                boost::mpl::char_<'0' + digit_number<X, Digit>::value>
            >::type,
            X,
            Digit - 1
        >::type
    type;
};

template <class String, int X>
struct to_mpl_string_impl<String, X, 0> {
    typedef String type;
};

} // namespace to_mpl_string_detail

template <int X>
struct to_string {
    typedef
        typename to_mpl_string_detail::to_mpl_string_impl<
            typename boost::mpl::string<>::type,
            X,
			to_mpl_string_detail::digit<X>::value
        >::type
    type;
};


}} // namespace shand::mpl


#endif // SHAND_MPL_TO_STRING_INCLUDE


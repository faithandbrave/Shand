#ifndef SHAND_IO_ADAPTOR_ADAPTED_STD_DEQUE_INCLUDE
#define SHAND_IO_ADAPTOR_ADAPTED_STD_DEQUE_INCLUDE

#include <boost/mpl/bool.hpp>
#include "../traits.hpp"

namespace std {

template <class T, class Alloc>
class deque;

} // namespace std

namespace shand { namespace io_adaptors {

template <class T, class Alloc>
struct is_adapted<std::deque<T, Alloc> > : boost::mpl::true_ {};

template <class T, class Alloc>
struct tag_of<std::deque<T, Alloc> > : boost::mpl::identity<range_tag> {};

}} // namespace shand::io_adaptors

#endif // SHAND_IO_ADAPTOR_ADAPTED_STD_DEQUE_INCLUDE



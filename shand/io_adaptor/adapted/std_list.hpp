#ifndef SHAND_IO_ADAPTOR_ADAPTED_STD_LIST_INCLUDE
#define SHAND_IO_ADAPTOR_ADAPTED_STD_LIST_INCLUDE

#include <boost/mpl/bool.hpp>
#include "../traits.hpp"

namespace std {

template <class T, class Alloc>
class list;

} // namespace std

namespace shand { namespace io_adaptors {

template <class T, class Alloc>
struct is_adapted<std::list<T, Alloc> > : boost::mpl::true_ {};

template <class T, class Alloc>
struct tag_of<std::list<T, Alloc> > : boost::mpl::identity<range_tag> {};

}} // namespace shand::io_adaptors

#endif // SHAND_IO_ADAPTOR_ADAPTED_STD_LIST_INCLUDE



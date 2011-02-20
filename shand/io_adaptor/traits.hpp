#ifndef SHAND_IO_ADAPTOR_TRAITS_INCLUDE
#define SHAND_IO_ADAPTOR_TRAITS_INCLUDE

#include <boost/mpl/identity.hpp>
#include <boost/mpl/void.hpp>

namespace shand { namespace io_adaptors {

template <class Seq, class EnableIfDummy = boost::mpl::void_>
struct is_adapted : boost::mpl::false_ {};

struct none_tag {};
struct range_tag {};
struct fusion_tag {};

template <class T, class EnableIfDummy = boost::mpl::void_>
struct tag_of : boost::mpl::identity<none_tag> {};

}} // namespace shand::io_adaptors

#endif // SHAND_IO_ADAPTOR_TRAITS_INCLUDE


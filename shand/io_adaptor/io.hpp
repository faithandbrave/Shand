#ifndef SHAND_IO_ADAPTOR_IO_HPP
#define SHAND_IO_ADAPTOR_IO_HPP

#include <ostream>
#include <boost/mpl/bool.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/range.hpp>
#include "./traits.hpp"

namespace shand { namespace io_adaptors {

template <class Seq>
inline void out(std::ostream& os, const Seq& seq);

template <class T>
inline void out_detail(std::ostream& os, const T& x, none_tag)
{
    os << x;
}

template <class Seq>
inline void out_detail(std::ostream& os, const Seq& seq, range_tag)
{
    out(os, '{');

    typedef typename boost::range_iterator<const Seq>::type iterator;
    iterator first = boost::begin(seq);
    iterator last = boost::end(seq);

    bool is_beginning = true;
    for (; first != last; ++first) {
        if (!is_beginning)
            out(os, ',');
        else
            is_beginning = false;

        out(os, *first);
    }

    out(os, '}');
}

template <class Seq>
inline void out(std::ostream& os, const Seq& seq)
{
    out_detail(os, seq, typename tag_of<Seq>::type());
}

namespace operators {

    template <class Seq>
    inline typename boost::enable_if<
            is_adapted<Seq>,
            std::ostream&
    >::type operator<<(std::ostream& os, const Seq& seq)
    {
        io_adaptors::out(os, seq);
        return os;
    }

} // namespace operators

}} // namespace shand::io_adaptors

#endif // SHAND_IO_ADAPTOR_IO_HPP


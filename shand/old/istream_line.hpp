#ifndef SHAND_ISTREAM_LINE_INCLUDE
#define SHAND_ISTREAM_LINE_INCLUDE

// Copyright Akira Takahashi 2007
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <iosfwd>
#include <string>

namespace shand {

template <class CharT,
          class Traits = std::char_traits<CharT>,
          class Allocator = std::allocator<CharT> >
class istream_line_iterator {
public:
    typedef CharT                                       char_type;
    typedef Traits                                      traits_type;
    typedef Allocator                                   allocator_type;
    typedef std::basic_istream<CharT, Traits>           istream_type;
    typedef std::basic_string<CharT, Traits, Allocator> string_type;

    typedef std::forward_iterator_tag   iterator_category;
    typedef string_type                 value_type;
    typedef size_t                      difference_type;
    typedef string_type*                pointer;
    typedef string_type&                reference;

    istream_line_iterator()
        : in_ptr_(0), delim_(), line_(){}

    explicit istream_line_iterator(istream_type& is)
        : in_ptr_(&is), delim_(is.widen('\n')), line_()
    {
        increment();
    }

    istream_line_iterator(istream_type& is, CharT delim)
        : in_ptr_(&is), delim_(delim), line_()
    {
        increment();
    }

    istream_line_iterator& operator++ () { increment(); return *this; }
    istream_line_iterator operator++ (int) { istream_line_iterator own(*this); increment(); return own; }
    string_type& operator* () { return dereference(); }
    bool operator== (const istream_line_iterator& rhs) const { return equal(rhs); }
    bool operator!= (const istream_line_iterator& rhs) const { return !equal(rhs); }

private:
    istream_type*   in_ptr_;
    CharT           delim_;
    string_type     line_;

    string_type& dereference()
    {
        return line_;
    }

    void increment()
    {
        if (!std::getline(*in_ptr_, line_, delim_))
            in_ptr_ = 0;
    }

    bool equal(const istream_line_iterator& rhs) const
    {
        return in_ptr_ == rhs.in_ptr_;
    }
};

template<typename CharT, typename Traits>
std::pair<istream_line_iterator<CharT, Traits>, istream_line_iterator<CharT, Traits> >
make_istream_line_range(std::basic_istream<CharT, Traits>& is)
{
    typedef istream_line_iterator<CharT, Traits> istream_line_iterator_t;
    return std::make_pair(istream_line_iterator_t(is), istream_line_iterator_t());
}

} // namespace shand

#endif // SHAND_ISTREAM_LINE_INCLUDE


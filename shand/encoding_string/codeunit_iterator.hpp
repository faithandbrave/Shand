#ifndef SHAND_ENCODING_STRING_CODEUNIT_ITERATOR_INCLUDE
#define SHAND_ENCODING_STRING_CODEUNIT_ITERATOR_INCLUDE

// Copyright Akira Takahashi 2013
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <cassert>
#include <string>
#include <stdexcept>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/optional.hpp>
#include <boost/utility/string_ref.hpp>

namespace shand {

template <class StringDataType,
          class ElementStringType,
          class SizeGetter,
          class BomSkipper>
class codeunit_iterator :
    public boost::iterator_facade<
        codeunit_iterator<StringDataType, ElementStringType, SizeGetter, BomSkipper>,
        ElementStringType,
        boost::single_pass_traversal_tag,
        ElementStringType
    >
{
    boost::optional<StringDataType> data_;
    boost::optional<std::size_t> pos_;
    boost::optional<std::size_t> size_;
public:
    codeunit_iterator() {}

    codeunit_iterator(const StringDataType& data)
        : data_(data)
    {
        if (data_.get().empty()) {
            pos_ = boost::none;
        }
        else {
            pos_ = BomSkipper()(data);
        }
    }

private:
    friend class boost::iterator_core_access;

    void increment()
    {
        assert(pos_);

        const std::size_t size = SizeGetter()(data_.get(), pos_.get());

        pos_.get() += size;
        size_ = size;

        if (pos_.get() >= data_.get().size())
            pos_ = boost::none;
    }

    ElementStringType dereference() const
    {
        assert(pos_);

        std::size_t size = 0;
        if (size_) {
            size = size_.get();
        }
        else {
            size = SizeGetter()(data_.get(), pos_.get());
        }
        return StringDataType(data_.get(), pos_.get(), size).c_str();
    }

    bool equal(const codeunit_iterator& other) const
    {
        return pos_ == other.pos_;
    }
};

} // namespace shand

#endif // SHAND_ENCODING_STRING_CODEUNIT_ITERATOR_INCLUDE


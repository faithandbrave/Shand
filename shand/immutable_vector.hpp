#ifndef SHAND_IMMUTABLE_VECTOR_INCLUDE
#define SHAND_IMMUTABLE_VECTOR_INCLUDE

// Copyright Akira Takahashi 2014
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <vector>
#include <utility>
#include <boost/config.hpp>
#include <boost/optional.hpp>

namespace shand {

template <class T, class Alloc = std::allocator<T>>
using vector_builder = std::vector<T, Alloc>;

template <class T, class Alloc = std::allocator<T>>
class immutable_vector {
    std::vector<T, Alloc> vec_;
public:
    using vector_type       = std::vector<T, Alloc>;
    using iterator          = typename vector_type::const_iterator;
    using const_iterator    = typename vector_type::const_iterator;
    using value_type        = typename vector_type::value_type;
    using const_reference   = typename vector_type::const_reference;
    using size_type         = typename vector_type::size_type;
    using difference_type   = typename vector_type::difference_type;

    immutable_vector() {}
    immutable_vector(vector_builder<T, Alloc>&& builder)
        : vec_(std::move(builder)) {}

    immutable_vector(const immutable_vector&) = delete;
    immutable_vector& operator=(const immutable_vector&) = delete;

    void build(vector_builder<T, Alloc>&& builder)
    {
        vec_ = std::move(builder);
    }

    const_iterator begin() const BOOST_NOEXCEPT { return vec_.cbegin(); }
    const_iterator cbegin() const BOOST_NOEXCEPT { return vec_.cbegin(); }

    const_iterator end() const BOOST_NOEXCEPT { return vec_.cend(); }
    const_iterator cend() const BOOST_NOEXCEPT { return vec_.cend(); }

    size_type size() const BOOST_NOEXCEPT { return vec_.size(); }
    bool empty() const BOOST_NOEXCEPT { return vec_.empty(); }

    const_reference operator[](size_type n) const
    { return vec_[n]; }

    const_reference at(size_type n) const
    { return vec_.at(n); }

    boost::optional<const_reference> opt_at(size_t n) const BOOST_NOEXCEPT
    {
        if (n < size())
            return vec_[n];
        return boost::none;
    }

    boost::optional<const_reference> opt_front() const BOOST_NOEXCEPT
    {
        if (!empty())
            return vec_[0u];
        return boost::none;
    }

    boost::optional<const_reference> opt_back() const BOOST_NOEXCEPT
    {
        if (!empty())
            return vec_[size() - 1u];
        return boost::none;
    }

    // reference raw data
    const T* data() const BOOST_NOEXCEPT { return vec_.data(); }
    const vector_type& get() const { return vec_; }
};

} // namespace shand

#endif // SHAND_IMMUTABLE_VECTOR_INCLUDE


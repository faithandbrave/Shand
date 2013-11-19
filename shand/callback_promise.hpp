#ifndef SHAND_CALLBACK_PROMISE_INCLUDE
#define SHAND_CALLBACK_PROMISE_INCLUDE

// Callback promise class. (single thread only yet)
//
// Copyright Akira Takahashi 2013
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/optional.hpp>
#include <boost/function.hpp>
 
namespace shand {
 
template <class R>
class callback_promise {
    boost::optional<R> value_;
    boost::function<void(const R&)> callback_;
public:
    void set_value(const R& value)
    {
        value_ = value;
        if (callback_) {
            callback_(value);
        }
    }

    template <class F>
    void set_callback(F callback)
    {
        callback_ = callback;
        if (value_) {
            callback_(value_.get());
        }
    }

    void clear()
    {
        value_ = boost::none;
        callback_.clear();
    }
};

template <>
class callback_promise<void> {
    bool has_value_;
    boost::function<void()> callback_;
public:
    callback_promise()
        : has_value_(false) {}

    void set_value()
    {
        has_value_ = true;
        if (callback_) {
            callback_();
        }
    }

    template <class F>
    void set_callback(F callback)
    {
        callback_ = callback;
        if (has_value_) {
            callback_();
        }
    }

    void clear()
    {
        has_value_ = false;
        callback_.clear();
    }
};
 
} // namespace shand

#endif // SHAND_CALLBACK_PROMISE_INCLUDE


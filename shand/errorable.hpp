#ifndef SHAND_ERRORABLE_INCLUDE
#define SHAND_ERRORABLE_INCLUDE

// Shand C++ Library
//
// Copyright Akira Takahashi 2013
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <string>
#include <boost/type_traits/decay.hpp>
#include <boost/variant.hpp>
#include <boost/optional.hpp>

namespace shand {

template <class T>
class error_t {
    T value_;
public:
    error_t() : value_() {}

    error_t(const T& value)
        : value_(value) {}

    template <class U>
    error_t(const error_t<U>& other)
        : value_(other.what()) {}
 
    const T& what() const
    {
        return value_;
    }
};

template <class T>
error_t<typename boost::decay<T>::type> error(T&& value)
{
    return error_t<typename boost::decay<T>::type>(value);
}

template <class T, class ErrorType=std::string>
class errorable {
    boost::variant<error_t<ErrorType>, T> value_;
public:
    errorable() {}

    template <class ErrorTypeU>
    errorable(const error_t<ErrorTypeU>& err)
        : value_(error_t<ErrorType>(err)) {}
 
    errorable(const T& value)
        : value_(value) {}
 
    errorable& operator=(const error_t<ErrorType>& err)
    {
        value_ = err;
        return *this;
    }
 
    errorable& operator=(const T& value)
    {
        value_ = value;
        return *this;
    }
 
    boost::optional<T> get_value() const
    {
        if (value_.which() == 1) {
            return boost::get<T>(value_);
        }
        return boost::none;
    }
 
    boost::optional<ErrorType> get_error() const
    {
        if (value_.which() == 0) {
            return boost::get<error_t<ErrorType>>(value_).what();
        }
        return boost::none;
    }
 
    bool is_error() const { return value_.which() == 0; }
 
    template <class F>
    const errorable& value_if(F f) const
    {
        if (value_.which() == 1) {
            f(boost::get<T>(value_));
        }
        return *this;
    }
 
    template <class F>
    const errorable& error_if(F f) const
    {
        if (value_.which() == 0) {
            f(boost::get<error_t<ErrorType>>(value_).what());
        }
        return *this;
    }
};


} // namespace shand

#endif // SHAND_ERRORABLE_INCLUDE


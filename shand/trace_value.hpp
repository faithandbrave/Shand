#ifndef SHAND_TRACE_VALUE_INCLUDE
#define SHAND_TRACE_VALUE_INCLUDE

// `trace_value` class records stacktrace when modify operation.

// Copyright Akira Takahashi 2016
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <ostream>
#include <sstream>
#include <boost/stacktrace.hpp> // https://github.com/apolukhin/stacktrace

namespace shand {

template <class ArithmeticType>
class trace_value {
    ArithmeticType value_ {0};
    boost::stacktrace::stacktrace trace_;

    template <class F>
    trace_value& modify_this(F f)
    {
        trace_ = boost::stacktrace::stacktrace();
        f();
        return *this;
    }

    template <class F>
    void modify(F f)
    {
        trace_ = boost::stacktrace::stacktrace();
        f();
    }

public:
    using value_type = ArithmeticType;

    value_type& get() { return value_; }
    const value_type& get() const { return value_; }

    trace_value() = default;
    trace_value(ArithmeticType x)
        : value_(x) {}

    trace_value& operator=(const trace_value& x)
    {
        return modify_this([this, x] { value_ = x.get(); });
    }

    trace_value& operator=(ArithmeticType x)
    {
        return modify_this([this, x] { value_ = x; });
    }

    trace_value& operator+=(ArithmeticType x)
    {
        return modify_this([this, x] { value_ += x; });
    }

    trace_value& operator-=(ArithmeticType x)
    {
        return modify_this([this, x] { value_ -= x; });
    }

    trace_value& operator*=(ArithmeticType x)
    {
        return modify_this([this, x] { value_ *= x; });
    }

    trace_value& operator/=(ArithmeticType x)
    {
        return modify_this([this, x] { value_ /= x; });
    }

    trace_value operator%=(ArithmeticType x)
    {
        return modify_this([this, x] { value_ %= x; });
    }

    trace_value& operator++()
    {
        return modify_this([this] { ++value_; });
    }

    trace_value operator++(int)
    {
        trace_value result = *this;
        modify([this] { ++value_; });
        return result;
    }

    trace_value& operator--()
    {
        return modify_this([this] { --value_; });
    }

    trace_value operator--(int)
    {
        trace_value result = *this;
        modify([this] { --value_; });
        return result;
    }

    // output stacktrace to `os`
    void output_trace(std::ostream& os) const
    {
        os << trace_;
    }

    // get stacktrace as `std::string`
    std::string trace() const
    {
        std::ostringstream ss;
        ss << trace_;
        return ss.str();
    }
};

template <class ArithmeticType1, class ArithmeticType2>
auto operator+(const trace_value<ArithmeticType1>& a, const trace_value<ArithmeticType2>& b)
{
    auto result = a.get() + b.get();
    return trace_value<decltype(result)>(result);
}

template <class ArithmeticType1, class ArithmeticType2>
auto operator-(const trace_value<ArithmeticType1>& a, const trace_value<ArithmeticType2>& b)
{
    auto result = a.get() - b.get();
    return trace_value<decltype(result)>(result);
}

template <class ArithmeticType1, class ArithmeticType2>
auto operator*(const trace_value<ArithmeticType1>& a, const trace_value<ArithmeticType2>& b)
{
    auto result = a.get() * b.get();
    return trace_value<decltype(result)>(result);
}

template <class ArithmeticType1, class ArithmeticType2>
auto operator/(const trace_value<ArithmeticType1>& a, const trace_value<ArithmeticType2>& b)
{
    auto result = a.get() / b.get();
    return trace_value<decltype(result)>(result);
}

template <class ArithmeticType1, class ArithmeticType2>
auto operator%(const trace_value<ArithmeticType1>& a, const trace_value<ArithmeticType2>& b)
{
    auto result = a.get() % b.get();
    return trace_value<decltype(result)>(result);
}

template <class ArithmeticType1, class ArithmeticType2>
bool operator==(const trace_value<ArithmeticType1>& a, const trace_value<ArithmeticType2>& b)
{
    return a.get() == b.get();
}

template <class ArithmeticType1, class ArithmeticType2>
bool operator!=(const trace_value<ArithmeticType1>& a, const trace_value<ArithmeticType2>& b)
{
    return a.get() != b.get();
}

template <class ArithmeticType1, class ArithmeticType2>
bool operator<(const trace_value<ArithmeticType1>& a, const trace_value<ArithmeticType2>& b)
{
    return a.get() < b.get();
}

template <class ArithmeticType1, class ArithmeticType2>
bool operator<=(const trace_value<ArithmeticType1>& a, const trace_value<ArithmeticType2>& b)
{
    return a.get() <= b.get();
}

template <class ArithmeticType1, class ArithmeticType2>
bool operator>(const trace_value<ArithmeticType1>& a, const trace_value<ArithmeticType2>& b)
{
    return a.get() > b.get();
}

template <class ArithmeticType1, class ArithmeticType2>
bool operator>=(const trace_value<ArithmeticType1>& a, const trace_value<ArithmeticType2>& b)
{
    return a.get() >= b.get();
}

} // namespace shand

#endif // SHAND_TRACE_VALUE_INCLUDE


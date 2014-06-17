#ifndef SHAND_SPECIAL_VALUE_INCLUDE
#define SHAND_SPECIAL_VALUE_INCLUDE

// Variant of arithmetic type and enum (special value)
// For example, The class can use for pop view :
// special_value<int, PopType> v;
// v = 1;
// v = PopType::Root;
//
// Copyright Akira Takahashi 2014
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/variant.hpp>

namespace shand {

template <class ValueType, class Enum>
class special_value {
    boost::variant<ValueType, Enum> value_;
public:
    using value_type = ValueType;
    using enum_type = Enum;

    special_value() {} // initialize ValueType

    special_value(ValueType value)
        : value_(value) {}

    special_value(Enum e)
        : value_(e) {}

    special_value& operator=(ValueType value)
    {
        value_ = value;
        return *this;
    }

    special_value& operator=(Enum e)
    {
        value_ = e;
        return *this;
    }

    bool has_value() const
    { return value_.which() == 0; }

    bool has_enum() const
    { return value_.which() == 1; }

    ValueType& get_value()
    { return boost::get<ValueType>(value_); }

    const ValueType& get_value() const
    { return boost::get<ValueType>(value_); }

    Enum& get_enum()
    { return boost::get<Enum>(value_); }

    const Enum& get_enum() const
    { return boost::get<Enum>(value_); }

    template <class F> // void(ValueType& value) or void(ValueType& value)
    special_value& on_value(F f)
    {
        if (has_value()) {
            f(get_value());
        }
        return *this;
    }

    template <class F>
    const special_value& on_value(F f) const
    {
        return const_cast<special_value&>(*this).on_value(f);
    }

    template <class F> // void(Enum value) or void(Enum& value)
    special_value& on_enum(F f)
    {
        if (has_enum()) {
            f(get_enum());
        }
        return *this;
    }

    template <class F>
    const special_value& on_enum(F f) const
    {
        return const_cast<special_value&>(*this).on_enum(f);
    }
};

} // namespace shand

#endif // SHAND_SPECIAL_VALUE_INCLUDE


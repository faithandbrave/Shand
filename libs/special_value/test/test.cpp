// Copyright Akira Takahashi 2014
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/detail/lightweight_test.hpp>
#include <shand/special_value.hpp>

#include <string>
#include <utility>
#include <tuple>
#include <functional>
#include <type_traits>

enum class E { e };

template <class SpecialValue>
std::pair<bool, bool> call(SpecialValue& value)
{
    using MutableSpecialValue = typename std::remove_const<SpecialValue>::type;

    bool is_call_on_value = false;
    bool is_call_on_enum = false;
    value.on_value([&is_call_on_value](typename MutableSpecialValue::value_type x) {
        static_cast<void>(x);
        is_call_on_value = true;
    })
    .on_enum([&is_call_on_enum](typename MutableSpecialValue::enum_type e) {
        static_cast<void>(e);
        is_call_on_enum = true;
    });
    return std::make_pair(is_call_on_value, is_call_on_enum);
}

template <class T>
void value_test(T x)
{
    shand::special_value<T, E> value = x;
    value = x;

    BOOST_TEST(value.has_value());
    BOOST_TEST(!value.has_enum());
    BOOST_TEST(value.get_value() == x);

    bool is_call_on_value, is_call_on_enum;
    std::tie(is_call_on_value, is_call_on_enum) = call<decltype(value)>(value);
    BOOST_TEST(is_call_on_value);
    BOOST_TEST(!is_call_on_enum);

    call<const decltype(value)>(value);
}

void enum_test()
{
    shand::special_value<int, E> value = E::e;

    BOOST_TEST(!value.has_value());
    BOOST_TEST(value.has_enum());
    BOOST_TEST(value.get_enum() == E::e);

    bool is_call_on_value, is_call_on_enum;
    std::tie(is_call_on_value, is_call_on_enum) = call<decltype(value)>(value);
    BOOST_TEST(!is_call_on_value);
    BOOST_TEST(is_call_on_enum);

    call<const decltype(value)>(value);
}

int main()
{
    value_test<int>(3);
    value_test<std::string>("hello");

    enum_test();

    return boost::report_errors();
}

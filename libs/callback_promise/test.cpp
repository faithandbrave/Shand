// Copyright Akira Takahashi 2013.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/detail/lightweight_test.hpp>
#include <shand/callback_promise.hpp>

struct IntCallOrder {
    static void callback_value_test()
    {
        int result = 0;
        shand::callback_promise<int> p;

        p.set_callback([&](int value) {
            result = value;
        });
        p.set_value(3);

        BOOST_TEST(result == 3);
    }

    static void value_callback_test()
    {
        int result = 0;
        shand::callback_promise<int> p;

        p.set_value(3);
        p.set_callback([&](int value) {
            result = value;
        });

        BOOST_TEST(result == 3);
    }
};

struct VoidCallOrder {
    static void callback_value_test()
    {
        bool is_called = false;
        shand::callback_promise<void> p;

        p.set_callback([&] {
            is_called = true;
        });
        p.set_value();

        BOOST_TEST(is_called);
    }

    static void value_callback_test()
    {
        bool is_called = false;
        shand::callback_promise<void> p;

        p.set_value();
        p.set_callback([&] {
            is_called = true;
        });

        BOOST_TEST(is_called);
    }
};

int main()
{
    IntCallOrder::callback_value_test();
    IntCallOrder::value_callback_test();

    VoidCallOrder::callback_value_test();
    VoidCallOrder::value_callback_test();

    return boost::report_errors();
}

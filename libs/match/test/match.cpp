// Copyright Akira Takahashi 2015
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/detail/lightweight_test.hpp>
#include <boost/optional.hpp>
#include <shand/match.hpp>

void test_one_arg_value_call()
{
    boost::optional<int> opt = 3;

    bool called = false;
    shand::match(opt, [&](int& x) {
        BOOST_TEST(x == opt.get());
        called = true;
    });
    BOOST_TEST(called);
}

void test_one_arg_none_not_call()
{
    boost::optional<int> opt = 3;

    bool called = false;
    shand::match(opt, [&called] {
        called = true;
    });
    BOOST_TEST(!called);
}

void test_one_arg_value_not_call()
{
    boost::optional<int> opt;

    bool called = false;
    shand::match(opt, [&called](int&) {
        called = true;
    });
    BOOST_TEST(!called);
}

void test_one_arg_none_call()
{
    boost::optional<int> opt;

    bool called = false;
    shand::match(opt, [&called] {
        called = true;
    });
    BOOST_TEST(called);
}

void test_two_args_has_value()
{
    boost::optional<int> opt = 3;

    bool has_value_called = false;
    bool none_called = false;

    shand::match(opt,
        [&](int& x) {
            BOOST_TEST(x == opt.get());
            has_value_called = true;
        },
        [&] {
            none_called = true;
        }
    );

    BOOST_TEST(has_value_called);
    BOOST_TEST(!none_called);
}

void test_two_args_none()
{
    boost::optional<int> opt;

    bool has_value_called = false;
    bool none_called = false;

    shand::match(opt,
        [&](int&) {
            has_value_called = true;
        },
        [&] {
            none_called = true;
        }
    );

    BOOST_TEST(!has_value_called);
    BOOST_TEST(none_called);
}

int main()
{
    test_one_arg_value_call();
    test_one_arg_none_not_call();

    test_one_arg_value_not_call();
    test_one_arg_none_call();

    test_two_args_has_value();
    test_two_args_none();

    return boost::report_errors();
}

// Copyright Akira Takahashi 2012
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/detail/lightweight_test.hpp>
#include <shand/strong_typedef/tagged_int.hpp>
#include <shand/strong_typedef/tagged_int_io.hpp>
#include <sstream>

struct tag {};
typedef shand::tagged_int<int, tag> integer;

int main ()
{
    // initialize
    integer x(1);
    const integer& cx = x;

    // reference
    int& ref = x.get();
    const int& cref = cx.get();
    BOOST_TEST(x == integer(ref));
    BOOST_TEST(x == integer(cref));

    // relational operators
    BOOST_TEST(x == integer(1));
    BOOST_TEST(x != integer(2));
    BOOST_TEST(x < integer(2));
    BOOST_TEST(x <= integer(2));
    BOOST_TEST(x > integer(0));
    BOOST_TEST(x >= integer(0));

    // add operators
    {
        integer y(1);
        y += integer(2);
        BOOST_TEST(y == integer(3));

        integer z = integer(1) + integer(2);
        BOOST_TEST(z == integer(3));
    }

    // subtract operators
    {
        integer y(3);
        y -= integer(1);
        BOOST_TEST(y == integer(2));

        integer z = integer(3) - integer(1);
        BOOST_TEST(z == integer(2));
    }

    // multiply operators
    {
        integer y(3);
        y *= integer(2);
        BOOST_TEST(y == integer(6));

        integer z = integer(3) * integer(2);
        BOOST_TEST(z == integer(6));
    }

    // divide operators
    {
        integer y(6);
        y /= integer(2);
        BOOST_TEST(y == integer(3));

        integer z = integer(6) / integer(2);
        BOOST_TEST(z == integer(3));
    }

    // modulo operators
    {
        integer y(6);
        y %= integer(2);
        BOOST_TEST(y == integer(0));

        integer z = integer(6) % integer(2);
        BOOST_TEST(z == integer(0));
    }

    // bit-and operators
    {
        integer y(0x000B);
        y &= integer(0x000E);
        BOOST_TEST(y == integer(0x000A));

        integer z = integer(0x000B) & integer(0x000E);
        BOOST_TEST(z == integer(0x000A));
    }

    // bit-or operators
    {
        integer y(0x000B);
        y |= integer(0x000E);
        BOOST_TEST(y == integer(0x000F));

        integer z = integer(0x000B) | integer(0x000E);
        BOOST_TEST(z == integer(0x000F));
    }

    // bit-xor operators
    {
        integer y(0x000B);
        y ^= integer(0x000E);
        BOOST_TEST(y == integer(0x0005));

        integer z = integer(0x000B) ^ integer(0x000E);
        BOOST_TEST(z == integer(0x0005));
    }

    // increment operators
    {
        integer y(1);
        integer y_prev = y++;
        BOOST_TEST(y_prev == integer(1));
        BOOST_TEST(y == integer(2));

        integer z(1);
        integer z_after = ++z;
        BOOST_TEST(z_after == integer(2));
        BOOST_TEST(z == integer(2));
    }

    // decrement operators
    {
        integer y(2);
        integer y_prev = y--;
        BOOST_TEST(y_prev == integer(2));
        BOOST_TEST(y == integer(1));

        integer z(2);
        integer z_after = --z;
        BOOST_TEST(z_after == integer(1));
        BOOST_TEST(z == integer(1));
    }

    // output stream
    {
        integer y(3);
        std::ostringstream ss;
        ss << y;
        BOOST_TEST(ss.str() == "3");
    }

    // input stream
    {
        integer y;
        std::stringstream ss;
        ss << "3";
        ss >> y;
        BOOST_TEST(y == integer(3));
    }

    return boost::report_errors();
}


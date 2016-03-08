// Copyright Akira Takahashi 2012
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/detail/lightweight_test.hpp>
#include <shand/strong_typedef/tagged_float.hpp>
#include <shand/strong_typedef/tagged_float_io.hpp>
#include <sstream>

struct tag {};
typedef shand::tagged_float<double, tag> floating_point;

int main ()
{
    // initialize
    floating_point x(1.0);
    const floating_point& cx = x;

    // reference
    double& ref = x.get();
    const double& cref = cx.get();
    BOOST_TEST(x.equals(floating_point(ref)));
    BOOST_TEST(x.equals(floating_point(cref)));

    // relational operators
    BOOST_TEST(x.equals(floating_point(1.0)));
    BOOST_TEST(x < floating_point(2.0));
    BOOST_TEST(x <= floating_point(2.0));
    BOOST_TEST(x > floating_point(0.1));
    BOOST_TEST(x >= floating_point(0.1));

    // add operators
    {
        floating_point y(1.0);
        y += floating_point(2.0);
        BOOST_TEST(y.equals(floating_point(3.0)));

        floating_point z = floating_point(1.0) + floating_point(2.0);
        BOOST_TEST(z.equals(floating_point(3.0)));
    }

    // subtract operators
    {
        floating_point y(3.0);
        y -= floating_point(1.0);
        BOOST_TEST(y.equals(floating_point(2.0)));

        floating_point z = floating_point(3.0) - floating_point(1.0);
        BOOST_TEST(z.equals(floating_point(2.0)));
    }

    // multiply operators
    {
        floating_point y(3.0);
        y *= floating_point(2.0);
        BOOST_TEST(y.equals(floating_point(6.0)));

        floating_point z = floating_point(3.0) * floating_point(2.0);
        BOOST_TEST(z.equals(floating_point(6.0)));
    }

    // divide operators
    {
        floating_point y(6.0);
        y /= floating_point(2.0);
        BOOST_TEST(y.equals(floating_point(3.0)));

        floating_point z = floating_point(6.0) / floating_point(2.0);
        BOOST_TEST(z.equals(floating_point(3.0)));
    }

    // output stream
    {
        floating_point y(3.0);
        std::ostringstream ss;
        ss << y;
        BOOST_TEST(ss.str() == "3");
    }

    // input stream
    {
        floating_point y;
        std::stringstream ss;
        ss << "3.0";
        ss >> y;
        BOOST_TEST(y.equals(floating_point(3.0)));
    }

    return boost::report_errors();
}


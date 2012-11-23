// Copyright Akira Takahashi 2012
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/detail/lightweight_test.hpp>
#include <shand/strong_typedef/tagged_real.hpp>
#include <sstream>

struct tag {};
typedef shand::tagged_real<double, tag> real;

int main ()
{
    // initialize
    real x = 1.0;
    const real& cx = x;

    // reference
    double& ref = x.get();
    const double& cref = x.get();
    BOOST_TEST(x.equals(ref));
    BOOST_TEST(x.equals(cref));

    // relational operators
    BOOST_TEST(x.equals(1.0));
    BOOST_TEST(x < 2.0);
    BOOST_TEST(x <= 2.0);
    BOOST_TEST(x > 0.1);
    BOOST_TEST(x >= 0.1);

    // add operators
    {
        real y = 1.0;
        y += real(2.0);
        BOOST_TEST(y.equals(3.0));

        real z = real(1.0) + real(2.0);
        BOOST_TEST(z.equals(3.0));
    }

    // subtract operators
    {
        real y = 3.0;
        y -= 1.0;
        BOOST_TEST(y.equals(2.0));

        real z = real(3.0) - real(1.0);
        BOOST_TEST(z.equals(2.0));
    }

    // multiply operators
    {
        real y = 3.0;
        y *= 2.0;
        BOOST_TEST(y.equals(6.0));

        real z = real(3.0) * real(2.0);
        BOOST_TEST(z.equals(6.0));
    }

    // divide operators
    {
        real y = 6.0;
        y /= 2.0;
        BOOST_TEST(y.equals(3.0));

        real z = real(6.0) / real(2.0);
        BOOST_TEST(z.equals(3.0));
    }

    // output stream
    {
        real y = 3.0;
        std::ostringstream ss;
        ss << y;
        BOOST_TEST(ss.str() == "3");
    }

    // input stream
    {
        real y;
        std::stringstream ss;
        ss << "3.0";
        ss >> y;
        BOOST_TEST(y.equals(3.0));
    }

    return boost::report_errors();
}


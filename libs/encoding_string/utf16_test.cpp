// Copyright Akira Takahashi 2013
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/detail/lightweight_test.hpp>
#include <shand/encoding_string.hpp>

using shand::encoding_string;
namespace encoding = shand::encoding;

int main()
{
    const encoding_string<encoding::utf16> s = u"𠮟";

    BOOST_TEST(s.raw_str().size() == 2);
    BOOST_TEST(s.codeunit_size() == 1);

    return boost::report_errors();
}


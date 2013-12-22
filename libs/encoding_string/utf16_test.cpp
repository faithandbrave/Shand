// Copyright Akira Takahashi 2013
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/config.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <shand/encoding_string.hpp>

#if defined(BOOST_NO_CXX11_CHAR16_T)
    #define LITERAL(s) L ## s
#else
    #define LITERAL(s) u ## s
#endif

using shand::encoding_string;
namespace encoding = shand::encoding;

void codeunit_size_test()
{
    // the character is surrogate pair (4 bytes = 2 characters space)
    const encoding_string<encoding::utf16> s = LITERAL("𠮟");

    BOOST_TEST(s.raw_str().size() == 2);
    BOOST_TEST(s.codeunit_size() == 1);
}

void codeunit_at_test()
{
    const encoding_string<encoding::utf16> s = LITERAL("あい𠮟aa");
    const encoding_string<encoding::utf16> at = s.codeunit_at(2);

    BOOST_TEST(at == LITERAL("𠮟"));
}

void codeunit_substr_range_test()
{
    const encoding_string<encoding::utf16> s = LITERAL("あいうえお");
    const encoding_string<encoding::utf16> sub = s.codeunit_substr(2, 3);
    BOOST_TEST(sub == encoding_string<encoding::utf16>(LITERAL("うえお")));
}

void codeunit_substr_start_test()
{
    const encoding_string<encoding::utf16> s = LITERAL("あいうえお");
    const encoding_string<encoding::utf16> sub = s.codeunit_substr(2);
    BOOST_TEST(sub == encoding_string<encoding::utf16>(LITERAL("うえお")));
}

void ostream_test()
{
    const encoding_string<encoding::utf16> s = LITERAL("あいうえお");

    std::stringstream ss;
    ss << s;

    encoding_string<encoding::system> result = ss.str().c_str();
    BOOST_TEST(result == encoding_string<encoding::system>("あいうえお"));
}

void empty_test()
{
    const encoding_string<encoding::utf16> s = LITERAL("あいうえお");
    BOOST_TEST(!s.empty());

    encoding_string<encoding::utf16> empty;
    BOOST_TEST(empty.empty());
}

int main()
{
    codeunit_size_test();
    codeunit_at_test();
    codeunit_substr_range_test();
    codeunit_substr_start_test();
    ostream_test();
    empty_test();

    return boost::report_errors();
}


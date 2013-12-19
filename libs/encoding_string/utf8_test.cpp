// Copyright Akira Takahashi 2013
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/detail/lightweight_test.hpp>
#include <shand/encoding_string.hpp>

#include <vector>
#include <sstream>

using shand::encoding_string;
namespace encoding = shand::encoding;

const encoding_string<encoding::utf8> string = u8"あいうえお";

void codeunit_size_test()
{
    std::size_t codeunit_size = string.codeunit_size();
    BOOST_TEST(codeunit_size == 5);
}

void codeunit_at_test()
{
    encoding_string<encoding::utf8> at = string.codeunit_at(2);
    BOOST_TEST(at == encoding_string<encoding::utf8>(u8"う"));
}

void iteration_test()
{
    std::vector<encoding_string<encoding::utf8>> cont;
    for (decltype(string)::value_type c : string) {
        cont.push_back(c);
    }

    const std::vector<encoding_string<encoding::utf8>> expected = {
        u8"あ",
        u8"い",
        u8"う",
        u8"え",
        u8"お"
    };

    BOOST_TEST(cont == expected);
}

void ostream_test()
{
    // システムの文字コードで出力
    std::stringstream ss;
    ss << string;

    encoding_string<encoding::system> result = ss.str().c_str();
    BOOST_TEST(result == encoding_string<encoding::system>("あいうえお"));
}

void codeunit_substr_range_test()
{
    encoding_string<encoding::utf8> sub = string.codeunit_substr(2, 3);
    BOOST_TEST(sub == encoding_string<encoding::utf8>(u8"うえお"));
}

void codeunit_substr_start_test()
{
    encoding_string<encoding::utf8> sub = string.codeunit_substr(2);
    BOOST_TEST(sub == encoding_string<encoding::utf8>(u8"うえお"));
}

void empty_test()
{
    BOOST_TEST(!string.empty());

    encoding_string<encoding::utf8> empty;
    BOOST_TEST(empty.empty());
}

void bom_test()
{
    encoding_string<encoding::utf8> utf8 = u8"\xef\xbb\xbfあいうえお";
    BOOST_TEST(utf8 == encoding_string<encoding::utf8>(u8"あいうえお"));
}

int main()
{
    codeunit_size_test();
    codeunit_at_test();
    iteration_test();
    ostream_test();
    codeunit_substr_range_test();
    codeunit_substr_start_test();
    empty_test();
    bom_test();

    return boost::report_errors();
}


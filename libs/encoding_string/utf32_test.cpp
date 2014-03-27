// Copyright Akira Takahashi 2013
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/config.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <shand/encoding_string.hpp>

using shand::encoding_string;
namespace encoding = shand::encoding;

const encoding_string<encoding::utf32> input = U"あいうえお";

void codeunit_size_test()
{
    BOOST_TEST(input.raw_str().size() == 5);
    BOOST_TEST(input.codeunit_size() == 5);
}

void codeunit_at_test()
{
    const encoding_string<encoding::utf32> at = input.codeunit_at(2);
    BOOST_TEST(at == U"う");
}

void iteration_test()
{
    std::vector<encoding_string<encoding::utf32>> cont;
    for (decltype(input)::value_type c : input) {
        cont.push_back(c);
    }

    const std::vector<encoding_string<encoding::utf32>> expected = {
        U"あ",
        U"い",
        U"う",
        U"え",
        U"お"
    };

    BOOST_TEST(cont == expected);
}

void codeunit_substr_range_test()
{
    const encoding_string<encoding::utf32> sub = input.codeunit_substr(1, 3);
    BOOST_TEST(sub == encoding_string<encoding::utf32>(U"いうえ"));
}

void codeunit_substr_start_test()
{
    const encoding_string<encoding::utf32> sub = input.codeunit_substr(2);
    BOOST_TEST(sub == encoding_string<encoding::utf32>(U"うえお"));
}

void ostream_test()
{
    const encoding_string<encoding::utf32> s = U"あいうえお";

    std::stringstream ss;
    ss << s;

    encoding_string<encoding::system> result = ss.str().c_str();
    BOOST_TEST(result == encoding_string<encoding::system>("あいうえお"));
}

void empty_test()
{
    BOOST_TEST(!input.empty());

    const encoding_string<encoding::utf32> empty;
    BOOST_TEST(empty.empty());
}

void bom_test()
{
    const std::vector<const encoding_string<encoding::utf32>::cchar_type*> literal_list = {
        U"あいうえお",       // system endian
        U"\x0000feffあいうえお", // big endian
        U"\xfffe0000あいうえお"  // little endian
    };

    const std::vector<encoding_string<encoding::utf32>> utf32_list = {
        literal_list[0],
        literal_list[1],
        literal_list[2]
    };

    for (std::size_t i = 0; i < utf32_list.size(); ++i) {
        const auto& literal = literal_list[i];
        const auto& utf32 = utf32_list[i];

        // not delete BOM
        BOOST_TEST(utf32 == encoding_string<encoding::utf32>(literal));

        // ignore BOM
        BOOST_TEST(utf32.codeunit_size() == 5);
        BOOST_TEST(utf32.codeunit_at(2) == encoding_string<encoding::utf32>(U"う"));
        BOOST_TEST(utf32.codeunit_substr(2) == encoding_string<encoding::utf32>(U"うえお"));

        std::vector<encoding_string<encoding::utf32>> cont;
        for (encoding_string<encoding::utf32>::value_type c : utf32) {
            cont.push_back(c);
        }

        const std::vector<encoding_string<encoding::utf32>> expected = {
            U"あ",
            U"い",
            U"う",
            U"え",
            U"お"
        };

        BOOST_TEST(cont == expected);
    }
}

int main()
{
    codeunit_size_test();
    codeunit_at_test();
    iteration_test();
    codeunit_substr_range_test();
    codeunit_substr_start_test();
    ostream_test();
    empty_test();
    bom_test();

    return boost::report_errors();
}


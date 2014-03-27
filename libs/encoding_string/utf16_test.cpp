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

void iteration_test()
{
    const encoding_string<encoding::utf16> s = LITERAL("あいうえお");

    std::vector<encoding_string<encoding::utf16>> cont;
    for (decltype(s)::value_type c : s) {
        cont.push_back(c);
    }

    const std::vector<encoding_string<encoding::utf16>> expected = {
        LITERAL("あ"),
        LITERAL("い"),
        LITERAL("う"),
        LITERAL("え"),
        LITERAL("お")
    };

    BOOST_TEST(cont == expected);
}

void codeunit_substr_range_test()
{
    const encoding_string<encoding::utf16> s = LITERAL("あいうえお");
    const encoding_string<encoding::utf16> sub = s.codeunit_substr(1, 3);
    BOOST_TEST(sub == encoding_string<encoding::utf16>(LITERAL("いうえ")));
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

void bom_test()
{
    const std::vector<const encoding_string<encoding::utf16>::cchar_type*> literal_list = {
        LITERAL("あいうえお"),       // system endian
        LITERAL("\xfeffあいうえお"), // big endian
        LITERAL("\xfffeあいうえお")  // little endian
    };

    const std::vector<encoding_string<encoding::utf16>> utf16_list = {
        literal_list[0],
        literal_list[1],
        literal_list[2]
    };

    for (std::size_t i = 0; i < utf16_list.size(); ++i) {
        const auto& literal = literal_list[i];
        const auto& utf16 = utf16_list[i];

        // not delete BOM
        BOOST_TEST(utf16 == encoding_string<encoding::utf16>(literal));

        // ignore BOM
        BOOST_TEST(utf16.codeunit_size() == 5);
        BOOST_TEST(utf16.codeunit_at(2) == encoding_string<encoding::utf16>(LITERAL("う")));
        BOOST_TEST(utf16.codeunit_substr(2) == encoding_string<encoding::utf16>(LITERAL("うえお")));

        std::vector<encoding_string<encoding::utf16>> cont;
        for (encoding_string<encoding::utf16>::value_type c : utf16) {
            cont.push_back(c);
        }

        const std::vector<encoding_string<encoding::utf16>> expected = {
            LITERAL("あ"),
            LITERAL("い"),
            LITERAL("う"),
            LITERAL("え"),
            LITERAL("お")
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


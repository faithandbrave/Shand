// Copyright Akira Takahashi 2013
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/config.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <shand/encoding_string.hpp>

using shand::encoding_string;
namespace encoding = shand::encoding;

template <class FromEncoding, class ToEncoding, class FromValue, class ToValue>
void test(FromValue from_literal, ToValue to_literal)
{
    const encoding_string<FromEncoding> from = from_literal;
    const encoding_string<ToEncoding> to = shand::encode<ToEncoding>(from);

    BOOST_TEST(to == encoding_string<ToEncoding>(to_literal));
}

int main()
{
    const char utf8[] = u8"あいうえお";
    const char16_t utf16[] = u"あいうえお";
    const char32_t utf32[] = U"あいうえお";
    const char sys[] = "あいうえお";

    test<encoding::utf8, encoding::utf8>(utf8, utf8);
    test<encoding::utf8, encoding::utf16>(utf8, utf16);
    test<encoding::utf8, encoding::utf32>(utf8, utf32);
    test<encoding::utf8, encoding::system>(utf8, sys);

    test<encoding::utf16, encoding::utf8>(utf16, utf8);
    test<encoding::utf16, encoding::utf16>(utf16, utf16);
    test<encoding::utf16, encoding::utf32>(utf16, utf32);
    test<encoding::utf16, encoding::system>(utf16, sys);

    test<encoding::utf32, encoding::utf8>(utf32, utf8);
    test<encoding::utf32, encoding::utf16>(utf32, utf16);
    test<encoding::utf32, encoding::utf32>(utf32, utf32);
    test<encoding::utf32, encoding::system>(utf32, sys);

    return boost::report_errors();
}


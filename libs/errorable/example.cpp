// Shand C++ Library
//
// Copyright Akira Takahashi 2013
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <system_error>
#include <shand/errorable.hpp>

int main()
{
	// 初期状態はエラー
    {
		shand::errorable<int> x;
		BOOST_ASSERT(x.is_error());
    }

	// エラーが発生しているケース
	// エラー理由を格納する
	// デフォルトのエラー型はstd::string
    {
		shand::errorable<int> value = shand::error("invalid argument");
        if (boost::optional<std::string> err = value.get_error()) {
            std::cout << err.get() << std::endl;
        }
    }

	// 正常な値が入っているケース
    {
		shand::errorable<int> value = 3;
        if (boost::optional<int> x = value.get_value()) {
            std::cout << x.get() << std::endl;
        }
    }

	// 値が正常かエラーかによって、関数を呼び分ける
    {
		shand::errorable<int> value = shand::error("invalid argument");
        value.value_if([](int x) {
            std::cout << x << std::endl;
        })
        .error_if([](const std::string& err) {
            std::cout << err << std::endl;
        });
    }

	// 第2テンプレート引数で、エラー型をカスタマイズ可能
	{
		shand::errorable<int, std::errc> value = shand::error(std::errc::invalid_argument);
		if (boost::optional<std::errc> err = value.get_error()) {
			std::cout << std::make_error_code(err.get()).message() << std::endl;
		}
	}
}


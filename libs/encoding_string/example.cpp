#include <iostream>
#include <shand/encoding_string.hpp>

int main()
{
    using namespace shand;
    encoding_string<encoding::utf8> s = u8"あいうえお";

    std::cout << s.codeunit_size() << std::endl; // 5
    std::cout << s.codeunit_at(2) << std::endl; // u8"う"

    // 1文字ずつ出力
    for (decltype(s)::value_type c : s) {
        std::cout << c << std::endl;
    }
    // あ
    // い
    // う
    // え
    // お
}


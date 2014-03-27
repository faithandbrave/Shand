#codeunit_substr
```cpp
encoding_string<Encoding> codeunit_substr(std::size_t index, std::size_t codeunit_size) const; // (1)
encoding_string<Encoding> codeunit_substr(std::size_t index) const;                            // (2)
```

##概要
部分文字列を取得する。


##要件
- `index < codeunit_size()`であること。
- `codeunit_size > 0`であること。


##戻り値
- (1) : コードポイント範囲`[index, index + codeunit_size]`の文字列を抽出して返す。
- (2) : コードポイント範囲`[index, end)`の文字列を抽出して返す。


##計算量
- O(N)
- UTF-32はO(1)


##例
```cpp
#include <iostream>
#include <shand/encoding_string.hpp>

int main()
{
    using namespace shand;
    encoding_string<encoding::utf8> s = u8"あいうえお";

    // コードポイントの範囲[1, 1 + 3]を取得する
    encoding_string<encoding::utf8> sub1 = s.codeunit_substr(1, 3);
    std::cout << sub1 << std::endl;

    // 1番目のコードポイントから終端までを取得する
    encoding_string<encoding::utf8> sub2 = s.codeunit_substr(1);
    std::cout << sub2 << std::endl;
}
```

##出力
```
いうえ
いうえお
```



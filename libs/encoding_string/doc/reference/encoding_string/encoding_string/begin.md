#begin
```cpp
iterator begin();
const_iterator begin() const;
```

##概要
先頭のコードユニットを指すイテレータを取得する。


##戻り値
先頭のコードユニットを指すイテレータを返す。

このイテレータは、コードユニット単位で走査を行う。ひとつのコードユニットは、`encoding_string`オブジェクトとして表現される。


##例
```cpp
#include <iostream>
#include <algorithm>
#include <shand/encoding_string.hpp>

int main()
{
    using namespace shand;
    encoding_string<encoding::utf8> s = u8"あいうえお";

    // コードユニットを一つずつ出力
    std::for_each(s.begin(), s.end(), [](const encoding_string<encoding::utf8>& c) {
        std::cout << c << std::endl;
    });

    std::cout << std::endl;

    // 範囲for文にも適用可能
    for (const encoding_string<encoding::utf8>& c : s) {
        std::cout << c << std::endl;
    }
}
```

##出力
```
あ
い
う
え
お

あ
い
う
え
お
```



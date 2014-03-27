#end
```cpp
iterator end();
const_iterator end() const;
```

##概要
末尾コードユニットの次を指すイテレータを取得する。


##戻り値
末尾コードユニットの次を指すイテレータを返す。


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



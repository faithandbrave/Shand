#codeunit_at
```cpp
value_type codeunit_at(std::size_t index) const;
```

##概要
任意の位置のコードユニットを取得する。


##要件
`index < codeunit_size()`であること。


##戻り値
`index`番目のコードユニットを返す。


##計算量
O(N)


##例
```cpp
#include <iostream>
#include <shand/encoding_string.hpp>

int main()
{
    using namespace shand;
    encoding_string<encoding::utf8> s = u8"あいうえお";

    // 2番目のコードユニット(u8"う")を取得
    encoding_string<encoding::utf8> u = s.codeunit_at(2);
    std::cout << u << std::endl;
}
```

##出力
```
う
```



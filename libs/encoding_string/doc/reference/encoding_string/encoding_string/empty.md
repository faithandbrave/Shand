#empty
```cpp
bool empty() const;
```

##概要
文字列が空かを判定する。


##戻り値
文字列が空の場合は`true`、そうでなければ`false`を返す。


##計算量
O(1)


##例
```cpp
#include <cassert>
#include <shand/encoding_string.hpp>

int main()
{
    using namespace shand;

    encoding_string<encoding::utf8> s1;
    assert(s1.empty());

    encoding_string<encoding::utf8> s2 = "hello";
    assert(!s2.empty());
}
```

##出力
```
```



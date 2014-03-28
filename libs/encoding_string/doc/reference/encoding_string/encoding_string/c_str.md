#c_str
```cpp
const char_type* c_str() const;
```

##概要
C文字列を取得する。


##戻り値
C言語の文字列表現を返す。

この関数によって返されるポインタの寿命は、`*this`オブジェクトと同じである。


##計算量
O(1)


##備考
この関数は、C言語のAPIに文字列を渡すために使用できる。


##例
```cpp
#include <iostream>
#include <shand/encoding_string.hpp>

int main()
{
    using namespace shand;

    encoding_string<encoding::utf8> s = "hello";
    const char* c = s.c_str();

    std::cout << c << std::endl;
}
```

##出力
```
hello
```



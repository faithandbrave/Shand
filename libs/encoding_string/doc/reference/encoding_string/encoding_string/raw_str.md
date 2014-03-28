#raw_str
```cpp
const string_type& raw_str() const;
```

##概要
[`basic_string`](https://sites.google.com/site/cpprefjp/reference/string/basic_string)文字列を取得する。


##戻り値
[`basic_string`](https://sites.google.com/site/cpprefjp/reference/string/basic_string)表現の文字列への参照を返す。

この関数によって返される参照の寿命は、`*this`オブジェクトと同じである。


##計算量
O(1)


##備考
この関数は、文字列のバイト表現に関するプロパティを取得するために使用できる。


##例
```cpp
#include <iostream>
#include <shand/encoding_string.hpp>

int main()
{
    using namespace shand;

    encoding_string<encoding::utf8> s = "hello";
    const std::string raw = s.raw_str();

    std::cout << raw << std::endl;
}
```

##出力
```
hello
```



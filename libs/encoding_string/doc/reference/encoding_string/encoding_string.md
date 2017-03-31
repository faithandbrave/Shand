# encoding_stringクラス

## 宣言
```cpp
namespace shand {

// エンコード文字列
template <class Encoding>
class encoding_string;

} // namespace shand
```

## 概要
`encoding_string`は、文字コード情報を持つ文字列クラスである。

[`std::basic_string`][basic_string]が文字型(`char`、`wchar_t`、`char16_t`、`char32_t`)をテンプレートパラメータにとるのに対し、このクラスはテンプレートパラメータとして文字コードの種類を表す型を取る。


## メンバ関数
### 構築・破棄

| 名前                                                   | 説明           |
|--------------------------------------------------------|----------------|
| [`(constructor)`](./encoding_string/op_constructor.md) | コンストラクタ |
| `~encoding_string() = default;`                        | デストラクタ   |


### 文字列プロパティ

| 名前                                      | 説明                                           |
|-------------------------------------------|------------------------------------------------|
| [`empty`](./encoding_string/empty.md)     | 文字列が空かを判定する                         |
| [`c_str`](./encoding_string/c_str.md)     | C文字列を取得する                              |
| [`raw_str`](./encoding_string/raw_str.md) | [`basic_string`][basic_string]文字列を取得する |


### コードユニットのインタフェース

コードユニット(≒ 文字)単位で文字列を操作するインタフェース。結合文字や異体字セレクタは考慮しない。

システム文字コードは、このインタフェースを持たない。

| 名前              | 説明                                             |
|-----------------------------------------------------------|--------------------------------------------------|
| [`codeunit_size`](./encoding_string/codeunit_size.md)     | コードユニット数を取得する                       |
| [`codeunit_at`](./encoding_string/codeunit_at.md)         | 任意の位置のコードユニットを取得する             |
| [`codeunit_substr`](./encoding_string/codeunit_substr.md) | 部分文字列を取得する                             |
| [`begin`](./encoding_string/begin.md)                     | 先頭のコードユニットを指すイテレータを取得する   |
| [`end`](./encoding_string/end.md)                         | 末尾コードユニットの次を指すイテレータを取得する |


## メンバ型

| 名前 | 説明 |
|------------------|------|
| `char_type`      | 文字型。<br/> UTF-8なら`char`、UTF-16なら16ビットの文字型、UTF-32なら32ビットの文字型、システムは`char`。 |
| `string_type`    | 内部表現の文字列型で、`raw_str()`メンバ関数の戻り値。`basic_string<char_type>` |
| `iterator`       | コードユニット単位のイテレータ型 |
| `const_iterator` | コードユニット単位の読み取り専用イテレータ型 |
| `value_type`     | イテレータの要素型。`encoding_string<Encoding>`。 |


## 例
```cpp
#include <iostream>
#include <shand/encoding_string.hpp>

int main()
{
    using namespace shand;

    const encoding_string<encoding::utf8> s = u8"あいうえお";

    // 出力ストリーム
    std::cout << s << std::endl; // "あいうえお"

    // 部分文字列の取得
    std::cout << s.codeunit_substr(2, 3) << std::endl; // "うえお"
    std::cout << s.codeunit_substr(2) << std::endl; // "うえお"

    // UTF-8文字もまたUTF-8文字列
    encoding_string<encoding::utf8> at = s.codeunit_at(2);
    std::cout << at << std::endl; // "う"
}
```

### 出力
```
あいうえお
うえお
うえお
う
```

[basic_string]: https://cpprefjp.github.io/reference/string/basic_string.html


#`<shand/encoding_string.hpp>`

##概要
```cpp
namespace shand {

// エンコーディングの種類
namespace encoding {
struct utf16 {};
struct utf8 {};
struct utf32 {};
struct system {};
} // namespace encoding

// エンコード文字列
template <class Encoding>
class encoding_string;

// 文字コードの変換
template <class To, class From>
encoding_string<To> encode(const encoding_string<From>& from);

// ストリーム出力
template <class CharT, class Encoding>
std::basic_ostream<CharT>&
  operator<<(std::basic_ostream<CharT>& os, const encoding_string<Encoding>& s);

// Unicode正規化
template <class Encoding>
encoding_string<Encoding> compose(const encoding_string<Encoding>& s);

template <class Encoding>
encoding_string<Encoding> decompose(const encoding_string<Encoding>& s);

template <class Encoding>
encoding_string<Encoding> compatible_compose(const encoding_string<Encoding>& s);

template <class Encoding>
encoding_string<Encoding> compatible_decompose(const encoding_string<Encoding>& s);

} // namespace shand
```

##エンコーディングの種類

エンコーディングの種類は、`shand::encoding`名前空間内に、それぞれ空クラスのタグとして定義している。

| 名前                   | 説明                                       |
|------------------------|--------------------------------------------|
| `utf16`                | UTF-16。システムのエンディアンを使用する。 |
| `utf8`                 | UTF-8                                      |
| `utf32`                | UTF-32。システムのエンディアンを使用する。 |
| `system`               | システムの文字コード。ストリームの出力に使用する文字コード。 |


##エンコード文字列クラスと、エンコード関数

| 名前              | 説明                                                          |
|-------------------|---------------------------------------------------------------|
| [`encoding_string`](./encoding_string/encoding_string.md) | 文字コードのエンコーディング情報を持つ文字列クラス            |
| `encode()`        | `encoding_string`オブジェクトを、他の文字コードに変換する関数 |
| `operator<<`      | ストリーム出力                                                |

##Unicode正規化

| 名前                     | 説明           |
|--------------------------|----------------|
| `compose()`              | 結合文字を合成する関数(Windows環境のみ実装している) |
| `decompose()`            | 文字を結合文字に分解する関数(Windows環境のみ実装している) |
| `compatible_compose()`   | 結合文字を、互換性のある文字に合成する関数(Windows環境のみ実装している) |
| `compatible_decompose()` | 文字を、互換性のある結合文字に分解する関数(Windows環境のみ実装している) |



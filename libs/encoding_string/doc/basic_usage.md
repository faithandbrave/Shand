#基本的な使い方
`encoding_string`クラスは、`std::basic_string`クラスのように文字型をテンプレート引数を設定するのではなく、文字コードを設定して使用する。

```cpp
encoding_string<encoding::utf16> utf16_str = u"あいうえお";  // UTF-16文字列
encoding_string<encoding::utf8>  utf8_str  = u8"あいうえお"; // UTF-8文字列　
encoding_string<encoding::utf32> utf32_str = U"あいうえお";  // UTF-32文字列
```

以下に述べる機能は、システム文字コード以外で使用可能である。

##文字数を取得する
`encoding_string::codeunit_size()`メンバ関数は、文字列に含まれるコードポイントの数を返す。文字数と考えていい。

UTF-16のサロゲートペアもまた、1文字と数える。ただし、結合文字については複数文字として扱う(「が」という文字が「か」と「゛」で分かれていることがある)。結合文字はUnicodeの正規化を行えば1文字に変換可能である(未実装)。

```cpp
encoding_string<encoding::utf8> utf8_str = u8"あいうえお";

std::size_t n = utf8_str.codeunit_size(); // n == 5
```

##i番目の文字を取得する
`encoding_string::codeunit_at()`メンバ関数は、引数で指定したインデックスの文字を返す。

`encoding_string`クラスにおいては、1文字もまた`encoding_string`文字列である。これはRuby 1.9以降の文字列の設計を踏襲している。

```cpp
encoding_string<encoding::utf8> utf8_str = u8"あいうえお";

// 2番目の文字を取得
encoding_string<encoding::utf8> at = utf8_str.codeunit_at(2); // at == u8"う"
```

##部分文字列を取得する
`encoding_string::codeunit_substr()`メンバ関数は、`i`番目から`n`文字を抽出して返す。開始位置のみを指定した場合、開始位置以降の全ての文字列を返す。

```cpp
encoding_string<encoding::utf8> utf8_str = u8"あいうえお";

// 2番目から3文字を取得
encoding_string<encoding::utf8> sub1 = utf8_str.codeunit_substr(2, 3);
// sub1 == u8"うえお"

// 2番目以降の文字列を取得
encoding_string<encoding::utf8> sub2 = utf8_str.codeunit_substr(2);
// sub2 == u8"うえお"
```

##ストリーム出力
`encoding_string`クラスは、`operator<<`によってストリーム出力ができる。この演算子を使用した場合、システム文字コード(`encoding::system`)に変換して出力される。

ファイル出力の場合は任意の文字コードで出力したいであろうから、その場合は`operator<<`を使用すべきではない。`c_str()`メンバ関数によるC文字列の取得、もしくは`raw_str()`メンバ関数による`std::basic_string`オブジェクトの取得機能を使用すること。

```cpp
encoding_string<encoding::utf8> utf8_str = u8"あいうえお";

std::cout << utf8_str << std::endl; // あいうえお
```


##イテレータ
`encoding_string`クラスは、`begin()`/`end()`メンバ関数を持っている。これらによって、1文字ずつ順番に処理を行える。

```cpp
encoding_string<encoding::utf8> utf8_str = u8"あいうえお";

for (decltype(utf8_str)::value_type c : utf8_str) {
  std::cout << c << std::endl;
}
/*
以下の順に出力される：
あ
い
う
え
お
*/
```


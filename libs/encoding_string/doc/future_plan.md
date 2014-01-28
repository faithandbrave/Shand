#将来の予定

##文字のイテレートと、文字数取得のインタフェース

現在は、コードユニット(コードポイント)単位でのインタフェースのみ提供しているが、文字インタフェースの実装を考えている。

###実装方針案(考え中)

デフォルトポリシーとして、以下の方針で文字数を数える。このポリシーをカスタマイズ可能にするかは、検討中。


以下のパターンに合致するものを、1文字と数える：

- 文字列先頭の結合文字 x 1
- 基底文字
- 基底文字 + (結合文字 x n)
- 基底文字 + (結合文字 x n) + (異体字セレクタ x 1)


以下のパターンに合致するものを、0文字と数える：

- ゼロ幅文字


###なぜNFC後のコードユニット数 + 異体字セレクタではいけないのか

NFCは、NFDで分解した後に、合成除外表に載っていないもののみ合成する。そのため、合成されない結合文字が存在する。

合成されない結合文字も、ポリシーのカスタマイズによって1文字と数える必要があるかもしれない。


###実装検討中の部品

- 異体字セレクタか判定する`is_variation_selector()`

```cpp
bool is_variation_selector(char32_t codeunit)
{
    return (codeunit >= 0x180b && codeunit <= 0x180d) ||
           (codeunit >= 0xfe00 && codeunit <= 0xfe0f) ||
           (codeunit >= 0xe0100 && codeunit <= 0xe01ef);
}
```

- 結合文字か判定する`is_combining_character()`

```cpp
bool is_combining_character(char32_t codeunit)
{
    icu::UCErrorCode error_code;
    icu::Normalizer2* normalizer = icu::Normalizer2::getNFCInstance(error_code);
    if (U_FAILURE(error_code)) {
        throw std::runtime_error("failed icu::Normalizer2::getNFCInstance()");
    }

    return normalizer->getCombiningClass(codeunit) > 0;
}
```

- ゼロ幅文字を判定する`is_zero_width_character(char32_t codeunit)`

```cpp
bool is_zero_width_character(char32_t codeunit)
{
    return codeunit == 0x200b || // ZERO WIDTH SPACE
           codeunit == 0x2029 || // PARAGRAPH SEPARATOR
           codeunit == 0x202a;   // LEFT-TO-RIGHT EMBEDDING
}
```


##ICUベースの正規化

ICUベースの、以下の実装を用意する：

- `compose()`
- `decompose()`
- `compatibility_compose()`
- `compatibility_decompose()`


##エンコード情報付きファイルクラス

`encoding_string`クラスは、エンディアンの情報を扱わず、文字・文字列の情報のみを扱う。そのため、エンディアンの情報を吸収するクラスとして、`encoding_file<Encoding>`クラスを作成する予定。


#当面やらないもの

- 正規表現 : Boost.RegexにICUのラッパーがあるので、それを使って十分なはず。十分でない場合は検討する。



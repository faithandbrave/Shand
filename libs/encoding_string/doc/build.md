#ビルド方法
Shandライブラリおよび`encoding_string`クラスはヘッダオンリーで実装している。

ここでは、`encoding_string`クラスが依存しているライブラリであるICUのビルド方法を、例として示す。

##ダウンロード
以下のページから、ソースファイルをダウンロードする。

[Downloading ICU](http://site.icu-project.org/download)


##ビルド

展開したデータの`icu/source`ディレクトリに移動し、以下のようなコマンドを実行する。

```
chmod +x runConfigureICU configure install-sh
./runConfigureICU MacOSX C=gcc-mp-4.8 CC=g++-mp-4.8 --enable-static
make
sudo make install
```

- `MacOSX` : OSの指定。
- `C` : C言語のコンパイラを指定。`.c`拡張子のソースコードをビルドするために使用する。
- `CC` : C++のコンパイラを指定。`.cpp`拡張子のソースコードをビルドするために使用する。
- `--enable-static` : 静的ライブラリを作る。指定しない場合は、動的ライブラリが作られる。

これで、


##ICUのリンク

`encoding_string`クラスを使用する場合、プログラムのコンパイルオプションとして、`icuuc.a`をリンクする。以下は、g++でのコンパイル例：

```
g++-mp-4.8 main.cpp -std=c++11 -I/Users/MyUser/Library/icu/source/common -L/Users/MyUser/Library/icu/source/lib -licuuc
```


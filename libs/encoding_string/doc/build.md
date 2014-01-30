#ビルド方法
Shandライブラリおよび`encoding_string`クラスはヘッダオンリーで実装している。

ここでは、`encoding_string`クラスが依存しているライブラリであるICUのビルド方法を、例として示す。

##Mac OS X

MacPortsでインストールする。以下のコマンドを実行することで、`/opt/local/lib/`ディレクトリ以下に、ICUの静的および動的ライブラリがインストールされ、ヘッダファイルへのパスも自動的に通る。

```
sudo port install icu
```


`encoding_string`クラスを使用する場合、プログラムのコンパイルオプションとして、`libicuuc.a`および`libicudata.a`をリンクする。以下は、g++でのコンパイル例：

```
g++-mp-4.8 main.cpp -std=c++11 -L/opt/local/lib -licuuc -licudata
```


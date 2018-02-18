# 競プロ用ライブラリ

競プロ用ライブラリ(スニペット)です。独自のファイル形式に沿って書かれています。
[KIDE](https://github.com/algon-320/KIDE)でのスニペット形式の自動出力に対応しています。

## ファイル形式
拡張子は`.snip`です。
```
<NAME> /* ここに名前を書く */
<TRIGGER> /* ここにスニペットを発動させるトリガーを書く */
<TAG> /* タグを書く(カンマ区切り) */
<*NOTE>
/* この行から次の<*CODE>の行までを使って、
複数行で説明を書く */
<*CODE>
/* この行からコードの内容を書く */
```

`<TAG_NAME>`は一行タグで、`<*TAG_NAME>`は複数行タグです。タグは行の先頭から書く必要があります。
上で挙げた以外の名前のタグを用いることも出来ます。(KIDEでは意味をなさないタグとなります。)

一行タグは'>'の後ろに半角スペースがあってもなくても大丈夫です。
(n個の半角スペースを書いた場合、n-1個の半角スペースとして処理される。)

複数行タグは、'>'の後ろに書いたものは無視されます。
```
<*NOTE> この部分は無視される。
---- 説明文 ----
```

また、タグのない部分(ファイルの先頭)に書いたものも無視されます。

従って次の例のように、ファイルの先頭にブロックコメントの始まりを書いて、<*CODE>タグの後ろに
ブロックコメントの終わりを書くことで、スニペットファイルをそのままC++のコードとしてコピペできるようにすることもできます。
`/* <NAME>`などと書いてしまうとNAMEタグが無効になるので注意してください。

例
``` cpp
/*
<NAME> Binary Indexed Tree (Range minmum or maximum query)
<TRIGGER> BITRMQ
<TAG> data-structure
<*NOTE>
変更クエリが単調増加(単調減少)する場合のみ動作する。
クエリは1-indexedなので注意！

verify: https://beta.atcoder.jp/contests/dwacon2018-final-open/submissions/2071426

<*CODE> */
// 1-indexed
struct BIT_RMQ {
    vector<int> data;
    int size;
    BIT_RMQ(int n): size(n), data(n, ${2:0}) {}
    void update(int i, int x) {
        while (i <= size) {
            data[i] = ${1:max}(data[i], x);
            i += i & -i;
        }
    }
    int get_${1:max}(int i) {
        int ret = ${2:0};
        while (i > 0) {
            ret = ${1:max}(ret, data[i]);
            i -= i & -i;
        }
        return ret;
    }
};
```

KIDEでMarkdown出力した結果
~~~text
## Binary Indexed Tree (Range minmum or maximum query)
### Note
変更クエリが単調増加(単調減少)する場合のみ動作する。
クエリは1-indexedなので注意！

verify: https://beta.atcoder.jp/contests/dwacon2018-final-open/submissions/2071426

### Code
````cpp
// 1-indexed
struct BIT_RMQ {
    vector<int> data;
    int size;
    BIT_RMQ(int n): size(n), data(n, ${2:0}) {}
    void update(int i, int x) {
        while (i <= size) {
            data[i] = ${1:max}(data[i], x);
            i += i & -i;
        }
    }
    int get_${1:max}(int i) {
        int ret = ${2:0};
        while (i > 0) {
            ret = ${1:max}(ret, data[i]);
            i -= i & -i;
        }
        return ret;
    }
};
```
~~~

KIDEでvscode用のスニペット形式で出力した結果
```
"Binary Indexed Tree (Range minmum or maximum query)": {
	"description": "Binary Indexed Tree (Range minmum or maximum query)",
	"prefix": "BITRMQ",
	"body": [
		"// 1-indexed",
		"struct BIT_RMQ {",
		"    vector<int> data;",
		"    int size;",
		"    BIT_RMQ(int n): size(n), data(n, ${2:0}) {}",
		"    void update(int i, int x) {",
		"        while (i <= size) {",
		"            data[i] = ${1:max}(data[i], x);",
		"            i += i & -i;",
		"        }",
		"    }",
		"    int get_${1:max}(int i) {",
		"        int ret = ${2:0};",
		"        while (i > 0) {",
		"            ret = ${1:max}(ret, data[i]);",
		"            i -= i & -i;",
		"        }",
		"        return ret;",
		"    }",
		"};",
		""
	]
},
```
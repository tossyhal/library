---
title: Lexicographically Smallest Concatenation
documentation_of: ../smallest_concatenation.hpp
---

文字列列を並べ替えて連結した結果の辞書順最小値を求めます。

## 使い方

```cpp
string answer = smallest_concatenation(strings);
```

比較では`a+b < b+a`と同値な判定を、一時文字列を生成せずに行います。

入力は値渡しのため、呼び出し元の`strings`の順序は変わりません。返り値は全要素をちょうど1回ずつ連結した文字列です。

## 計算量

文字列数をK、全文字数をL、最大文字列長をMとすると、ソートは概ねO(K log K · M)、連結はO(L)です。

## 注意点

- 通常の辞書順で比較し、数値文字列の先頭ゼロを特別扱いしません。
- 空文字列を含めることができ、空のvectorには空文字列を返します。

## 検証

- 小さなランダム入力について全順列を試す愚直解と比較

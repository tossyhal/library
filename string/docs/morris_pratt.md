---
title: Morris–Pratt Algorithm
documentation_of: ../morris_pratt.hpp
---

`failure[0] = -1`形式の失敗関数を使う文字列検索です。

## 使い方

```cpp
auto failure = morris_pratt_failure(pattern);
auto positions = morris_pratt(text, pattern);
```

`failure`は照合失敗時の戻り先、`positions`は完全一致した開始位置を0-indexedの昇順で表します。

## 計算量

`N = text.size()`, `M = pattern.size()`としてO(N+M)、追加メモリO(M)です。

## 注意点

- 列の要素は`==`で比較できる必要があります。
- 空パターンは全境界に一致します。
- KMPと同じ用途ですが、失敗関数の形式が異なります。

## 検証

- [AOJ ALDS1_14_B - String Search](https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_14_B)

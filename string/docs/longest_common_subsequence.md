---
title: Longest Common Subsequence
documentation_of: ../longest_common_subsequence.hpp
---

2列の最長共通部分列を求めます。

## 使い方

```cpp
int length = longest_common_subsequence_length(s, t);
auto sequence = longest_common_subsequence(s, t);
```

## 計算量

- 長さのみ: O(NM)、メモリO(min(N,M))
- 復元あり: O(NM)、メモリO(NM)

`longest_common_subsequence_length`は長さを、`longest_common_subsequence`は実際の要素列を返します。文字列を渡した場合は`string`を返します。

## 注意点

- 部分列なので、要素は連続している必要がありません。
- 最適解が複数ある場合、いずれか1つを返します。
- 要素型は`==`で比較できる必要があります。
- 大きな入力で長さだけ必要なら、メモリの少ないlength版を使います。

## 検証

- [AOJ ALDS1_10_C - Longest Common Subsequence](https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_10_C)

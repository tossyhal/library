---
title: Knuth–Morris–Pratt Algorithm
documentation_of: ../kmp.hpp
---

1つのパターンをテキストからO(N+M)で検索します。

## 使い方

```cpp
auto positions = kmp(text, pattern);
auto pi = prefix_function(pattern);
auto periods = minimum_periods(s);
```

- `positions`: 完全一致する開始位置を0-indexedの昇順で返します。
- `pi[i]`: `s[0, i+1)`の真の接頭辞と接尾辞が一致する最大長です。
- `periods[i]`: `s[0, i+1)`の最小周期長です。

## 計算量

検索は`N = text.size()`, `M = pattern.size()`としてO(N+M)、追加メモリO(M)です。補助配列の構築はO(M)です。

## 注意点

- 列の要素は`==`で比較できる必要があります。
- 空パターンは`0`から`text.size()`までの全境界に一致します。

## 検証

- [AOJ ALDS1_14_B - String Search](https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_14_B)

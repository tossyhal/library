---
title: LCP / Substring Comparison / String Search
documentation_of: ../lcp.hpp
---

Suffix ArrayとSparse Tableを用いて、同じ列上のLCP・辞書順比較・パターン検索を行います。

## 使い方

```cpp
LCP lcp(s);

int x = lcp.suffix_lcp(i, j);
int y = lcp.query(l1, r1, l2, r2);
int cmp = lcp.compare(l1, r1, l2, r2);
auto [first, last] = lcp.equal_range(pattern);
```

- `suffix_lcp(i, j)`: `s[i, N)`と`s[j, N)`のLCP長。
- `query(l1, r1, l2, r2)`: 2つの半開区間のLCP長。
- `compare(...)`: 第1区間が小さければ負、等しければ0、大きければ正。
- `equal_range(pattern)`: patternを接頭辞に持つ接尾辞のSuffix Array上の半開区間。

## 計算量

構築O(N log N)、LCPと比較はO(1)、検索はO(|pattern| log N)です。メモリO(N log N)です。

## 注意点

- 全区間は0-indexedの半開区間で、構築後に元の列を変更しないでください。
- `equal_range`の返り値は元文字列上の位置ではなく、Suffix Array上の添字範囲です。
- 空パターンは全接尾辞に一致します。

## 検証

- [Library Checker - Z Algorithm](https://judge.yosupo.jp/problem/zalgorithm)
- [AOJ ALDS1_14_D - Multiple String Matching](https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_14_D)

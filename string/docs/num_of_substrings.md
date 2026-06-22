---
title: Number of Distinct Substrings
documentation_of: ../num_of_substrings.hpp
---

空文字列を除く異なる部分文字列数をSuffix ArrayとLCP Arrayで求めます。

## 使い方

```cpp
long long count = num_of_substrings(s);
```

返り値は64-bit整数です。全ての部分文字列数`N(N+1)/2`から、Suffix Array上で隣接する接尾辞のLCPの総和を引いて求めます。

## 計算量

- 文字列: O(N)
- 一般の比較可能な列: 座標圧縮を含めO(N log N)
- 追加メモリ: O(N)

## 注意点

- 空文字列は種類数に含みません。
- 空列には0を返します。

## 検証

- [Library Checker - Number of Substrings](https://judge.yosupo.jp/problem/number_of_substrings)

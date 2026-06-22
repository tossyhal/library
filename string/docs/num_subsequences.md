---
title: Number of Distinct Subsequences
documentation_of: ../num_subsequences.hpp
---

異なる部分列の個数を法modで求めます。

## 使い方

```cpp
long long count = num_subsequences(sequence, 998244353);
long long with_empty = num_subsequences(sequence, 998244353, true);
```

同じ値列になる部分列は、選んだ添字が異なっても1種類として数えます。デフォルトでは空部分列を除き、`include_empty = true`なら含めます。

## 計算量

hash tableを用いるため期待時間O(N)、追加メモリO(K)です。Kは異なる要素数です。

## 注意点

- 要素型に`std::hash`と等値比較が必要です。
- `mod`には正の整数を指定します。
- 返り値は`[0, mod)`に正規化されます。

## 検証

- [Library Checker - Number of Subsequences](https://judge.yosupo.jp/problem/number_of_subsequences)

---
title: Edit Distance
documentation_of: ../edit_distance.hpp
---

挿入・削除・置換の最小回数、Levenshtein距離を求めます。

## 使い方

```cpp
int distance = edit_distance(s, t);
```

`s`, `t`は`size()`と添字アクセスを持つ同じ型の列です。返り値は、一方をもう一方へ変換するために必要な1要素の挿入・削除・置換の最小回数です。

## 計算量

`N = s.size()`, `M = t.size()`として、時間O(NM)、追加メモリO(min(N,M))です。

## 注意点

- 要素同士を`!=`で比較できる必要があります。
- 各操作のコストはすべて1です。重み付き編集距離や操作列の復元には対応しません。
- 空列も使用でき、もう一方の長さを返します。

## 検証

- [AOJ DPL_1_E - Edit Distance](https://onlinejudge.u-aizu.ac.jp/problems/DPL_1_E)

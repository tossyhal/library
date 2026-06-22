---
title: Multiple-base Rolling Hash
documentation_of: ../rolling_hash.hpp
---

mod `2^61-1`上で、独立した複数基底を使うRolling Hashです。

## 使い方

```cpp
RollingHash hash(s); // BasicRollingHash<2>

auto h = hash.get(l, r);
auto whole = hash.get();
int common = hash.lcp(hash, l1, r1, l2, r2);
auto joined = RollingHash::concat(left, right, right_length);
```

基底数は変更できます。

```cpp
BasicRollingHash<3> hash(s);
```

## 計算量

基底数をBとすると、構築O(BN)、区間hash O(B)、LCP O(B log N)です。
確率的な比較を許容できない場合は`LCP`を使用してください。

## API

- `get(l, r)`: 半開区間`[l, r)`のハッシュ。
- `get()`: 全体のハッシュ。
- `concat(left, right, right_length)`: 2つのハッシュを連結した値。
- `lcp(other, ...)`: 指定区間同士のLCP長。
- `size()`: 元の列の長さ。

## 注意点

- 同じプロセス内の`BasicRollingHash<BaseCount>`同士は共通の基底を使うため比較できます。
- ハッシュ一致には非常に低い確率で衝突があります。
- `concat`の`right_length`は右側ハッシュに対応する列長です。
- 全区間は0-indexedの半開区間です。

## 検証

- [AOJ ALDS1_14_B - String Search](https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_14_B)
- [Library Checker - Z Algorithm](https://judge.yosupo.jp/problem/zalgorithm)

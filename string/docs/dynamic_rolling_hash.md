---
title: Dynamic Rolling Hash
documentation_of: ../dynamic_rolling_hash.hpp
---

1点更新に対応したRolling Hashです。セグメント木に順方向と逆方向のhashを保持し、更新後の部分文字列比較、回文判定、LCPに使用できます。

## 使い方

```cpp
DynamicRollingHash hash(s);
hash.set(index, value);

auto forward = hash.get(l, r);
auto reverse = hash.get_reverse(l, r);
bool palindrome = hash.is_palindrome(l, r);
int common = hash.lcp(other, l1, r1, l2, r2);
```

基底数は`BasicDynamicRollingHash<BaseCount>`で変更できます。同じ`BaseCount`の`BasicRollingHash`と基底を共有するため、返されたhashを相互に比較できます。

## API

| シグネチャ | 説明 | 計算量 |
| --- | --- | --- |
| `BasicDynamicRollingHash()` | 空列を構築する | O(1) |
| `explicit BasicDynamicRollingHash(const Sequence &s)` | 列`s`から構築する | O(BN) |
| `int size() const` | 列の長さを返す | O(1) |
| `void set(int index, const T &value)` | `index`の値を更新する | O(B log N) |
| `Hash get(int l, int r) const` | `[l, r)`の順方向hashを返す | O(B log N) |
| `Hash get() const` | 列全体の順方向hashを返す | O(1) |
| `Hash get_reverse(int l, int r) const` | `[l, r)`を反転したhashを返す | O(B log N) |
| `bool is_palindrome(int l, int r) const` | `[l, r)`が回文か判定する | O(B log N) |
| `int lcp(const BasicDynamicRollingHash &other, ...) const` | 指定区間同士のLCP長を返す | O(B log^2 N) |

Bは基底数です。メモリはO(BN)です。

## 注意点

- 添字は0-indexed、区間は半開区間です。
- `set`の添字と各区間は範囲内である必要があります。
- hash一致には非常に低い確率で衝突があります。
- 空区間のhashは0で、空区間は回文です。
- `lcp`の省略した右端は、それぞれの列の末尾になります。

## 検証

- ランダムな1点更新、全区間のhash、逆方向hash、回文判定、LCPを愚直解と比較

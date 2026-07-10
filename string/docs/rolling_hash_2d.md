---
title: 2D Rolling Hash
documentation_of: ../rolling_hash_2d.hpp
---

長方形領域を比較するための2次元Rolling Hashです。横方向と縦方向に独立した基底を使い、長方形ごとに正規化したhashを返します。

## 使い方

```cpp
RollingHash2D hash(grid);
auto rectangle = hash.get(top, bottom, left, right);
auto whole = hash.get();
```

行と列は0-indexedで、`get(top, bottom, left, right)`は半開長方形`[top, bottom) x [left, right)`を表します。

## API

| シグネチャ | 説明 | 計算量 |
| --- | --- | --- |
| `BasicRollingHash2D()` | 空のグリッドを構築する | O(B) |
| `explicit BasicRollingHash2D(const Grid &grid)` | 長方形グリッドから構築する | O(BHW) |
| `int height() const` | 行数を返す | O(1) |
| `int width() const` | 列数を返す | O(1) |
| `Hash get(int top, int bottom, int left, int right) const` | 指定長方形のhashを返す | O(B) |
| `Hash get() const` | グリッド全体のhashを返す | O(B) |

Bは基底数です。メモリはO(BHW)です。

## 注意点

- 全ての行は同じ長さである必要があります。
- `Hash`はhash値に加えて高さと幅を持ちます。内容が同じでも形が異なる長方形は一致しません。
- 同じ`BaseCount`の`BasicRollingHash2D`同士で比較してください。
- hash一致には非常に低い確率で衝突があります。
- 0行の入力からは幅を復元できないため、空グリッドの大きさは`0 x 0`です。

## 検証

- [AOJ ALDS1_14_C - Pattern Search](https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_14_C)
- 小さいランダムグリッドの全長方形を、切り出して再構築したhashと比較

---
title: Run Enumeration
documentation_of: ../run_enumerate.hpp
---

極大な周期部分文字列を列挙します。

## 使い方

```cpp
auto runs = run_enumerate(s);
for (auto [period, l, r] : runs) {
    // s[l, r) の最小周期がperiod、長さは2*period以上
}
```

戻り値は`(period, l, r)`の辞書順です。計算量はO(N log N)です。

各要素は半開区間`s[l, r)`が最小周期`period`を持ち、`r-l >= 2*period`である極大なrunを表します。

## 計算量

時間O(N log N)、追加メモリO(N log N)です。

## 注意点

- 区間は0-indexedの半開区間です。
- 同じ区間が異なる周期で重複して返ることはなく、最小周期を返します。
- 要素型は比較可能である必要があります。
- 空列や長さ1の列には空のvectorを返します。

## 検証

- [Library Checker - Run Enumerate](https://judge.yosupo.jp/problem/runenumerate)

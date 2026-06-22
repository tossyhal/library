---
title: Z Algorithm
documentation_of: ../z_algorithm.hpp
---

列`S`の各位置について、`S`自身との最長共通接頭辞長をO(N)で求めます。

## 使い方

```cpp
auto z = z_algorithm(s);
// z[i] = LCP(s, s[i, n))
```

返り値は入力と同じ長さの`vector<int>`で、空でなければ`z[0] = s.size()`です。

## 計算量

時間O(N)、追加メモリO(N)です。

## 注意点

- `size()`と添字アクセスを持ち、要素を`==`で比較できる列に使用できます。
- 空列では空配列を返します。
- 文字列検索に使う場合、パターンとテキストの間に元の列に現れない区切り要素を置きます。

## 検証

- [Library Checker - Z Algorithm](https://judge.yosupo.jp/problem/zalgorithm)

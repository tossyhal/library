---
title: Lyndon Words
documentation_of: ../lyndon_word.hpp
---

Lyndon分解、Lyndon word判定、最小巡回表現をO(N)で求めます。

## 使い方

```cpp
auto factors = lyndon_factorization(s); // vector<pair<int, int>>, [l, r)
bool lyndon = is_lyndon_word(s);
int start = minimum_rotation(s);
```

- `lyndon_factorization`はDuval法による分解を半開区間`[l, r)`の列で返します。
- `is_lyndon_word`は、非空列が自身の全ての非自明な巡回・接尾辞より辞書順で小さいか判定します。
- `minimum_rotation`は辞書順最小の巡回表現が始まる0-indexed位置を返します。

## 計算量

各関数とも時間O(N)、分解の返り値を除く追加メモリO(1)です。

## 注意点

- 要素型に辞書順比較が必要です。
- 同じ最小巡回表現が複数ある場合は最小の開始位置を返します。
- 空列に対する判定・開始位置は実装の契約を確認し、通常は非空列へ使用してください。

## 検証

- [Library Checker - Lyndon Factorization](https://judge.yosupo.jp/problem/lyndon_factorization)

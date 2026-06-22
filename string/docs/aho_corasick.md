---
title: Aho–Corasick
documentation_of: ../aho_corasick.hpp
---

複数パターンを同時に検索します。

## 使い方

```cpp
AhoCorasick<> aho;
int id = aho.insert(pattern);
aho.build();
auto counts = aho.count_matches(text);
```

`counts[id]`がパターンの出現回数です。`build()`後はパターンを追加できません。

- `insert(pattern)`はパターンIDを返します。同じ文字列を複数回登録すると別IDになります。
- `next_state(state, c)`は1文字読んだ後の状態を返します。
- `count_matches(text)`は各IDの出現回数を、重なりを含めて返します。

## 計算量

登録は各パターン長に比例します。構築はO(ノード数×Sigma)、検索と集計はO(|text|+ノード数+パターン数)です。メモリはO(ノード数×Sigma)です。

## 注意点

- `AhoCorasick<Sigma, Margin>`が扱える文字は`[Margin, Margin + Sigma)`です。
- 空文字列パターンの出現回数は、位置`0..|text|`の`|text| + 1`箇所として数えます。
- 全パターンを登録してから`build()`を1回呼びます。
- `build()`後の`insert()`と再度の`build()`はできません。
- テキスト中の文字種範囲外の文字は根へ戻る区切りとして扱います。

## 検証

- [AOJ ALDS1_14_D - Multiple String Matching](https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_14_D)

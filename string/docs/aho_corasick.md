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
long long total = aho.count_all_matches(text);
```

`counts[id]`がパターンの出現回数です。`build()`後はパターンを追加できません。

- `insert(pattern)`はパターンIDを返します。同じ文字列を複数回登録すると別IDになります。
- `next_state(state, c)`は1文字読んだ後の状態を返します。
- `count_matches(text)`は各IDの出現回数を、重なりを含めて返します。
- `count_all_matches(text)`は全パターンの出現回数の合計を、重なりと重複登録を含めて返します。

## API

| シグネチャ | 説明 | 計算量 |
| --- | --- | --- |
| `AhoCorasick()` | 空のTrieを構築する | O(1) |
| `int insert(const Sequence &s)` | パターンを登録してIDを返す | O(|s|) |
| `void build()` | suffix linkとオートマトン遷移を構築する | O(V Sigma) |
| `int next_state(int state, char c) const` | 1文字読んだ後の状態を返す | O(1) |
| `std::vector<int> count_matches(const Sequence &text) const` | パターンごとの出現回数を返す | O(|text| + V + P) |
| `std::int64_t count_all_matches(const Sequence &text) const` | 全パターンの出現回数の合計を返す | O(|text|) |

## 計算量

Vをノード数、Pをパターン数とします。メモリはO(V Sigma + P)です。

## 注意点

- `AhoCorasick<Sigma, Margin>`が扱える文字は`[Margin, Margin + Sigma)`です。
- 空文字列パターンの出現回数は、位置`0..|text|`の`|text| + 1`箇所として数えます。
- 全パターンを登録してから`build()`を1回呼びます。
- `build()`後の`insert()`と再度の`build()`はできません。
- テキスト中の文字種範囲外の文字は根へ戻る区切りとして扱います。
- `nodes[v].parent`と`nodes[v].parent_char`はTrie上の親と親からの文字です。
- `nodes[v].next`は`build()`後にはTrieの子だけでなく、suffix linkを補ったオートマトン遷移を表します。

## 検証

- [AOJ ALDS1_14_D - Multiple String Matching](https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_14_D)
- [Library Checker - Aho Corasick](https://judge.yosupo.jp/problem/aho_corasick)

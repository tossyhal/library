---
title: Suffix Automaton
documentation_of: ../suffix_automaton.hpp
---

存在する遷移だけを保持する省メモリなSuffix Automatonです。

## 使い方

```cpp
SuffixAutomaton automaton(s);

bool exists = automaton.contains(pattern);
int state = automaton.find(pattern);
long long distinct = automaton.num_substrings();

automaton.build_occurrences();
auto order = automaton.topological_order();
```

各ノードは64-bit maskとソート済み遷移配列を持ちます。`Sigma <= 64`が必要です。

```cpp
SuffixAutomaton<26, 'a'> lower_case(s);
```

## APIと返り値

- `extend(c)`: 末尾へ1文字追加します。
- `next(state, c)`: 遷移先、存在しなければ`-1`。
- `find(pattern)`: パターンを読んだ状態、存在しなければ`-1`。
- `contains(pattern)`: パターンが部分文字列か。
- `num_substrings()`: 異なる非空部分文字列数。
- `topological_order()`: `nodes[v].length`の昇順の状態列。
- `build_occurrences()`: 各状態の出現回数をsuffix linkへ集約。

## 計算量

長さNの構築は償却O(N×Sigma)以内、状態数と遷移数はO(N)です。検索はO(|pattern|×Sigma)以内、種類数計算と出現数集約はO(N)です。

## 注意点

- `1 <= Sigma <= 64`で、文字は指定範囲内である必要があります。
- `nodes[state].occurrences`を完成した出現回数として使う前に`build_occurrences()`を呼びます。
- `find`が返す状態には複数の部分文字列が対応する場合があります。

## 検証

- [Library Checker - Number of Substrings](https://judge.yosupo.jp/problem/number_of_substrings)

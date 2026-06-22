---
title: Palindromic Tree / Eertree
documentation_of: ../palindromic_tree.hpp
---

異なる回文部分文字列をノードとして管理します。

## 使い方

```cpp
PalindromicTree tree(s);
int distinct = tree.num_palindromes();
tree.build_occurrences();
```

- `nodes[0]`: 長さ-1の仮想ノード
- `nodes[1]`: 長さ0の仮想ノード
- `nodes[v].length`: 回文長
- `nodes[v].link`: 最大の真の回文接尾辞
- `nodes[v].parent`: 両端を除いた回文
- `nodes[v].occurrences`: `build_occurrences()`後の出現数
- `suffix_history[i]`: `s[0, i+1)`の最長回文接尾辞

`add(c)`は文字を末尾へ追加し、新しい文字列の最長回文接尾辞に対応するノード番号を返します。`num_palindromes()`は異なる非空回文の種類数です。

## 計算量

1文字追加は償却O(1)、長さNの構築と`build_occurrences()`はO(N)、メモリO(N×Sigma)です。

## 注意点

- `PalindromicTree<Sigma, Margin>`の文字種範囲内だけを追加できます。
- `occurrences`を全出現回数として使う前に、全文字追加後に`build_occurrences()`を1回呼びます。
- ノード番号0と1は仮想ノードなので、実際の回文は2番以降です。

## 検証

- [Library Checker - Eertree](https://judge.yosupo.jp/problem/eertree)

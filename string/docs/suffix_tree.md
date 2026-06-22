---
title: Compact Suffix Tree
documentation_of: ../suffix_tree.hpp
---

Suffix ArrayとLCP Arrayから圧縮Suffix Treeを構築します。

## 使い方

```cpp
SuffixTree tree(s);

for (int v = 1; v < tree.nodes.size(); ++v) {
    int parent = tree.nodes[v].parent;
    int edge_length = tree.nodes[v].depth - tree.nodes[parent].depth;
}
```

`nodes[v].suffix_start`と親の深さから辺ラベルを復元できます。

## ノード

- `parent`: 親ノード番号。根は`-1`。
- `depth`: 根から対応文字列までの長さ。
- `suffix_start`: 辺ラベルを元の列から取り出すための接尾辞開始位置。
- `children`: 子ノード番号。
- `is_leaf()`: 子を持たないか。

親を`p`とすると、辺ラベルは元の列の
`[suffix_start + nodes[p].depth, suffix_start + depth)`です。

## 計算量

構築はSuffix ArrayとLCP Arrayを含め、文字列ではO(N)、一般列では座標圧縮によりO(N log N)です。ノード数とメモリはO(N)です。

## 注意点

- 根は`nodes[0]`です。
- 辺ラベル自体はコピーせず、元の列上の区間として保持します。木の利用中は元の列を参照できるようにしてください。
- 空接尾辞は葉として含みません。

## 検証

- [Library Checker - Number of Substrings](https://judge.yosupo.jp/problem/number_of_substrings)

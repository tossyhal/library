---
title: Trie
documentation_of: ../trie.hpp
---

固定アルファベット用Trieです。

## 使い方

```cpp
Trie<> trie; // 英小文字
int node = trie.insert(s);
bool exists = trie.contains(s);
int count = trie.count_prefix(prefix);
```

`Trie<Sigma, Margin>`で文字種類数と先頭文字を指定できます。

- `insert(s)`は終端ノード番号を返し、重複挿入も数えます。
- `find(s)`は対応ノード番号、存在しなければ`-1`を返します。
- `contains(s)`は完全一致する登録済み文字列があるか返します。
- `count_prefix(prefix)`はその接頭辞を持つ登録文字列数を重複込みで返します。

## 計算量

各操作は対象文字列長に比例します。ノード数をVとするとメモリO(V×Sigma)です。

## 注意点

- 各文字は`[Margin, Margin + Sigma)`の範囲である必要があります。
- `find`はTrie上に経路があるかを返し、その文字列自体が登録済みかは`contains`で判定します。
- `nodes[v].terminal`はノードvで終わる登録数、`count`はノードvを通る登録数です。

## 検証

- [AtCoder ABC287 E - Karuta](https://atcoder.jp/contests/abc287/tasks/abc287_e)

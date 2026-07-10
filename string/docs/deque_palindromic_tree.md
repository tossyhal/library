---
title: Deque Palindromic Tree
documentation_of: ../deque_palindromic_tree.hpp
---

文字列の両端への文字追加・削除に対応したPalindromic Treeです。現在の異なる非空回文部分文字列数、最長回文接頭辞、最長回文接尾辞を管理します。

## 使い方

```cpp
DequePalindromicTree<> tree;
tree.push_front(c);
tree.push_back(c);
tree.pop_front();
tree.pop_back();

int distinct = tree.num_palindromes();
int prefix = tree.longest_prefix_palindrome();
int suffix = tree.longest_suffix_palindrome();
```

## API

| シグネチャ | 説明 | 計算量 |
| --- | --- | --- |
| `DequePalindromicTree()` | 空文字列を構築する | O(1) |
| `int size() const` | 現在の文字列長を返す | O(1) |
| `bool empty() const` | 空文字列か返す | O(1) |
| `void push_front(char c)` | 先頭へ文字を追加する | O(Sigma) |
| `void push_back(char c)` | 末尾へ文字を追加する | O(Sigma) |
| `void pop_front()` | 先頭の文字を削除する | 償却O(1) |
| `void pop_back()` | 末尾の文字を削除する | 償却O(1) |
| `int num_palindromes() const` | 異なる非空回文部分文字列数を返す | O(1) |
| `int longest_prefix_palindrome() const` | 最長回文接頭辞の長さを返す | O(1) |
| `int longest_suffix_palindrome() const` | 最長回文接尾辞の長さを返す | O(1) |

`Sigma`を固定定数とみなす場合、文字追加もO(1)です。長さNに対するメモリはO(N Sigma)です。

## 挙動と制約

- `DequePalindromicTree<Sigma, Margin>`が扱える文字は`[Margin, Margin + Sigma)`です。
- 空の状態で`pop_front()`または`pop_back()`は呼べません。
- 更新はオブジェクト自身を変更します。
- 削除によって出現しなくなった回文ノードは内部で破棄されるため、安定した公開ノード番号は提供しません。
- quick linkにより、通常のsuffix linkを長くたどるケースを避けます。

## 検証

- [Library Checker - Palindromes in Deque](https://judge.yosupo.jp/problem/palindromes_in_deque)

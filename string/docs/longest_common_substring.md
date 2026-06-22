---
title: Longest Common Substring
documentation_of: ../longest_common_substring.hpp
---

2文字列の最長共通部分文字列をSuffix Arrayで求めます。

## 使い方

```cpp
auto result = longest_common_substring(s, t);

result.length;
result.first_pos;
result.second_pos;
```

対応する区間はそれぞれ
`s[first_pos, first_pos+length)`と`t[second_pos, second_pos+length)`です。

## 計算量

`N = s.size()`, `M = t.size()`として時間O(N+M)、追加メモリO(N+M)です。

## 注意点

- 「部分文字列」なので要素は連続します。部分列とは異なります。
- 最長解が複数ある場合はいずれか1つを返します。
- 共通する文字がない場合は`length = 0`です。この場合、位置は空区間として扱います。

## 検証

- [Library Checker - Longest Common Substring](https://judge.yosupo.jp/problem/longest_common_substring)

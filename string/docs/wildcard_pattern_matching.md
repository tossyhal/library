---
title: Wildcard Pattern Matching
documentation_of: ../wildcard_pattern_matching.hpp
---

wildcardを任意の1文字としてパターン検索します。text側・pattern側の両方にwildcardを置けます。

## 使い方

```cpp
auto positions = wildcard_pattern_matching(text, pattern, '?');
```

返り値は、wildcard以外の全ての位置が一致する開始位置を0-indexedの昇順で返します。wildcard同士、または片方だけがwildcardの位置は常に一致します。

## 計算量

- 小入力: 直接比較によるO(NM)
- 大入力: 3つのmodによるNTTでO((N+M) log(N+M))
- 追加メモリ: O(N+M)

## 注意点

- パターンがテキストより長い場合は空のvectorを返します。
- 空パターンは全境界に一致します。
- 通常文字はbyte値として扱います。wildcardには通常文字として照合したい文字を指定しないでください。
- NTT内部で複数modを使い、整数的に一致判定します。

## 検証

- [Library Checker - Wildcard Pattern Matching](https://judge.yosupo.jp/problem/wildcard_pattern_matching)

---
title: Manacher's Algorithm
documentation_of: ../manacher.hpp
---

奇数長・偶数長回文の最大半径をO(N)で求めます。

## 使い方

```cpp
Manacher manacher(s);

int odd_length = 2 * manacher.odd[i] - 1;
int even_length = 2 * manacher.even[i];
bool palindrome = manacher.is_palindrome(l, r);

auto lengths = enumerate_palindromes(s);
```

`lengths`は左から並べた`2N-1`個の中心ごとの最大回文長です。

- `odd[i]`は位置`i`を中心とする奇数長回文の半径で、長さは`2*odd[i]-1`です。
- `even[i]`は境界`i-1 | i`を中心とする偶数長回文の半径で、長さは`2*even[i]`です。
- `is_palindrome(l, r)`は半開区間`s[l, r)`をO(1)で判定します。

## 計算量

構築と列挙はO(N)、回文判定はO(1)、メモリO(N)です。

## 注意点

- `enumerate_palindromes`の返り値は空列では空、非空列では長さ`2N-1`です。
- 区間は0-indexedの半開区間です。
- 要素を`==`で比較できる任意の列に使用できます。

## 検証

- [Library Checker - Enumerate Palindromes](https://judge.yosupo.jp/problem/enumerate_palindromes)

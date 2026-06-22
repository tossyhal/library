---
title: Suffix Array (SA-IS)
documentation_of: ../suffix_array.hpp
---

接尾辞配列をSA-ISで構築します。空接尾辞は返り値に含みません。

## 使い方

```cpp
auto sa = suffix_array(s);
auto lcp = lcp_array(s, sa);
```

`suffix_array.hpp`は接尾辞配列とLCP配列の両方を提供します。
`sa[k]`は辞書順でk番目の接尾辞の開始位置、`lcp[k]`は隣接接尾辞のLCPです。

整数列の値域が既知なら次を使用します。

```cpp
vector<int> a = ...; // 0 <= a[i] <= upper
auto sa = suffix_array(a, upper);
```

## 計算量

- 文字列・値域指定整数列: O(N)
- 一般列: 座標圧縮を含めO(N log N)
- LCP Array: O(N)

## 返り値

`sa`の長さはNで、`sa[k]`は辞書順でk番目の接尾辞の開始位置です。`lcp`の長さは`max(0, N-1)`で、`lcp[k]`は`sa[k]`と`sa[k+1]`から始まる接尾辞のLCP長です。

## 注意点

- `suffix_array(vector<int>, upper)`では全要素が`0 <= a[i] <= upper`を満たす必要があります。
- 一般列版では要素に`<`と`!=`による比較が必要です。
- 空列には空配列を返します。
- 検索や部分文字列比較を頻繁に行う場合は`LCP`クラスも利用できます。

## 検証

- [Library Checker - Suffix Array](https://judge.yosupo.jp/problem/suffixarray)
- [Library Checker - Number of Substrings](https://judge.yosupo.jp/problem/number_of_substrings)

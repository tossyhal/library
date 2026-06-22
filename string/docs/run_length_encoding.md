---
title: Run-Length Encoding
documentation_of: ../run_length_encoding.hpp
---

連続する同じ値を`(値, 個数)`へ圧縮します。

## 使い方

```cpp
auto encoded = run_length_encoding(sequence);
for (auto [value, count] : encoded) {
    // valueがcount個連続する
}
```

返り値は`vector<pair<value_type, int>>`です。組を順に展開すると元の列に戻ります。

## 計算量

時間O(N)、返り値を除く追加メモリO(1)です。

## 注意点

- 隣接要素を`==`で比較できる必要があります。
- 同じ値でも離れた区間は別の組になります。
- 空列には空のvectorを返します。

## 検証

- 復元結果と隣接runの性質を全長12の二値列で検証

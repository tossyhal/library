#pragma once
#include <algorithm>
#include <utility>
#include <vector>

// Returns half-open intervals of the non-increasing Lyndon factorization.
template <class Sequence> std::vector<std::pair<int, int>> lyndon_factorization(const Sequence &s) {
    const int n = static_cast<int>(s.size());
    std::vector<std::pair<int, int>> result;
    for (int i = 0; i < n;) {
        int j = i + 1, k = i;
        while (j < n && !(s[j] < s[k])) {
            if (s[k] < s[j]) {
                k = i;
            } else {
                ++k;
            }
            ++j;
        }
        while (i <= k) {
            result.emplace_back(i, i + j - k);
            i += j - k;
        }
    }
    return result;
}

template <class Sequence> bool is_lyndon_word(const Sequence &s) {
    const auto factors = lyndon_factorization(s);
    return factors.size() == 1 && factors[0].first == 0 && factors[0].second == static_cast<int>(s.size()) &&
           !s.empty();
}

template <class Sequence> int minimum_rotation(const Sequence &s) {
    const int n = static_cast<int>(s.size());
    if (n == 0) {
        return 0;
    }
    int i = 0, j = 1, k = 0;
    while (i < n && j < n && k < n) {
        const auto &a = s[(i + k) % n];
        const auto &b = s[(j + k) % n];
        if (a == b) {
            ++k;
            continue;
        }
        if (b < a) {
            i += k + 1;
        } else {
            j += k + 1;
        }
        if (i == j) {
            ++j;
        }
        k = 0;
    }
    return std::min(i, j);
}

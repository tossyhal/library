#pragma once
#include <vector>

template <class Sequence> std::vector<int> prefix_function(const Sequence &s) {
    const int n = static_cast<int>(s.size());
    std::vector<int> pi(n);
    for (int i = 1; i < n; ++i) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) {
            j = pi[j - 1];
        }
        if (s[i] == s[j]) {
            ++j;
        }
        pi[i] = j;
    }
    return pi;
}

template <class Sequence> std::vector<int> minimum_periods(const Sequence &s) {
    const std::vector<int> pi = prefix_function(s);
    std::vector<int> period(s.size());
    for (int i = 1; i <= static_cast<int>(s.size()); ++i) {
        period[i - 1] = i - pi[i - 1];
    }
    return period;
}

template <class Text, class Pattern> std::vector<int> kmp(const Text &text, const Pattern &pattern) {
    std::vector<int> result;
    const int n = static_cast<int>(text.size());
    const int m = static_cast<int>(pattern.size());
    if (m == 0) {
        result.resize(n + 1);
        for (int i = 0; i <= n; ++i) {
            result[i] = i;
        }
        return result;
    }
    const auto pi = prefix_function(pattern);
    for (int i = 0, j = 0; i < n; ++i) {
        while (j > 0 && text[i] != pattern[j]) {
            j = pi[j - 1];
        }
        if (text[i] == pattern[j]) {
            ++j;
        }
        if (j == m) {
            result.push_back(i - m + 1);
            j = pi[j - 1];
        }
    }
    return result;
}

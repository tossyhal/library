#pragma once
#include <vector>

// failure[i]: mismatch after matching i characters moves the state to failure[i].
template <class Sequence> std::vector<int> morris_pratt_failure(const Sequence &pattern) {
    const int m = static_cast<int>(pattern.size());
    std::vector<int> failure(m + 1);
    failure[0] = -1;
    for (int i = 0, j = -1; i < m;) {
        while (j >= 0 && pattern[i] != pattern[j]) {
            j = failure[j];
        }
        failure[++i] = ++j;
    }
    return failure;
}

template <class Text, class Pattern> std::vector<int> morris_pratt(const Text &text, const Pattern &pattern) {
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
    const auto failure = morris_pratt_failure(pattern);
    for (int i = 0, j = 0; i < n;) {
        while (j >= 0 && text[i] != pattern[j]) {
            j = failure[j];
        }
        ++i;
        ++j;
        if (j == m) {
            result.push_back(i - m);
            j = failure[j];
        }
    }
    return result;
}

#pragma once
#include <algorithm>
#include <string>
#include <vector>

template <class Sequence> int longest_common_subsequence_length(const Sequence &a, const Sequence &b) {
    if (a.size() < b.size()) {
        return longest_common_subsequence_length(b, a);
    }
    std::vector<int> dp(b.size() + 1);
    for (const auto &x : a) {
        int diagonal = 0;
        for (int j = 0; j < static_cast<int>(b.size()); ++j) {
            const int old = dp[j + 1];
            if (x == b[j]) {
                dp[j + 1] = diagonal + 1;
            } else {
                dp[j + 1] = std::max(dp[j + 1], dp[j]);
            }
            diagonal = old;
        }
    }
    return dp.back();
}

template <class Sequence>
std::vector<typename Sequence::value_type> longest_common_subsequence(const Sequence &a, const Sequence &b) {
    const int n = static_cast<int>(a.size());
    const int m = static_cast<int>(b.size());
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            dp[i + 1][j + 1] = a[i] == b[j] ? dp[i][j] + 1 : std::max(dp[i][j + 1], dp[i + 1][j]);
        }
    }
    std::vector<typename Sequence::value_type> result;
    for (int i = n, j = m; i && j;) {
        if (a[i - 1] == b[j - 1]) {
            result.push_back(a[--i]);
            --j;
        } else if (dp[i - 1][j] >= dp[i][j - 1]) {
            --i;
        } else {
            --j;
        }
    }
    std::reverse(result.begin(), result.end());
    return result;
}

inline std::string longest_common_subsequence(const std::string &a, const std::string &b) {
    const auto result = longest_common_subsequence<std::string>(a, b);
    return {result.begin(), result.end()};
}

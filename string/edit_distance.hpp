#pragma once
#include <algorithm>
#include <vector>

template <class Sequence> int edit_distance(const Sequence &a, const Sequence &b) {
    if (a.size() < b.size()) {
        return edit_distance(b, a);
    }
    std::vector<int> dp(b.size() + 1);
    for (int j = 0; j <= static_cast<int>(b.size()); ++j) {
        dp[j] = j;
    }
    for (int i = 0; i < static_cast<int>(a.size()); ++i) {
        int diagonal = dp[0]++;
        for (int j = 0; j < static_cast<int>(b.size()); ++j) {
            const int old = dp[j + 1];
            dp[j + 1] = std::min({
                dp[j + 1] + 1,
                dp[j] + 1,
                diagonal + (a[i] != b[j]),
            });
            diagonal = old;
        }
    }
    return dp.back();
}

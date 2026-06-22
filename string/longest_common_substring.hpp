#pragma once
#include <string>
#include <utility>
#include <vector>
#include "suffix_array.hpp"

struct LongestCommonSubstring {
    int length = 0;
    int first_pos = 0;
    int second_pos = 0;
};

inline LongestCommonSubstring longest_common_substring(const std::string &a, const std::string &b) {
    const int n = static_cast<int>(a.size());
    const int m = static_cast<int>(b.size());
    std::vector<int> joined;
    joined.reserve(n + m + 1);
    for (unsigned char c : a) {
        joined.push_back(c + 1);
    }
    joined.push_back(0);
    for (unsigned char c : b) {
        joined.push_back(c + 1);
    }
    const auto sa = suffix_array(joined, 256);
    const auto lcp = lcp_array(joined, sa);
    LongestCommonSubstring result;
    for (int i = 0; i + 1 < static_cast<int>(sa.size()); ++i) {
        int x = sa[i], y = sa[i + 1];
        if (x > y) {
            std::swap(x, y);
        }
        if (x < n && y > n && lcp[i] > result.length) {
            result.length = lcp[i];
            result.first_pos = x;
            result.second_pos = y - n - 1;
        }
    }
    return result;
}

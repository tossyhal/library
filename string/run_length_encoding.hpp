#pragma once
#include <utility>
#include <vector>

template <class Sequence> auto run_length_encoding(const Sequence &s) {
    using T = typename Sequence::value_type;
    std::vector<std::pair<T, int>> result;
    for (const T &x : s) {
        if (result.empty() || result.back().first != x) {
            result.emplace_back(x, 1);
        } else {
            ++result.back().second;
        }
    }
    return result;
}

#pragma once
#include <cstdint>
#include "suffix_array.hpp"

template <class Sequence> std::int64_t num_of_substrings(const Sequence &s) {
    const std::int64_t n = static_cast<std::int64_t>(s.size());
    const auto sa = suffix_array(s);
    const auto lcp = lcp_array(s, sa);
    std::int64_t result = n * (n + 1) / 2;
    for (int x : lcp) {
        result -= x;
    }
    return result;
}

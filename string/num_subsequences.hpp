#pragma once
#include <cassert>
#include <cstdint>
#include <unordered_map>

// Number of distinct subsequences. The empty subsequence is excluded by default.
template <class Sequence>
std::int64_t num_subsequences(const Sequence &s, std::int64_t mod = 1'000'000'007, bool include_empty = false) {
    assert(mod > 0);
    std::unordered_map<typename Sequence::value_type, std::int64_t> before;
    std::int64_t total = 1;
    for (const auto &x : s) {
        const std::int64_t old = total;
        total = (2 * total - before[x]) % mod;
        if (total < 0) {
            total += mod;
        }
        before[x] = old;
    }
    if (!include_empty) {
        total = (total + mod - 1) % mod;
    }
    return total;
}

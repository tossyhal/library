#pragma once
#include <algorithm>
#include <set>
#include <tuple>
#include <utility>
#include <vector>
#include "z_algorithm.hpp"

// A run (period, l, r) is a maximal periodic substring s[l, r)
// whose minimum period is period and whose length is at least 2*period.
template <class Sequence> std::vector<std::tuple<int, int, int>> run_enumerate(const Sequence &s) {
    using Run = std::tuple<int, int, int>;
    const int n = static_cast<int>(s.size());
    std::vector<std::vector<std::pair<int, int>>> candidates(n + 1);

    auto crossing_runs = [](Sequence left, Sequence right) {
        const int left_size = static_cast<int>(left.size());
        const int right_size = static_cast<int>(right.size());

        Sequence reversed_left = left;
        std::reverse(reversed_left.begin(), reversed_left.end());

        Sequence joined = right;
        joined.insert(joined.end(), left.begin(), left.end());
        joined.insert(joined.end(), right.begin(), right.end());

        const std::vector<int> left_lcp = z_algorithm(reversed_left);
        const std::vector<int> right_lcp = z_algorithm(joined);
        std::vector<std::tuple<int, int, int>> result;
        for (int period = 1; period <= left_size; ++period) {
            const int extend_left =
                period == left_size ? period : std::min(period + left_lcp[period], left_size);
            const int extend_right = std::min(right_lcp[left_size + right_size - period], right_size);
            if (extend_left + extend_right >= 2 * period) {
                result.emplace_back(period, extend_left, extend_right);
            }
        }
        return result;
    };

    auto divide = [&](auto &&self, int l, int r) -> void {
        if (r - l <= 1) {
            return;
        }
        const int middle = (l + r) / 2;
        self(self, l, middle);
        self(self, middle, r);

        Sequence left(s.begin() + l, s.begin() + middle);
        Sequence right(s.begin() + middle, s.begin() + r);
        for (const auto &[period, extend_left, extend_right] : crossing_runs(left, right)) {
            candidates[period].emplace_back(middle - extend_left, middle + extend_right);
        }

        std::reverse(left.begin(), left.end());
        std::reverse(right.begin(), right.end());
        for (const auto &[period, extend_right, extend_left] : crossing_runs(right, left)) {
            candidates[period].emplace_back(middle - extend_left, middle + extend_right);
        }
    };
    divide(divide, 0, n);

    std::set<std::pair<int, int>> used_intervals;
    std::vector<Run> result;
    for (int period = 1; period <= n; ++period) {
        auto &intervals = candidates[period];
        std::sort(intervals.begin(), intervals.end(), [](const auto &left, const auto &right) {
            if (left.first != right.first) {
                return left.first < right.first;
            }
            return left.second > right.second;
        });
        int farthest_right = -1;
        for (const auto &[l, r] : intervals) {
            if (r <= farthest_right) {
                continue;
            }
            farthest_right = r;
            if (used_intervals.emplace(l, r).second) {
                result.emplace_back(period, l, r);
            }
        }
    }
    std::sort(result.begin(), result.end());
    return result;
}

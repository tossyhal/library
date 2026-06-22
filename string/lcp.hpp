#pragma once
#include <algorithm>
#include <cassert>
#include <utility>
#include <vector>
#include "suffix_array.hpp"

template <class Sequence> class LCP {
    int n_;
    Sequence sequence_;
    std::vector<int> sa_, rank_, log_;
    std::vector<std::vector<int>> table_;

  public:
    explicit LCP(const Sequence &s)
        : n_(static_cast<int>(s.size())), sequence_(s), sa_(suffix_array(sequence_)), rank_(n_) {
        for (int i = 0; i < n_; ++i) {
            rank_[sa_[i]] = i;
        }
        const auto adjacent = lcp_array(sequence_, sa_);
        log_.assign(n_ + 1, 0);
        for (int i = 2; i <= n_; ++i) {
            log_[i] = log_[i / 2] + 1;
        }
        if (!adjacent.empty()) {
            table_.push_back(adjacent);
            for (int k = 1; (1 << k) <= static_cast<int>(adjacent.size()); ++k) {
                const int size = static_cast<int>(adjacent.size()) - (1 << k) + 1;
                table_.emplace_back(size);
                for (int i = 0; i < size; ++i) {
                    table_[k][i] = std::min(table_[k - 1][i], table_[k - 1][i + (1 << (k - 1))]);
                }
            }
        }
    }

    const std::vector<int> &suffixes() const { return sa_; }
    const std::vector<int> &ranks() const { return rank_; }

    int suffix_lcp(int i, int j) const {
        assert(0 <= i && i < n_ && 0 <= j && j < n_);
        if (i == j) {
            return n_ - i;
        }
        int l = rank_[i], r = rank_[j];
        if (l > r) {
            std::swap(l, r);
        }
        const int k = log_[r - l];
        return std::min(table_[k][l], table_[k][r - (1 << k)]);
    }

    int query(int l1, int r1, int l2, int r2) const {
        assert(0 <= l1 && l1 <= r1 && r1 <= n_);
        assert(0 <= l2 && l2 <= r2 && r2 <= n_);
        if (l1 == r1 || l2 == r2) {
            return 0;
        }
        return std::min({suffix_lcp(l1, l2), r1 - l1, r2 - l2});
    }

    int compare(int l1, int r1, int l2, int r2) const {
        assert(0 <= l1 && l1 <= r1 && r1 <= n_);
        assert(0 <= l2 && l2 <= r2 && r2 <= n_);
        const int common = query(l1, r1, l2, r2);
        if (l1 + common == r1 || l2 + common == r2) {
            if (r1 - l1 == r2 - l2) {
                return 0;
            }
            return r1 - l1 < r2 - l2 ? -1 : 1;
        }
        return sequence_[l1 + common] < sequence_[l2 + common] ? -1 : 1;
    }

    template <class Pattern> std::pair<int, int> equal_range(const Pattern &pattern) const {
        auto suffix_is_less = [&](int suffix, bool pattern_is_prefix) {
            int i = suffix;
            int j = 0;
            while (i < n_ && j < static_cast<int>(pattern.size()) && sequence_[i] == pattern[j]) {
                ++i;
                ++j;
            }
            if (j == static_cast<int>(pattern.size())) {
                return pattern_is_prefix;
            }
            if (i == n_) {
                return true;
            }
            return sequence_[i] < pattern[j];
        };

        int left = 0;
        int right = n_;
        while (left < right) {
            const int middle = (left + right) / 2;
            if (suffix_is_less(sa_[middle], false)) {
                left = middle + 1;
            } else {
                right = middle;
            }
        }
        const int lower = left;

        left = lower;
        right = n_;
        while (left < right) {
            const int middle = (left + right) / 2;
            if (suffix_is_less(sa_[middle], true)) {
                left = middle + 1;
            } else {
                right = middle;
            }
        }
        return {lower, left};
    }
};

template <class Sequence> LCP(const Sequence &) -> LCP<Sequence>;

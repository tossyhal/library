#pragma once
#include <algorithm>
#include <cassert>
#include <numeric>
#include <string>
#include <vector>

namespace suffix_array_internal {

inline std::vector<int> sa_is(const std::vector<int> &s, int upper) {
    const int n = static_cast<int>(s.size());
    if (n == 0) {
        return {};
    }
    if (n == 1) {
        return {0};
    }
    if (n == 2) {
        if (s[0] < s[1]) {
            return {0, 1};
        }
        return {1, 0};
    }

    std::vector<bool> is_s(n);
    is_s[n - 1] = true;
    for (int i = n - 2; i >= 0; --i) {
        if (s[i] == s[i + 1]) {
            is_s[i] = is_s[i + 1];
        } else {
            is_s[i] = s[i] < s[i + 1];
        }
    }

    std::vector<int> bucket_start(upper + 2), bucket_end(upper + 2);
    for (int value : s) {
        ++bucket_start[value + 1];
        ++bucket_end[value];
    }
    std::partial_sum(bucket_start.begin(), bucket_start.end(), bucket_start.begin());
    std::partial_sum(bucket_end.begin(), bucket_end.end(), bucket_end.begin());

    std::vector<int> sa(n, -1);
    auto induce = [&](const std::vector<int> &lms) {
        std::fill(sa.begin(), sa.end(), -1);

        std::vector<int> end = bucket_end;
        for (int i = static_cast<int>(lms.size()) - 1; i >= 0; --i) {
            const int position = lms[i];
            sa[--end[s[position]]] = position;
        }

        std::vector<int> start = bucket_start;
        for (int i = 0; i < n; ++i) {
            const int position = sa[i];
            if (position > 0 && !is_s[position - 1]) {
                sa[start[s[position - 1]]++] = position - 1;
            }
        }

        end = bucket_end;
        for (int i = n - 1; i >= 0; --i) {
            const int position = sa[i];
            if (position > 0 && is_s[position - 1]) {
                sa[--end[s[position - 1]]] = position - 1;
            }
        }
    };

    std::vector<int> lms_map(n + 1, -1);
    int lms_count = 0;
    for (int i = 1; i < n; ++i) {
        if (!is_s[i - 1] && is_s[i]) {
            lms_map[i] = lms_count++;
        }
    }

    std::vector<int> lms;
    lms.reserve(lms_count);
    for (int i = 1; i < n; ++i) {
        if (lms_map[i] != -1) {
            lms.push_back(i);
        }
    }
    induce(lms);

    if (lms_count > 0) {
        std::vector<int> sorted_lms;
        sorted_lms.reserve(lms_count);
        for (int position : sa) {
            if (position >= 0 && lms_map[position] != -1) {
                sorted_lms.push_back(position);
            }
        }

        auto same_lms_substring = [&](int left, int right) {
            if (left == right) {
                return true;
            }
            while (true) {
                if (s[left] != s[right] || is_s[left] != is_s[right]) {
                    return false;
                }
                ++left;
                ++right;
                const bool left_is_lms = lms_map[left] != -1;
                const bool right_is_lms = lms_map[right] != -1;
                if (left_is_lms || right_is_lms) {
                    return left_is_lms && right_is_lms;
                }
            }
        };

        std::vector<int> reduced(lms_count);
        int reduced_upper = 0;
        reduced[lms_map[sorted_lms[0]]] = 0;
        for (int i = 1; i < lms_count; ++i) {
            if (!same_lms_substring(sorted_lms[i - 1], sorted_lms[i])) {
                ++reduced_upper;
            }
            reduced[lms_map[sorted_lms[i]]] = reduced_upper;
        }

        const std::vector<int> reduced_sa = sa_is(reduced, reduced_upper);
        for (int i = 0; i < lms_count; ++i) {
            sorted_lms[i] = lms[reduced_sa[i]];
        }
        induce(sorted_lms);
    }
    return sa;
}

inline std::vector<int> build(const std::vector<int> &values, int upper) {
    assert(0 <= upper);
    std::vector<int> with_sentinel(values.size() + 1);
    for (int i = 0; i < static_cast<int>(values.size()); ++i) {
        assert(0 <= values[i] && values[i] <= upper);
        with_sentinel[i] = values[i] + 1;
    }
    const std::vector<int> sa_with_sentinel = sa_is(with_sentinel, upper + 1);
    return {sa_with_sentinel.begin() + 1, sa_with_sentinel.end()};
}

} // namespace suffix_array_internal

inline std::vector<int> suffix_array(const std::string &s) {
    std::vector<int> values(s.size());
    for (int i = 0; i < static_cast<int>(s.size()); ++i) {
        values[i] = static_cast<unsigned char>(s[i]);
    }
    return suffix_array_internal::build(values, 255);
}

inline std::vector<int> suffix_array(const std::vector<int> &s, int upper) {
    return suffix_array_internal::build(s, upper);
}

template <class Sequence> std::vector<int> suffix_array(const Sequence &s) {
    const int n = static_cast<int>(s.size());
    if (n == 0) {
        return {};
    }
    std::vector<int> order(n), values(n);
    std::iota(order.begin(), order.end(), 0);
    std::sort(order.begin(), order.end(), [&](int i, int j) {
        return s[i] < s[j];
    });
    int rank = 0;
    values[order[0]] = 0;
    for (int i = 1; i < n; ++i) {
        if (s[order[i - 1]] != s[order[i]]) {
            ++rank;
        }
        values[order[i]] = rank;
    }
    return suffix_array_internal::build(values, rank);
}

template <class Sequence> std::vector<int> lcp_array(const Sequence &s, const std::vector<int> &sa) {
    const int n = static_cast<int>(s.size());
    assert(static_cast<int>(sa.size()) == n);
    if (n <= 1) {
        return {};
    }
    std::vector<int> rank(n), lcp(n - 1);
    for (int i = 0; i < n; ++i) {
        rank[sa[i]] = i;
    }
    for (int i = 0, height = 0; i < n; ++i) {
        if (rank[i] == n - 1) {
            height = 0;
            continue;
        }
        const int j = sa[rank[i] + 1];
        while (i + height < n && j + height < n && s[i + height] == s[j + height]) {
            ++height;
        }
        lcp[rank[i]] = height;
        if (height > 0) {
            --height;
        }
    }
    return lcp;
}

#pragma once
#include <vector>

template <class Sequence> struct Manacher {
    std::vector<int> odd;  // palindrome length = 2 * odd[i] - 1
    std::vector<int> even; // palindrome length = 2 * even[i], center is between i-1 and i

    explicit Manacher(const Sequence &s) {
        const int n = static_cast<int>(s.size());
        odd.assign(n, 0);
        even.assign(n, 0);
        for (int i = 0, l = 0, r = -1; i < n; ++i) {
            int k = i > r ? 1 : std::min(odd[l + r - i], r - i + 1);
            while (i - k >= 0 && i + k < n && s[i - k] == s[i + k]) {
                ++k;
            }
            odd[i] = k--;
            if (i + k > r) {
                l = i - k, r = i + k;
            }
        }
        for (int i = 0, l = 0, r = -1; i < n; ++i) {
            int k = i > r ? 0 : std::min(even[l + r - i + 1], r - i + 1);
            while (i - k - 1 >= 0 && i + k < n && s[i - k - 1] == s[i + k]) {
                ++k;
            }
            even[i] = k--;
            if (i + k > r) {
                l = i - k - 1, r = i + k;
            }
        }
    }

    bool is_palindrome(int l, int r) const {
        const int len = r - l;
        if (len <= 1) {
            return true;
        }
        if (len & 1) {
            return odd[(l + r) / 2] >= (len + 1) / 2;
        }
        return even[(l + r) / 2] >= len / 2;
    }
};

template <class Sequence> Manacher(const Sequence &) -> Manacher<Sequence>;

// Maximum palindrome length for each of the 2*n-1 centers.
// result[2*i] is centered at s[i].
// result[2*i+1] is centered between s[i] and s[i+1].
template <class Sequence> std::vector<int> enumerate_palindromes(const Sequence &s) {
    const int n = static_cast<int>(s.size());
    if (n == 0) {
        return {};
    }
    const Manacher result(s);
    std::vector<int> lengths(2 * n - 1);
    for (int i = 0; i < n; ++i) {
        lengths[2 * i] = 2 * result.odd[i] - 1;
        if (i + 1 < n) {
            lengths[2 * i + 1] = 2 * result.even[i + 1];
        }
    }
    return lengths;
}

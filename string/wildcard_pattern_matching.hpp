#pragma once
#include <algorithm>
#include <cassert>
#include <cstdint>
#include <string>
#include <vector>

namespace wildcard_internal {
template <int Mod> int power(int a, int n) {
    long long result = 1;
    while (n) {
        if (n & 1) {
            result = result * a % Mod;
        }
        a = static_cast<long long>(a) * a % Mod;
        n >>= 1;
    }
    return static_cast<int>(result);
}

template <int Mod> void ntt(std::vector<int> &a, bool inverse) {
    const int n = static_cast<int>(a.size());
    assert((Mod - 1) % n == 0);
    for (int i = 1, j = 0; i < n; ++i) {
        int bit = n >> 1;
        while (j & bit) {
            j ^= bit, bit >>= 1;
        }
        j ^= bit;
        if (i < j) {
            std::swap(a[i], a[j]);
        }
    }
    for (int length = 2; length <= n; length <<= 1) {
        int root = power<Mod>(3, (Mod - 1) / length);
        if (inverse) {
            root = power<Mod>(root, Mod - 2);
        }
        for (int i = 0; i < n; i += length) {
            long long w = 1;
            for (int j = 0; j < length / 2; ++j) {
                const int u = a[i + j];
                const int v = static_cast<int>(w * a[i + j + length / 2] % Mod);
                a[i + j] = u + v < Mod ? u + v : u + v - Mod;
                a[i + j + length / 2] = u - v >= 0 ? u - v : u - v + Mod;
                w = w * root % Mod;
            }
        }
    }
    if (inverse) {
        const int inverse_n = power<Mod>(n, Mod - 2);
        for (int &x : a) {
            x = static_cast<long long>(x) * inverse_n % Mod;
        }
    }
}

template <int Mod> std::vector<int> convolution(std::vector<int> a, std::vector<int> b) {
    if (a.empty() || b.empty()) {
        return {};
    }
    const int result_size = static_cast<int>(a.size() + b.size()) - 1;
    int size = 1;
    while (size < result_size) {
        size <<= 1;
    }
    a.resize(size);
    b.resize(size);
    ntt<Mod>(a, false);
    ntt<Mod>(b, false);
    for (int i = 0; i < size; ++i) {
        a[i] = static_cast<long long>(a[i]) * b[i] % Mod;
    }
    ntt<Mod>(a, true);
    a.resize(result_size);
    return a;
}

template <int Mod>
std::vector<int> mismatch_values(const std::string &text, const std::string &pattern, char wildcard) {
    const int n = static_cast<int>(text.size());
    const int m = static_cast<int>(pattern.size());
    std::vector<int> t1(n), t2(n), t3(n), p1(m), p2(m), p3(m);
    for (int i = 0; i < n; ++i) {
        if (text[i] == wildcard) {
            continue;
        }
        const long long x = static_cast<unsigned char>(text[i]) + 1;
        t1[i] = x;
        t2[i] = x * x % Mod;
        t3[i] = x * x % Mod * x % Mod;
    }
    for (int i = 0; i < m; ++i) {
        if (pattern[i] == wildcard) {
            continue;
        }
        const long long x = static_cast<unsigned char>(pattern[i]) + 1;
        const int j = m - 1 - i;
        p1[j] = x;
        p2[j] = x * x % Mod;
        p3[j] = x * x % Mod * x % Mod;
    }
    auto a = convolution<Mod>(t3, p1);
    const auto b = convolution<Mod>(t2, p2);
    const auto c = convolution<Mod>(t1, p3);
    for (int i = 0; i < static_cast<int>(a.size()); ++i) {
        a[i] = (a[i] - 2LL * b[i] % Mod + c[i]) % Mod;
        if (a[i] < 0) {
            a[i] += Mod;
        }
    }
    return a;
}
} // namespace wildcard_internal

// '?' matches any single byte in either the text or the pattern. O((n+m) log(n+m)).
inline std::vector<int> wildcard_pattern_matching(const std::string &text, const std::string &pattern,
                                                  char wildcard = '?') {
    const int n = static_cast<int>(text.size());
    const int m = static_cast<int>(pattern.size());
    std::vector<int> result;
    if (m == 0) {
        result.resize(n + 1);
        for (int i = 0; i <= n; ++i) {
            result[i] = i;
        }
        return result;
    }
    if (m > n) {
        return result;
    }
    if (static_cast<long long>(n) * m <= 4096) {
        for (int i = 0; i + m <= n; ++i) {
            bool matches = true;
            for (int j = 0; j < m; ++j) {
                matches &= text[i + j] == wildcard || pattern[j] == wildcard || text[i + j] == pattern[j];
            }
            if (matches) {
                result.push_back(i);
            }
        }
        return result;
    }
    const auto first = wildcard_internal::mismatch_values<998244353>(text, pattern, wildcard);
    const auto second = wildcard_internal::mismatch_values<469762049>(text, pattern, wildcard);
    const auto third = wildcard_internal::mismatch_values<1004535809>(text, pattern, wildcard);
    for (int i = 0; i + m <= n; ++i) {
        const int index = i + m - 1;
        if (first[index] == 0 && second[index] == 0 && third[index] == 0) {
            result.push_back(i);
        }
    }
    return result;
}

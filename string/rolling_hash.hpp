#pragma once
#include <algorithm>
#include <array>
#include <cassert>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <random>
#include <vector>

template <std::size_t BaseCount = 2> class BasicRollingHash {
  public:
    using u64 = std::uint64_t;

    struct Hash {
        std::array<u64, BaseCount> value{};

        bool operator==(const Hash &) const = default;
    };

  private:
    static constexpr u64 mod = (u64{1} << 61) - 1;
    inline static std::array<u64, BaseCount> bases_{};
    inline static std::array<std::vector<u64>, BaseCount> powers_{};
    std::vector<Hash> prefix_;

    static u64 add(u64 a, u64 b) {
        a += b;
        if (a >= mod) {
            a -= mod;
        }
        return a;
    }

    static u64 subtract(u64 a, u64 b) {
        return a >= b ? a - b : a + mod - b;
    }

    static u64 multiply(u64 a, u64 b) {
        const __uint128_t product = static_cast<__uint128_t>(a) * b;
        u64 result = static_cast<u64>(product >> 61) + (static_cast<u64>(product) & mod);
        if (result >= mod) {
            result -= mod;
        }
        return result;
    }

    static void initialize_bases() {
        if (bases_[0] != 0) {
            return;
        }
        std::uint64_t seed = std::chrono::steady_clock::now().time_since_epoch().count();
        seed ^= reinterpret_cast<std::uintptr_t>(&seed);
        std::mt19937_64 random(seed);
        for (std::size_t i = 0; i < BaseCount; ++i) {
            while (true) {
                const u64 candidate = 256 + random() % (mod - 512);
                bool unique = true;
                for (std::size_t j = 0; j < i; ++j) {
                    if (candidate == bases_[j]) {
                        unique = false;
                    }
                }
                if (unique) {
                    bases_[i] = candidate;
                    powers_[i] = {1};
                    break;
                }
            }
        }
    }

    static void reserve_powers(int length) {
        initialize_bases();
        for (std::size_t i = 0; i < BaseCount; ++i) {
            while (static_cast<int>(powers_[i].size()) <= length) {
                powers_[i].push_back(multiply(powers_[i].back(), bases_[i]));
            }
        }
    }

    template <class T> static u64 encode(const T &value) {
        return static_cast<u64>(value) % (mod - 1) + 1;
    }

  public:
    BasicRollingHash() : prefix_(1) {
        initialize_bases();
    }

    template <class Sequence> explicit BasicRollingHash(const Sequence &s) : prefix_(s.size() + 1) {
        reserve_powers(static_cast<int>(s.size()));
        for (int i = 0; i < static_cast<int>(s.size()); ++i) {
            const u64 encoded = encode(s[i]);
            for (std::size_t j = 0; j < BaseCount; ++j) {
                prefix_[i + 1].value[j] = add(multiply(prefix_[i].value[j], bases_[j]), encoded);
            }
        }
    }

    int size() const {
        return static_cast<int>(prefix_.size()) - 1;
    }

    Hash get(int l, int r) const {
        assert(0 <= l && l <= r && r <= size());
        Hash result;
        for (std::size_t i = 0; i < BaseCount; ++i) {
            result.value[i] = subtract(prefix_[r].value[i], multiply(prefix_[l].value[i], powers_[i][r - l]));
        }
        return result;
    }

    Hash get() const {
        return prefix_.back();
    }

    static Hash concat(const Hash &left, const Hash &right, int right_length) {
        assert(right_length >= 0);
        reserve_powers(right_length);
        Hash result;
        for (std::size_t i = 0; i < BaseCount; ++i) {
            result.value[i] = add(multiply(left.value[i], powers_[i][right_length]), right.value[i]);
        }
        return result;
    }

    int lcp(const BasicRollingHash &other, int l1 = 0, int r1 = -1, int l2 = 0, int r2 = -1) const {
        if (r1 < 0) {
            r1 = size();
        }
        if (r2 < 0) {
            r2 = other.size();
        }
        assert(0 <= l1 && l1 <= r1 && r1 <= size());
        assert(0 <= l2 && l2 <= r2 && r2 <= other.size());
        int low = 0;
        int high = std::min(r1 - l1, r2 - l2) + 1;
        while (high - low > 1) {
            const int middle = (low + high) / 2;
            if (get(l1, l1 + middle) == other.get(l2, l2 + middle)) {
                low = middle;
            } else {
                high = middle;
            }
        }
        return low;
    }
};

using RollingHash = BasicRollingHash<2>;

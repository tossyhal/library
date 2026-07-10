#pragma once
#include <array>
#include <cassert>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <random>
#include <vector>
#include "rolling_hash.hpp"

template <std::size_t BaseCount = 2> class BasicRollingHash2D {
  public:
    using u64 = std::uint64_t;

    struct Hash {
        std::array<u64, BaseCount> value{};
        int height = 0;
        int width = 0;

        bool operator==(const Hash &) const = default;
    };

  private:
    using Context = rolling_hash_internal::Context<BaseCount>;
    inline static std::array<u64, BaseCount> vertical_bases_{};
    inline static std::array<std::vector<u64>, BaseCount> vertical_powers_{};

    int height_ = 0;
    int width_ = 0;
    std::vector<Hash> prefix_{1};

    static void initialize_vertical_bases() {
        Context::initialize();
        if (vertical_bases_[0] != 0) {
            return;
        }
        std::uint64_t seed = std::chrono::steady_clock::now().time_since_epoch().count();
        seed ^= reinterpret_cast<std::uintptr_t>(&seed);
        seed ^= 0x9e3779b97f4a7c15ULL;
        std::mt19937_64 random(seed);
        for (std::size_t i = 0; i < BaseCount; ++i) {
            while (true) {
                const u64 candidate = 256 + random() % (Context::mod - 512);
                bool unique = true;
                for (std::size_t j = 0; j < BaseCount; ++j) {
                    unique &= candidate != Context::bases[j];
                }
                for (std::size_t j = 0; j < i; ++j) {
                    unique &= candidate != vertical_bases_[j];
                }
                if (unique) {
                    vertical_bases_[i] = candidate;
                    vertical_powers_[i] = {1};
                    break;
                }
            }
        }
    }

    static void reserve_powers(int height, int width) {
        assert(height >= 0 && width >= 0);
        initialize_vertical_bases();
        Context::reserve_powers(width);
        for (std::size_t i = 0; i < BaseCount; ++i) {
            while (static_cast<int>(vertical_powers_[i].size()) <= height) {
                vertical_powers_[i].push_back(Context::multiply(vertical_powers_[i].back(), vertical_bases_[i]));
            }
        }
    }

    Hash &prefix(int row, int column) { return prefix_[row * (width_ + 1) + column]; }
    const Hash &prefix(int row, int column) const { return prefix_[row * (width_ + 1) + column]; }

  public:
    BasicRollingHash2D() {
        initialize_vertical_bases();
        prefix_[0].height = 0;
        prefix_[0].width = 0;
    }

    template <class Grid> explicit BasicRollingHash2D(const Grid &grid) : height_(grid.size()) {
        width_ = height_ == 0 ? 0 : static_cast<int>(grid[0].size());
        for (const auto &row : grid) {
            assert(static_cast<int>(row.size()) == width_);
        }
        reserve_powers(height_, width_);
        prefix_.assign((height_ + 1) * (width_ + 1), Hash());
        for (int row = 0; row < height_; ++row) {
            for (int column = 0; column < width_; ++column) {
                const u64 encoded = Context::encode(grid[row][column]);
                for (std::size_t base = 0; base < BaseCount; ++base) {
                    u64 value = encoded;
                    value = Context::add(
                        value, Context::multiply(vertical_bases_[base], prefix(row, column + 1).value[base]));
                    value =
                        Context::add(value, Context::multiply(Context::bases[base], prefix(row + 1, column).value[base]));
                    value = Context::subtract(
                        value, Context::multiply(Context::multiply(vertical_bases_[base], Context::bases[base]),
                                                 prefix(row, column).value[base]));
                    prefix(row + 1, column + 1).value[base] = value;
                }
            }
        }
    }

    int height() const { return height_; }
    int width() const { return width_; }

    Hash get(int top, int bottom, int left, int right) const {
        assert(0 <= top && top <= bottom && bottom <= height_);
        assert(0 <= left && left <= right && right <= width_);
        const int rectangle_height = bottom - top;
        const int rectangle_width = right - left;
        Hash result;
        result.height = rectangle_height;
        result.width = rectangle_width;
        for (std::size_t base = 0; base < BaseCount; ++base) {
            u64 value = prefix(bottom, right).value[base];
            value = Context::subtract(
                value, Context::multiply(Context::powers[base][rectangle_width], prefix(bottom, left).value[base]));
            value = Context::subtract(
                value, Context::multiply(vertical_powers_[base][rectangle_height], prefix(top, right).value[base]));
            const u64 corner_scale =
                Context::multiply(vertical_powers_[base][rectangle_height], Context::powers[base][rectangle_width]);
            value = Context::add(value, Context::multiply(corner_scale, prefix(top, left).value[base]));
            result.value[base] = value;
        }
        return result;
    }

    Hash get() const { return get(0, height_, 0, width_); }
};

using RollingHash2D = BasicRollingHash2D<2>;

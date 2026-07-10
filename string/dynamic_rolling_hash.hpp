#pragma once
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <vector>
#include "rolling_hash.hpp"

template <std::size_t BaseCount = 2> class BasicDynamicRollingHash {
  public:
    using Hash = typename BasicRollingHash<BaseCount>::Hash;

  private:
    using Context = rolling_hash_internal::Context<BaseCount>;

    struct Node {
        Hash forward;
        Hash reverse;
        int length = 0;
    };

    int n_ = 0;
    int leaf_size_ = 1;
    std::vector<Node> tree_{2};

    static Node combine(const Node &left, const Node &right) {
        return {Context::concat(left.forward, right.forward, right.length),
                Context::concat(right.reverse, left.reverse, left.length), left.length + right.length};
    }

    template <class T> static Node leaf(const T &value) {
        const Hash hash = Context::single(value);
        return {hash, hash, 1};
    }

    Node range_node(int l, int r) const {
        assert(0 <= l && l <= r && r <= n_);
        Node left, right;
        for (l += leaf_size_, r += leaf_size_; l < r; l >>= 1, r >>= 1) {
            if (l & 1) {
                left = combine(left, tree_[l++]);
            }
            if (r & 1) {
                right = combine(tree_[--r], right);
            }
        }
        return combine(left, right);
    }

  public:
    BasicDynamicRollingHash() { Context::initialize(); }

    template <class Sequence> explicit BasicDynamicRollingHash(const Sequence &s) : n_(s.size()) {
        Context::reserve_powers(n_);
        while (leaf_size_ < n_) {
            leaf_size_ <<= 1;
        }
        tree_.assign(2 * leaf_size_, Node());
        for (int i = 0; i < n_; ++i) {
            tree_[leaf_size_ + i] = leaf(s[i]);
        }
        for (int i = leaf_size_ - 1; i > 0; --i) {
            tree_[i] = combine(tree_[2 * i], tree_[2 * i + 1]);
        }
    }

    int size() const { return n_; }

    template <class T> void set(int index, const T &value) {
        assert(0 <= index && index < n_);
        int node = leaf_size_ + index;
        tree_[node] = leaf(value);
        while (node >>= 1) {
            tree_[node] = combine(tree_[2 * node], tree_[2 * node + 1]);
        }
    }

    Hash get(int l, int r) const { return range_node(l, r).forward; }

    Hash get() const { return tree_[1].forward; }

    Hash get_reverse(int l, int r) const { return range_node(l, r).reverse; }

    bool is_palindrome(int l, int r) const {
        const Node node = range_node(l, r);
        return node.forward == node.reverse;
    }

    int lcp(const BasicDynamicRollingHash &other, int l1 = 0, int r1 = -1, int l2 = 0, int r2 = -1) const {
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

using DynamicRollingHash = BasicDynamicRollingHash<2>;

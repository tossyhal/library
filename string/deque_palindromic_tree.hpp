#pragma once
#include <algorithm>
#include <array>
#include <cassert>
#include <iterator>
#include <utility>
#include <vector>

namespace deque_palindromic_tree_internal {

template <class T> class AmortizedDeque {
  private:
    std::vector<T> left_;
    std::vector<T> right_;

    static void move_half(std::vector<T> &destination, std::vector<T> &source) {
        const int count = (static_cast<int>(source.size()) + 1) / 2;
        std::move(source.rend() - count, source.rend(), std::back_inserter(destination));
        source.erase(source.begin(), source.begin() + count);
    }

  public:
    int size() const { return static_cast<int>(left_.size() + right_.size()); }
    bool empty() const { return left_.empty() && right_.empty(); }

    T &operator[](int index) {
        assert(0 <= index && index < size());
        return index < static_cast<int>(left_.size()) ? left_[left_.size() - 1 - index]
                                                      : right_[index - left_.size()];
    }

    const T &operator[](int index) const {
        assert(0 <= index && index < size());
        return index < static_cast<int>(left_.size()) ? left_[left_.size() - 1 - index]
                                                      : right_[index - left_.size()];
    }

    T &front() { return left_.empty() ? right_.front() : left_.back(); }
    const T &front() const { return left_.empty() ? right_.front() : left_.back(); }
    T &back() { return right_.empty() ? left_.front() : right_.back(); }
    const T &back() const { return right_.empty() ? left_.front() : right_.back(); }

    void push_front(T value) { left_.push_back(std::move(value)); }
    void push_back(T value) { right_.push_back(std::move(value)); }

    void pop_front() {
        assert(!empty());
        if (left_.empty()) {
            move_half(left_, right_);
        }
        left_.pop_back();
    }

    void pop_back() {
        assert(!empty());
        if (right_.empty()) {
            move_half(right_, left_);
        }
        right_.pop_back();
    }
};

} // namespace deque_palindromic_tree_internal

template <int Sigma = 26, char Margin = 'a'> class DequePalindromicTree {
    static_assert(Sigma > 0);

  private:
    static constexpr int odd_root = 0;
    static constexpr int even_root = 1;

    struct Node {
        std::array<int, Sigma> next;
        int parent = odd_root;
        int link = odd_root;
        int quick = odd_root;
        int length = 0;
        int active_count = 0;
        int link_count = 0;

        Node() { next.fill(-1); }
    };

    struct DequeNode {
        int key = 0;
        int prefix_surface = even_root;
        int suffix_surface = even_root;
    };

    deque_palindromic_tree_internal::AmortizedDeque<DequeNode> deque_;
    std::vector<Node> nodes_{2};
    std::vector<int> free_nodes_;
    int palindrome_count_ = 0;

    int allocate_node() {
        if (free_nodes_.empty()) {
            nodes_.emplace_back();
            return static_cast<int>(nodes_.size()) - 1;
        }
        const int node = free_nodes_.back();
        free_nodes_.pop_back();
        nodes_[node] = Node();
        return node;
    }

    void release_node(int node) { free_nodes_.push_back(node); }

    int back_appendable(int key, int node) const {
        const int n = deque_.size();
        while (true) {
            if (nodes_[node].length == -1 ||
                (nodes_[node].length < n && deque_[n - nodes_[node].length - 1].key == key)) {
                return node;
            }
            const int link = nodes_[node].link;
            if (nodes_[link].length == -1 || deque_[n - nodes_[link].length - 1].key == key) {
                return link;
            }
            node = nodes_[node].quick;
        }
    }

    int front_appendable(int key, int node) const {
        const int n = deque_.size();
        while (true) {
            if (nodes_[node].length == -1 ||
                (nodes_[node].length < n && deque_[nodes_[node].length].key == key)) {
                return node;
            }
            const int link = nodes_[node].link;
            if (nodes_[link].length == -1 || deque_[nodes_[link].length].key == key) {
                return link;
            }
            node = nodes_[node].quick;
        }
    }

    static int encode(char c) {
        const int key = static_cast<unsigned char>(c) - static_cast<unsigned char>(Margin);
        assert(0 <= key && key < Sigma);
        return key;
    }

  public:
    DequePalindromicTree() {
        nodes_[odd_root].length = -1;
        nodes_[odd_root].parent = odd_root;
        nodes_[odd_root].link = odd_root;
        nodes_[odd_root].quick = odd_root;
        nodes_[even_root].length = 0;
        nodes_[even_root].parent = odd_root;
        nodes_[even_root].link = odd_root;
        nodes_[even_root].quick = odd_root;
    }

    int size() const { return deque_.size(); }
    bool empty() const { return deque_.empty(); }
    int num_palindromes() const { return palindrome_count_; }

    int longest_prefix_palindrome() const {
        return empty() ? 0 : nodes_[deque_.front().prefix_surface].length;
    }

    int longest_suffix_palindrome() const {
        return empty() ? 0 : nodes_[deque_.back().suffix_surface].length;
    }

    void push_back(char c) {
        const int key = encode(c);
        const int parent = empty() ? odd_root : back_appendable(key, deque_.back().suffix_surface);
        int n = size();
        int node = nodes_[parent].next[key];
        int link = even_root;
        if (node == -1) {
            node = allocate_node();
            nodes_[node].parent = parent;
            nodes_[node].length = nodes_[parent].length + 2;
            if (parent != odd_root) {
                const int link_parent = back_appendable(key, nodes_[parent].link);
                link = nodes_[link_parent].next[key];
                assert(link != -1);
            }
            nodes_[node].link = link;
            ++nodes_[link].link_count;
            deque_.push_back({key, even_root, even_root});
            ++n;
            if (nodes_[link].link != odd_root &&
                deque_[n - nodes_[link].length - 1].key == deque_[n - nodes_[nodes_[link].link].length - 1].key) {
                nodes_[node].quick = nodes_[link].quick;
            } else {
                nodes_[node].quick = nodes_[link].link;
            }
            nodes_[parent].next[key] = node;
            ++palindrome_count_;
        } else {
            deque_.push_back({key, even_root, even_root});
            ++n;
            link = nodes_[node].link;
        }
        deque_[n - 1].suffix_surface = node;
        deque_[n - nodes_[node].length].prefix_surface = node;
        if (nodes_[link].length >= 1 &&
            deque_[n - nodes_[node].length + nodes_[link].length - 1].suffix_surface == link) {
            deque_[n - nodes_[node].length + nodes_[link].length - 1].suffix_surface = even_root;
        }
        ++nodes_[node].active_count;
    }

    void push_front(char c) {
        const int key = encode(c);
        const int parent = empty() ? odd_root : front_appendable(key, deque_.front().prefix_surface);
        int node = nodes_[parent].next[key];
        int link = even_root;
        if (node == -1) {
            node = allocate_node();
            nodes_[node].parent = parent;
            nodes_[node].length = nodes_[parent].length + 2;
            if (parent != odd_root) {
                const int link_parent = front_appendable(key, nodes_[parent].link);
                link = nodes_[link_parent].next[key];
                assert(link != -1);
            }
            nodes_[node].link = link;
            ++nodes_[link].link_count;
            deque_.push_front({key, even_root, even_root});
            if (nodes_[link].link != odd_root &&
                deque_[nodes_[link].length].key == deque_[nodes_[nodes_[link].link].length].key) {
                nodes_[node].quick = nodes_[link].quick;
            } else {
                nodes_[node].quick = nodes_[link].link;
            }
            nodes_[parent].next[key] = node;
            ++palindrome_count_;
        } else {
            deque_.push_front({key, even_root, even_root});
            link = nodes_[node].link;
        }
        deque_[0].prefix_surface = node;
        deque_[nodes_[node].length - 1].suffix_surface = node;
        if (nodes_[link].length >= 1 && deque_[nodes_[node].length - nodes_[link].length].prefix_surface == link) {
            deque_[nodes_[node].length - nodes_[link].length].prefix_surface = even_root;
        }
        ++nodes_[node].active_count;
    }

    void pop_back() {
        assert(!empty());
        const int node = deque_.back().suffix_surface;
        const int key = deque_.back().key;
        const int link = nodes_[node].link;
        if (nodes_[node].length >= 2 &&
            nodes_[deque_[size() - nodes_[node].length + nodes_[link].length - 1].suffix_surface].length <
                nodes_[link].length) {
            deque_[size() - nodes_[node].length + nodes_[link].length - 1].suffix_surface = link;
            deque_[size() - nodes_[node].length].prefix_surface = link;
        } else {
            deque_[size() - nodes_[node].length].prefix_surface = even_root;
        }
        --nodes_[node].active_count;
        if (nodes_[node].link_count == 0 && nodes_[node].active_count == 0) {
            nodes_[nodes_[node].parent].next[key] = -1;
            --nodes_[link].link_count;
            release_node(node);
            --palindrome_count_;
        }
        deque_.pop_back();
    }

    void pop_front() {
        assert(!empty());
        const int node = deque_.front().prefix_surface;
        const int key = deque_.front().key;
        const int link = nodes_[node].link;
        if (nodes_[node].length >= 2 &&
            nodes_[deque_[nodes_[node].length - nodes_[link].length].prefix_surface].length < nodes_[link].length) {
            deque_[nodes_[node].length - nodes_[link].length].prefix_surface = link;
            deque_[nodes_[node].length - 1].suffix_surface = link;
        } else {
            deque_[nodes_[node].length - 1].suffix_surface = even_root;
        }
        --nodes_[node].active_count;
        if (nodes_[node].link_count == 0 && nodes_[node].active_count == 0) {
            nodes_[nodes_[node].parent].next[key] = -1;
            --nodes_[link].link_count;
            release_node(node);
            --palindrome_count_;
        }
        deque_.pop_front();
    }
};

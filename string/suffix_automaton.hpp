#pragma once
#include <algorithm>
#include <bit>
#include <cassert>
#include <cstdint>
#include <utility>
#include <vector>

template <int Sigma = 26, char Margin = 'a'> class SuffixAutomaton {
    static_assert(1 <= Sigma && Sigma <= 64);

  public:
    struct Node {
        std::vector<std::pair<unsigned char, int>> next;
        std::uint64_t transition_mask = 0;
        int link = -1;
        int length = 0;
        int first_pos = -1;
        std::int64_t occurrences = 0;
        bool clone = false;

        int find(unsigned char key) const {
            if (((transition_mask >> key) & 1ULL) == 0) {
                return -1;
            }
            const std::uint64_t lower_mask = key == 0 ? 0 : transition_mask & ((1ULL << key) - 1);
            return next[std::popcount(lower_mask)].second;
        }

        void set(unsigned char key, int destination) {
            const std::uint64_t lower_mask = key == 0 ? 0 : transition_mask & ((1ULL << key) - 1);
            const int index = std::popcount(lower_mask);
            if (((transition_mask >> key) & 1ULL) != 0) {
                next[index].second = destination;
                return;
            }
            transition_mask |= 1ULL << key;
            next.insert(next.begin() + index, {key, destination});
        }
    };

    std::vector<Node> nodes{1};
    int last = 0;

    SuffixAutomaton() = default;

    template <class Sequence> explicit SuffixAutomaton(const Sequence &s) {
        nodes.reserve(2 * s.size());
        for (char c : s) {
            extend(c);
        }
    }

    int next(int state, char c) const {
        const int key = static_cast<unsigned char>(c) - static_cast<unsigned char>(Margin);
        if (key < 0 || key >= Sigma) {
            return -1;
        }
        return nodes[state].find(static_cast<unsigned char>(key));
    }

    void extend(char c) {
        const int key = static_cast<unsigned char>(c) - static_cast<unsigned char>(Margin);
        assert(0 <= key && key < Sigma);

        const int current = static_cast<int>(nodes.size());
        nodes.emplace_back();
        nodes[current].length = nodes[last].length + 1;
        nodes[current].first_pos = nodes[current].length - 1;
        nodes[current].occurrences = 1;

        int p = last;
        while (p != -1 && nodes[p].find(key) == -1) {
            nodes[p].set(key, current);
            p = nodes[p].link;
        }

        if (p == -1) {
            nodes[current].link = 0;
        } else {
            const int q = nodes[p].find(key);
            if (nodes[p].length + 1 == nodes[q].length) {
                nodes[current].link = q;
            } else {
                const int clone = static_cast<int>(nodes.size());
                nodes.push_back(nodes[q]);
                nodes[clone].length = nodes[p].length + 1;
                nodes[clone].occurrences = 0;
                nodes[clone].clone = true;

                while (p != -1 && nodes[p].find(key) == q) {
                    nodes[p].set(key, clone);
                    p = nodes[p].link;
                }
                nodes[q].link = clone;
                nodes[current].link = clone;
            }
        }
        last = current;
    }

    template <class Sequence> int find(const Sequence &pattern) const {
        int state = 0;
        for (char c : pattern) {
            state = next(state, c);
            if (state == -1) {
                return -1;
            }
        }
        return state;
    }

    template <class Sequence> bool contains(const Sequence &pattern) const {
        return find(pattern) != -1;
    }

    std::vector<int> topological_order() const {
        int maximum_length = 0;
        for (const Node &node : nodes) {
            maximum_length = std::max(maximum_length, node.length);
        }
        std::vector<int> count(maximum_length + 1), order(nodes.size());
        for (const Node &node : nodes) {
            ++count[node.length];
        }
        for (int i = 1; i <= maximum_length; ++i) {
            count[i] += count[i - 1];
        }
        for (int i = static_cast<int>(nodes.size()) - 1; i >= 0; --i) {
            order[--count[nodes[i].length]] = i;
        }
        return order;
    }

    std::int64_t num_substrings() const {
        std::int64_t result = 0;
        for (int state = 1; state < static_cast<int>(nodes.size()); ++state) {
            result += nodes[state].length - nodes[nodes[state].link].length;
        }
        return result;
    }

    void build_occurrences() {
        const std::vector<int> order = topological_order();
        for (int i = static_cast<int>(order.size()) - 1; i > 0; --i) {
            const int state = order[i];
            nodes[nodes[state].link].occurrences += nodes[state].occurrences;
        }
    }
};

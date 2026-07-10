#pragma once
#include <array>
#include <cassert>
#include <cstdint>
#include <queue>
#include <vector>
#include "trie.hpp"

template <int Sigma = 26, char Margin = 'a'> class AhoCorasick {
  public:
    struct Node {
        std::array<int, Sigma> next;
        int parent = -1;
        char parent_char = 0;
        int link = 0;
        int exit_count = 0;
        std::vector<int> pattern_ids;
        Node(int p = -1, char c = 0) : parent(p), parent_char(c) { next.fill(-1); }
    };

    std::vector<Node> nodes{Node()};
    std::vector<int> pattern_node;
    std::vector<int> bfs_order;
    bool built = false;

    template <class Sequence> int insert(const Sequence &s) {
        assert(!built);
        int v = 0;
        for (char c : s) {
            const int x = static_cast<unsigned char>(c) - static_cast<unsigned char>(Margin);
            assert(0 <= x && x < Sigma);
            if (nodes[v].next[x] == -1) {
                nodes[v].next[x] = static_cast<int>(nodes.size());
                nodes.emplace_back(v, c);
            }
            v = nodes[v].next[x];
        }
        const int id = static_cast<int>(pattern_node.size());
        pattern_node.push_back(v);
        nodes[v].pattern_ids.push_back(id);
        return id;
    }

    void build() {
        assert(!built);
        built = true;
        std::queue<int> queue;
        bfs_order.clear();
        bfs_order.push_back(0);
        nodes[0].exit_count = static_cast<int>(nodes[0].pattern_ids.size());
        for (int c = 0; c < Sigma; ++c) {
            int &next = nodes[0].next[c];
            if (next == -1) {
                next = 0;
            } else {
                queue.push(next);
            }
        }
        while (!queue.empty()) {
            const int v = queue.front();
            queue.pop();
            bfs_order.push_back(v);
            nodes[v].exit_count = static_cast<int>(nodes[v].pattern_ids.size()) + nodes[nodes[v].link].exit_count;
            for (int c = 0; c < Sigma; ++c) {
                int &next = nodes[v].next[c];
                if (next == -1) {
                    next = nodes[nodes[v].link].next[c];
                } else {
                    nodes[next].link = nodes[nodes[v].link].next[c];
                    queue.push(next);
                }
            }
        }
    }

    int next_state(int state, char c) const {
        assert(built);
        const int x = static_cast<unsigned char>(c) - static_cast<unsigned char>(Margin);
        return x < 0 || x >= Sigma ? 0 : nodes[state].next[x];
    }

    template <class Sequence> std::vector<int> count_matches(const Sequence &text) const {
        assert(built);
        std::vector<int> visits(nodes.size());
        int state = 0;
        for (char c : text) {
            state = next_state(state, c);
            ++visits[state];
        }
        for (int i = static_cast<int>(bfs_order.size()) - 1; i > 0; --i) {
            const int v = bfs_order[i];
            visits[nodes[v].link] += visits[v];
        }
        std::vector<int> result(pattern_node.size());
        for (int id = 0; id < static_cast<int>(pattern_node.size()); ++id) {
            result[id] = visits[pattern_node[id]] + (pattern_node[id] == 0);
        }
        return result;
    }

    template <class Sequence> std::int64_t count_all_matches(const Sequence &text) const {
        assert(built);
        std::int64_t result = nodes[0].exit_count;
        int state = 0;
        for (char c : text) {
            state = next_state(state, c);
            result += nodes[state].exit_count;
        }
        return result;
    }
};

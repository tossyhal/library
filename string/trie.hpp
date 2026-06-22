#pragma once
#include <array>
#include <cassert>
#include <vector>

template <int Sigma = 26, char Margin = 'a'> class Trie {
  public:
    struct Node {
        std::array<int, Sigma> next;
        int parent = -1;
        int count = 0;
        int terminal = 0;
        char parent_char = 0;
        Node(int p = -1, char c = 0) : parent(p), parent_char(c) { next.fill(-1); }
    };

    std::vector<Node> nodes{Node()};

    template <class Sequence> int insert(const Sequence &s) {
        int v = 0;
        ++nodes[v].count;
        for (char c : s) {
            const int x = static_cast<unsigned char>(c) - static_cast<unsigned char>(Margin);
            assert(0 <= x && x < Sigma);
            if (nodes[v].next[x] == -1) {
                nodes[v].next[x] = static_cast<int>(nodes.size());
                nodes.emplace_back(v, c);
            }
            v = nodes[v].next[x];
            ++nodes[v].count;
        }
        ++nodes[v].terminal;
        return v;
    }

    template <class Sequence> int find(const Sequence &s) const {
        int v = 0;
        for (char c : s) {
            const int x = static_cast<unsigned char>(c) - static_cast<unsigned char>(Margin);
            if (x < 0 || x >= Sigma || nodes[v].next[x] == -1) {
                return -1;
            }
            v = nodes[v].next[x];
        }
        return v;
    }

    template <class Sequence> bool contains(const Sequence &s) const {
        const int v = find(s);
        return v != -1 && nodes[v].terminal > 0;
    }

    template <class Sequence> int count_prefix(const Sequence &prefix) const {
        const int v = find(prefix);
        return v == -1 ? 0 : nodes[v].count;
    }
};

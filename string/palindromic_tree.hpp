#pragma once
#include <array>
#include <cassert>
#include <string>
#include <vector>

template <int Sigma = 26, char Margin = 'a'> class PalindromicTree {
  public:
    struct Node {
        std::array<int, Sigma> next;
        int link = 0;
        int parent = -1;
        int length = 0;
        int occurrences = 0;
        int first_end = -1;
        Node(int len = 0) : length(len) { next.fill(-1); }
    };

    std::vector<Node> nodes;
    std::string text;
    std::vector<int> suffix_history;
    int suffix = 1;

    PalindromicTree() : nodes{Node(-1), Node(0)} {
        nodes[0].link = 0;
        nodes[1].link = 0;
    }

    explicit PalindromicTree(const std::string &s) : PalindromicTree() {
        nodes.reserve(s.size() + 2);
        for (char c : s) {
            add(c);
        }
    }

    int add(char c) {
        const int x = static_cast<unsigned char>(c) - static_cast<unsigned char>(Margin);
        assert(0 <= x && x < Sigma);
        text.push_back(c);
        const int pos = static_cast<int>(text.size()) - 1;
        int current = suffix;
        while (pos - 1 - nodes[current].length < 0 || text[pos - 1 - nodes[current].length] != c) {
            current = nodes[current].link;
        }
        if (nodes[current].next[x] != -1) {
            suffix = nodes[current].next[x];
            ++nodes[suffix].occurrences;
            suffix_history.push_back(suffix);
            return suffix;
        }
        const int created = static_cast<int>(nodes.size());
        nodes.emplace_back(nodes[current].length + 2);
        nodes[created].parent = current;
        nodes[created].occurrences = 1;
        nodes[created].first_end = pos;
        nodes[current].next[x] = created;
        if (nodes[created].length == 1) {
            nodes[created].link = 1;
        } else {
            int link = nodes[current].link;
            while (pos - 1 - nodes[link].length < 0 || text[pos - 1 - nodes[link].length] != c) {
                link = nodes[link].link;
            }
            nodes[created].link = nodes[link].next[x];
        }
        suffix = created;
        suffix_history.push_back(suffix);
        return created;
    }

    int num_palindromes() const { return static_cast<int>(nodes.size()) - 2; }

    void build_occurrences() {
        for (int v = static_cast<int>(nodes.size()) - 1; v >= 2; --v) {
            nodes[nodes[v].link].occurrences += nodes[v].occurrences;
        }
    }
};

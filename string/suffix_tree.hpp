#pragma once
#include <cassert>
#include <vector>
#include "suffix_array.hpp"

// Compact suffix tree built in O(n log n) (the suffix-array construction dominates).
// An edge parent -> v represents s[nodes[v].suffix_start + parent.depth,
//                                  nodes[v].suffix_start + nodes[v].depth).
template <class Sequence> class SuffixTree {
  public:
    struct Node {
        int parent = -1;
        int depth = 0;
        int suffix_start = -1;
        std::vector<int> children;
        bool terminal = false;
        bool is_leaf() const { return children.empty(); }
    };

    std::vector<Node> nodes;
    std::vector<int> sa;
    std::vector<int> lcp;

    explicit SuffixTree(const Sequence &s) : nodes(1), sa(suffix_array(s)), lcp(lcp_array(s, sa)) {
        const int n = static_cast<int>(s.size());
        int current = 0;
        for (int i = 0; i < n; ++i) {
            const int common = i == 0 ? 0 : lcp[i - 1];
            while (nodes[current].depth > common) {
                current = nodes[current].parent;
            }
            if (nodes[current].depth < common) {
                const int previous_child = nodes[current].children.back();
                nodes[current].children.pop_back();
                const int middle = static_cast<int>(nodes.size());
                nodes.push_back({current, common, sa[i - 1], {previous_child}, false});
                nodes[previous_child].parent = middle;
                nodes[current].children.push_back(middle);
                current = middle;
            }
            const int leaf = static_cast<int>(nodes.size());
            nodes.push_back({current, n - sa[i], sa[i], {}, true});
            nodes[current].children.push_back(leaf);
            current = leaf;
        }
    }
};

template <class Sequence> SuffixTree(const Sequence &) -> SuffixTree<Sequence>;

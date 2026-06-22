#define PROBLEM "https://judge.yosupo.jp/problem/number_of_substrings"

#include <iostream>
#include <string>
#include "../suffix_tree.hpp"

using namespace std;

int main() {
    string s;
    cin >> s;
    const SuffixTree tree(s);
    long long answer = 0;
    for (int node = 1; node < static_cast<int>(tree.nodes.size()); ++node) {
        answer += tree.nodes[node].depth - tree.nodes[tree.nodes[node].parent].depth;
    }
    cout << answer << '\n';
}

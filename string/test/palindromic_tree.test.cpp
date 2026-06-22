#define PROBLEM "https://judge.yosupo.jp/problem/eertree"

#include <iostream>
#include <string>
#include "../palindromic_tree.hpp"

using namespace std;

int main() {
    string s;
    cin >> s;
    PalindromicTree tree(s);
    cout << tree.num_palindromes() << '\n';
    for (int node = 2; node < static_cast<int>(tree.nodes.size()); ++node) {
        const int parent = tree.nodes[node].parent - 1;
        const int suffix_link = tree.nodes[node].link <= 1 ? 0 : tree.nodes[node].link - 1;
        cout << parent << ' ' << suffix_link << '\n';
    }
    for (int i = 0; i < static_cast<int>(tree.suffix_history.size()); ++i) {
        if (i > 0) {
            cout << ' ';
        }
        cout << tree.suffix_history[i] - 1;
    }
    cout << '\n';
}

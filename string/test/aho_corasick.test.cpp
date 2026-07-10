#define PROBLEM "https://judge.yosupo.jp/problem/aho_corasick"

#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include "../aho_corasick.hpp"

using namespace std;

int main() {
    {
        AhoCorasick check;
        check.insert(string());
        check.insert(string("a"));
        check.insert(string("aa"));
        check.insert(string("a"));
        check.build();
        const vector<int> expected = {4, 3, 2, 3};
        assert(check.count_matches(string("aaa")) == expected);
        assert(check.count_all_matches(string("aaa")) == 12);
    }

    int n;
    cin >> n;
    AhoCorasick aho;
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        aho.insert(s);
    }
    aho.build();

    cout << aho.nodes.size() << '\n';
    for (int v = 1; v < static_cast<int>(aho.nodes.size()); ++v) {
        cout << aho.nodes[v].parent << ' ' << aho.nodes[v].link << '\n';
    }
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            cout << ' ';
        }
        cout << aho.pattern_node[i];
    }
    cout << '\n';
}

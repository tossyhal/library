#define PROBLEM "https://atcoder.jp/contests/abc287/tasks/abc287_e"

#include <iostream>
#include <string>
#include <vector>
#include "../trie.hpp"

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<string> strings(n);
    Trie trie;
    for (string &s : strings) {
        cin >> s;
        trie.insert(s);
    }
    for (const string &s : strings) {
        int node = 0;
        int answer = 0;
        for (int i = 0; i < static_cast<int>(s.size()); ++i) {
            node = trie.nodes[node].next[s[i] - 'a'];
            if (trie.nodes[node].count >= 2) {
                answer = i + 1;
            }
        }
        cout << answer << '\n';
    }
}

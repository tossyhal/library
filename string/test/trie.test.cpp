#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <cassert>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include "../trie.hpp"

using namespace std;

int main() {
    Trie<3, 'a'> trie;
    vector<string> inserted;
    mt19937 random(0);

    for (int iteration = 0; iteration < 2000; ++iteration) {
        string s(random() % 8, 'a');
        for (char &c : s) {
            c = static_cast<char>('a' + random() % 3);
        }
        trie.insert(s);
        inserted.push_back(s);

        for (int query = 0; query < 20; ++query) {
            string pattern(random() % 8, 'a');
            for (char &c : pattern) {
                c = static_cast<char>('a' + random() % 3);
            }

            int exact = 0;
            int prefix = 0;
            bool path = false;
            for (const string &t : inserted) {
                exact += t == pattern;
                prefix += t.starts_with(pattern);
                path |= t.starts_with(pattern);
            }
            assert(trie.contains(pattern) == (exact > 0));
            assert(trie.count_prefix(pattern) == prefix);
            assert((trie.find(pattern) != -1) == path);
        }
    }

    assert(!trie.contains("d"));
    assert(trie.find("d") == -1);
    assert(trie.count_prefix("d") == 0);

    int a, b;
    cin >> a >> b;
    cout << a + b << '\n';
}

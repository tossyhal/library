#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_14_D"

#include <iostream>
#include <string>
#include <vector>
#include "../aho_corasick.hpp"

using namespace std;

int main() {
    string text;
    int q;
    cin >> text >> q;
    AhoCorasick<128, '\0'> aho;
    while (q--) {
        string pattern;
        cin >> pattern;
        aho.insert(pattern);
    }
    aho.build();
    for (int count : aho.count_matches(text)) {
        cout << (count > 0) << '\n';
    }
}

#define PROBLEM "https://judge.yosupo.jp/problem/wildcard_pattern_matching"

#include <iostream>
#include <string>
#include <vector>
#include "../wildcard_pattern_matching.hpp"

using namespace std;

int main() {
    string text, pattern;
    cin >> text >> pattern;
    const vector<int> positions = wildcard_pattern_matching(text, pattern, '*');
    vector<bool> matches(text.size() - pattern.size() + 1);
    for (int position : positions) {
        matches[position] = true;
    }
    for (bool match : matches) {
        cout << match;
    }
    cout << '\n';
}

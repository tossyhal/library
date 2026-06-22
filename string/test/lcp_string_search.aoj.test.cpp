#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_14_D"

#include <iostream>
#include <string>
#include "../lcp.hpp"

using namespace std;

int main() {
    string text;
    int q;
    cin >> text >> q;
    const LCP lcp(text);
    while (q--) {
        string pattern;
        cin >> pattern;
        const auto [left, right] = lcp.equal_range(pattern);
        cout << (left < right) << '\n';
    }
}

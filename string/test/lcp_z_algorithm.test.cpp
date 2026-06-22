#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"

#include <iostream>
#include <string>
#include "../lcp.hpp"

using namespace std;

int main() {
    string s;
    cin >> s;
    const LCP lcp(s);
    for (int i = 0; i < static_cast<int>(s.size()); ++i) {
        if (i > 0) {
            cout << ' ';
        }
        cout << lcp.suffix_lcp(0, i);
    }
    cout << '\n';
}

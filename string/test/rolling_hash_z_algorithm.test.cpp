#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"

#include <iostream>
#include <string>
#include "../rolling_hash.hpp"

using namespace std;

int main() {
    string s;
    cin >> s;
    const RollingHash hash(s);
    for (int i = 0; i < static_cast<int>(s.size()); ++i) {
        if (i > 0) {
            cout << ' ';
        }
        cout << hash.lcp(hash, 0, s.size(), i, s.size());
    }
    cout << '\n';
}

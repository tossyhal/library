#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_10_C"

#include <iostream>
#include <string>
#include "../longest_common_subsequence.hpp"

using namespace std;

int main() {
    int q;
    cin >> q;
    while (q--) {
        string s, t;
        cin >> s >> t;
        cout << longest_common_subsequence_length(s, t) << '\n';
    }
}

#define PROBLEM "https://judge.yosupo.jp/problem/suffixarray"

#include <iostream>
#include <string>
#include "../suffix_array.hpp"

using namespace std;

int main() {
    string s;
    cin >> s;
    const auto sa = suffix_array(s);
    for (int i = 0; i < static_cast<int>(sa.size()); ++i) {
        if (i) {
            cout << ' ';
        }
        cout << sa[i];
    }
    cout << '\n';
}

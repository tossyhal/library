#define PROBLEM "https://judge.yosupo.jp/problem/lyndon_factorization"

#include <iostream>
#include <string>
#include "../lyndon_word.hpp"

using namespace std;

int main() {
    string s;
    cin >> s;
    const auto factors = lyndon_factorization(s);
    cout << 0;
    for (const auto &[l, r] : factors) {
        (void)l;
        cout << ' ' << r;
    }
    cout << '\n';
}

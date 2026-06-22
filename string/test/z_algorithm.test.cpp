#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"

#include <iostream>
#include <string>
#include "../z_algorithm.hpp"

using namespace std;

int main() {
    string s;
    cin >> s;
    const auto z = z_algorithm(s);
    for (int i = 0; i < static_cast<int>(z.size()); ++i) {
        if (i) {
            cout << ' ';
        }
        cout << z[i];
    }
    cout << '\n';
}

#define PROBLEM "https://judge.yosupo.jp/problem/runenumerate"

#include <iostream>
#include <string>
#include "../run_enumerate.hpp"

using namespace std;

int main() {
    string s;
    cin >> s;
    const auto runs = run_enumerate(s);
    cout << runs.size() << '\n';
    for (const auto &[period, l, r] : runs) {
        cout << period << ' ' << l << ' ' << r << '\n';
    }
}

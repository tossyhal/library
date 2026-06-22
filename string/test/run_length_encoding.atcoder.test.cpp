#define PROBLEM "https://atcoder.jp/contests/past17-open/tasks/past17_e"

#include <iostream>
#include <string>
#include "../run_length_encoding.hpp"

using namespace std;

int main() {
    string s;
    cin >> s;
    for (const auto &[character, count] : run_length_encoding(s)) {
        cout << character << ' ' << count << ' ';
    }
    cout << '\n';
}

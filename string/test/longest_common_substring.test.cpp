#define PROBLEM "https://judge.yosupo.jp/problem/longest_common_substring"

#include <iostream>
#include <string>
#include "../longest_common_substring.hpp"

using namespace std;

int main() {
    string s, t;
    cin >> s >> t;
    const auto result = longest_common_substring(s, t);
    cout << result.first_pos << ' ' << result.first_pos + result.length << ' ' << result.second_pos << ' '
              << result.second_pos + result.length << '\n';
}

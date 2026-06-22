#define PROBLEM "https://judge.yosupo.jp/problem/number_of_substrings"

#include <iostream>
#include <string>
#include "../num_of_substrings.hpp"

using namespace std;

int main() {
    string s;
    cin >> s;
    cout << num_of_substrings(s) << '\n';
}

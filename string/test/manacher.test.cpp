#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_palindromes"

#include <iostream>
#include <string>
#include "../manacher.hpp"

using namespace std;

int main() {
    string s;
    cin >> s;
    const auto answer = enumerate_palindromes(s);
    for (int i = 0; i < static_cast<int>(answer.size()); ++i) {
        if (i > 0) {
            cout << ' ';
        }
        cout << answer[i];
    }
    cout << '\n';
}

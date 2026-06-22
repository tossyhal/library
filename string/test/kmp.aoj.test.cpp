#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_14_B"

#include <iostream>
#include <string>
#include "../kmp.hpp"

using namespace std;

int main() {
    string text, pattern;
    cin >> text >> pattern;
    for (int position : kmp(text, pattern)) {
        cout << position << '\n';
    }
}

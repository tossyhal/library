#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_14_B"

#include <iostream>
#include <string>
#include "../morris_pratt.hpp"

using namespace std;

int main() {
    string text, pattern;
    cin >> text >> pattern;
    for (int position : morris_pratt(text, pattern)) {
        cout << position << '\n';
    }
}

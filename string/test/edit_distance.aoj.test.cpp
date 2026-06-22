#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/DPL_1_E"

#include <iostream>
#include <string>
#include "../edit_distance.hpp"

using namespace std;

int main() {
    string s, t;
    cin >> s >> t;
    cout << edit_distance(s, t) << '\n';
}

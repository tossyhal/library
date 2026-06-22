#define PROBLEM "https://judge.yosupo.jp/problem/number_of_subsequences"

#include <iostream>
#include <vector>
#include "../num_subsequences.hpp"

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> values(n);
    for (int &value : values) {
        cin >> value;
    }
    cout << num_subsequences(values, 998244353) << '\n';
}

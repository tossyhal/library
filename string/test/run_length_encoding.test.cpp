#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <cassert>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include "../run_length_encoding.hpp"

using namespace std;

template <class Sequence> void verify(const Sequence &sequence) {
    const auto encoded = run_length_encoding(sequence);
    Sequence restored;
    for (const auto &[value, count] : encoded) {
        assert(count > 0);
        if (!restored.empty()) {
            assert(restored.back() != value);
        }
        restored.insert(restored.end(), count, value);
    }
    assert(restored == sequence);
}

int main() {
    assert(run_length_encoding(string()).empty());
    assert((run_length_encoding(string("aaabbc")) ==
            vector<pair<char, int>>{{'a', 3}, {'b', 2}, {'c', 1}}));
    assert((run_length_encoding(vector<int>{1, 1, 2, 1, 1}) ==
            vector<pair<int, int>>{{1, 2}, {2, 1}, {1, 2}}));

    for (int mask = 0; mask < (1 << 12); ++mask) {
        string sequence(12, 'a');
        for (int i = 0; i < 12; ++i) {
            sequence[i] += mask >> i & 1;
        }
        verify(sequence);
    }

    int a, b;
    cin >> a >> b;
    cout << a + b << '\n';
}

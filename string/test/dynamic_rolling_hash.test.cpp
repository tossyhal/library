#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <string>
#include "../dynamic_rolling_hash.hpp"

using namespace std;

int naive_lcp(const string &a, int l1, int r1, const string &b, int l2, int r2) {
    int length = 0;
    while (l1 + length < r1 && l2 + length < r2 && a[l1 + length] == b[l2 + length]) {
        ++length;
    }
    return length;
}

void verify(const string &s, const DynamicRollingHash &hash) {
    const RollingHash static_hash(s);
    assert(hash.size() == static_cast<int>(s.size()));
    assert(hash.get() == static_hash.get());
    for (int l = 0; l <= static_cast<int>(s.size()); ++l) {
        for (int r = l; r <= static_cast<int>(s.size()); ++r) {
            assert(hash.get(l, r) == static_hash.get(l, r));
            string reversed = s.substr(l, r - l);
            reverse(reversed.begin(), reversed.end());
            assert(hash.get_reverse(l, r) == RollingHash(reversed).get());
            assert(hash.is_palindrome(l, r) == equal(s.begin() + l, s.begin() + (l + r) / 2, s.rbegin() + s.size() - r));
        }
    }
}

int main() {
    const string empty_string;
    DynamicRollingHash empty(empty_string);
    assert(empty.size() == 0);
    assert(empty.get(0, 0) == RollingHash(empty_string).get());
    assert(empty.is_palindrome(0, 0));

    mt19937 random(0);
    for (int iteration = 0; iteration < 100; ++iteration) {
        const int n = 1 + random() % 30;
        string a(n, 'a'), b(n, 'a');
        for (char &c : a) {
            c += random() % 4;
        }
        for (char &c : b) {
            c += random() % 4;
        }
        DynamicRollingHash hash_a(a), hash_b(b);
        for (int query = 0; query < 100; ++query) {
            if (random() & 1) {
                const int index = random() % n;
                const char value = static_cast<char>('a' + random() % 4);
                if (random() & 1) {
                    a[index] = value;
                    hash_a.set(index, value);
                } else {
                    b[index] = value;
                    hash_b.set(index, value);
                }
            }
            int l1 = random() % (n + 1), r1 = random() % (n + 1);
            int l2 = random() % (n + 1), r2 = random() % (n + 1);
            if (l1 > r1) {
                swap(l1, r1);
            }
            if (l2 > r2) {
                swap(l2, r2);
            }
            assert(hash_a.lcp(hash_b, l1, r1, l2, r2) == naive_lcp(a, l1, r1, b, l2, r2));
        }
        verify(a, hash_a);
        verify(b, hash_b);
    }

    int a, b;
    cin >> a >> b;
    cout << a + b << '\n';
}

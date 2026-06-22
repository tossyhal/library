#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include "../smallest_concatenation.hpp"

using namespace std;

string brute_force(vector<string> strings) {
    sort(strings.begin(), strings.end());
    string result;
    bool first = true;
    do {
        string concatenated;
        for (const string &s : strings) {
            concatenated += s;
        }
        if (first || concatenated < result) {
            first = false;
            result = concatenated;
        }
    } while (next_permutation(strings.begin(), strings.end()));
    return result;
}

int main() {
    assert(smallest_concatenation({}) == "");
    assert(smallest_concatenation({"a"}) == "a");
    assert(smallest_concatenation({"abc", "abc"}) == "abcabc");
    assert(smallest_concatenation({"b", "ba"}) == "bab");
    assert(smallest_concatenation({"c", "cb", "cba"}) == "cbacbc");
    assert(smallest_concatenation({"x", "xx", "xxx"}) == "xxxxxx");
    assert(smallest_concatenation({"abba", "abacaba", "bcd", "er", "cb"}) == "abacabaabbabcdcber");

    mt19937 random(0);
    for (int iteration = 0; iteration < 2000; ++iteration) {
        vector<string> strings(random() % 8);
        for (string &s : strings) {
            s.resize(random() % 5);
            for (char &c : s) {
                c = static_cast<char>('a' + random() % 3);
            }
        }
        assert(smallest_concatenation(strings) == brute_force(strings));
    }

    int a, b;
    cin >> a >> b;
    cout << a + b << '\n';
}

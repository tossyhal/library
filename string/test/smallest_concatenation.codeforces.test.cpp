#define PROBLEM "https://codeforces.com/contest/632/problem/C"

#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include "../smallest_concatenation.hpp"

using namespace std;

// Codeforces only exposes the statement samples to the downloader, so guard the
// core logic with deterministic assertions as well.
void unit_tests() {
    assert(smallest_concatenation({"a"}) == "a");
    assert(smallest_concatenation({"abc", "abc"}) == "abcabc");
    assert(smallest_concatenation({"b", "ba"}) == "bab");
    assert(smallest_concatenation({"c", "cb", "cba"}) == "cbacbc");
    assert(smallest_concatenation({"x", "xx", "xxx"}) == "xxxxxx");
    assert(smallest_concatenation({"abba", "abacaba", "bcd", "er", "cb"}) == "abacabaabbabcdcber");
}

int main() {
    unit_tests();

    int n;
    cin >> n;
    vector<string> strings(n);
    for (string &s : strings) {
        cin >> s;
    }
    cout << smallest_concatenation(strings) << '\n';
}

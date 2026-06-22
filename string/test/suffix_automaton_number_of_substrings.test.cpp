#define PROBLEM "https://judge.yosupo.jp/problem/number_of_substrings"

#include <iostream>
#include <string>
#include "../suffix_automaton.hpp"

using namespace std;

int main() {
    string s;
    cin >> s;
    const SuffixAutomaton automaton(s);
    cout << automaton.num_substrings() << '\n';
}

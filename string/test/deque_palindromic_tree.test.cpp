#define PROBLEM "https://judge.yosupo.jp/problem/palindromes_in_deque"

#include <iostream>
#include "../deque_palindromic_tree.hpp"

using namespace std;

int main() {
    int q;
    cin >> q;
    DequePalindromicTree tree;
    while (q--) {
        int type;
        cin >> type;
        if (type == 0) {
            char c;
            cin >> c;
            tree.push_front(c);
        } else if (type == 1) {
            char c;
            cin >> c;
            tree.push_back(c);
        } else if (type == 2) {
            tree.pop_front();
        } else {
            tree.pop_back();
        }
        cout << tree.num_palindromes() << ' ' << tree.longest_prefix_palindrome() << ' '
             << tree.longest_suffix_palindrome() << '\n';
    }
}

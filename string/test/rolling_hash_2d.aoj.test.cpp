#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_14_C"

#include <cassert>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include "../rolling_hash_2d.hpp"

using namespace std;

void randomized_test() {
    mt19937 random(0);
    for (int iteration = 0; iteration < 100; ++iteration) {
        const int height = 1 + random() % 6;
        const int width = 1 + random() % 6;
        vector<string> grid(height, string(width, 'a'));
        for (string &row : grid) {
            for (char &c : row) {
                c += random() % 4;
            }
        }
        const RollingHash2D hash(grid);
        for (int top = 0; top <= height; ++top) {
            for (int bottom = top; bottom <= height; ++bottom) {
                for (int left = 0; left <= width; ++left) {
                    for (int right = left; right <= width; ++right) {
                        vector<string> rectangle(bottom - top);
                        for (int row = top; row < bottom; ++row) {
                            rectangle[row - top] = grid[row].substr(left, right - left);
                        }
                        if (rectangle.empty()) {
                            assert(hash.get(top, bottom, left, right).height == 0);
                        } else {
                            assert(hash.get(top, bottom, left, right) == RollingHash2D(rectangle).get());
                        }
                    }
                }
            }
        }
        if (height >= 2 && width >= 2) {
            assert(hash.get(0, 1, 0, 2) != hash.get(0, 2, 0, 1));
        }
    }
}

int main() {
    randomized_test();

    int height, width;
    cin >> height >> width;
    vector<string> grid(height);
    for (string &row : grid) {
        cin >> row;
    }
    int pattern_height, pattern_width;
    cin >> pattern_height >> pattern_width;
    vector<string> pattern(pattern_height);
    for (string &row : pattern) {
        cin >> row;
    }

    const RollingHash2D grid_hash(grid);
    const auto target = RollingHash2D(pattern).get();
    for (int row = 0; row + pattern_height <= height; ++row) {
        for (int column = 0; column + pattern_width <= width; ++column) {
            if (grid_hash.get(row, row + pattern_height, column, column + pattern_width) == target) {
                cout << row << ' ' << column << '\n';
            }
        }
    }
}

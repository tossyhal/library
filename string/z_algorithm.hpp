#pragma once
#include <vector>

template <class Sequence> std::vector<int> z_algorithm(const Sequence &s) {
    const int n = static_cast<int>(s.size());
    std::vector<int> z(n);
    if (n == 0) {
        return z;
    }
    z[0] = n;
    for (int i = 1, j = 0; i < n;) {
        while (i + j < n && s[j] == s[i + j]) {
            ++j;
        }
        z[i] = j;
        if (j == 0) {
            ++i;
            continue;
        }
        int k = 1;
        while (k < j && k + z[k] < j) {
            z[i + k] = z[k];
            ++k;
        }
        i += k;
        j -= k;
    }
    return z;
}

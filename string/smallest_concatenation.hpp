#pragma once
#include <algorithm>
#include <string>
#include <vector>

inline std::string smallest_concatenation(std::vector<std::string> strings) {
    std::sort(strings.begin(), strings.end(), [](const std::string &a, const std::string &b) {
        const std::size_t size = a.size() + b.size();
        for (std::size_t i = 0; i < size; ++i) {
            const char x = i < a.size() ? a[i] : b[i - a.size()];
            const char y = i < b.size() ? b[i] : a[i - b.size()];
            if (x != y) {
                return x < y;
            }
        }
        return false;
    });
    std::size_t size = 0;
    for (const auto &s : strings) {
        size += s.size();
    }
    std::string result;
    result.reserve(size);
    for (auto &s : strings) {
        result += s;
    }
    return result;
}

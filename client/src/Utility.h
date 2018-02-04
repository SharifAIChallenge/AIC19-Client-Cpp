#ifndef AIC18_CLIENT_CPP_UTILITY_H
#define AIC18_CLIENT_CPP_UTILITY_H

#include <cstdio>
#include <cstring>
#include <cstdarg>

#include <iostream>
#include <vector>

template <class T, class U>
std::vector<T> const_list_cast(const std::vector<U>& input) {
    return std::vector<T>(input.begin(), input.end());
}

template <class T, class U>
std::vector<std::vector<T>> const_grid_cast(const std::vector<std::vector<U>>& input) {
    std::vector<std::vector<T>> result;
    for (const auto& row : input)
        result.push_back(const_list_cast<T>(row));
    return result;
}

template <class T>
std::vector<T> flatten_list(const std::vector<std::vector<T>>& input) {
    std::vector<T> result;
    for (const auto& row : input)
        result.insert(result.end(), row.begin(), row.end());
    return result;
}

inline std::string format_string(const std::string& format, ...) {
    constexpr size_t BUFFER_LEN = 512;
    static char buffer[BUFFER_LEN];

    memset(buffer, 0, BUFFER_LEN);

    va_list vl;
    va_start(vl, format);
    vsnprintf(buffer, BUFFER_LEN, format.c_str(), vl);
    va_end(vl);

    return std::string(buffer);
}

extern bool global_verbose_flag;
#define DEBUG(x) if (global_verbose_flag) std::cerr << x << std::endl

#endif // AIC18_CLIENT_CPP_UTILITY_H

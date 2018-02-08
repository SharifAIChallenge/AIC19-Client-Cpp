#ifndef AIC18_CLIENT_CPP_UTILITY_H
#define AIC18_CLIENT_CPP_UTILITY_H

#include <cstdio>
#include <cstring>
#include <cstdarg>

#include <iostream>
#include <fstream>
#include <vector>
#include <memory>

/**
 * Convert a 2d vector to a 1d vector
 *
 * @param input The 2d vector to convert
 *
 * @return A vector containing copies of all elements in the input 2d vector
 */
template <class T>
std::vector<T> flatten_list(const std::vector<std::vector<T>>& input) {
    std::vector<T> result;
    for (const auto& row : input)
        result.insert(result.end(), row.begin(), row.end());
    return result;
}

/**
 * Rotate a 2d vector so that output[x][y] equals input[y][x]
 *
 * @param input The 2d vector to rotate
 *
 * @return The rotated form of the input vector
 */
template <class T>
std::vector<std::vector<T>> rotate_grid(const std::vector<std::vector<T>>& input) {
    std::vector<std::vector<T>> result(input.front().size(), std::vector<T>(input.size()));
    for (size_t i = 0; i < input.size(); ++i)
        for (size_t j = 0; j < input[i].size(); ++j)
            result[j][i] = input[i][j];
    return result;
}

/**
 * Format a string and its arguments like in printf
 *
 * @return The output formatted string
 */
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

template <class T, class U>
std::unique_ptr<T> dynamic_unique_ptr_cast(std::unique_ptr<U>&& input) {
    if (dynamic_cast<T*>(input.get()))
        return std::unique_ptr<T>(dynamic_cast<T*>(input.release()));
    return std::unique_ptr<T>();
}

#endif // AIC18_CLIENT_CPP_UTILITY_H

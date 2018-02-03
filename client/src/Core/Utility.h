#ifndef AIC18_CLIENT_CPP_UTILITY_H
#define AIC18_CLIENT_CPP_UTILITY_H

#include <vector>
#include <memory>
#include <algorithm>

template <class T>
using SharedPtrList = std::vector<std::shared_ptr<T>>;

template <class T>
using SharedPtrGrid = std::vector<std::vector<std::shared_ptr<T>>>;

template <class T, class U>
inline std::vector<T*> shared_ptr_list_to_raw_pointer_list(const SharedPtrList<U>& input) {
    std::vector<T*> result(input.size());
    std::transform(input.begin(), input.end(), result.begin(), [](const auto& x) { return x.get(); });
    return result;
};

template <class T, class U>
inline std::vector<std::vector<T*>> shared_ptr_grid_to_raw_pointer_grid(const SharedPtrGrid<U>& input) {
    std::vector<std::vector<T*>> result;
    for (const auto& row : input)
        result.push_back(shared_ptr_list_to_raw_pointer_list<T>(row));
    return result;
};

template <class T>
std::vector<T> flatten_list(const std::vector<std::vector<T>>& input) {
    std::vector<T> result;
    for (const auto& row : input)
        result.insert(result.end(), row.begin(), row.end());
    return result;
}

#endif // AIC18_CLIENT_CPP_UTILITY_H

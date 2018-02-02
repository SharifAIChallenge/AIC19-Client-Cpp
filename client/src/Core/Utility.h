#ifndef AIC18_CLIENT_CPP_UTILITY_H
#define AIC18_CLIENT_CPP_UTILITY_H

#include <vector>
#include <memory>


template <class T>
using SharedPtrList = std::vector<std::shared_ptr<T>>;

template <class T>
using SharedPtrGrid = std::vector<std::vector<std::shared_ptr<T>>>;

#endif // AIC18_CLIENT_CPP_UTILITY_H

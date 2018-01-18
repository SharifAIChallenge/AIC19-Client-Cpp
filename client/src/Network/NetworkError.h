#ifndef AIC18_CLIENT_CPP_NETWORK_ERROR_H
#define AIC18_CLIENT_CPP_NETWORK_ERROR_H

#include <string>
#include <stdexcept>

/**
 * An exception caused by a network operation
 */
class NetworkError : public std::runtime_error {
public:

    explicit inline NetworkError(const std::string& message)
            : std::runtime_error("Network error: " + message)
    {
    }
};


#endif // AIC18_CLIENT_CPP_NETWORK_ERROR_H

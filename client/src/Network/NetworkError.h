#ifndef AIC19_CLIENT_CPP_NETWORK_ERROR_H
#define AIC19_CLIENT_CPP_NETWORK_ERROR_H

#include <string>
#include <stdexcept>

/**
 * An exception caused by a network operation
 */
class NetworkError : public std::runtime_error {
public:

    explicit inline NetworkError(const std::string& message)
            : std::runtime_error(message)
    {
    }
};

class NetworkEOFError : public NetworkError {
public:

    explicit inline NetworkEOFError()
            : NetworkError("Reached EOF")
    {
    }
};

#endif // AIC19_CLIENT_CPP_NETWORK_ERROR_H

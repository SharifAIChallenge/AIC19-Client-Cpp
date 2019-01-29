#ifndef AIC18_CLIENT_CPP_PARSE_ERROR_H
#define AIC18_CLIENT_CPP_PARSE_ERROR_H

#include <string>
#include <stdexcept>

/**
 * An exception encountered when parsing messages from server
 */
class ParseError : public std::runtime_error {
public:
    explicit inline ParseError(const std::string& message)
            : std::runtime_error(message)
    {
    }
};

#endif // AIC18_CLIENT_CPP_PARSE_ERROR_H

#ifndef AIC18_CLIENT_CPP_PARSE_ERROR_H
#define AIC18_CLIENT_CPP_PARSE_ERROR_H

#include <string>
#include <stdexcept>

class ParseError : public std::runtime_error {
public:
    explicit inline ParseError(const std::string& message)
            : std::runtime_error("Parse error: " + message)
    {
    }
};

#endif // AIC18_CLIENT_CPP_PARSE_ERROR_H

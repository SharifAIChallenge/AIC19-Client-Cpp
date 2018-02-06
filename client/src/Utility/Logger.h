#ifndef AIC18_CLIENT_CPP_LOGGER_H
#define AIC18_CLIENT_CPP_LOGGER_H

#include <iostream>
#include <fstream>

enum LogLevel {
    DEBUG = 0,
    INFO = 1,
    WARNING = 2,
    ERROR = 3
};

class Logger final {
public:

    ~Logger() = default;

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    inline static Logger& Get(LogLevel level) {
        static Logger instance;

        instance.m_current_level = level;

        constexpr const char* LOG_LEVEL_STRING[] = {"Debug", "Info", "Warning", "Error"};
        constexpr static size_t INDENT_WIDTH = 12;

        std::string line = "[" + std::string(LOG_LEVEL_STRING[level]) + "]";
        line.insert(line.end(), INDENT_WIDTH - line.size(), ' ');
        instance << line;

        return instance;
    }

    template <class Type>
    inline Logger& operator<< (const Type& message) {
#ifdef AIC_CLIENT_DEBUG
        if (m_current_level >= STDERR_MIN_LEVEL)
            std::cerr << message;
        m_output_file << message;
#endif
        return *this;
    }

    inline Logger& operator<< (std::ostream&(*f)(std::ostream&)) {
#ifdef AIC_CLIENT_DEBUG
        if (m_current_level >= STDERR_MIN_LEVEL)
            f(std::cerr);
        f(m_output_file);
#endif
        return *this;
    }

    /// Minimum severity level for logs shown in standard error stream
    static LogLevel STDERR_MIN_LEVEL = LogLevel::WARNING;

private:

    inline Logger()
            : m_output_file("client.log"),
              m_current_level(DEBUG)
    {
    }

    /// The output file used for storing log
    std::ofstream m_output_file;

    /// Last call to @see Get will set this parameter
    LogLevel m_current_level;

};

#endif // AIC18_CLIENT_CPP_LOGGER_H
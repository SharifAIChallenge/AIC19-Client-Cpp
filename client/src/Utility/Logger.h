#ifndef AIC18_CLIENT_CPP_LOGGER_H
#define AIC18_CLIENT_CPP_LOGGER_H

#include <iostream>
#include <fstream>

enum LogLevel {
    TRACE = 0,
    DEBUG = 1,
    INFO = 2,
    WARNING = 3,
    ERROR = 4
};

class Logger final {
public:

    ~Logger() = default;

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    inline static Logger& Get() {
        return instance;
    }

    inline static Logger& Get(LogLevel level) {
        instance.m_current_level = level;

        constexpr const char* LOG_LEVEL_STRING[] = {"Trace", "Debug", "Info", "Warning", "Error"};
        constexpr size_t INDENT_WIDTH = 12;

        std::string line = "[" + std::string(LOG_LEVEL_STRING[level]) + "]";
        line.insert(line.end(), INDENT_WIDTH - line.size(), ' ');
        instance << line;

        return instance;
    }

    template <class Type>
    inline Logger& operator<< (const Type& message) {
#ifdef AIC_CLIENT_DEBUG
        if (m_current_level >= m_stderr_min_level)
            std::cerr << message;
        m_output_file << message;
#endif
        return *this;
    }

    inline Logger& operator<< (std::ostream&(*f)(std::ostream&)) {
#ifdef AIC_CLIENT_DEBUG
        if (m_current_level >= m_stderr_min_level)
            f(std::cerr);
        f(m_output_file);
#endif
        return *this;
    }

    inline void set_stderr_min_level(LogLevel level) {
        m_stderr_min_level = level;
    }

private:

    inline Logger()
            : m_output_file("client.log"),
              m_current_level(DEBUG),
              m_stderr_min_level(INFO)
    {
    }

    /// Singleton instance
    static Logger instance;

    /// The output file used for storing log
    std::ofstream m_output_file;

    /// Last call to @see Get will set this parameter
    LogLevel m_current_level;

    /// Minimum severity level for logs shown in standard error stream
    LogLevel m_stderr_min_level;

};

#endif // AIC18_CLIENT_CPP_LOGGER_H
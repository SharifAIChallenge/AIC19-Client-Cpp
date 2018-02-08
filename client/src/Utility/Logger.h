#ifndef AIC18_CLIENT_CPP_LOGGER_H
#define AIC18_CLIENT_CPP_LOGGER_H

#include <iostream>
#include <fstream>
#include <utility>

enum LogLevel {
    LogLevel_TRACE = 0,
    LogLevel_DEBUG = 1,
    LogLevel_INFO = 2,
    LogLevel_WARNING = 3,
    LogLevel_ERROR = 4
};

class Logger final {
public:

    /**
     * Configuration of a log sink
     *
     * @param first Is logging enabled for this sink
     * @param second Minimum severity level for logs shown in this sink
     */
    typedef std::pair<bool, LogLevel> LogSinkConfig;

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
        if (m_stderr_config.first && m_current_level >= m_stderr_config.second)
            std::cerr << message;

        if (m_logfile_config.first && m_current_level >= m_logfile_config.second)
            m_output_file << message;

        return *this;
    }

    inline Logger& operator<< (std::ostream&(*f)(std::ostream&)) {
        if (m_stderr_config.first && m_current_level >= m_stderr_config.second)
            f(std::cerr);

        if (m_logfile_config.first && m_current_level >= m_logfile_config.second)
            f(m_output_file);

        return *this;
    }

    inline void set_stderr_config(const LogSinkConfig& config) {
        m_stderr_config = config;
    }

    inline void set_logfile_config(const LogSinkConfig& config) {
        m_logfile_config = config;

        if (config.first)
            m_output_file.open("client.log");
    }

private:

    inline Logger()
            : m_current_level(LogLevel_DEBUG),
              m_stderr_config{true, LogLevel_INFO},
              m_logfile_config{false, LogLevel_TRACE}
    {
    }

    /// Singleton instance
    static Logger instance;

    /// The output file used for storing log
    std::ofstream m_output_file;

    /// Last call to @see Get will set this parameter
    LogLevel m_current_level;

    /// Standard output config
    LogSinkConfig m_stderr_config;

    /// Log to file config
    LogSinkConfig m_logfile_config;

};

#endif // AIC18_CLIENT_CPP_LOGGER_H
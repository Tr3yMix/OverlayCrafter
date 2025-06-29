#pragma once

#include <iostream>
#include <string>


namespace Logger {

    template<typename T>
    concept Streamable = requires(std::ostream& os, T t)
    {
        {os << t} -> std::same_as<std::ostream&>;
    };

    enum class LogType {Info, Error, Warn, Debug};

    inline const char* logLevelToString(const LogType logType) {
        switch (logType) {
            case LogType::Info: return "[Info]: ";
            case LogType::Error: return "[Error]: ";
            case LogType::Warn: return "[Warn]: ";
            case LogType::Debug: return "[Debug]: ";
        }
        return "[]: ";
    }

    template <Streamable... Args>
    void log(const LogType level = LogType::Info, Args&&... args) {
        std::stringstream stream;
        (stream << ... << std::forward<Args>(args));
        std::cout << logLevelToString(level) << stream.str() << std::endl;
    }

    template <Streamable... Args>
    void debug(Args&&... args){log(LogType::Debug, std::forward<Args>(args)...);}

    template <typename... Args>
    void logf(const LogType level, const std::string_view fmt, Args&&... args) {
        std::cout << logLevelToString(level) << std::vformat(fmt, std::make_format_args(args...)) << std::endl;
    }

    template <typename... Args>
    void debugf(std::string_view fmt, Args&&... args) {
        logf(LogType::Debug, fmt, std::forward<Args>(args)...);
    }

}




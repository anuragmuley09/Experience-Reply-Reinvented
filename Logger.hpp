#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <chrono>
#include <ctime>
#include <sstream>

class Logger {
public:
    enum LogLevel { INFO, WARNING, ERROR };

    static void log(const std::string &message, LogLevel level = INFO) {
        std::string levelStr;
        switch (level) {
            case INFO: levelStr = "INFO"; break;
            case WARNING: levelStr = "WARNING"; break;
            case ERROR: levelStr = "ERROR"; break;
        }
        auto now = std::chrono::system_clock::now();
        std::time_t now_time = std::chrono::system_clock::to_time_t(now);
        std::string timeStr = std::ctime(&now_time);
        timeStr.pop_back(); // Remove newline
        std::cout << timeStr << " [" << levelStr << "]: " << message << std::endl;
    }
};

#endif 

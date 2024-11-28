#pragma once

#include <memory>
#include <vector>
#include <string>

class Logger {
public:
    virtual void writeNum(size_t message) = 0;
    virtual void writeStr(std::string message) = 0;
    virtual ~Logger() = default;
};

class LogMonitor {
public:
    void attach(std::shared_ptr<Logger> listener);
    void detach(std::shared_ptr<Logger> listener);
    ~LogMonitor() = default;

    friend LogMonitor& operator<<(LogMonitor& log, std::string message);
    friend LogMonitor& operator<<(LogMonitor& log, size_t message);

private:
    std::vector<std::shared_ptr<Logger>> listeners;
};
#include <memory>
#include <string>
#include <algorithm>
#include <logging/structures.h>

void LogMonitor::attach(std::shared_ptr<Logger> listener) {
    listeners.push_back(listener);
}

void LogMonitor::detach(std::shared_ptr<Logger> listener) {
    auto newEnd = std::remove(listeners.begin(), listeners.end(), listener);
    listeners.erase(newEnd, listeners.end());
}

LogMonitor& operator<<(LogMonitor& log, std::string message) {
    for (auto& listener : log.listeners) {
        listener->writeStr(message);
    }
    return log;
}

LogMonitor& operator<<(LogMonitor& log, size_t message) {
    for (auto& listener : log.listeners) {
        listener->writeNum(message);
    }
    return log;
}
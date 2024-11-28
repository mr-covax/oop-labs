#pragma once

#include <string>
#include <logging/structures.h>

class DisplayLogger : public Logger {
public:
    DisplayLogger() = default;
    void writeNum(size_t message) override;
    void writeStr(std::string message) override;
    ~DisplayLogger() override = default;
};
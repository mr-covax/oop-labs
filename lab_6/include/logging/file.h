#pragma once

#include <fstream>
#include <logging/structures.h>

class FileLogger : public Logger {
public:
    FileLogger(std::string filePath);
    void writeNum(size_t message) override;
    void writeStr(std::string message) override;
    ~FileLogger() override;

private:
    std::ofstream output;
};

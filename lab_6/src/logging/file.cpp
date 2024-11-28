#include <string>
#include <fstream>
#include <logging/file.h>

FileLogger::FileLogger(std::string filePath) {
    output = std::ofstream(filePath);
    if (!output.is_open()) {
        output.close();
        throw std::ios_base::failure("Failed to open file!");
    }
}

void FileLogger::writeNum(size_t message) {
    output << message;
}

void FileLogger::writeStr(std::string message) {
    output << message;
}

FileLogger::~FileLogger() {
    output.close();
}
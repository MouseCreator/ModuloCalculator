#include "TestUtils.h"
#include <fstream>

std::istringstream loadTestFile(const std::string& name, bool& success) {
    std::ifstream file(name);
    if (!file.is_open()) {
        success = false;
        return std::istringstream("");
    }
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    success = true;
    return std::istringstream(content);
}

std::vector<std::string> readLines(const std::string& name, bool& success) {
    std::ifstream inputFile(name);
    std::vector<std::string> lines;
    std::string line;

    if (!inputFile.is_open()) {
        success = false;
        return std::vector<std::string>();
    }

    while (std::getline(inputFile, line)) {
        if (line.empty()) {
            continue;
        }
        lines.push_back(line);
    }
    inputFile.close();
    return lines;
}
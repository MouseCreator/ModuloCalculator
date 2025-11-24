#include "StringUtils.h"
#include <fstream>
#include <string>

bool replace(std::string& str, const std::string& from, const std::string& to) {
    size_t start_pos = str.find(from);
    if (start_pos == std::string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}
void replaceAll(std::string& str, const std::string& from, const std::string& to) {
    if (from.empty())
        return;
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
}

bool startsWith(const std::string& str, const std::string& target) {
    return str.rfind(target, 0) == 0;
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

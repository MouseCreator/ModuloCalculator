#pragma once
#include <iostream>
#include <vector>
bool replace(std::string& str, const std::string& from, const std::string& to);
void replaceAll(std::string& str, const std::string& from, const std::string& to);
bool startsWith(const std::string& str, const std::string& target);
std::vector<std::string> readLines(const std::string& name, bool& success);
#pragma once
#include <iostream>
#include <sstream>
#include <vector>
std::istringstream loadTestFile(const std::string& name, bool& success);
std::vector<std::string> readLines(const std::string& name, bool& success);
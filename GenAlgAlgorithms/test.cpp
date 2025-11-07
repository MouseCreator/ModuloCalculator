#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <iostream>

#include "MathBase/parse/scanner.h"
#include "MathBase/parse/parser.hpp"
#include "MathBase/parse/interpreter.h"
#include <fstream>
#include <sstream>
#include <string>

using namespace MathBase;
TEST_CASE("Generic test") {

	CHECK(10 + 15 != 35);
	CHECK(10 + 25 == 35);

}

std::istringstream loadFile(const std::string& name, bool& success) {
    std::ifstream file(name);
    if (!file.is_open()) {
        success = false;
        return std::istringstream("");
    }
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    success = true;
    return std::istringstream(content);
}
TEST_CASE("Parse input test") {
    bool isOpened = false;
    std::string filename = "input.txt";
    std::istringstream stream = loadFile(filename, isOpened);
    if (!isOpened) {
        std::cout << "Cannot open " << filename << std::endl;
    }
	CHECK(isOpened == true);
    Interpreter i;
    i.switchInputStream(&stream);
    i.configLocation(filename, true, true);
    int res = i.parse();
    CHECK(res == 0);
}

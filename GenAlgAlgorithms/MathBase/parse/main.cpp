

#include <iostream>
#include "scanner.h"
#include "parser.hpp"
#include "interpreter.h"
#include <fstream>
#include <sstream>
#include <string>

using namespace MathBase;
using namespace std;


istringstream loadFile(const string& name, bool& success) {
    ifstream file(name);
    if (!file.is_open()) {
        success = false;
        return istringstream("");
    }
    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    success = true;
    return istringstream(content);
}

int main(int argc, char **argv) {
    bool isOpened = false;
    string filename = "input.txt";
    istringstream stream = loadFile(filename, isOpened);
    if (!isOpened) {
        cout << "Cannot open " << filename << endl;
    }
    Interpreter i;
    i.switchInputStream(&stream);
    i.configLocation(filename, true, true);
    int res = i.parse();
    cout << "Parse complete. Result = " << res << endl << i.str() << endl;
    return res;
}

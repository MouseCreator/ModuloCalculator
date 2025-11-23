
#include <cstdlib>
#include <cstring>
#include <string>
#include <stdexcept>

const int MAX_MESSAGE_LENGTH = 4096;

extern "C" char* finite_field(const char* expression, const char* n, char* errorStr)
{
    char* resStr = nullptr;
    resStr = new char[MAX_MESSAGE_LENGTH];
    std::string s = "0";
    strcpy_s(resStr, MAX_MESSAGE_LENGTH, s.c_str());
    return resStr;
}


extern "C" char* number_factorization(const char* n, char* errorStr)
{
    char* resStr = nullptr;
    resStr = new char[MAX_MESSAGE_LENGTH];
    std::string s = "0";
    strcpy_s(resStr, MAX_MESSAGE_LENGTH, s.c_str());
    return resStr;
}

extern "C" char* number_order(const char* number, const char* n, char* errorStr)
{
    char* resStr = nullptr;
    resStr = new char[MAX_MESSAGE_LENGTH];
    std::string s = "0";
    strcpy_s(resStr, MAX_MESSAGE_LENGTH, s.c_str());
    return resStr;
}


extern "C" char* prime_test(const char* number, const char* iterations, char* errorStr)
{
    char* resStr = nullptr;
    resStr = new char[MAX_MESSAGE_LENGTH];
    std::string s = "0";
    strcpy_s(resStr, MAX_MESSAGE_LENGTH, s.c_str());
    return resStr;
}

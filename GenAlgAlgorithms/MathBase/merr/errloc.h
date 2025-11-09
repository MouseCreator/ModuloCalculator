#ifndef ERRORLOC_H
#define ERRORLOC_H
#include <iostream>
namespace merr {
    class LocationStruct {
    private:
        std::string m_file;
        int m_line;
        int m_column;
        bool m_absolute;
    public:
        LocationStruct(std::string file = "", int line = 0, int column = 0, bool absolute = false);
        LocationStruct(const LocationStruct& other) : m_file(other.m_file), m_line(other.m_line), m_column(other.m_column), m_absolute(other.m_absolute) {}
        std::string str() const;
    };
}

std::ostream& operator<<(std::ostream& os, const merr::LocationStruct& error);
#endif
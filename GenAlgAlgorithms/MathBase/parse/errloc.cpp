#include <iostream>
#include <sstream>
#include "errloc.h"
namespace merr {
    LocationStruct::LocationStruct(std::string file, int line, int column, bool absolute)  {
        this->m_file = file;
        this->m_line = line;
        this->m_column = column;
        this->m_absolute = absolute;
    }
    
    std::string LocationStruct::str() const {
        std::stringstream stream;
        if (!m_file.empty()) {
            stream << m_file << ".";
        }
        if (!m_absolute) {
            stream << m_line << ".";
        }
        stream << m_column;
        return stream.str();
    }
}
std::ostream& operator<<(std::ostream& os, const merr::LocationStruct& error) {
    os << error.str();
    return os;
}
#pragma once
#include <iostream>
class StringPrintable {
public:
    virtual ~StringPrintable() = default;
    virtual std::string str() const = 0;
};

std::ostream& operator<<(std::ostream& os, const StringPrintable& stp);
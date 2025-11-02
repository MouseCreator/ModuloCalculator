
#include "StringPrintable.h"

std::ostream& operator<<(std::ostream& os, const StringPrintable& stp) {
	os << stp.str();
	return os;
}
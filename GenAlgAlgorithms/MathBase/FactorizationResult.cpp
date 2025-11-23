#include "FactorizationResult.h"
#include <sstream>

FactorizationResult::FactorizationResult() {

}

void FactorizationResult::addFactors(std::vector<SignedNumber> factors) {
	for (SignedNumber s : factors) {
		this->factors.emplace_back(s);
	}
}

std::string FactorizationResult::toString() {
	std::stringstream ss;
	ss << "[";
	if (factors.empty()) {
		ss << "]";
		return ss.str();;
	}
	ss << factors[0].toString();
	std::size_t size = factors.size();
	for (std::size_t i = 1; i < size; i++) {
		ss << "," << factors[i].toString();
	}
	ss << "]";
	return ss.str();

}
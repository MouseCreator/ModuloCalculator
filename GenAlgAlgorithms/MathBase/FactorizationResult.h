#pragma once
#include <iostream>
#include <vector>
#include "SignedNumber.h"

class FactorizationResult {
public:
	FactorizationResult();
	void addFactors(std::vector<SignedNumber> factors);
	std::string toString();
private:
	std::vector<SignedNumber> factors;
};
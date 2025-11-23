#pragma once
#include "PositiveNumber.h"
#include "FiniteNumber.h"
#include "merr/ErrorManager.h"

class OrderResult {
private:
	bool isGenerator;
	PositiveNumber order;
public:
	OrderResult(PositiveNumber order = PositiveNumber(0), bool generator = false);
	std::string toString();
};

class OrderEngine {
public:
	OrderResult orderAndGenerator(FiniteNumber finiteNumber, merr::Errors* err);
};
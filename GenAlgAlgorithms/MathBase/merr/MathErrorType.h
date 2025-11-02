#pragma once
#include <iostream>
namespace merr {
	enum MathErrorType {
		UNDEFINED_ERROR, SCAN_ERROR, PARSE_ERROR, INTERPRETATION_ERROR, CALCULATION_ERROR, MATH_ERROR, VALIDATION_ERROR
	};

	std::string stringifyErrorType(MathErrorType errorType);
	MathErrorType toErrorType(std::string type);
	std::string simpleErrorType(MathErrorType errorType);
}
#include "MathErrorType.h"
namespace merr {
	std::string stringifyErrorType(MathErrorType errorType) {
		switch (errorType)
		{
		case merr::UNDEFINED_ERROR:
			return "Error";
		case merr::SCAN_ERROR:
			return "Scan error";
		case merr::PARSE_ERROR:
			return "Parse error";
		case merr::CALCULATION_ERROR:
			return "Calculation error";
		case merr::INTERPRETATION_ERROR:
			return "Interpretation error";
		case merr::MATH_ERROR:
			return "Math error";
		default:
			return "Error";
		}
	}
	std::string simpleErrorType(MathErrorType errorType) {
		switch (errorType)
		{
		case merr::UNDEFINED_ERROR:
			return "undefined";
		case merr::SCAN_ERROR:
			return "scan";
		case merr::PARSE_ERROR:
			return "parse";
		case merr::CALCULATION_ERROR:
			return "calculation";
		case merr::INTERPRETATION_ERROR:
			return "interpretation";
		case merr::MATH_ERROR:
			return "math";
		default:
			return "error";
		}
	}
	MathErrorType toErrorType(std::string type) {
		if (type == "scan") {
			return merr::SCAN_ERROR;
		}
		if (type == "calculation") {
			return merr::CALCULATION_ERROR;
		}
		if (type == "parse") {
			return merr::PARSE_ERROR;
		}
		if (type == "interpretation") {
			return merr::INTERPRETATION_ERROR;
		}
		if (type == "math") {
			return merr::MATH_ERROR;
		}
		return merr::UNDEFINED_ERROR;
	}
}
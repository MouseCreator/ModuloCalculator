#include "AST_Operation.h"
namespace Operation {
	BINARY_OPERATION binary_from_string(std::string str) {
		if (str == "+") {
			return PLUS;
		}
		if (str == "-") {
			return MINUS;
		}
		if (str == "*") {
			return MULTIPLY;
		}
		if (str == "/") {
			return DIVIDE;
		}
		if (str == "**" || str == "^") {
			return EXPONENT;
		}
		if (str == "%") {
			return MODULO;
		}
		return NONE;
	}
	UNARY_OPERATION unary_from_string(std::string str) {
		if (str == "+") {
			return UPLUS;
		}
		if (str == "-") {
			return UMINUS;
		}
		return UNONE;
	}
}
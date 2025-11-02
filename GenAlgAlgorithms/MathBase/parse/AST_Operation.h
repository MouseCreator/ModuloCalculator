#pragma once
#include <iostream>
namespace Operation {
	enum BINARY_OPERATION {
		NONE, PLUS, MINUS, MULTIPLY, DIVIDE, EXPONENT, MODULO
	};
	enum UNARY_OPERATION {
		UNONE, UPLUS, UMINUS
	};

	BINARY_OPERATION binary_from_string(std::string str);

	UNARY_OPERATION unary_from_string(std::string str);
}
#pragma once

#include "TestEngineUtils.h"
#include "../FiniteNumber.h"
#include "TestUtils.h"
#include <optional>
struct FFArguments {
	int number = -1;
	std::vector<std::string> arguments;
};

struct ResultArguments {
	FiniteNumber actual;
	FiniteNumber expected;
	std::string message;
};

class TestEngineFiniteField : TestEngine {
private:
	std::optional<FFArguments> _getArguments(int number, std::string line, TestExecutionResult& testResult);
	void _processArguments(FFArguments args, TestExecutionResult& testResult);
	void _on_calculate(int n, std::string expression, std::string moduloStr, std::string operationStr, std::string expectedStr,
						std::string message, std::string defaultMessage, TestExecutionResult& testResult);
	void _on_errorDetect(int n, std::string expression, std::string modulo, std::string expectedType, 
		std::string message, std::string defaultMessage, TestExecutionResult& testResult);
	bool _isCommentLine(std::string& line);

public:
	TestExecutionResult execute(std::string filename) override;
};
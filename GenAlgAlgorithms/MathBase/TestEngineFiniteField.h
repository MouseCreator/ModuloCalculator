#pragma once

#include "FiniteNumber.h"
#include <optional>
#include <vector>
#include "utils/StringPrintable.h"

class TestInternalError : public StringPrintable {
private:
	int number;
	std::string reason;
public:
	TestInternalError();
	TestInternalError(int number, std::string reason);
	std::string str() const override;
};

class TestExecutionResult : public StringPrintable {
private:
	std::vector<TestInternalError> internalErrors;
public:
	void pushInternalError(TestInternalError internalError);
	std::vector<TestInternalError> getInternalErrors();
	bool success() const;
	std::string str() const override;
};

class TestEngine {
public:
	virtual TestExecutionResult execute(std::string filename) = 0;
};


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
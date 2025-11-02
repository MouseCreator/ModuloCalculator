#pragma once
#include <iostream>
#include <vector>
#include "StringPrintable.h"
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
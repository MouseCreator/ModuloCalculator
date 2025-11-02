#include "TestEngineUtils.h"
#include <sstream>
TestInternalError::TestInternalError() {
	number = -2;;
	reason = "";
}
TestInternalError::TestInternalError(int number, std::string reason) {
	this->number = number;
	this->reason = reason;

}
std::string TestInternalError::str() const {
	std::stringstream ss;
	ss << "Test " << number << " : " << reason;
	return ss.str();
}

void TestExecutionResult::pushInternalError(TestInternalError internalError) {
	internalErrors.emplace_back(internalError);
}
std::vector<TestInternalError> TestExecutionResult::getInternalErrors() {
	return internalErrors;
}
bool TestExecutionResult::success() const {
	return internalErrors.size() == 0;
}
std::string TestExecutionResult::str() const {
	std::stringstream ss;
	if (success()) {
		return "Engine test success!";
	}
	ss << "Engine test failed! Reasons:" << std::endl;
	for (TestInternalError err : internalErrors) {
		ss << err << std::endl;
	}
	return ss.str();
}
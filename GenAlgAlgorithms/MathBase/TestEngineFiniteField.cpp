#include "TestEngineFiniteField.h"
#include "Executor.h"
#include "utils/StringUtils.h"
#include <sstream>
TestInternalError::TestInternalError() {
	number = -2;
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


std::optional<FFArguments> TestEngineFiniteField::_getArguments(int number, std::string line, TestExecutionResult& testResult) {
	bool quoted = false;
	bool building = false;
	FFArguments arguments;
	arguments.number = number;
	std::string current;
	for (char ch : line) {
		if (quoted) {
			if (ch == '"') {
				quoted = false;
				building = false;
				arguments.arguments.emplace_back(current);
				current = "";
			}
			else {
				current += ch;
			}
		}
		else {
			if (ch == '"') {
				quoted = true;
				if (building) {
					arguments.arguments.emplace_back(current);
					current = "";
				}
			}
			else if (ch == ' ') {
				if (building) {
					building = false;
					arguments.arguments.emplace_back(current);
					current = "";
				}
			}
			else {
				current += ch;
				building = true;
			}
		}
	}
	if (quoted) {
		testResult.pushInternalError(TestInternalError(number, "Error reading line: Unmacched '\"' in the line."));
		return {};
	}
	if (building) {
		arguments.arguments.emplace_back(current);
	}
	return arguments;
}




void TestEngineFiniteField::_processArguments(FFArguments args, TestExecutionResult& testResult) {
	int n = args.number;
	int count = args.arguments.size();
	if (count < 5) {
		testResult.pushInternalError(TestInternalError(n, "Expected line format \"expr\" % \"mod\" operation \"expected\""));
		return;
	}
	std::string expression = args.arguments[0];
	std::string next = args.arguments[1];
	std::string moduloStr = args.arguments[2];
	std::string operationStr = args.arguments[3];
	if (operationStr == "==" || operationStr == "!=") {
		std::string moduloStr = args.arguments[2];
		std::string operationStr = args.arguments[3];
		std::string expectedStr = args.arguments[4];
		std::string defaultMessage = "$actual " + operationStr + " $expected (mod " + moduloStr + ")";
		std::string message = "$default";
		if (args.arguments.size() > 5) {
			if (args.arguments[5] != ":") {
				testResult.pushInternalError(TestInternalError(n, "Use ': msg' to print custom error message"));
				return;
			}
		}
		if (args.arguments.size() > 6) {
			message = args.arguments[6];
		}
		_on_calculate(n, expression, moduloStr, operationStr, expectedStr, message, defaultMessage, testResult);
	}
	else if (operationStr == "X" || operationStr == "x") {
		std::string expectedType = args.arguments[4];
		std::string defaultMessage = "Expected error of type $expected, but got $actual";
		std::string message = "$default";
		if (args.arguments.size() > 5) {
			if (args.arguments[5] != ":") {
				testResult.pushInternalError(TestInternalError(n, "Use ': msg' to print custom error message"));
				return;
			}
		}
		if (args.arguments.size() > 6) {
			message = args.arguments[6];
		}
		_on_errorDetect(n, expression, moduloStr, expectedType, message, defaultMessage, testResult);
	}
	else {
		testResult.pushInternalError(TestInternalError(n, "Unexpected second argument of test expression. Use % for calculation and X for error detection"));
	}
}

void TestEngineFiniteField::_on_calculate(int n, std::string expression, std::string moduloStr, std::string operationStr, std::string expectedStr,
	std::string message, std::string defaultMessage, TestExecutionResult& testResult) {
	Executor executor;
	merr::Errors errors;
	PositiveNumber p(moduloStr);
	FiniteNumber result;
	result = executor.finite_field(expression, &p, &errors);
	if (errors.hasError()) {
		std::string message = errors.concat();
		testResult.pushInternalError(TestInternalError(n, message));
		return;
	}
	FiniteNumber expected = FiniteNumber(expectedStr, FiniteField(p));
	bool comparison = false;
	if (operationStr == "==") {
		comparison = result == expected;
	}
	else if (operationStr == "!=") {
		comparison = result != expected;
	}
	else {
		testResult.pushInternalError(TestInternalError(n, "Unexpected comparison: " + operationStr));
		return;
	}
	if (!comparison) {
		replaceAll(message, "$default", defaultMessage);
		replaceAll(message, "$expected", expectedStr);
		replaceAll(message, "$actual", result.toString());
		replaceAll(message, "$expr", expression);

		testResult.pushInternalError(TestInternalError(n, "ASSERT FAILED: " + message));
		return;
	}
}
void TestEngineFiniteField::_on_errorDetect(int n, std::string expression, std::string moduloStr, std::string expectedType, std::string message,
	std::string defaultMessage, TestExecutionResult& testResult) {
	Executor executor;
	merr::Errors errors;
	PositiveNumber p(moduloStr);
	FiniteNumber result;
	result = executor.finite_field(expression, &p, &errors);
	std::string actualErrorType;
	bool failed = false;
	if (!errors.hasError()) {
		actualErrorType = "none";
		failed = true;
	}
	else {
		std::vector<merr::MathError> errList = errors.getAllErrors();
		if (errList.size() > 1 && expectedType != "multiple") {
			std::stringstream ss;
			ss << "Expression produced unexprected number of errors (" << errList.size() << "): " << errors.concat();
			testResult.pushInternalError(TestInternalError(n, ss.str()));
			return;
		}
		merr::MathError primaryError = errList[0];
		merr::MathErrorType type = primaryError.getType();
		if (expectedType != "multiple" && expectedType != "any") {
			actualErrorType = merr::simpleErrorType(type);
			merr::MathErrorType expected = merr::toErrorType(expectedType);
			if (type != expected) {
				failed = true;
			}
		}
	}

	if (failed) {
		replaceAll(message, "$default", defaultMessage);
		replaceAll(message, "$expected", expectedType);
		replaceAll(message, "$actual", actualErrorType);
		replaceAll(message, "$expr", expression);
		testResult.pushInternalError(TestInternalError(n, "ASSERT FAILED: " + message));
	}
}

bool TestEngineFiniteField::_isCommentLine(std::string& line) {
	for (char ch : line) {
		if (ch == ' ' || ch == '\t')
			continue;
		if (ch == '#')
			return true;
		return false;
	}
}
TestExecutionResult TestEngineFiniteField::execute(std::string input) {
	TestExecutionResult result;
	bool success = true;
	std::vector<std::string> lines = readLines(input, success);
	if (!success) {
		result.pushInternalError(TestInternalError(-1, "Cannot read input file: " + input));
		return result;
	}
	int count = 0;
	for (std::string line : lines) {
		if (_isCommentLine(line)) {
			continue;
		}
		std::optional<FFArguments> args = _getArguments(++count, line, result);
		if (args) {
			_processArguments(args.value(), result);
		}
	}
	return result;
}
#include "InterpretationManager.h"
#include <sstream>
InterpretationManager::InterpretationManager() : interpreter() {
	interpreter.configLocation("", false, false);
}
InterpretationManager::~InterpretationManager() {
}
std::optional<MathBase::AST*> InterpretationManager::parseInput(std::string input, merr::Errors* errors) {
	std::istringstream* input_stream = new std::istringstream(input);
	interpreter.switchInputStream(input_stream);

	int parseResult = interpreter.parse();
	merr::ErrorFlag errFlag;
	MathBase::AST* result = nullptr;
	if (parseResult) { /*Error result*/
		std::string error = "Cannot parse given input: " + input;
		errFlag.set(merr::MathError(merr::INTERPRETATION_ERROR, error));
	}
	else { /*Success*/
		std::size_t size = interpreter.total_asts();
		if (size != 1) {
			std::stringstream ss;
			ss << "Incorrect number of result Abstract Syntax Trees: " << size;
			std::string errMsg = ss.str();
			errFlag.set(merr::MathError(merr::INTERPRETATION_ERROR, errMsg));
		}
	}
	if (interpreter.hasError()) {
		merr::MathError error = interpreter.getError();
		errFlag.set(error);
	}
	if (errFlag.hasError()) {
		errors->addError(errFlag.get());
		interpreter.clrError();
	}
	else {
		result = interpreter.get_ast(0);
		interpreter.clear();
	}

	interpreter.switchInputStream(nullptr);
	delete input_stream;
	if (!result) {
		return {};
	}
	return result;
}

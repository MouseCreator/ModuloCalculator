#pragma once
#include "parse/interpreter.h"
#include "parse/AST_Core.h"
#include "merr/ErrorManager.h"
#include <optional>
class InterpretationManager {
private:
	MathBase::Interpreter interpreter;
public:
	InterpretationManager();
	~InterpretationManager();
	std::optional<MathBase::AST*> parseInput(std::string input, merr::Errors* errors);
};
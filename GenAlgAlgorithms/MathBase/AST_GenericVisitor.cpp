#include "AST_Generic_Visitor.h"
#include <sstream>
namespace MathBase {
	void ASTVisitor::setError(merr::MathError err) {
		this->errFlag.set(err);
	}
	bool ASTVisitor::hasError() {
		return errFlag.hasError();
	}
	void ASTVisitor::clearError() {
		errFlag.clr();
	}
	merr::MathError ASTVisitor::getError() {
		return errFlag.get();
	}
	void ASTVisitor::raiseError(std::string error, merr::LocationStruct* loc) {
		merr::MathError t = merr::MathError(merr::CALCULATION_ERROR, error, loc);
		errFlag.set(t);
	}
	bool ASTVisitor::testErrorPicker(merr::ErrorPicker& p, merr::LocationStruct* loc) {
		bool hasError = p.picked();
		if (!hasError) {
			return false;
		}
		merr::MathErrorType type = merr::MATH_ERROR;
		merr::MathErrorType pt = p.getType();
		if (pt != merr::UNDEFINED_ERROR) {
			type = pt;
		}
		setError(merr::MathError(type, p.getMessage(), loc));
		return true;
	}
	bool ASTVisitor::_validateNumArguments(FunctionNode& func, int count) {
		std::string name = func.functionName;
		int actual = func.num_argumnets();
		if (actual != count) {
			std::stringstream ss;
			ss << "Unexpected number of arguments for function " << name << ". Expected " << count << ", but got " << actual;
			raiseError(ss.str(), &func.loc());
			return true;
		}
		return false;
	}
}
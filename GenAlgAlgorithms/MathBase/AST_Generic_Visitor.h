#pragma once
#include "parse/command.h"
#include "merr/MathError.h"
#include "merr/errpick.h"
#include "AST_Core.h"
namespace MathBase {
	class ASTVisitor {
	protected:
		merr::ErrorFlag errFlag;
	public:
		void setError(merr::MathError err);
		bool hasError();
		void clearError();
		merr::MathError getError();
		void raiseError(std::string error, merr::LocationStruct* loc = nullptr);
		bool testErrorPicker(merr::ErrorPicker& p, merr::LocationStruct* loc = nullptr);

		virtual void visitNumber(NumberNode& number) = 0;
		virtual void visitOperation(OperationNode& operation) = 0;
		virtual void visitUnary(UnaryNode& operation) = 0;
		virtual void visitFunction(FunctionNode& func) = 0;
	};
}

#pragma once
#include <optional>

#include "SignedNumber.h"
#include "parse/command.h"
#include "AST_Generic_Visitor.h"
#include "AST_Context_Type.h"
#include "FiniteNumber.h"
namespace MathBase {

	class FiniteFieldCalculator : public ASTVisitor {
	private:
		FiniteFieldContext context;
		FiniteNumber* _value;
	public:
		void visitNumber(NumberNode& number) override;
		void visitVariable(VariableNode& variable) override;
		void visitOperation(OperationNode& operation) override;
		void visitUnary(UnaryNode& operation) override;
		void visitFunction(FunctionNode& func) override;
		FiniteNumber readValue() const;
		void clearValue();
		void writeValue(FiniteNumber n);


	private:
	};

}

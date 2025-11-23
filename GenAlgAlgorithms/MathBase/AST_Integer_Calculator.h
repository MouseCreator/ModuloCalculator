#pragma once

#include "AST_Generic_Visitor.h"
#include "SignedNumber.h"
#include <optional>
namespace MathBase {

	class IntegerCalculator : public ASTVisitor {
	private:
		SignedNumber* _value;
	public:
		void visitNumber(NumberNode& number) override;
		void visitOperation(OperationNode& operation) override;
		void visitUnary(UnaryNode& operation) override;
		void visitFunction(FunctionNode& func) override;

		SignedNumber readValue() const;
		void clearValue();
		void writeValue(SignedNumber n);
		std::optional<SignedNumber> safeReadValue() const;

		IntegerCalculator();
		~IntegerCalculator();
	private:
		SignedNumber _visitAndGetValue(ASTNode* node);
	};
}

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
		FiniteNumber* _value;
		FiniteFieldContext context;
	public:
		void visitNumber(NumberNode& number) override;
		void visitVariable(VariableNode& variable) override;
		void visitOperation(OperationNode& operation) override;
		void visitUnary(UnaryNode& operation) override;
		void visitFunction(FunctionNode& func) override;

		FiniteNumber readValue() const;
		void clearValue();
		void writeValue(FiniteNumber n);
		std::optional<FiniteNumber> safeReadValue() const;
		FiniteFieldContext getContext() const;

		FiniteFieldCalculator(FiniteFieldContext& ffc);
		~FiniteFieldCalculator();
		
	private:
		FiniteNumber _visitAndGetValue(ASTNode* node);
		std::optional<SignedNumber> _visitSigned(ASTNode* node);
	};

}

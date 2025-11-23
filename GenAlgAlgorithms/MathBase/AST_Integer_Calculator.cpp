#include "AST_Integer_Calculator.h"
#include "AST_Operation.h"
namespace MathBase {

	void IntegerCalculator::visitNumber(NumberNode& number) {
		if (hasError()) {
			return;
		}
		writeValue(SignedNumber());
	}
	
	void IntegerCalculator::visitOperation(OperationNode& operation) {
		if (hasError()) {
			return;
		}
		writeValue(SignedNumber());
	}
	void IntegerCalculator::visitUnary(UnaryNode& operation) {
		if (hasError()) {
			return;
		}
		writeValue(SignedNumber());
	}
	void IntegerCalculator::visitFunction(FunctionNode& func) {
		if (hasError()) {
			return;
		}
		writeValue(SignedNumber());
	}

	SignedNumber IntegerCalculator::readValue() const {
		if (this->_value) {
			return SignedNumber(*this->_value);
		}
		return SignedNumber();
	}

	void IntegerCalculator::clearValue() {
		if (this->_value) {
			delete this->_value;
		}
		this->_value = nullptr;
	}

	void IntegerCalculator::writeValue(SignedNumber n) {
		clearValue();
		this->_value = new SignedNumber(n);
	}

	std::optional<SignedNumber> IntegerCalculator::safeReadValue() const {
		if (this->_value) {
			return SignedNumber(*this->_value);
		}
		return {};
	}

	IntegerCalculator::IntegerCalculator() {
		this->_value = nullptr;
	}
	IntegerCalculator::~IntegerCalculator() {
		clearValue();
		clearError();
	}

	SignedNumber IntegerCalculator::_visitAndGetValue(ASTNode* node) {
		if (hasError()) {
			return SignedNumber();
		}
		if (node == nullptr) {
			raiseError("Integer Visitor encountered null node.");
			return SignedNumber();
		}
		node->acceptVisitor(this);
		if (hasError()) {
			return SignedNumber();
		}
		std::optional<SignedNumber> optional = this->safeReadValue();
		if (optional.has_value()) {
			return optional.value();
		}
		raiseError("Integer visitor got no value after reading node: " + node->str());
		return SignedNumber();
	}
}
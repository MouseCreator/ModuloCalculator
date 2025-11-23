#include "AST_FiniteFieldCalculator.h"
#include "AST_Operation.h"
namespace MathBase {

	void FiniteFieldCalculator::visitNumber(NumberNode& number) {
		if (hasError()) {
			return;
		}
		
		writeValue(FiniteNumber());
	}
	void FiniteFieldCalculator::visitOperation(OperationNode& operation) {
		if (hasError()) {
			return;
		}
		
	}
	void FiniteFieldCalculator::visitUnary(UnaryNode& operation) {
		if (hasError()) {
			return;
		}
		writeValue(FiniteNumber());
	}

	void FiniteFieldCalculator::visitFunction(FunctionNode& func) {
		if (hasError()) {
			return;
		}
		writeValue(FiniteNumber());
	}

	FiniteNumber FiniteFieldCalculator::readValue() const {
		if (this->_value == nullptr) {
			return FiniteNumber("0", context.getField());
		}
		return FiniteNumber(*this->_value);
	}
	void FiniteFieldCalculator::clearValue() {
		if (this->_value) {
			delete this->_value;
		}
		this->_value = nullptr;
	}
	void FiniteFieldCalculator::writeValue(FiniteNumber n) {
		clearValue();
		this->_value = new FiniteNumber(n);
	}
	std::optional<FiniteNumber> FiniteFieldCalculator::safeReadValue() const {
		if (this->_value == nullptr) {
			return {};
		}
		return FiniteNumber(*this->_value);
	}
	FiniteFieldContext FiniteFieldCalculator::getContext() const {
		return this->context;
	}

	FiniteFieldCalculator::FiniteFieldCalculator(FiniteFieldContext& ffc) {
		this->context = ffc;
		this->_value = nullptr;
	}
	FiniteFieldCalculator::~FiniteFieldCalculator() {
		clearValue();
	}
}
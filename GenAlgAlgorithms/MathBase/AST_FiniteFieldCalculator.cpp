#include "AST_FiniteFieldCalculator.h"
#include "AST_Operation.h"
#include "AST_Integer_Calculator.h"
#include "Exponent.h"
#include <sstream>
#include "Euler.h"
#include "Logarithm.h"
namespace MathBase {

	void FiniteFieldCalculator::visitNumber(NumberNode& number) {
		if (hasError()) {
			return;
		}
		std::string digits = number.digits;
		FiniteField field = context.getField();
		FiniteNumber finiteNumber = FiniteNumber(digits, field);
		writeValue(finiteNumber);
	}
	void FiniteFieldCalculator::visitOperation(OperationNode& operation) {
		if (hasError()) {
			return;
		}
		std::string operationStr = operation.operation;
		Operation::BINARY_OPERATION binary = Operation::binary_from_string(operationStr);
		if (binary == Operation::EXPONENT) {
			IntegerCalculator integerCalculator;
			operation.right->acceptVisitor(&integerCalculator);
			if (integerCalculator.hasError()) {
				setError(integerCalculator.getError());
			}
			FiniteNumber left = this->_visitAndGetValue(operation.left);
			if (hasError()) {
				return;
			}
			std::optional<SignedNumber> rightOpt = integerCalculator.safeReadValue();

			if (rightOpt.has_value()) {
				SignedNumber right = rightOpt.value();
				FiniteNumber base = right.isPositive() ? left : left.inverse();
				PositiveNumber exponent = right.asPositive();
				Exponentiation exp;
				FiniteNumber result = exp.fastExponentiation(base, exponent);
				writeValue(result);
			}
			else {
				raiseError("Finite Field Visitor received no value from the right argument during exponentiation");
			}
			return;
		}
		FiniteNumber left = _visitAndGetValue(operation.left);
		FiniteNumber right = _visitAndGetValue(operation.right);
		FiniteNumber result;
		switch (binary) {
		case Operation::PLUS:
			result = left + right;
			break;
		case Operation::MINUS:
			result = left - right;
			break;
		case Operation::MULTIPLY:
			result = left * right;
			break;
		case Operation::DIVIDE:
			if (right.isZero()) {
				setError(merr::MathError(merr::MATH_ERROR, "Division by zero", &operation.loc()));
			}
			else {
				result = left / right;
			}
			break;
		case Operation::MODULO:
			setError(merr::MathError(merr::MATH_ERROR, "Modulo operation is not supported", &operation.loc()));
			break;
		default:
			raiseError("Unknown binary operation: " + operationStr, &operation.loc());
		}
		writeValue(result);
	}
	void FiniteFieldCalculator::visitUnary(UnaryNode& operation) {
		if (hasError()) {
			return;
		}
		Operation::UNARY_OPERATION unary = Operation::unary_from_string(operation.operation);
		FiniteNumber target = _visitAndGetValue(operation.target);
		FiniteNumber result;
		switch (unary) {
		case Operation::UMINUS:
			result = FiniteNumber("0", context.getField()) - target;
			break;
		case Operation::UPLUS:
			result = target;
			break;
		default:
			raiseError("Unknown unaryOperation operation: " + operation.operation, &operation.loc());
		}
		writeValue(result);
	}

	void FiniteFieldCalculator::visitFunction(FunctionNode& func) {
		if (hasError()) {
			return;
		}
		std::string name = func.functionName;
		if (func.isNamed("sqrt")) {
			if (_validateNumArguments(func, 1)) {
				return;
			}
			merr::ErrorPicker errorPicker;
			FiniteNumber a = _visitAndGetValue(func.arguments[0]);
			FiniteNumber b = CalculationOfSquareRoot::tonelli_shanks(a, errorPicker);
			this->testErrorPicker(errorPicker, &func.loc());
			writeValue(b);
		}
		else if (func.isNamed("eul")) {
			if (_validateNumArguments(func, 1)) {
				return;
			}
			std::optional<SignedNumber> signedNumberOpt = _visitSigned(func.arguments[0]);
			if (!signedNumberOpt) { return; }
			SignedNumber signedNumber = signedNumberOpt.value();
			if (signedNumber < SignedNumber(0)) {
				setError(merr::MathError(merr::CALCULATION_ERROR,
					"Cannot calculate Euler function for negative number: " + signedNumber.toString(), &func.loc()));
			}
			PositiveNumber positiveNumber = signedNumber.asPositive();
			PositiveNumber res = Euler(positiveNumber);
			writeValue(FiniteNumber(res, context.getField().getP()));
		}
		else if (func.isNamed("kar") || func.isNamed("car")) {
			if (_validateNumArguments(func, 1)) {
				return;
			}
			std::optional<SignedNumber> signedNumberOpt = _visitSigned(func.arguments[0]);
			if (!signedNumberOpt) {
				return;
			}
			SignedNumber signedNumber = signedNumberOpt.value();
			if (signedNumber < SignedNumber(0)) {
				setError(merr::MathError(merr::CALCULATION_ERROR,
					"Cannot calculate Karmichael function for negative number: " + signedNumber.toString(), &func.loc()));
			}
			PositiveNumber positiveNumber = signedNumber.asPositive();
			PositiveNumber res = Carmichel(positiveNumber);
			writeValue(FiniteNumber(res, context.getField().getP()));
		}
		else if (func.isNamed("log")) {
			if (_validateNumArguments(func, 2)) {
				return;
			}
			FiniteNumber a = _visitAndGetValue(func.arguments[0]);
			if (hasError()) {
				return;
			}
			FiniteNumber b = _visitAndGetValue(func.arguments[1]);
			if (hasError()) {
				return;
			}
			merr::ErrorPicker err;
			PositiveNumber f = Logarithm::log(a, b, err);
			testErrorPicker(err, &func.loc());
			writeValue(FiniteNumber(f, context.getField().getP()));
		}
		else {
			raiseError("Unknown function: " + func.functionName, &func.loc());
		}
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

	FiniteNumber FiniteFieldCalculator::_visitAndGetValue(ASTNode* node) {
		if (hasError()) {
			return FiniteNumber();
		}
		if (node == nullptr) {
			raiseError("Finite field visitor encountered null node");
			return FiniteNumber();
		}
		node->acceptVisitor(this);
		std::optional<FiniteNumber> optional = this->safeReadValue();
		if (optional.has_value()) {
			this->clearValue();
			return optional.value();
		}
		if (hasError()) {
			return FiniteNumber();
		}
		raiseError("Finite field visitor got no value after visiting " + node->str(), &node->loc());
		return FiniteNumber();
	}

	std::optional<SignedNumber> FiniteFieldCalculator::_visitSigned(ASTNode* target) {
		IntegerCalculator integerCalculator;
		target->acceptVisitor(&integerCalculator);
		if (integerCalculator.hasError()) {
			setError(integerCalculator.getError());
		}
		return integerCalculator.safeReadValue();
	}
}
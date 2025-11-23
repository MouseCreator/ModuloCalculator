#include "AST_Integer_Calculator.h"
#include "AST_Operation.h"
#include "Exponent.h"
#include "Logarithm.h"
#include "Euler.h"
#include <sstream>
namespace MathBase {

	void IntegerCalculator::visitNumber(NumberNode& number) {
		if (hasError()) {
			return;
		}
		SignedNumber signedNumber = SignedNumber(number.digits);
		writeValue(signedNumber);
	}
	
	void IntegerCalculator::visitOperation(OperationNode& operation) {
		if (hasError()) {
			return;
		}
		std::string operationString = operation.operation;
		Operation::BINARY_OPERATION binary = Operation::binary_from_string(operationString);
		SignedNumber left = this->_visitAndGetValue(operation.left);
		SignedNumber right = this->_visitAndGetValue(operation.right);
		SignedNumber result;
		if (hasError()) {
			return;
		}
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
		case Operation::EXPONENT:
		{
			Exponentiation exp;
			if (right < SignedNumber(0)) {
				std::stringstream ss;
				ss << "Cannot use negative power in exponent: " << left.toString() << "^" << right.toString();
				raiseError(ss.str(), &operation.loc());
				return;
			}
			result = exp.fastExponentiation(left, right.asPositive());
			break;
		}
		case Operation::MODULO:
			if (right.isZero()) {
				setError(merr::MathError(merr::MATH_ERROR, "Division by zero", &operation.loc()));
			}
			else {
				result = left % right;
			}
			break;
		default:
			raiseError("Unknown binary operation: " + operationString, &operation.loc());
		}
		writeValue(result);
	}
	void IntegerCalculator::visitUnary(UnaryNode& operation) {
		if (hasError()) {
			return;
		}
		std::string operationString = operation.operation;
		Operation::UNARY_OPERATION unary = Operation::unary_from_string(operationString);
		SignedNumber target = this->_visitAndGetValue(operation.target);
		SignedNumber result;
		if (hasError()) {
			return;
		}
		switch (unary) {
		case Operation::UPLUS:
			result = target;
			break;
		case Operation::UMINUS:
			result = SignedNumber() - target;
			break;
		default:
			raiseError("Unknown unary operation: " + operationString, &operation.loc());
		}
		writeValue(result);
	}
	void IntegerCalculator::visitFunction(FunctionNode& func) {
		if (hasError()) {
			return;
		}
		std::string name = func.functionName;
		if (func.isNamed("sqrt")) {
			if (_validateNumArguments(func, 1)) {
				return;
			}
			SignedNumber signedNumber = _visitAndGetValue(func.arguments[0]);
			merr::ErrorPicker err;
			PositiveNumber res = CalculationOfSquareRoot::newton_sqrt(signedNumber, err);
			testErrorPicker(err, &func.loc());
			writeValue(SignedNumber(res, PLUS));
		}
		else if (func.isNamed("eul")) {
			if (_validateNumArguments(func, 1)) {
				return;
			}
			SignedNumber signedNumber = _visitAndGetValue(func.arguments[0]);
			if (hasError()) {
				return;
			}
			if (signedNumber < SignedNumber(0)) {
				setError(merr::MathError(merr::CALCULATION_ERROR,
					"Cannot calculate Euler function for negative number: " + signedNumber.toString(), &func.loc()));
			}
			PositiveNumber positiveNumber = signedNumber.asPositive();
			PositiveNumber res = Euler(positiveNumber);
			writeValue(SignedNumber(res, PLUS));
		}
		else if (func.isNamed("kar") || func.isNamed("car")) {
			if (_validateNumArguments(func, 1)) {
				return;
			}
			SignedNumber signedNumber = _visitAndGetValue(func.arguments[0]);
			if (hasError()) {
				return;
			}
			if (signedNumber < SignedNumber(0)) {
				setError(merr::MathError(merr::CALCULATION_ERROR,
					"Cannot calculate Karmichael function for negative number: " + signedNumber.toString(), &func.loc()));
			}
			PositiveNumber positiveNumber = signedNumber.asPositive();
			PositiveNumber res = Carmichel(positiveNumber);
			writeValue(SignedNumber(res, PLUS));
		}
		else if (func.isNamed("log")) {
			if (_validateNumArguments(func, 2)) {
				return;
			}
			SignedNumber p = _visitAndGetValue(func.arguments[0]);
			if (hasError()) {
				return;
			}
			SignedNumber h = _visitAndGetValue(func.arguments[1]);
			if (hasError()) {
				return;
			}
			merr::ErrorPicker err;
			PositiveNumber result = Logarithm::log(p, h, err);
			testErrorPicker(err, &func.loc());
			writeValue(SignedNumber(result, PLUS));
		}
		else {
			raiseError("Unknown function: " + func.functionName, &func.loc());
		}
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
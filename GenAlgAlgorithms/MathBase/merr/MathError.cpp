#include "MathError.h"
#include <sstream>
namespace merr {
	MathError::MathError(MathErrorType type, std::string message, LocationStruct* loc) {
		this->type = type;
		this->message = message;
		if (loc != nullptr) {
			this->location = LocationStruct(*loc);
		}
		this->useLocation = (loc != nullptr);
	}

	std::string MathError::str() const {
		std::stringstream stream;
		stream << stringifyErrorType(this->type);
		if (!message.empty()) {
			stream << ": " << message;
		}
		if (useLocation) {
			stream << ". Error location: " << location;
		}
		return stream.str();
	}

	MathErrorType MathError::getType() const {
		return type;
	}

	ErrorFlag::ErrorFlag() {
		m_hasError = false;
		m_error = MathError();
	}
	void ErrorFlag::set(MathError error) {
		m_hasError = true;
		m_error = error;
	}
	void ErrorFlag::clr() {
		m_hasError = false;
		m_error = MathError();
	}
	MathError ErrorFlag::get() {
		return m_error;
	}
	bool ErrorFlag::hasError() {
		return m_hasError;
	}
	std::string ErrorFlag::str() const {
		return m_hasError ? m_error.str() : "No error";
	}

}

std::ostream& operator<<(std::ostream& os, const merr::MathError& error) {
	os << error.str();
	return os;
}
std::ostream& operator<<(std::ostream& os, const merr::ErrorFlag& error) {
	os << error.str();
	return os;
}
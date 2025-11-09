#include "errpick.h"

namespace merr {
	ErrorPicker::ErrorPicker(MathErrorType type, std::string message) {
		this->m_type = type;
		m_message = message;
		m_hasError = !message.empty();
	}
	void ErrorPicker::setMessage(std::string msg) {
		m_message = msg;
		m_hasError = true;
	}
	bool ErrorPicker::picked() {
		return m_hasError;
	}
	std::string ErrorPicker::getMessage() {
		return m_message;
	}
	MathErrorType ErrorPicker::getType() {
		return m_type;
	}
	void ErrorPicker::clear() {
		m_message = "";
		m_hasError = false;
	}


}
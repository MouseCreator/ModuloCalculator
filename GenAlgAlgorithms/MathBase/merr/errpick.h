#pragma once
#include "MathErrorType.h"
namespace merr {
	class ErrorPicker {
	private:
		std::string m_message;
		MathErrorType m_type;
		bool m_hasError;
	public:
		ErrorPicker(MathErrorType type = UNDEFINED_ERROR, std::string message = "");
		void setMessage(std::string message);
		bool picked();
		std::string getMessage();
		MathErrorType getType();
		void clear();
	};

}
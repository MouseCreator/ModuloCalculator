#pragma once

#include <iostream>
#include "errloc.h"
#include "../utils/StringPrintable.h"
#include "MathErrorType.h"
namespace merr {
	class MathError : public StringPrintable {
	private:
		MathErrorType type;
		std::string message;
		LocationStruct location;
		bool useLocation;
	public:
		MathError(MathErrorType type = UNDEFINED_ERROR, std::string message = "", LocationStruct* loc = nullptr);
		MathError(const MathError& other) {
			this->type = other.type;
			this->message = other.message;
			this->location = other.location;
			this->useLocation = other.useLocation;
		}
		std::string str() const override;
		MathErrorType getType() const;
	};

	class ErrorFlag : public StringPrintable {
	private:
		bool m_hasError;
		MathError m_error;
	public:
		ErrorFlag();
		void set(MathError error);
		void clr();
		MathError get();
		bool hasError();
		std::string str() const override;
	};
}
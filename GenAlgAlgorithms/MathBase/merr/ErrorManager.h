#pragma once
#include <iostream>
#include <vector>
#include "MathError.h"
#include "errpick.h"
namespace merr {
	class Errors {
	private:
		std::vector<merr::MathError> errors;
		std::string formatOutputError(const std::string& input);
	public:
		void addError(std::string s);
		void addError(merr::MathError e);
		void addError(merr::ErrorPicker p);
		bool hasError();
		std::vector<merr::MathError> getAllErrors();
		void clear();
		std::string concat();
	};
}
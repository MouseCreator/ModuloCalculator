#include "ErrorManager.h"

namespace merr {

	std::string Errors::formatOutputError(const std::string& input) {
		std::string result;
		size_t length = input.length();
		size_t i = 0;

		while (i < length) {
			if (input[i] == ';') {
				size_t start = i;
				while (i < length && input[i] == ';') {
					i++;
				}
				size_t count = i - start;
				result.append(count + 1, ';');
			}
			else {
				result += input[i];
				i++;
			}
		}

		return result;
	}
	void Errors::addError(std::string s) {
		merr::MathError instance = merr::MathError(merr::UNDEFINED_ERROR, s);
		errors.emplace_back(instance);
	}
	void Errors::addError(merr::ErrorPicker p) {
		merr::MathError instance = merr::MathError(p.getType(), p.getMessage());
		errors.emplace_back(instance);
	}
	void Errors::addError(merr::MathError e) {
		errors.emplace_back(e);
	}
	bool Errors::hasError() {
		return !errors.empty();
	}
	std::vector<merr::MathError> Errors::getAllErrors() {
		return errors;
	}
	void Errors::clear() {
		errors.clear();
	}
	std::string Errors::concat() {
		if (!hasError()) {
			return "";
		}
		std::size_t size = errors.size();
		std::string origin = formatOutputError(errors[0].str());
		for (std::size_t i = 1; i < size; i++) {
			std::string err = errors[i].str();
			std::string formatted = formatOutputError(err);
			origin += ";";
			origin += formatted;
		}
		return origin;
	}
}
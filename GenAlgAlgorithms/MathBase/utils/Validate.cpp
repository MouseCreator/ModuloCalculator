#include "Validate.h"
#include <sstream>
namespace Validate {

	void notZero(PositiveNumber positiveNumber, merr::ErrorPicker& errorPicker) {
		if (positiveNumber.isZero()) {
			errorPicker.setMessage("Unexpected zero input!");
		}
	}
	void notZero(SignedNumber signedNumber, merr::ErrorPicker& errorPicker) {
		if (signedNumber.isZero()) {
			errorPicker.setMessage("Unexpected zero input!");
		}
	}

	std::optional<SignedNumber> validateIsNumber(const std::string& number, merr::ErrorPicker& errorPicker) {
		if (number.empty()) {
			return SignedNumber(0);
		}
		std::size_t index = 0;
		if (number[0] == '-') {
			index++;
		}
		std::size_t len = number.length();
		std::stringstream ss;
		for (; index < len; index++) {
			char curr = number[index];
			if ('0' <= curr && curr <= '9') {
				continue;
			}
			ss << curr;
		}
		std::string extras = ss.str();
		if (extras.empty()) {
			return SignedNumber(number);
		}
		errorPicker.setMessage("The input is not a number: " + number + ". Extra symbols detected: " + extras);
		return {};
	}

	std::optional<PositiveNumber> validatePositiveNumber(const std::string& number, merr::ErrorPicker& errorPicker) {
		if (number.empty()) {
			return PositiveNumber(0);
		}
		std::size_t len = number.length();
		std::stringstream ss;
		for (std::size_t index = 0; index < len; index++) {
			char curr = number[index];
			if ('0' <= curr && curr <= '9') {
				continue;
			}
			ss << curr;
		}
		std::string extras = ss.str();
		if (extras.empty()) {
			return PositiveNumber(number);
		}
		errorPicker.setMessage("The input is not a positive number: " + number + ". Extra symbols detected: " + extras);
		return {};
	}

	std::optional<PositiveNumber> validatePositiveNumber(const char* number, merr::ErrorPicker& errorPicker) {
		return validatePositiveNumber(std::string(number), errorPicker);
	}
	std::optional<SignedNumber> validateIsNumber(const char* number, merr::ErrorPicker& errorPicker) {
		return validateIsNumber(std::string(number), errorPicker);
	}


	std::optional<int> validateInteger(const char* number, int maxDigits, merr::ErrorPicker& errorPicker) {
		return validateInteger(std::string(number), maxDigits, errorPicker);
	}
	std::optional<int> validateInteger(const std::string& number, int maxDigits, merr::ErrorPicker& errorPicker) {
		std::size_t size = number.size();
		std::string expectedMax;
		for (int i = 0; i < size; i++) {
			if (i > maxDigits) {
				errorPicker.setMessage("The input number is greater than expected maximum: " + expectedMax);
				return {};
			}
			expectedMax += "9";
			char curr = number[i];
			if ('0' <= curr && curr <= '9') {
				continue;
			}
			errorPicker.setMessage("Unexpected input symbol: " + curr);
			return {};
		}
		return std::stoi(number);
	}
}
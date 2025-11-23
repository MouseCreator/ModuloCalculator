#pragma once
#include "../merr/errpick.h"
#include "../SignedNumber.h"
#include <optional>
namespace Validate {
	std::optional<SignedNumber> validateIsNumber(const std::string& number, merr::ErrorPicker& errorPicker);
	std::optional<PositiveNumber> validatePositiveNumber(const std::string& number, merr::ErrorPicker& errorPicker);

	std::optional<SignedNumber> validateIsNumber(const char* number, merr::ErrorPicker& errorPicker);
	std::optional<PositiveNumber> validatePositiveNumber(const char* number, merr::ErrorPicker& errorPicker);

	std::optional<int> validateInteger(const char* number, int maxDigits, merr::ErrorPicker& errorPicker);
	std::optional<int> validateInteger(const std::string& number, int maxDigits, merr::ErrorPicker& errorPicker);
}
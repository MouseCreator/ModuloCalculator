#pragma once
#include "SignedNumber.h"
#include "merr/errpick.h"
namespace GenericMath {
	SignedNumber pow(SignedNumber number, SignedNumber power,merr::ErrorPicker& picker) {
		SignedNumber result = SignedNumber(1);
		if (power < SignedNumber()) {
			picker.setMessage("Negative power is not allowed.");
		}
		for (SignedNumber i = SignedNumber(); i <= power; i = i + SignedNumber(1)) {
			result = result * number;
		}
		return result;
	}
}
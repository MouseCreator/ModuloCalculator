#pragma once
#include "FiniteNumber.h"
#include "PositiveNumber.h"
#include "SignedNumber.h"
#include "CalculationOfSquareRoot.h"
#include "Exponent.h"

namespace Logarithm {
	PositiveNumber log(const FiniteNumber& g, const FiniteNumber& h, merr::ErrorPicker& err);
	PositiveNumber log(const PositiveNumber& g, const PositiveNumber& h);
	PositiveNumber log(const SignedNumber& g, const SignedNumber& h, merr::ErrorPicker& picker);
}
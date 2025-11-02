#pragma once
#include "Pollard.h"
#include "GCD.h"
#include "Exponent.h"

PositiveNumber EulerForPrimeValues(PositiveNumber number, PositiveNumber degree = PositiveNumber("1"));
PositiveNumber Euler(PositiveNumber number);
PositiveNumber CarmichelForPrimePower(PositiveNumber prime, PositiveNumber degree);
PositiveNumber Carmichel(PositiveNumber number);
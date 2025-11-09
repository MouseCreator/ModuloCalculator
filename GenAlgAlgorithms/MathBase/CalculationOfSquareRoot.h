#pragma once
#include "PositiveNumber.h"
#include "FiniteNumber.h"
#include "SignedNumber.h"
#include "merr/errpick.h"
namespace CalculationOfSquareRoot {
    PositiveNumber power_mod_internal(const PositiveNumber& a, const PositiveNumber& b, const PositiveNumber& n);
    PositiveNumber square_root_mod(const PositiveNumber& a, const PositiveNumber& p, merr::ErrorPicker& err);
    bool is_quadratic_residue(const PositiveNumber& a, const PositiveNumber& p);
    FiniteNumber tonelli_shanks(const FiniteNumber& n, merr::ErrorPicker& err);
    PositiveNumber newton_sqrt(const PositiveNumber& n, merr::ErrorPicker& err);
    PositiveNumber newton_sqrt(const SignedNumber& n, merr::ErrorPicker& err);
}
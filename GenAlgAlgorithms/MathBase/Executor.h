#pragma once
#include "merr/ErrorManager.h"
#include "SignedNumber.h"
#include "FiniteNumber.h"
#include "FactorizationEngine.h"
#include "OrderEngine.h"
class Executor {
public:
    SignedNumber random_prime(PositiveNumber* min, PositiveNumber* max, merr::Errors* errors);
    FiniteNumber finite_field(std::string expression, PositiveNumber* n, merr::Errors* errors);
    SignedNumber infinite_field(std::string expression, merr::Errors* errors);
    FactorizationResult to_factors(SignedNumber number, merr::Errors* errors);
    OrderResult find_order(FiniteNumber f, merr::Errors* errors);
    bool test_for_prime(PositiveNumber a, int iterations, merr::Errors* errors);
};
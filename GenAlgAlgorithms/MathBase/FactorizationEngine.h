#pragma once
#include "FactorizationResult.h"
#include "merr/ErrorManager.h"

class FactorizationEngine {
public:
	FactorizationResult toFactors(SignedNumber signedNumber, merr::Errors* err);
};
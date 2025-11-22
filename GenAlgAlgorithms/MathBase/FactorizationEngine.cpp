#include "FactorizationEngine.h"
#include "Pollard.h"

FactorizationResult FactorizationEngine::toFactors(SignedNumber signedNumber, merr::Errors* err) {
	FactorizationResult result;
	bool negative = signedNumber.isNegative();
	PositiveNumber p = signedNumber.asPositive();
	std::vector<PositiveNumber> numbers = PollardFactorization::pollardRho(p);

	std::vector<SignedNumber> signedRes;
	for (PositiveNumber positive : numbers) {
		signedRes.emplace_back(SignedNumber(positive, PLUS));
	}
	if (signedRes.size() > 0 && negative) {
		signedRes[0].flipSign();
	}
	result.addFactors(signedRes);
	return result;
}
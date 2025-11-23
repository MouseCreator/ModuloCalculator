#include "PrimeTestEngine.h"
#include "MillerRabin.h"

inline bool PrimeTest::testIfPrime(PositiveNumber n, int iterations) {
	return MillerRabin::miller_rabin(n, iterations);
}
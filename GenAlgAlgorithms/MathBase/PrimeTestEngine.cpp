#include "PrimeTestEngine.h"
#include "MillerRabin.h"

bool PrimeTest::testIfPrime(PositiveNumber n, int iterations) {
	return MillerRabin::miller_rabin(n, iterations);
}
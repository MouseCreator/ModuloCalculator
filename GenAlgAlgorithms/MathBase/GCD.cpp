#include "GCD.h"
namespace gcd {

	PositiveNumber GCD(PositiveNumber n1, PositiveNumber n2) {
		if (n1 == 0)
			return n2;

		return GCD(n2 % n1, n1);
	}
	PositiveNumber LCM(PositiveNumber n1, PositiveNumber n2) {
		PositiveNumber gcd = GCD(n1, n2);
		PositiveNumber res = (n1 * n2) / gcd;
		return res;
	}
}
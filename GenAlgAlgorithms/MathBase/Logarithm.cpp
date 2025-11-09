#include "Logarithm.h"

namespace Logarithm {

	void f(PositiveNumber* x, PositiveNumber* a, PositiveNumber* b, const FiniteNumber& g, const FiniteNumber& h, PositiveNumber* Q) {
		PositiveNumber _3("3");
		PositiveNumber _1("1");
		PositiveNumber _0("0");
		PositiveNumber _2("2");

		PositiveNumber sub = (*x) % _3;

		if (sub == _0) {
			/**x = ((*x) * g.asPositive()) % g.getP();
			*a = ((*a) + _1) % (*Q);*/
			*x = (*x) * (*x) % g.getP();
			*a = (*a) * _2 % (*Q);
			*b = (*b) * _2 % (*Q);
		}
		else if (sub == _1) {
			/**x = ((*x) * h.asPositive()) % g.getP();
			*b = ((*b) + _1) % (*Q);*/
			*x = (*x) * g.asPositive() % g.getP();
			*a = ((*a) + _1) % (*Q);
		}
		else {
			/**x = ((*x) * (*x)) % g.getP();
			*a = ((*a) * _2) % (*Q);
			*b = ((*b) * _2) % (*Q);*/
			(*x) = (*x) * h.asPositive() % h.getP();
			(*b) = ((*b) + _1) % (*Q);
		}
	}

	PositiveNumber naive_log(const FiniteNumber& G, const FiniteNumber& H, merr::ErrorPicker& err) {
		PositiveNumber _1(1);
		PositiveNumber res(1);
		FiniteNumber g_c = G;
		FiniteNumber h_c = H;
		err.clear();
		while (g_c != h_c)
		{
			res += _1;
			g_c *= G;
		}
		return res;
	}

	PositiveNumber pollard(const FiniteNumber& G, const FiniteNumber& H, merr::ErrorPicker& err) {
		PositiveNumber _0(0);
		PositiveNumber _1(1);
		PositiveNumber _2(2);
		PositiveNumber Q = G.getP() - _1;

		PositiveNumber x = G.asPositive() * H.asPositive();
		PositiveNumber X = x;
		PositiveNumber a(1);
		PositiveNumber A(1);
		PositiveNumber b(1);
		PositiveNumber B(1);

		PositiveNumber i(1);
		for (; i < G.getP(); i += _1) {
			f(&x, &a, &b, G, H, &Q);
			f(&X, &A, &B, G, H, &Q);
			f(&X, &A, &B, G, H, &Q);
			if (x == X) {
				break;
			}
		}

		if (b == B) {
			err.setMessage("Logarithm does not exist");
			return _0;
		}

		FiniteNumber a_A(SignedNumber(a.toString()) - SignedNumber(A.toString()), G.getP() - _1);
		FiniteNumber B_b(SignedNumber(B.toString()) - SignedNumber(b.toString()), G.getP() - _1);
		if (gcd::GCD(B_b.asPositive(), B_b.getP()) != _1) {
			err.setMessage("Inverse_error");
			return _1;
		}
		FiniteNumber res = a_A / B_b;
		return res.asPositive();
	}

	//Pollard-Rho's algorithm for logarithm
	PositiveNumber log(const FiniteNumber& G, const FiniteNumber& H, merr::ErrorPicker& err) {
		PositiveNumber res = pollard(G, H, err);
		if (err.picked() == true && err.getMessage() == "Inverse_error") {
			res = naive_log(G, H, err);
		}
		return res;
	}

	PositiveNumber log(const PositiveNumber& g, const PositiveNumber& h) {
		PositiveNumber _1(1);
		PositiveNumber g_c = g;
		PositiveNumber res(0);
		while (g_c <= h)
		{
			res += _1;
			g_c *= g;
		}
		return res;
	}

	PositiveNumber log(const SignedNumber& g, const SignedNumber& h, merr::ErrorPicker& picker) {
		if (g.isNegative() || h.isNegative()) {
			picker.setMessage("Base or result is negative");
			return PositiveNumber(0);
		}
		return log(g.asPositive(), h.asPositive());
	}
}
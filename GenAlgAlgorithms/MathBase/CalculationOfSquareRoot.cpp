#include "CalculationOfSquareRoot.h"
#include "merr/errpick.h"
#include "FiniteNumber.h"
#include "Exponent.h"
namespace CalculationOfSquareRoot {

    PositiveNumber power_mod_internal(const PositiveNumber& base, const PositiveNumber& exponent, const PositiveNumber& mod) {
        PositiveNumber result(1);
        PositiveNumber b = base % mod;
        PositiveNumber e = exponent;

        while (e > 0) {
            if (e % PositiveNumber(2) != 0) {
                result = (result * b) % mod;
            }
            b = (b * b) % mod;
            e = e / PositiveNumber(2);
        }
        return result;
    }

    PositiveNumber square_root_mod(const PositiveNumber& a, const PositiveNumber& p, merr::ErrorPicker& err) {

        if (!is_quadratic_residue(a, p)) {
            err.setMessage("Square root does not exist");
            return PositiveNumber(0);
        }

        if ((p % 4) == 3) {
            return power_mod_internal(a, (p + 1) / PositiveNumber(4), p);
        }

        PositiveNumber s = p - 1;
        PositiveNumber e(0);
        while ((s % PositiveNumber(2)) == 0) {
            s = s / PositiveNumber(2);
            e = e + PositiveNumber(1);
        }

        PositiveNumber n(2);
        while (is_quadratic_residue(n, p)) {
            n = n + PositiveNumber(1);
        }

        PositiveNumber x = power_mod_internal(a, (s + 1) / PositiveNumber(2), p);
        PositiveNumber b = power_mod_internal(a, s, p);
        PositiveNumber g = power_mod_internal(n, s, p);
        PositiveNumber r = e;

        while (b != PositiveNumber(1)) {
            PositiveNumber m(0);
            PositiveNumber temp = b;
            while (temp != PositiveNumber(1) && m < r) {
                temp = (temp * temp) % p;
                m = m + PositiveNumber(1);
            }
            PositiveNumber shift_value = power_mod_internal(PositiveNumber(2), r - m - PositiveNumber(1), p);
            PositiveNumber t = power_mod_internal(g, shift_value, p);
            g = (t * t) % p;
            x = (x * t) % p;
            b = (b * g) % p;
            r = m;
        }
        return x;
    }

    bool is_quadratic_residue(const PositiveNumber& a, const PositiveNumber& p) {
        return power_mod_internal(a, (p - 1) / PositiveNumber(2), p) == PositiveNumber(1);
    }

    PositiveNumber newton_sqrt(const SignedNumber& n, merr::ErrorPicker& err) {
        if (!n.isPositive()) {
            err.setMessage("Square root does not exist : number is negative");
            return PositiveNumber("0");
        }
        else {
            return newton_sqrt(n.asPositive(), err);
        }
    }

    PositiveNumber newton_sqrt(const PositiveNumber& n, merr::ErrorPicker& err) {
        PositiveNumber _2("2");
        if (n == _2) {
            return n;
        }

        PositiveNumber x = n;

        while (true)
        {
            PositiveNumber next_x = (x + n / x) / _2;
            if (next_x == x) {
                break;
            }
            x = next_x;
        }
        return x;
    }

    FiniteNumber tonelli_shanks(const FiniteNumber& n, merr::ErrorPicker& err) {
        Exponentiation exp;
        PositiveNumber _2 = PositiveNumber(2);
        PositiveNumber _1 = PositiveNumber(1);
        PositiveNumber _0 = PositiveNumber(0);

        if ((exp.fastExponentiation(n, (n.getP() - _1) / _2)).asPositive() != _1) {
            err.setMessage("Square root does not exist : number is not a quadratic risidue");
            return FiniteNumber("0", n.getP());
        }


        PositiveNumber s = PositiveNumber(0);
        PositiveNumber q = n.getP() - _1;
        while (q % _2 == _0) {
            s = s + _1;
            q = q / _2;
        }
        FiniteNumber z("2", n.getP());
        while (exp.fastExponentiation(z, (n.getP() - _1) / _2).asPositive() != (n.getP() - _1))
        {
            z = z + FiniteNumber(_1, n.getP());
        }

        PositiveNumber m = s;
        FiniteNumber c = exp.fastExponentiation(z, q);
        FiniteNumber t = exp.fastExponentiation(n, q);
        FiniteNumber r = exp.fastExponentiation(n, (q + _1) / _2);

        while (t.asPositive() != _1)
        {
            FiniteNumber t2i = t;
            PositiveNumber i(1);
            for (; i < m; i = i + _1) {
                t2i = exp.fastExponentiation(t2i, _2);
                if (t2i.asPositive() == _1) {
                    break;
                }
            }
            FiniteNumber b = exp.fastExponentiation(c, exp.fastExponentiation(_2, m - i - _1));
            m = i;
            c = exp.fastExponentiation(b, _2);
            t = t * c;
            r = r * b;
        }
        return r;
    }


}
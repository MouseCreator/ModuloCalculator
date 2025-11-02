#pragma once
#include <cassert>
#include "FiniteField.h"
#include "SignedNumber.h"
#include "GCD.h"

class FiniteNumber : public PositiveNumber {
private: 
	//p stands for field
	FiniteField f;
	void setP(PositiveNumber p, bool gotNegativeBase = false) {
		f.setP(p);
		toFieldSize(gotNegativeBase);
	}

public:
	FiniteNumber() {}

	FiniteNumber(PositiveNumber base, PositiveNumber p) {
		f = (FiniteField(p));
		this->digits = base.getDigits();
		toFieldSize();
	}
	FiniteNumber(SignedNumber base, PositiveNumber p) {
		f = (FiniteField(p));
		if (base.isPositive()) {
			this->digits = base.asPositive().getDigits();
			toFieldSize();
		}
		else {
			PositiveNumber pos = base.asPositive();
			PositiveNumber base_positive = p - (pos % p);
			this->digits = base_positive.getDigits();
		}
	}
	FiniteNumber(std::vector<int> v, FiniteField f_) : f(f_.getP()) {
		digits = v;
		toFieldSize();
	}
	PositiveNumber asPositive() const{
		return PositiveNumber(this->digits);
	}
	FiniteNumber(std::string digits, FiniteField f_) : f(f_.getP()) {
		initDigits(digits, f.getP());
	}
	FiniteNumber(int number, FiniteField f_) : f(f_.getP()) {
		std::string digits = std::to_string(number);
		initDigits(digits, f.getP());
	}
	FiniteNumber(std::string from, PositiveNumber p) {
		initDigits(from, p);
	}
	void initDigits(std::string from, PositiveNumber p) {
		bool negativeBase = parseIsNegative(from);
		this->digits = parseDigits(from);
		toFieldSize();
		setP(p, negativeBase);
	}
	FiniteNumber(char* from, PositiveNumber p) {
		std::string str = std::string(from);
		initDigits(str, p);
	}

	FiniteNumber(long long a, long long p) : PositiveNumber(a) {
		this->f = FiniteField(PositiveNumber(p));
		toFieldSize();
	}

	/**
	* Input: string of value "xP N", where P - is field size, N - positive integer
	* Alternative: "N xP"
	* Alternative: "P N"
	*/
	FiniteNumber(std::string from) {
		std::string partOne = from.substr(0, from.find_first_of(' '));
		std::string partTwo = from.substr(from.find_first_of(' ') + 1);
		std::string p;
		std::string n;
		if (partOne[0] == 'x') {
			p = partOne.substr(1);
			n = partTwo;
		}
		else if (partTwo[0] == 'x') {
			p = partTwo.substr(1);
			n = partOne;
		}
		else {
			p = partOne;
			n = partTwo;
		}
		bool negativeBase = parseIsNegative(from);
		this->digits = parseDigits(n);
		setP(p, negativeBase);
	}

	PositiveNumber getP() const {
		return f.getP();
	}



	/*
	* overloaded operators
	*/
	friend FiniteNumber operator+(FiniteNumber left, const FiniteNumber& n) {
		left.addTo(n);
		left.toFieldSize();
		return left;
	}

	FiniteNumber& operator+=(const FiniteNumber& n) {
		this->addTo(n);
		this->toFieldSize();
		return *this;
	}
	friend FiniteNumber operator*(FiniteNumber left, const FiniteNumber& n) {
		return left.toFinite(left.simpleMultiplication(n));
	}
	//FiniteNumber operator*(const FiniteNumber& n) {
	//	return this->toFinite(simpleMultiplication(n));
	//}
	FiniteNumber operator*=(const FiniteNumber& n) {
		this->multiplyBy(n);
		this->toFieldSize();
		return *this;
	}
	friend FiniteNumber operator-(FiniteNumber left, const FiniteNumber& n) {
		bool is_greater = true;
		FiniteNumber n_copy = n;
		if (left < n_copy) {
			is_greater = false;
		}
		left.subtract(n);
		if (is_greater) {
			left.toFieldSize();
			return left;
		}
		else {
			return FiniteNumber(left.getP() - left, left.getP());
		}
		
	}

	FiniteNumber& operator-=(const FiniteNumber& n) {
		bool is_greater = true;
		FiniteNumber n_copy = n;
		if (*this < n_copy) {
			is_greater = false;
		}
		this->subtract(n);
		if (is_greater) {
			this->toFieldSize();
			return *this;
		}
		else {
			*this = FiniteNumber(this->getP() - *this, this->getP());
			return *this;
		}
	}

	friend FiniteNumber operator/(FiniteNumber left, const FiniteNumber& n) {
		left.divideBy(n);
		left.toFieldSize();
		return left;
	}


	bool operator==(const FiniteNumber& n) const {
		return this->equals(const_cast<FiniteNumber&>(n)) && this->getP().equals(const_cast<FiniteNumber&>(n).getP());
	}

	bool operator>(FiniteNumber& n) const {
		PositiveNumber p1 = getP();
		PositiveNumber p2 = n.getP();
		if (p1 != p2)
			return false;
		return PositiveNumber::operator>(n);
	}

	bool operator>=(FiniteNumber& n) const {
		PositiveNumber p1 = getP();
		PositiveNumber p2 = n.getP();
		if (p1 != p2)
			return false;
		return PositiveNumber::operator<=(n);
	}
	bool operator<(FiniteNumber& n) const {
		PositiveNumber p1 = getP();
		PositiveNumber p2 = n.getP();
		if (p1 != p2)
			return false;
		return PositiveNumber::operator<(n);
	}
	bool operator<=(FiniteNumber& n) const {
		PositiveNumber p1 = getP();
		PositiveNumber p2 = n.getP();
		if (p1 != p2)
			return false;
		return PositiveNumber::operator<=(n);
	}


	bool operator==(FiniteNumber& n) const {
		return equals(n);
	}
	bool operator!=(FiniteNumber& n) const {
		return !equals(n);
	}
	bool equals(FiniteNumber& n) const {
		PositiveNumber p1 = getP();
		PositiveNumber p2 = n.getP();
		if (p1 != p2)
			return false;
		return PositiveNumber::equals(n);
	}


	bool operator!=(const FiniteNumber& n) const {
		return !(*this == n);
	}



	/*
	* Find inverse number
	* if inverse number exists - finds inverse, else - returns 1
	*/
	FiniteNumber inverse() {
		PositiveNumber p = getP();
		PositiveNumber n = getP();
		PositiveNumber g(this->toString());
		PositiveNumber gcd = gcd::GCD(n, g);
		if (g.toString() == "1" || gcd.toString() != "1") {
			return FiniteNumber("1", getP());
		}
		// remainder = (t0*n + s0*g) + d*(t1*n + s1*g)
		// t0 and t1 are omitted because we don`t need them
		SignedNumber s0("0"), s1("1");
		while (true) {
			SignedNumber d("0");

			d = SignedNumber("-1") * (n / g);
			n -= (d * g).asPositive();
			SignedNumber temp_s = s0;
			s0 = s1;
			d.multiplyBy(s1);
			s1 = temp_s;
			s1.addTo(d);
			if (n.toString() == "1") {
				break;
			}
			else {
				PositiveNumber temp = n;
				n = g;
				g = temp;
			}
		}
		if (s1.getSign() == Sign::MINUS) {
			PositiveNumber s1_pos(s1.asPositive());
			while (s1_pos > p) {
				s1_pos -= p;
			}
			return FiniteNumber((p - s1_pos), p);
		}
		else {
			return FiniteNumber(s1, p);
		}
	}

	void divideBy(FiniteNumber num) {
		PositiveNumber p1 = getP();
		PositiveNumber p2 = num.getP();
		if (p1 != p2) {
			return;
		}
		*this *= num.inverse();
	}

	FiniteNumber divide(FiniteNumber num) {
		PositiveNumber p1 = getP();
		PositiveNumber p2 = num.getP();
		if (p1 != p2) {
			return FiniteNumber("1", this->getP());
		}
		return *this * num.inverse();
	}
	//Converts PositiveNumber to field size
	void toFieldSize(bool gotNegativeBase = false) {
		PositiveNumber p = getP();

		if (gotNegativeBase) { //Negative base
			PositiveNumber t = PositiveNumber(*this);
			if (t == p) {
				t = t % (p);
			}
			else {
				t = p - (t % (p));
			}
			this->digits = t.getDigits();
		}
		else { //Positive base
			if (p > *this) { //mod is greater than base
				return;
			}
			else { //otherwise
				PositiveNumber t = PositiveNumber(*this);
				t = t % (p);
				this->digits = t.getDigits();
			}
		}
	}
	// Converts PositiveNumber to FiniteNumber
	FiniteNumber toFinite(PositiveNumber num) {
		PositiveNumber p = getP();
		FiniteNumber res(num.toString(), p);
		res.toFieldSize();
		return res;
	}

	void toFieldSize(std::string p_str, std::string n_str) {
		PositiveNumber p = PositiveNumber(p_str);
		PositiveNumber n = PositiveNumber(n_str);
		if (p > n) {
			return;
		}
		else {
			n = n % p;
			this->digits = n.getDigits();
		}
	}

	FiniteNumber shift(int numDigits) {
		PositiveNumber p = getP();
		FiniteNumber number = FiniteNumber(*this);
		if (numDigits < 0) {
			for (int i = 0; i < -numDigits && number.digits.size()>0; i++) {
				number.digits.erase(number.digits.begin());
			}
		}
		else {
			for (int i = 0; i < numDigits; i++) {
				number.digits.insert(number.digits.begin(), 0);
			}
		}
		return FiniteNumber(number, p);
	}

	static bool parseIsNegative(std::string str) {

		bool gotMinus = false;

		for (char ch : str) {
			if (ch == '-') {
				if (gotMinus) {
					throw std::runtime_error("Incorrect argument syntax");
				}
				else {
					gotMinus = true;
				}
			}
		}

		return gotMinus;
	}
};

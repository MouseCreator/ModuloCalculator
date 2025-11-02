#pragma once
#include "PositiveNumber.h"
enum Sign { PLUS, MINUS };
class SignedNumber {
private:
	PositiveNumber positive;
	Sign sign = Sign::PLUS;

	void zeroSignCheck() {
		if (positive.isZero()) {
			sign = Sign::PLUS;
		}
	}

public:
	SignedNumber() {
		positive = PositiveNumber();
		sign = Sign::PLUS;
	}
	SignedNumber(long long s) {
		positive = PositiveNumber();
		sign = Sign::PLUS;
	}
	SignedNumber(std::string str) {
		if (str[0] == '-') {
			str = str.substr(1);
			this->sign = Sign::MINUS;
		}
		this->positive = PositiveNumber(str);
	}
	SignedNumber(PositiveNumber absolute, Sign sign) {
		this->sign = sign;
		this->positive = absolute;
	}

	friend SignedNumber operator+(SignedNumber left, const SignedNumber& n) {
		left.addTo(n);
		left.zeroSignCheck();
		return left;
	}
	friend SignedNumber operator+(SignedNumber left, const PositiveNumber& n) {
		left.addTo(SignedNumber(n, Sign::PLUS));
		left.zeroSignCheck();
		return left;
	}
	friend SignedNumber operator+(PositiveNumber left, const SignedNumber& n) {
		return n + left;
	}
	SignedNumber& operator+=(const SignedNumber& n) {
		this->addTo(n);
		zeroSignCheck();
		return *this;
	}
	SignedNumber& operator+=(const PositiveNumber& n) {
		this->addTo(SignedNumber(n, Sign::PLUS));
		zeroSignCheck();
		return *this;
	}
	SignedNumber operator*(const SignedNumber& n) {
		PositiveNumber p = positive * n.positive;
		SignedNumber result = SignedNumber(p, (this->sign == n.sign) ? Sign::PLUS : Sign::MINUS);
		result.zeroSignCheck();
		return result;
	}
	friend SignedNumber operator*(const SignedNumber& left, const SignedNumber& right) {
		PositiveNumber p = left.positive * right.positive;
		SignedNumber result = SignedNumber(p, (left.sign == right.sign) ? Sign::PLUS : Sign::MINUS);
		result.zeroSignCheck();
		return result;
	}
	SignedNumber operator*(const PositiveNumber& n) {
		SignedNumber result = SignedNumber(this->positive * n, this->sign);
		result.zeroSignCheck();
		return result;
	}
	SignedNumber operator*=(const SignedNumber& n) {
		this->multiplyBy(n);
		zeroSignCheck();
		return *this;
	}
	SignedNumber operator*=(const PositiveNumber& n) {
		this->multiplyBy(SignedNumber(n, Sign::PLUS));
		zeroSignCheck();
		return *this;
	}
	friend SignedNumber operator-(SignedNumber left, const SignedNumber& n) {
		left.subtractFrom(n);
		left.zeroSignCheck();
		return left;
	}
	friend SignedNumber operator-(SignedNumber left, const PositiveNumber& n) {
		left.subtractFrom(SignedNumber(n, Sign::PLUS));
		left.zeroSignCheck();
		return left;
	}
	friend SignedNumber operator-(PositiveNumber left, const SignedNumber& n) {
		SignedNumber result = SignedNumber(left, Sign::PLUS);
		result.subtractFrom(n);
		result.zeroSignCheck();
		return result;
	}
	SignedNumber& operator-=(const SignedNumber& n) {
		this->subtractFrom(n);
		zeroSignCheck();
		return *this;
	}
	SignedNumber& operator-=(const PositiveNumber& n) {
		this->subtractFrom(SignedNumber(n, Sign::PLUS));
		zeroSignCheck();
		return *this;
	}

	bool isPositive() const{
		return this->sign == Sign::PLUS;
	}
	bool isNegative() const{
		return this->sign == Sign::MINUS;
	}
	bool operator==(SignedNumber& n) const {
		return equals(n);
	}
	bool operator!=(SignedNumber& n) const {
		return !equals(n);
	}
	bool operator==(PositiveNumber& n) const {
		return equals(SignedNumber(n, Sign::PLUS));
	}
	bool operator!=(PositiveNumber& n) const {
		return !equals(SignedNumber(n, Sign::PLUS));
	}
	bool operator>(SignedNumber& n) const {
		if (n.sign == Sign::PLUS && this->sign == Sign::MINUS)
			return false;
		else if (this->sign == Sign::PLUS && n.sign == Sign::MINUS) {
			return true;
		}
		return positive > n.positive;
	}
	bool operator>(PositiveNumber& n) const {
		SignedNumber a = SignedNumber(n, Sign::PLUS);
		return operator>(a);
	}
	bool operator>=(PositiveNumber& n) const {
		SignedNumber a = SignedNumber(n, Sign::PLUS);
		return operator>=(a);
	}
	bool operator<(PositiveNumber& n) const {
		SignedNumber a = SignedNumber(n, Sign::PLUS);
		return operator<(a);
	}
	bool operator<=(PositiveNumber & n) const {
		SignedNumber a = SignedNumber(n, Sign::PLUS);
		return operator<=(a);
	}
	bool operator>=(SignedNumber& n) const {
		if (n.sign == Sign::PLUS && this->sign == Sign::MINUS)
			return false;
		else if (this->sign == Sign::PLUS && n.sign == Sign::MINUS) {
			return true;
		}
		return positive<=n.positive;
	}
	bool operator<(SignedNumber& n) const {
		if (n.sign == Sign::PLUS && this->sign == Sign::MINUS)
			return true;
		else if (this->sign == Sign::PLUS && n.sign == Sign::MINUS) {
			return false;
		}
		return positive<n.positive;
	}
	bool operator<(const SignedNumber& n) const {
        if (n.sign == Sign::PLUS && this->sign == Sign::MINUS)
			return true;
		else if (this->sign == Sign::PLUS && n.sign == Sign::MINUS) {
			return false;
		}
		return positive<n.positive;	
    }
	bool operator<=(SignedNumber& n) const {
		if (n.sign == Sign::PLUS && this->sign == Sign::MINUS)
			return true;
		else if (this->sign == Sign::PLUS && n.sign == Sign::MINUS) {
			return false;
		}
		return positive<=n.positive;
	}

	bool equals(SignedNumber n) const {
		if (this->sign != n.sign)
			return false;
		return n.positive == positive;
	}
	void addTo(SignedNumber other) {
		if (this->sign == other.sign) {
			positive.addTo(other.positive);
		}
		else {
			this->sign = positive > other.positive ? this->sign : other.sign;
			positive.subtract(other.positive);
		}

	}
	void subtractFrom(SignedNumber other) {
		if (this->sign == other.sign) {
			bool needsFlip = positive<other.positive;
			positive.subtract(other.positive);
			if (needsFlip) {
				flipSign();
			}
		}
		else {
			positive.addTo(other.positive);
		}
	}
	std::string toString() {
		std::string s = sign == Sign::PLUS ? "" : "-";
		s += positive.toString();
		return s;
	}
	void flipSign() {
		if (this->positive.getDigits().size() == 0) //is zero
			this->sign = Sign::PLUS;
		if (this->sign == Sign::MINUS)
			this->sign = Sign::PLUS;
		else
			this->sign = Sign::MINUS;
	}
	void multiplyBy(SignedNumber other) {
		positive.multiplyBy(other.positive);
		this->sign = (this->sign == other.sign) ? Sign::PLUS : Sign::MINUS;
	}


	//Division for SignedNumbers
	SignedNumber operator/(const SignedNumber& other) const{
		return divide(*this, other);
	}

	PositiveNumber toUnsigned() {
		if (this->sign == Sign::MINUS) {
			return PositiveNumber(this->toString().substr(1, this->positive.getDigits().size()));
		}
		else {
			return PositiveNumber(this->toString());
		}
	}

	SignedNumber divide(SignedNumber n1, SignedNumber n2) const{
		PositiveNumber p1 = n1.toUnsigned();
		PositiveNumber p2 = n2.toUnsigned();
		PositiveNumber num = p1 / p2;
		if (n1.sign != n2.sign && !num.isZero()) {
			return SignedNumber(num, Sign::MINUS);
		}
		else {
			return SignedNumber(num, Sign::PLUS);
		}
	}

	SignedNumber operator%(SignedNumber& other) {
		return remainder(*this, other);
	}

	SignedNumber remainder(SignedNumber n1, SignedNumber n2) {
		PositiveNumber p1 = n1.toUnsigned();
		PositiveNumber p2 = n2.toUnsigned();
		PositiveNumber num = p1 % p2;
		if (n1.sign == Sign::MINUS && !num.isZero()) {
			return SignedNumber(num, Sign::MINUS);
		}
		else {
			return SignedNumber(num, Sign::PLUS);
		}
	}
	bool isZero() {
		return positive.isZero();
	}
	Sign getSign() {
		return this->sign;
	}

	PositiveNumber asPositive() const{
		return PositiveNumber(positive);
	}

};

#pragma once
#include "PositiveNumber.h"

class FiniteField
{
private:
	PositiveNumber p;
public:
	//Constructor
	FiniteField() {
		p = PositiveNumber();
	}
	FiniteField(PositiveNumber p_) {
		p = p_;
	}
	//Getter
	PositiveNumber getP() const{
		return p;
	}
	//Setter
	void setP(PositiveNumber p) {
		this->p = p;
	}
	//Check whether it is the same field
	bool operator == (FiniteField& left) const{
		if (p != left.p) {
			return false;
		}
		return true;
	}

};


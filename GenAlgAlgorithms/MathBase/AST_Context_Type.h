#pragma once
#include "FiniteField.h"
class Context {
};

class FiniteFieldContext : public Context {
private:
	FiniteField field;
public:
	FiniteField getField() const;
	FiniteFieldContext();
	FiniteFieldContext(FiniteField field);
};
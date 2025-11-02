#include "AST_Context_Type.h"

FiniteField FiniteFieldContext::getField() const {
	return this->field;
}
FiniteFieldContext::FiniteFieldContext(FiniteField field) {
	this->field = field;
}
FiniteFieldContext::FiniteFieldContext() {
	this->field = FiniteField(0);
}

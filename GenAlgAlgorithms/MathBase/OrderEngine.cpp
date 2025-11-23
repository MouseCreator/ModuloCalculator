#include "OrderEngine.h"
#include "FiniteGroup.h"

OrderResult::OrderResult(PositiveNumber order, bool generator) {
	this->order = order;
	this->isGenerator = generator;
}

std::string OrderResult::toString() {
	std::string number = order.toString();
	std::string generator = isGenerator ? "1" : "0";
	return number + ":" + generator;
}

OrderResult OrderEngine::orderAndGenerator(FiniteNumber finiteNumber, merr::Errors* err) {
	FiniteField field = FiniteField(finiteNumber.getP());
	FiniteGroup g = FiniteGroup(field);
	PositiveNumber order = g.ElementOrder(finiteNumber);
	bool generator = g.isGenerator(finiteNumber);
	return OrderResult(order, generator);
}
#include "Executor.h"
#include "AST_Context_Type.h"
#include "InterpretationManager.h"
#include "AST_FiniteFieldCalculator.h"
#include "AST_Integer_Calculator.h"
#include "PrimeTestEngine.h"

SignedNumber Executor::random_prime(PositiveNumber* min, PositiveNumber* max, merr::Errors* errors) {
    return SignedNumber(0);
}

FiniteNumber Executor::finite_field(std::string expression, PositiveNumber* n, merr::Errors* errors) {
    FiniteNumber result = FiniteNumber("0", FiniteField(*n));
    InterpretationManager interpretationManager;
    std::optional<MathBase::AST*> astOptional = interpretationManager.parseInput(expression, errors);
    FiniteField field = FiniteField(*n);
    if (!astOptional) {
        if (!errors->hasError()) {
            errors->addError("An error occurred parsing input expression: " + expression);
        }
        return FiniteNumber("0", field);
    }

    FiniteFieldContext context = FiniteFieldContext(field);
    MathBase::AST* ast = astOptional.value();
    MathBase::FiniteFieldCalculator* calculator = new MathBase::FiniteFieldCalculator(context);

    ast->acceptVisitor(calculator);
    if (calculator->hasError()) {
        merr::MathError err = calculator->getError();
        errors->addError(err);
    }
    else {
        result = calculator->readValue();
    }

    delete ast;
    delete calculator;
    return result;
}

SignedNumber Executor::infinite_field(std::string expression, merr::Errors* errors) {
    SignedNumber result = SignedNumber("0");
    InterpretationManager interpretationManager;
    std::optional<MathBase::AST*> astOptional = interpretationManager.parseInput(expression, errors);
    if (!astOptional) {
        if (!errors->hasError()) {
            errors->addError("An error occurred parsing input expression: " + expression);
        }
        return SignedNumber("0");
    }

    MathBase::AST* ast = astOptional.value();
    MathBase::IntegerCalculator* calculator = new MathBase::IntegerCalculator();

    ast->acceptVisitor(calculator);
    if (calculator->hasError()) {
        merr::MathError err = calculator->getError();
        errors->addError(err);
    }
    else {
        result = calculator->readValue();
    }

    delete ast;
    delete calculator;
    return result;
}

FactorizationResult Executor::to_factors(SignedNumber number, merr::Errors* errors) {
    FactorizationEngine engine;
    return engine.toFactors(number, errors);
}

OrderResult Executor::find_order(FiniteNumber f, merr::Errors* errors) {
    OrderEngine engine;
    return engine.orderAndGenerator(f, errors);
}

bool Executor::test_for_prime(PositiveNumber a, int iterations, merr::Errors* errors) {
    return PrimeTest::testIfPrime(a, iterations);
}



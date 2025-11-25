#include <cstdlib>
#include <cstring>
#include <string>
#include <stdexcept>
#include "PrimeGenerator.h"
#include "utils/Validate.h"
#include "RNG.h"
#include "FiniteNumber.h"
#include "FiniteField.h"
#include "Executor.h"

const int MAX_MESSAGE_LENGTH = 4096;

#if defined(_WIN32) || defined(_WIN64)
#define COPY_STR(dst, src) strcpy_s((dst), MAX_MESSAGE_LENGTH, (src))
#else
#define COPY_STR(dst, src) strcpy((dst), (src))
#endif

void notZero(PositiveNumber positiveNumber, merr::ErrorPicker& errorPicker) {
    if (positiveNumber.isZero()) {
        errorPicker.setMessage("Unexpected zero input!");
    }
}
void notZero(SignedNumber signedNumber, merr::ErrorPicker& errorPicker) {
    if (signedNumber.isZero()) {
        errorPicker.setMessage("Unexpected zero input!");
    }
}

extern "C" char* random_prime(char* errorStr)
{
    char* resStr = nullptr;
    try
    {
        std::string prime = PrimeGenerator::generatePrime();
        resStr = new char[MAX_MESSAGE_LENGTH];
        COPY_STR(resStr, prime.c_str());
    }
    catch (const std::exception& ex)
    {
        COPY_STR(errorStr, ex.what());
    }

    return resStr;
}

extern "C" char* finite_field(const char* expression, const char* n, char* errorStr)
{
    char* resStr = nullptr;
    try
    {
        merr::ErrorPicker picker = merr::ErrorPicker(merr::VALIDATION_ERROR);
        merr::Errors errors;
        std::optional<PositiveNumber> posOpt = Validate::validatePositiveNumber(n, picker);
        std::string resultString;
        if (posOpt.has_value()) {
            PositiveNumber modNumber = posOpt.value();
            std::string expr(expression);
            FiniteField field(modNumber);

            Executor executor = Executor();


            if (modNumber.isZero()) {
                SignedNumber result = executor.infinite_field(expr, &errors);
                resultString = result.toString();
            }
            else {
                FiniteNumber result = executor.finite_field(expr, &modNumber, &errors);
                resultString = result.toString();
            }
        }
        else {
            errors.addError(picker);
        }
        resStr = new char[MAX_MESSAGE_LENGTH];
        if (errors.hasError()) {
            COPY_STR(errorStr, errors.concat().c_str());
            resStr[0] = '\0';
            return resStr;
        }
        COPY_STR(resStr, resultString.c_str());
    }
    catch (const std::exception& ex)
    {
        COPY_STR(errorStr, ex.what());
    }

    return resStr;
}


extern "C" char* number_factorization(const char* n, char* errorStr)
{
    char* resStr = nullptr;
    try
    {
        merr::ErrorPicker picker;
        std::optional<SignedNumber> mOpt = Validate::validateIsNumber(n, picker);
        merr::Errors errors;
        if (mOpt.has_value()) {
            SignedNumber m = SignedNumber(n);

            Executor executor = Executor();


            FactorizationResult result = executor.to_factors(m, &errors);
            resStr = new char[MAX_MESSAGE_LENGTH];
            std::string s = result.toString();
            COPY_STR(resStr, s.c_str());
        }
        else {
            errors.addError(picker);
            COPY_STR(errorStr, errors.concat().c_str());
        }
    }
    catch (const std::exception& ex)
    {
        COPY_STR(errorStr, ex.what());
    }

    return resStr;
}

extern "C" char* number_order(const char* number, const char* n, char* errorStr)
{
    char* resStr = nullptr;
    try
    {
        merr::ErrorPicker picker;
        std::optional<PositiveNumber> mOpt = Validate::validatePositiveNumber(number, picker);
        std::optional<PositiveNumber> pOpt = Validate::validatePositiveNumber(n, picker);
        if (pOpt.has_value()) {
            notZero(pOpt.value(), picker);
        }
        if (mOpt.has_value()) {
            notZero(mOpt.value(), picker);
        }
        merr::Errors errors;
        if (!picker.picked()) {
            SignedNumber m = SignedNumber(n);

            Executor executor = Executor();
            if (mOpt.has_value() && pOpt.has_value()) {
                FiniteNumber finite = FiniteNumber(mOpt.value(), pOpt.value());

                OrderResult result = executor.find_order(finite, &errors);
                resStr = new char[MAX_MESSAGE_LENGTH];
                std::string s = result.toString();
                COPY_STR(resStr, s.c_str());
            }
            else {
                errors.addError("Internal error. The values must be valid, but got empty numbers");
                COPY_STR(errorStr, errors.concat().c_str());
            }
        }
        else {
            errors.addError(picker);
            COPY_STR(errorStr, errors.concat().c_str());
        }
    }
    catch (const std::exception& ex)
    {
        COPY_STR(errorStr, ex.what());
    }

    return resStr;
}

extern "C" char* random_number(char* errorStr)
{
    char* resStr = nullptr;
    try
    {
        std::string rand = RNG::generateRandomNumber();
        resStr = new char[MAX_MESSAGE_LENGTH];
        COPY_STR(resStr, rand.c_str());
    }
    catch (const std::exception& ex)
    {
        COPY_STR(errorStr, ex.what());
    }

    return resStr;
}

extern "C" char* prime_test(const char* number, const char* iterations, char* errorStr)
{
    char* resStr = nullptr;
    try
    {
        merr::ErrorPicker picker;
        std::optional<PositiveNumber> mOpt = Validate::validatePositiveNumber(number, picker);
        std::optional<int> iOpt = Validate::validateInteger(iterations, 4, picker);
        merr::Errors errors;
        if (!picker.picked()) {

            Executor executor = Executor();
            bool result = executor.test_for_prime(mOpt.value(), iOpt.value(), &errors);
            resStr = new char[MAX_MESSAGE_LENGTH];
            std::string s = result ? "Prime" : "Not prime";
            COPY_STR(resStr, s.c_str());
        }
        else {
            errors.addError(picker);
            COPY_STR(errorStr, errors.concat().c_str());
        }
    }
    catch (const std::exception& ex)
    {
        COPY_STR(errorStr, ex.what());
    }

    return resStr;
}

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <iostream>

#include "parse/scanner.h"
#include "parse/parser.hpp"
#include "parse/interpreter.h"
#include <fstream>
#include <sstream>
#include <string>

#include "SignedNumber.h"
#include "FiniteNumber.h"
#include "FiniteGroup.h"
#include "CalculationOfSquareRoot.h"
#include "MillerRabin.h"
#include "Euler.h"
#include "InterpretationManager.h"
#include "Executor.h"
#include "merr/ErrorManager.h"
#include <random>
#include "Logarithm.h"
#include "PrimeGenerator.h"
#include "TestEngineFiniteField.h"

using namespace MathBase;
TEST_CASE("Generic test") {

	CHECK(10 + 15 != 35);
	CHECK(10 + 25 == 35);

}

std::istringstream loadFile(const std::string& name, bool& success) {
    std::ifstream file(name);
    if (!file.is_open()) {
        success = false;
        return std::istringstream("");
    }
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    success = true;
    return std::istringstream(content);
}
TEST_CASE("Parse input test") {
    bool isOpened = false;
    std::string filename = "MathBase/test_files/input.txt";
    std::istringstream stream = loadFile(filename, isOpened);
    if (!isOpened) {
        std::cout << "Cannot open " << filename << std::endl;
    }
	CHECK(isOpened == true);
    Interpreter i;
    i.switchInputStream(&stream);
    i.configLocation(filename, true, true);
    int res = i.parse();
    CHECK(res == 0);
}


TEST_CASE("Positive numbers") {
	std::cout << "Positive numbers" << std::endl;

	PositiveNumber a = PositiveNumber("1234");
	PositiveNumber b = PositiveNumber("99");
	CHECK((a * b).toString() == "122166");
	CHECK((b * a).toString() == "122166");
	CHECK((a - b).toString() == "1135");
	CHECK((b - a).toString() == "1135");
	CHECK((b + a).toString() == "1333");
	CHECK((a + b).toString() == "1333");

}

TEST_CASE("Division Test for PositiveNumber") {
	std::cout << "Division Test for PositiveNumber" << std::endl;
	PositiveNumber p1("12");
	PositiveNumber p2("3");
	PositiveNumber p3 = p1 / p2;
	CHECK(p3.toString() == "4");
	p3 = p2 / p1;
	CHECK(p3.toString() == "0");
	p1 = PositiveNumber("1008");
	p2 = PositiveNumber("23");
	p3 = p1 / p2;
	CHECK(p3.toString() == "43");
	p1 = PositiveNumber("669999");
	p2 = PositiveNumber("257");
	p3 = p1 / p2;
	CHECK(p3.toString() == "2607");
}

TEST_CASE("Division Test for SignedNumber") {
	std::cout << "Division Test for SignedNumber" << std::endl;
	SignedNumber p1("-12");
	SignedNumber p2("3");
	SignedNumber p3 = p1 / p2;
	CHECK(p3.toString() == "-4");
	p3 = p2 / p1;
	CHECK(p3.toString() == "0");
	p1 = SignedNumber("-16");
	p2 = SignedNumber("3");
	p3 = p1 / p2;
	CHECK(p3.toString() == "-5");
	p1 = SignedNumber("-11");
	p2 = SignedNumber("-3");
	p3 = p1 / p2;
	CHECK(p3.toString() == "3");
	p1 = SignedNumber("2");
	p2 = SignedNumber("-3");
	p3 = p1 / p2;
	CHECK(p3.toString() == "0");
}


TEST_CASE("Remainder Test for Positive Numbers") {
	std::cout << "Remainder Test for Positive Numbers" << std::endl;
	PositiveNumber p1("10");
	PositiveNumber p2("8");
	PositiveNumber p3 = p1 % p2;
	CHECK(p3.toString() == "2");
	p1 = PositiveNumber("102");
	p3 = p1 % p2;
	CHECK(p3.toString() == "6");
	p2 = PositiveNumber("2");
	p3 = p1 % p2;
	CHECK(p3.toString() == "0");
	p1 = PositiveNumber("7");
	p2 = PositiveNumber("8");
	p3 = p1 % p2;
	CHECK(p3.toString() == "7");
}


TEST_CASE("Remainder Test for Signed Numbers") {
	std::cout << "Remainder Test for Signed Numbers" << std::endl;
	SignedNumber p1("-10");
	SignedNumber p2("8");
	SignedNumber p3 = p1 % p2;
	CHECK(p3.toString() == "-2");
	p1 = SignedNumber("-102");
	p3 = p1 % p2;
	CHECK(p3.toString() == "-6");
	p2 = SignedNumber("-2");
	p3 = p1 % p2;
	CHECK(p3.toString() == "0");
	p1 = SignedNumber("7");
	p2 = SignedNumber("-8");
	p3 = p1 % p2;
	CHECK(p3.toString() == "7");
	p1 = SignedNumber("-9");
	p2 = SignedNumber("-8");
	p3 = p1 % p2;
	CHECK(p3.toString() == "-1");
}


TEST_CASE("Test on random numbers") {
	std::cout << "Test on random numbers" << std::endl;
	std::random_device rand_dev;
	std::mt19937 generator(rand_dev());
	std::uniform_int_distribution<int>  distr(0, 5000);
	for (int i = 0; i < 200; i++) {
		int a = distr(generator);
		int b = distr(generator);
		PositiveNumber aNum = PositiveNumber(std::to_string(a));
		PositiveNumber bNum = PositiveNumber(std::to_string(b));
		CHECK((aNum + bNum).toString() == std::to_string(a + b));
		CHECK((aNum - bNum).toString() == std::to_string(abs(a - b)));
		CHECK((aNum * bNum).toString() == std::to_string(a * b));
		if (b != 0) {
			CHECK((aNum / bNum).toString() == std::to_string(a / b));
			CHECK((aNum % bNum).toString() == std::to_string(a % b));
		}
	}
}

TEST_CASE("Test zero") {
	std::cout << "Test zero" << std::endl;
	PositiveNumber zero = PositiveNumber("0");
	PositiveNumber a = PositiveNumber("1000");
	PositiveNumber b = PositiveNumber("0000");
	CHECK(a * b == zero);
	CHECK(b * a == zero);
}


TEST_CASE("Exponent") {
	std::cout << "Exponent" << std::endl;

	FiniteNumber n = FiniteNumber("x17 100");
	FiniteNumber m = FiniteNumber("x17 431");
	CHECK(n.toString() == "15");
	CHECK((n * m).toString() == "5");
	CHECK((m * n).toString() == "5");

	PositiveNumber aN = PositiveNumber("15");
	CHECK((aN.shift(2)).toString() == "1500");
	CHECK((aN.shift(-2)).toString() == "0");
	CHECK(FiniteNumber("x257 10000").inverse().toString() == "67");

	FiniteNumber toMultiply = FiniteNumber("x257 128");
	FiniteNumber toMultiply2 = FiniteNumber("x257 80");
	Exponentiation exp = Exponentiation();
	FiniteNumber result = exp.montgomeryMultiplication(toMultiply, toMultiply2);
	CHECK(result.toString() == "217");

	toMultiply = FiniteNumber("x97 15");
	toMultiply2 = FiniteNumber("x97 75");
	CHECK(exp.montgomeryMultiplication(toMultiply, toMultiply2).toString() == "58");
	FiniteNumber base = FiniteNumber("x257 30");
	PositiveNumber power = PositiveNumber("5");
	result = exp.montgomeryExponentiation(base, power);
	CHECK(result.toString() == "136");

	base = FiniteNumber("x113 1222");
	power = PositiveNumber("4");
	result = exp.montgomeryExponentiation(base, power);
	CHECK(result.toString() == "8");
	base = FiniteNumber("x1015843 222222");
	power = PositiveNumber("600");
	std::string expected = "839534";
	CHECK(exp.montgomeryExponentiation(base, power).toString() == expected);
	CHECK(exp.fastExponentiation(base, power).toString() == expected);

	base = FiniteNumber("x5 9");
	power = PositiveNumber("1");
	FiniteNumber res = exp.montgomeryExponentiation(base, power);
	CHECK(res.toString() == "4");

	base = FiniteNumber("x2 1");
	power = PositiveNumber("8");
	res = exp.montgomeryExponentiation(base, power);
	CHECK(res.toString() == "1");

	base = FiniteNumber("x2 0");
	power = PositiveNumber("0");
	res = exp.montgomeryExponentiation(base, power);
	CHECK(res.toString() == "1");

	base = FiniteNumber("x2 0");
	power = PositiveNumber("100");
	res = exp.montgomeryExponentiation(base, power);
	CHECK(res.toString() == "0");


}

TEST_CASE("Exponentiation on random values") {
	std::cout << "Exponentiation on random values" << std::endl;
	std::random_device rand_dev;
	std::mt19937 generator(rand_dev());
	std::uniform_int_distribution<int> baseDistr(0, 2000);
	std::uniform_int_distribution<int> powDistr(0, 20);
	Exponentiation exponent;
	for (int i = 0; i < 200; i++) {
		int a = baseDistr(generator);
		int b = powDistr(generator);
		FiniteNumber aNum = FiniteNumber(std::to_string(a), PositiveNumber("197"));
		PositiveNumber bNum = PositiveNumber(std::to_string(b));
		CHECK(exponent.montgomeryExponentiation(aNum, bNum).toString() == exponent.slowExponentiation(aNum, bNum).toString());
	}
}

TEST_CASE("Test binary form") {
	std::cout << "Test binary form" << std::endl;
	CHECK(PositiveNumber("5").bits() == "101");
	CHECK(PositiveNumber("0").bits() == "0");
	CHECK(PositiveNumber("100").bits() == "1100100");
	CHECK(PositiveNumber("4").bits() == "100");
}


TEST_CASE("Test setIdentity and getIdentity methods") {
	std::cout << "Test setIdentity and getIdentity methods" << std::endl;
	FiniteGroup group(PositiveNumber("10"));

	group.setIdentity(FiniteNumber("0 x10"));
	CHECK(group.getIdentity() == FiniteNumber("0 x10"));
	CHECK(group.getIdentity() == FiniteNumber("0 x10"));
	group.setIdentity(FiniteNumber("1 x10"));
	CHECK(group.getIdentity() == FiniteNumber("1 x10"));
}

TEST_CASE("Test setGroupBinaryOperation method") {
	std::cout << "Test setGroupBinaryOperation method" << std::endl;
	FiniteGroup group(PositiveNumber("10"));

	// Test if the binary operation is set correctly
	CHECK(group.operate(FiniteNumber("2 x10"), FiniteNumber("3 x10")) == FiniteNumber("6 x10"));
}

TEST_CASE("Test getP method") {
	std::cout << "Test getP method" << std::endl;
	FiniteGroup group(PositiveNumber("10"));

	auto ten = PositiveNumber("10");
	CHECK(group.getP().equals(ten));

	// Test getP method with a different modulus
	FiniteGroup group2(PositiveNumber("7"));
	auto seven = PositiveNumber("7");
	CHECK(group2.getP() == seven);
}

TEST_CASE("Test ElementOrder method") {
	std::cout << "Test ElementOrder method" << std::endl;
	FiniteGroup group(PositiveNumber("7"));
	group.setIdentity(FiniteNumber("1 x7"));

	// Test ElementOrder method
	CHECK_THROWS_AS(group.ElementOrder(FiniteNumber("0 x7")).toString(), std::runtime_error);
	CHECK(group.ElementOrder(FiniteNumber("1 x7")).toString() == PositiveNumber("1").toString());
	CHECK(group.ElementOrder(FiniteNumber("2 x7")).toString() == PositiveNumber("3").toString());
	CHECK(group.ElementOrder(FiniteNumber("3 x7")).toString() == PositiveNumber("6").toString());
	CHECK(group.ElementOrder(FiniteNumber("4 x7")).toString() == PositiveNumber("3").toString());
	CHECK(group.ElementOrder(FiniteNumber("5 x7")).toString() == PositiveNumber("6").toString());
	CHECK(group.ElementOrder(FiniteNumber("6 x7")).toString() == PositiveNumber("2").toString());

	auto group2 = FiniteGroup(PositiveNumber("11"));
	group2.setIdentity(FiniteNumber("1 x11"));
	CHECK_THROWS_AS(group2.ElementOrder(FiniteNumber("0 x11")).toString(), std::runtime_error);
	CHECK(group2.ElementOrder(FiniteNumber("1 x11")).toString() == PositiveNumber("1").toString());
	CHECK(group2.ElementOrder(FiniteNumber("2 x11")).toString() == PositiveNumber("10").toString());
	CHECK(group2.ElementOrder(FiniteNumber("3 x11")).toString() == PositiveNumber("5").toString());
	CHECK(group2.ElementOrder(FiniteNumber("4 x11")).toString() == PositiveNumber("5").toString());
	CHECK(group2.ElementOrder(FiniteNumber("5 x11")).toString() == PositiveNumber("5").toString());
	CHECK(group2.ElementOrder(FiniteNumber("6 x11")).toString() == PositiveNumber("10").toString());
	CHECK(group2.ElementOrder(FiniteNumber("7 x11")).toString() == PositiveNumber("10").toString());
	CHECK(group2.ElementOrder(FiniteNumber("8 x11")).toString() == PositiveNumber("10").toString());
	CHECK(group2.ElementOrder(FiniteNumber("9 x11")).toString() == PositiveNumber("5").toString());
	CHECK(group2.ElementOrder(FiniteNumber("10 x11")).toString() == PositiveNumber("2").toString());

	auto group3 = FiniteGroup(PositiveNumber("10"));
	group3.setIdentity(FiniteNumber("1 x10"));
	CHECK(group3.ElementOrder(FiniteNumber("1 x10")).toString() == PositiveNumber("1").toString());
	CHECK_THROWS_AS(group3.ElementOrder(FiniteNumber("2 x10")).toString(), std::overflow_error);
	CHECK(group3.ElementOrder(FiniteNumber("3 x10")).toString() == PositiveNumber("4").toString());
	CHECK_THROWS_AS(group3.ElementOrder(FiniteNumber("4 x10")).toString(), std::overflow_error);
	CHECK_THROWS_AS(group3.ElementOrder(FiniteNumber("5 x10")).toString(), std::overflow_error);
	CHECK_THROWS_AS(group3.ElementOrder(FiniteNumber("6 x10")).toString(), std::overflow_error);
	CHECK(group3.ElementOrder(FiniteNumber("7 x10")).toString() == PositiveNumber("4").toString());
	CHECK_THROWS_AS(group3.ElementOrder(FiniteNumber("8 x10")).toString(), std::overflow_error);
	CHECK(group3.ElementOrder(FiniteNumber("9 x10")).toString() == PositiveNumber("2").toString());
	CHECK_THROWS_AS(group3.ElementOrder(FiniteNumber("10 x10")).toString(), std::overflow_error);
}


TEST_CASE("Test isGenerator method") {
	std::cout << "Test isGenerator method" << std::endl;
	FiniteGroup g1(PositiveNumber("x7"));
	g1.setIdentity(FiniteNumber("1 x7"));
	CHECK(!g1.isGenerator(FiniteNumber("1 x7")));
	CHECK(!g1.isGenerator(FiniteNumber("2 x7")));
	CHECK(g1.isGenerator(FiniteNumber("3 x7")));
	CHECK(!g1.isGenerator(FiniteNumber("4 x7")));
	CHECK(g1.isGenerator(FiniteNumber("5 x7")));
	CHECK(!g1.isGenerator(FiniteNumber("6 x7")));

	FiniteGroup g2(PositiveNumber("x11"));
	g2.setIdentity(FiniteNumber("1 x11"));
	CHECK(!g2.isGenerator(FiniteNumber("1 x11")));
	CHECK(g2.isGenerator(FiniteNumber("2 x11")));
	CHECK(!g2.isGenerator(FiniteNumber("3 x11")));
	CHECK(!g2.isGenerator(FiniteNumber("4 x11")));
	CHECK(!g2.isGenerator(FiniteNumber("5 x11")));
	CHECK(g2.isGenerator(FiniteNumber("6 x11")));
	CHECK(g2.isGenerator(FiniteNumber("7 x11")));
	CHECK(g2.isGenerator(FiniteNumber("8 x11")));
	CHECK(!g2.isGenerator(FiniteNumber("9 x11")));
	CHECK(!g2.isGenerator(FiniteNumber("10 x11")));

	FiniteGroup g3(PositiveNumber("x9"));
	g3.setIdentity(FiniteNumber("1 x9"));
	CHECK(!g3.isGenerator(FiniteNumber("1 x9")));
	CHECK(g3.isGenerator(FiniteNumber("2 x9")));
	CHECK_THROWS_AS(g3.isGenerator(FiniteNumber("3 x9")), std::runtime_error);
	CHECK(!g3.isGenerator(FiniteNumber("4 x9")));
	CHECK(g3.isGenerator(FiniteNumber("5 x9")));
	CHECK_THROWS_AS(g3.isGenerator(FiniteNumber("6 x9")), std::runtime_error);
	CHECK(!g3.isGenerator(FiniteNumber("7 x9")));
	CHECK(!g3.isGenerator(FiniteNumber("8 x9")));
}


TEST_CASE("Test Integer Constuctors") {
	std::cout << "Test Integer Constuctors" << std::endl;
	std::string aStr = "20", bStr = "44";
	int aInt = std::stoi(aStr);
	int bInt = std::stoi(bStr);
	PositiveNumber a = PositiveNumber(aInt);
	PositiveNumber b = PositiveNumber(bInt);
	CHECK("64" == (a + b).toString());

	FiniteNumber finite1 = FiniteNumber(18, 17);
	CHECK("1" == finite1.toString());
}

TEST_CASE("Additional operators") {
	std::cout << "Additional operators" << std::endl;
	FiniteNumber a = FiniteNumber("x17 16");
	FiniteNumber b = FiniteNumber("x17 14");
	CHECK(a > b);
	CHECK(b < a);
	CHECK(!(a < b));
	CHECK(!(b > a));
}

TEST_CASE("Modular Power") {
	std::cout << "Modular Power" << std::endl;
	std::string aStr, bStr, cStr;
	PositiveNumber a = PositiveNumber("81");
	PositiveNumber b = PositiveNumber("6");
	PositiveNumber c = PositiveNumber("12");
	auto result = mod_power(a, b, c).toString();
	CHECK("9" == result);
}

TEST_CASE("Miller-Rabin Primality Test") {
	std::cout << "Miller-Rabin Primality Test" << std::endl;
	std::ifstream f;
	f.open("MathBase/test_files/Miller-Rabin Primality Test.txt");
	std::string aStr;
	int num_tests;
	bool t;
	f >> num_tests;
	for (int i = 0; i < num_tests; i++) { 
		f >> t >> aStr;
		CHECK(t == MillerRabin::miller_rabin(PositiveNumber(aStr)));
	}
	f.close();

}

TEST_CASE("Naive Factorization") {
	PositiveNumber a1 = PositiveNumber(204562);
	std::map<PositiveNumber, int> result1 = map_factors(a1, naiveFactorization<PositiveNumber>);
	std::map<PositiveNumber, int> toCheck1 = { std::pair<PositiveNumber,int>(PositiveNumber(2),1),
		std::pair<PositiveNumber,int>(PositiveNumber(23),1),
		std::pair<PositiveNumber,int>(PositiveNumber(4447),1) };

	CHECK(result1 == toCheck1);

	PositiveNumber a2 = PositiveNumber(168);
	std::map<PositiveNumber, int> result2 = map_factors(a2, naiveFactorization<PositiveNumber>);
	std::map<PositiveNumber, int> toCheck2 = { std::pair<PositiveNumber,int>(PositiveNumber(2),3),
		std::pair<PositiveNumber,int>(PositiveNumber(3),1),
		std::pair<PositiveNumber,int>(PositiveNumber(7),1) };

	CHECK(result2 == toCheck2);

	PositiveNumber a3 = PositiveNumber(43);
	std::map<PositiveNumber, int> result3 = map_factors(a3, naiveFactorization<PositiveNumber>);
	std::map<PositiveNumber, int> toCheck3 = { std::pair<PositiveNumber,int>(PositiveNumber(43),1) };

	CHECK(result3 == toCheck3);

}

TEST_CASE("Pollard's Rho Factorization") {
	PositiveNumber a1 = PositiveNumber(204562);
	std::map<PositiveNumber, int> result1 = map_factors(a1, PollardFactorization::pollardRho<PositiveNumber>);
	std::map<PositiveNumber, int> toCheck1 = { std::pair<PositiveNumber,int>(PositiveNumber(2),1),
		std::pair<PositiveNumber,int>(PositiveNumber(23),1),
		std::pair<PositiveNumber,int>(PositiveNumber(4447),1) };

	CHECK(result1 == toCheck1);

	PositiveNumber a2 = PositiveNumber(168);
	std::map<PositiveNumber, int> result2 = map_factors(a2, PollardFactorization::pollardRho<PositiveNumber>);
	std::map<PositiveNumber, int> toCheck2 = { std::pair<PositiveNumber,int>(PositiveNumber(2),3),
		std::pair<PositiveNumber,int>(PositiveNumber(3),1),
		std::pair<PositiveNumber,int>(PositiveNumber(7),1) };

	CHECK(result2 == toCheck2);

	PositiveNumber a3 = PositiveNumber(43);
	std::map<PositiveNumber, int> result3 = map_factors(a3, PollardFactorization::pollardRho<PositiveNumber>);
	std::map<PositiveNumber, int> toCheck3 = { std::pair<PositiveNumber,int>(PositiveNumber(43),1) };

	CHECK(result3 == toCheck3);
}

TEST_CASE("Euler For Prime Values")
{
	std::cout << "Euler For Prime Values" << std::endl;

	PositiveNumber value1("2");
	PositiveNumber answer1("1");

	PositiveNumber value2("23");
	PositiveNumber degree2("3");
	PositiveNumber answer2("11638");

	CHECK(EulerForPrimeValues(value1) == answer1);
	CHECK(EulerForPrimeValues(value2, degree2) == answer2);
}

TEST_CASE("Euler")
{
	std::cout << "Euler" << std::endl;
	PositiveNumber value1("36");
	PositiveNumber value2("12345678");
	PositiveNumber value3("64");
	PositiveNumber value4("2");

	CHECK(Euler(value1).toString() == "12");
	CHECK(Euler(value2).toString() == "4027392");
	CHECK(Euler(value3).toString() == "32");
	CHECK(Euler(value4).toString() == "1");
}

TEST_CASE("Carmichel")
{
	PositiveNumber value1("9");
	PositiveNumber value2("32");
	PositiveNumber value3("36");
	PositiveNumber value4("169");

	CHECK(Carmichel(value1).toString() == "6");
	CHECK(Carmichel(value2).toString() == "8");
	CHECK(Carmichel(value3).toString() == "6");
	CHECK(Carmichel(value4).toString() == "156");
}

TEST_CASE("Executor. Complex finite Field calculation")
{
	std::string filename = "MathBase/test_files/EXECUTE_system.txt";
	TestEngineFiniteField engine;
	TestExecutionResult res = engine.execute(filename);
	CHECK_MESSAGE(res.success() == true, res.str());
}

TEST_CASE("tonelli-shanks sqrt")
{
	merr::ErrorPicker picker;
	FiniteNumber n(5, 41);
	FiniteNumber r = CalculationOfSquareRoot::tonelli_shanks(n, picker);
	CHECK(r.asPositive() == PositiveNumber(28));

	n = FiniteNumber(10, 13);
	r = CalculationOfSquareRoot::tonelli_shanks(n, picker);
	CHECK(r.asPositive() == PositiveNumber(7));

	n = FiniteNumber(2, 113);
	r = CalculationOfSquareRoot::tonelli_shanks(n, picker);
	CHECK(r.asPositive() == PositiveNumber(62));

	n = FiniteNumber(5, 11);
	r = CalculationOfSquareRoot::tonelli_shanks(n, picker);
	CHECK(r.asPositive() == PositiveNumber(4));

	n = FiniteNumber(7, 13);
	r = CalculationOfSquareRoot::tonelli_shanks(n, picker);
	CHECK(r.asPositive() == PositiveNumber(0));

	n = FiniteNumber(4561237, 9999991);
	r = CalculationOfSquareRoot::tonelli_shanks(n, picker);
	CHECK(r.asPositive() == PositiveNumber(5878273));
}


TEST_CASE("newton_sqrt") {
	merr::ErrorPicker picker;
	PositiveNumber n(9);
	PositiveNumber r = CalculationOfSquareRoot::newton_sqrt(n, picker);
	CHECK(r == PositiveNumber(3));

	n = PositiveNumber(69);
	r = CalculationOfSquareRoot::newton_sqrt(n, picker);
	CHECK(r == PositiveNumber(8));

	n = PositiveNumber("123456789123456");
	r = CalculationOfSquareRoot::newton_sqrt(n, picker);
	CHECK(r == PositiveNumber("11111111"));

	SignedNumber ns("9");
	r = CalculationOfSquareRoot::newton_sqrt(ns, picker);
	CHECK(r == PositiveNumber(3));

	ns = SignedNumber("-9");
	r = CalculationOfSquareRoot::newton_sqrt(ns, picker);
	CHECK(r == PositiveNumber(0));
}

TEST_CASE("Pollard Rho's logarithm") {
	merr::ErrorPicker picker;
	PositiveNumber p("53");
	FiniteNumber g("5", p);
	FiniteNumber h("22", p);
	PositiveNumber x = Logarithm::log(g, h, picker);
	CHECK(x == PositiveNumber("9"));
	p = PositiveNumber(1019);
	g = FiniteNumber("2", p);
	h = FiniteNumber("5", p);
	x = Logarithm::log(g, h, picker);
	CHECK((x == PositiveNumber("10") || x == PositiveNumber("519")));
	p = PositiveNumber(29);
	g = FiniteNumber("2", p);
	h = FiniteNumber("22", p);
	x = Logarithm::log(g, h, picker);
	CHECK(x == PositiveNumber("26"));
	p = PositiveNumber(11);
	g = FiniteNumber("3", p);
	h = FiniteNumber("4", p);
	x = Logarithm::log(g, h, picker);
	CHECK(picker.picked() == false);
	CHECK(x == PositiveNumber("4"));
	p = PositiveNumber(5);
	g = FiniteNumber("2", p);
	h = FiniteNumber("4", p);
	x = Logarithm::log(g, h, picker);
	CHECK(picker.picked() == false);
	CHECK(x == PositiveNumber("2"));
	p = PositiveNumber(5);
	g = FiniteNumber("2", p);
	h = FiniteNumber("3", p);
	x = Logarithm::log(g, h, picker);
	CHECK(picker.picked() == false);
	CHECK(x == PositiveNumber("3"));
}

TEST_CASE("Logarithm test") {
	std::cout << "Logarithm" << std::endl;
	merr::ErrorPicker picker;
	SignedNumber p("2");
	SignedNumber h("17");
	PositiveNumber x = Logarithm::log(p, h, picker);
	CHECK(x == PositiveNumber("4"));
	CHECK(picker.picked() == false);

	h = SignedNumber("32");
	x = Logarithm::log(p, h, picker);

	CHECK(x == PositiveNumber("5"));
	CHECK(picker.picked() == false);

	h = SignedNumber("-32");
	x = Logarithm::log(p, h, picker);

	CHECK(picker.picked() == true);
}

TEST_CASE("Square Root Test") {
	std::cout << "Square Root Test" << std::endl;
	merr::ErrorPicker picker;
	PositiveNumber base("101");
	FiniteField field(base);
	FiniteNumber a("65", field);
	merr::ErrorPicker err;
	FiniteNumber expected("60", field);
	FiniteNumber actual = CalculationOfSquareRoot::tonelli_shanks(a, err);
	CHECK(picker.picked() == false);
	CHECK(actual == expected);
}

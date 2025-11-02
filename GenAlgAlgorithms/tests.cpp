#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "MathBase/SignedNumber.h"
#include "MathBase/FiniteNumber.h"
#include "MathBase/Polynomial.h"
#include "MathBase/FiniteGroup.h"
#include "MathBase/CalculationOfSquareRoot.h"
#include "MathBase/MillerRabin.h"
#include "MathBase/Euler.h"
#include "MathBase/InterpretationManager.h"
#include "MathBase/Executor.h"
#include "MathBase/utils/TestUtils.h"
#include "MathBase/merr/ErrorManager.h"
#include <random>
#include <string>
#include <chrono>
#include <fstream>
#include "MathBase/utils/TestEngineFiniteField.h"
#include "MathBase/Logarithm.h"
#include "MathBase/PrimeGenerator.h"



TEST_CASE("Positive numbers") {
	std::cout << "Positive numbers" << std::endl;
	std::ifstream f;
	f.open("Positive numbers Test.txt");

	//PositiveNumber a = PositiveNumber("1234");
	//PositiveNumber b = PositiveNumber("99");
	std::string aStr,bStr;
	f >> aStr >> bStr;
	PositiveNumber a(aStr);
	PositiveNumber b(bStr);
	CHECK((a * b).toString() == "122166");
	CHECK((b * a).toString() == "122166");
	CHECK((a - b).toString() == "1135");
	CHECK((b - a).toString() == "1135");
	CHECK((b + a).toString() == "1333");
	CHECK((a + b).toString() == "1333");

	f.close();
}

TEST_CASE("Division Test for PositiveNumber") {
	std::cout << "Division Test for PositiveNumber" << std::endl;
	std::ifstream f;
	f.open("Division Test for PositiveNumber.txt");
	std::string p1Str, p2Str;
	f >> p1Str >> p2Str;

	PositiveNumber p1(p1Str);
	PositiveNumber p2(p2Str);
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
	f.close();
}

TEST_CASE("Division Test for SignedNumber") {
	std::cout << "Division Test for SignedNumber" << std::endl;
	std::ifstream f;
	f.open("Division Test for SignedNumber.txt");
	std::string p1Str, p2Str;
	f >> p1Str >> p2Str;
	SignedNumber p1(p1Str);
	SignedNumber p2(p2Str);
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
	f.close();
}


TEST_CASE("Remainder Test for Positive Numbers") {
	std::cout << "Remainder Test for Positive Numbers" << std::endl;
	std::ifstream f;
	f.open("Remainder Test for Positive Numbers.txt");
	std::string p1Str, p2Str;
	f >> p1Str >> p2Str;

	PositiveNumber p1(p1Str);
	PositiveNumber p2(p2Str);
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
	f.close();
}


TEST_CASE("Remainder Test for Signed Numbers") {
	std::cout << "Remainder Test for Signed Numbers" << std::endl;
	std::ifstream f;
	f.open("Remainder Test for Signed Numbers.txt");
	std::string p1Str, p2Str;
	f >> p1Str >> p2Str;
	SignedNumber p1(p1Str);
	SignedNumber p2(p2Str);
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

TEST_CASE("Signed numbers") {
	std::cout << "Signed numbers" << std::endl;
	std::ifstream f;
	f.open("Signed numbers Test.txt");
	std::string finiteStr, signedNStr, signedMStr,aStr,bStr;
	getline(f, finiteStr);
	f >> signedNStr >> signedMStr>>aStr>>bStr;
	
	FiniteNumber finite = FiniteNumber(finiteStr);
	CHECK(finite.toString() == "4");
	SignedNumber signedN = SignedNumber(signedNStr);
	SignedNumber signedM = SignedNumber(signedMStr);
	SignedNumber res = signedN;
	res -= signedM;
	CHECK(res.toString() == "1855");


	SignedNumber a = SignedNumber(aStr);
	SignedNumber b = SignedNumber(bStr);
	SignedNumber c = a * b;
	CHECK(c.toString() == "0");
	f.close();

}

TEST_CASE("Finite numbers") {
	std::cout << "Finite numbers" << std::endl;
	std::ifstream f;
	f.open("Finite numbers Tests.txt");
	std::string fin1Str, fin2Str,origStr;
	getline(f, fin1Str);
	getline(f, fin2Str);
	FiniteNumber fin1 = FiniteNumber(fin1Str);
	FiniteNumber fin2 = FiniteNumber(fin2Str);
	CHECK(fin1.toString() == "6");
	CHECK(fin2.toString() == "6");
	FiniteNumber fin3 = fin1 + fin2;
	CHECK(fin3.toString() == "2");
	fin1 += fin2;
	CHECK(fin1.toString() == "2");
	fin3 = fin1 - fin2;
	CHECK(fin3.toString() == "6");
	fin1 -= fin2;
	CHECK(fin1.toString() == "6");
	fin3 = fin1 * fin2;


	

	CHECK(fin3.toString() == "6");
	getline(f, origStr);
	FiniteNumber orig = FiniteNumber(origStr);


	FiniteNumber inv = orig.inverse();
	CHECK(inv.toString() == "3");
	getline(f, fin1Str);
	getline(f, fin2Str);
	fin1 = FiniteNumber(fin1Str);
	fin2 = FiniteNumber(fin2Str);
	FiniteNumber fin4 = fin1 / fin2;
	FiniteNumber fin5 = fin2 / fin1;
	CHECK(fin4.toString() == "8");
	CHECK(fin5.toString() == "3");
	fin1.divideBy(fin2);
	CHECK(fin1.toString() == "8");
	getline(f, fin1Str);
	getline(f, fin2Str);
	fin1 = FiniteNumber(fin1Str);
	fin2 = FiniteNumber(fin2Str);

	auto res = fin1 + fin2;
	CHECK(res.toString() == "1127822179038104809524733176879403005056");

	fin1 = FiniteNumber("-1232 x10");
	CHECK(fin1.toString() == "8");

	fin1 = FiniteNumber("-10 x6");
	CHECK(fin1.toString() == "2");

	fin1 = FiniteNumber("-1 x10");
	CHECK(fin1.toString() == "9");

	fin1 = FiniteNumber("-6 x6");
	CHECK(fin1.toString() == "0");

	fin1 = FiniteNumber("-6 x5");
	CHECK(fin1.toString() == "4");
	f.close();

	FiniteField field(PositiveNumber("272440612037865607952868223313"));
	FiniteNumber num(PositiveNumber("1111111111"), field.getP());
	
	 std::cout << num.inverse().toString() << "\n";
	 FiniteNumber num1 = num.inverse();
	 num *= num1;
	 std::cout << num.toString();
}


TEST_CASE("Test zero") {
	std::cout << "Test zero" << std::endl;
	std::ifstream f;
	f.open("Test zero.txt");
	std::string zeroStr, aStr, bStr;
	f >> zeroStr >> aStr >> bStr;
	PositiveNumber zero = PositiveNumber(zeroStr);
	PositiveNumber a = PositiveNumber(aStr);
	PositiveNumber b = PositiveNumber(bStr);
	CHECK(a * b == zero);
	CHECK(b * a == zero);
	f.close();
}


TEST_CASE("Exponent") {
	std::cout << "Exponent" << std::endl;
	std::ifstream f;
	f.open("Exponent Test.txt");
	std::string nStr, mStr, aNStr, toMultiplyStr, toMultiply2Str,baseStr,powerStr;
	getline(f, nStr);
	getline(f, mStr);
	getline(f, aNStr);
	getline(f, toMultiplyStr);
	getline(f, toMultiply2Str);
	
	FiniteNumber n = FiniteNumber(nStr);
	FiniteNumber m = FiniteNumber(mStr);
	CHECK(n.toString() == "15");
	CHECK((n * m).toString() == "5");
	CHECK((m * n).toString() == "5");

	PositiveNumber aN = PositiveNumber("15");
	CHECK((aN.shift(2)).toString() == "1500");
	CHECK((aN.shift(-2)).toString() == "0");
	CHECK(FiniteNumber("x257 10000").inverse().toString() == "67");

	FiniteNumber toMultiply = FiniteNumber(toMultiplyStr);
	FiniteNumber toMultiply2 = FiniteNumber(toMultiply2Str);
	Exponentiation exp = Exponentiation();
	FiniteNumber result = exp.montgomeryMultiplication(toMultiply, toMultiply2);
	CHECK(result.toString() == "217");
	getline(f, toMultiplyStr);
	getline(f, toMultiply2Str);
	getline(f, baseStr);
	getline(f, powerStr);
	toMultiply = FiniteNumber(toMultiplyStr);
	toMultiply2 = FiniteNumber(toMultiply2Str);
	CHECK(exp.montgomeryMultiplication(toMultiply, toMultiply2).toString() == "58");

	FiniteNumber base = FiniteNumber("x257 30");
	PositiveNumber power = PositiveNumber("5");
	result = exp.montgomeryExponentiation(base, power);
	CHECK(result.toString() == "136");

	getline(f, baseStr);
	getline(f, powerStr);
	base = FiniteNumber(baseStr);
	power = PositiveNumber(powerStr);
	result = exp.montgomeryExponentiation(base, power);


	CHECK(result.toString() == "8");

	getline(f, baseStr);
	getline(f, powerStr);
	base = FiniteNumber(baseStr);
	power = PositiveNumber(powerStr);
	std::string expected = "839534";
	//TIMING
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	CHECK(exp.montgomeryExponentiation(base, power).toString() == expected);
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	//std::cout << "Montgomery = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " ms" << std::endl;

	begin = std::chrono::steady_clock::now();
	CHECK(exp.fastExponentiation(base, power).toString() == expected);
	end = std::chrono::steady_clock::now();
	f.close();

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

	f.close();


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
//Tests for bits function
TEST_CASE("Test binary form") {
	std::cout << "Test binary form" << std::endl;
	std::ifstream f;
	f.open("Test binary form.txt");
	std::string aStr;
	f >> aStr;
	CHECK(PositiveNumber(aStr).bits() == "101");
	f >> aStr;
	CHECK(PositiveNumber(aStr).bits() == "0");
	f >> aStr;
	CHECK(PositiveNumber(aStr).bits() == "1100100");
	f >> aStr;
	CHECK(PositiveNumber(aStr).bits() == "100");
	f.close();
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
	std::ifstream f;
	f.open("Test Integer Constuctors.txt");
	std::string aStr, bStr;
	f >> aStr >> bStr;
	int aInt = std::stoi(aStr);
	int bInt = std::stoi(bStr);
	PositiveNumber a = PositiveNumber(aInt);
	PositiveNumber b = PositiveNumber(bInt);
	CHECK("64" == (a + b).toString());
	
	FiniteNumber finite1 = FiniteNumber(18, 17);
	CHECK("1" == finite1.toString());
	f.close();
}

TEST_CASE("Additional operators test") {
	std::cout << "Additional operators test" << std::endl;
	std::ifstream f;
	f.open("Additional operators test.txt");
	std::string aStr, bStr,cStr,dStr;
	getline(f, aStr);
	getline(f, bStr);
	getline(f, cStr);
	getline(f, dStr);
	FiniteNumber a = FiniteNumber(aStr);
	FiniteNumber b = FiniteNumber(bStr);
	FiniteNumber c = FiniteNumber(cStr);
	FiniteNumber d = FiniteNumber(dStr);
	CHECK(a == b);
	CHECK(a != c);
	CHECK(a != d);
	f.close();
}

TEST_CASE("Additional operators") {
	std::cout << "Additional operators" << std::endl;
	std::ifstream f;
	f.open("Additional operators.txt");
	std::string aStr, bStr;
	getline(f, aStr);
	getline(f, bStr);
	FiniteNumber a = FiniteNumber(aStr);
	FiniteNumber b = FiniteNumber(bStr);
	CHECK(a > b);
	CHECK(b < a);
	CHECK(!(a < b));
	CHECK(!(b > a));
	f.close();
}

TEST_CASE("Modular Power") {
	std::cout << "Modular Power" << std::endl;
	std::ifstream f;
	f.open("Modular Power.txt");
	std::string aStr, bStr,cStr;
	getline(f, aStr);
	getline(f, bStr);
	getline(f, cStr);
	PositiveNumber a = PositiveNumber(aStr);
	PositiveNumber b = PositiveNumber(bStr);
	PositiveNumber c = PositiveNumber(cStr);
	auto result = mod_power(a, b, c).toString();
	CHECK("9" == result);
}

TEST_CASE("Miller-Rabin Primality Test") {
	std::cout << "Miller-Rabin Primality Test" << std::endl;
	std::ifstream f;
	f.open("Miller-Rabin Primality Test.txt");
	std::string aStr;
	f >> aStr;
	CHECK(!MillerRabin::miller_rabin(PositiveNumber(aStr)));
	f >> aStr;
	CHECK(!MillerRabin::miller_rabin(PositiveNumber(aStr)));
	f >> aStr;
	CHECK(!MillerRabin::miller_rabin(PositiveNumber(aStr)));
	f >> aStr;
	CHECK(!MillerRabin::miller_rabin(PositiveNumber(aStr)));
	f >> aStr;
	CHECK(MillerRabin::miller_rabin(PositiveNumber(aStr)));
	f >> aStr;
	CHECK(MillerRabin::miller_rabin(PositiveNumber(aStr)));
	f >> aStr;
	CHECK(MillerRabin::miller_rabin(PositiveNumber(aStr)));
	f >> aStr;
	CHECK(MillerRabin::miller_rabin(PositiveNumber(aStr)));
	f >> aStr;
	CHECK(MillerRabin::miller_rabin(PositiveNumber(aStr)));
	f >> aStr;
	CHECK(MillerRabin::miller_rabin(PositiveNumber(aStr)));
	f >> aStr;
	CHECK(MillerRabin::miller_rabin(PositiveNumber(aStr)));
	f >> aStr;
	CHECK(MillerRabin::miller_rabin(PositiveNumber(aStr)));
	f >> aStr;
	CHECK(MillerRabin::miller_rabin(PositiveNumber(aStr)));
	f >> aStr;
	CHECK(MillerRabin::miller_rabin(PositiveNumber(aStr)));
	f >> aStr;
	CHECK(MillerRabin::miller_rabin(PositiveNumber(aStr)));
	f >> aStr;
	CHECK(MillerRabin::miller_rabin(PositiveNumber(aStr)));
	f >> aStr;
	CHECK(MillerRabin::miller_rabin(PositiveNumber(aStr)));
	f.close();

}

TEST_CASE("Naive Factorization") {
	std::cout << "Naive Factorization" << std::endl;
	std::ifstream f;
	f.open("Naive Factorization.txt");
	std::string a1Str,a2Str,a3Str;
	f >> a1Str >> a2Str >> a3Str;
	PositiveNumber a1 = PositiveNumber(a1Str);
	std::map<PositiveNumber, int> result1 = map_factors(a1, naiveFactorization<PositiveNumber>);
	std::map<PositiveNumber, int> toCheck1 = { std::pair<PositiveNumber,int>(PositiveNumber(2),1),
		std::pair<PositiveNumber,int>(PositiveNumber(23),1),
		std::pair<PositiveNumber,int>(PositiveNumber(4447),1) };

	CHECK(result1 == toCheck1);

	PositiveNumber a2 = PositiveNumber(a2Str);
	std::map<PositiveNumber, int> result2 = map_factors(a2, naiveFactorization<PositiveNumber>);
	std::map<PositiveNumber, int> toCheck2 = { std::pair<PositiveNumber,int>(PositiveNumber(2),3),
		std::pair<PositiveNumber,int>(PositiveNumber(3),1),
		std::pair<PositiveNumber,int>(PositiveNumber(7),1) };

	CHECK(result2 == toCheck2);

	PositiveNumber a3 = PositiveNumber(a3Str);
	std::map<PositiveNumber, int> result3 = map_factors(a3, naiveFactorization<PositiveNumber>);
	std::map<PositiveNumber, int> toCheck3 = { std::pair<PositiveNumber,int>(PositiveNumber(43),1) };

	CHECK(result3 == toCheck3);
	f.close();

}

TEST_CASE("Pollard's Rho Factorization") {
	std::cout << "Pollard's Rho Factorization" << std::endl;
	std::ifstream f;
	f.open("Pollard's Rho Factorization.txt");
	std::string a1Str, a2Str, a3Str;
	f >> a1Str >> a2Str >> a3Str;
	PositiveNumber a1 = PositiveNumber(a1Str);
	std::map<PositiveNumber,int> result1 = map_factors(a1, PollardFactorization::pollardRho<PositiveNumber>);
	std::map<PositiveNumber, int> toCheck1 = {std::pair<PositiveNumber,int>(PositiveNumber(2),1),
		std::pair<PositiveNumber,int>(PositiveNumber(23),1),
		std::pair<PositiveNumber,int>(PositiveNumber(4447),1) };
	
	CHECK(result1 == toCheck1);

	PositiveNumber a2 = PositiveNumber(a2Str);
	std::map<PositiveNumber, int> result2 = map_factors(a2, PollardFactorization::pollardRho<PositiveNumber>);
	std::map<PositiveNumber, int> toCheck2 = { std::pair<PositiveNumber,int>(PositiveNumber(2),3),
		std::pair<PositiveNumber,int>(PositiveNumber(3),1),
		std::pair<PositiveNumber,int>(PositiveNumber(7),1) };

	CHECK(result2 == toCheck2);

	PositiveNumber a3 = PositiveNumber(a3Str);
	std::map<PositiveNumber, int> result3 = map_factors(a3, PollardFactorization::pollardRho<PositiveNumber>);
	std::map<PositiveNumber, int> toCheck3 = { std::pair<PositiveNumber,int>(PositiveNumber(43),1) };

	CHECK(result3 == toCheck3);
	f.close();
}

TEST_CASE("Euler For Prime Values")
{
	std::cout << "Euler For Prime Values" << std::endl;
	std::ifstream f;
	f.open("Euler For Prime Values.txt");
	std::string value1Str, value2Str, degree2Str;
	f >> value1Str >> value2Str >> degree2Str;

	PositiveNumber value1(value1Str);
	PositiveNumber answer1("1");

	PositiveNumber value2(value2Str);
	PositiveNumber degree2(degree2Str);
	PositiveNumber answer2("11638");

	CHECK(EulerForPrimeValues(value1) == answer1);
	CHECK(EulerForPrimeValues(value2, degree2) == answer2);
	f.close();
}

TEST_CASE("Euler")
{
	std::cout << "Euler" << std::endl;
	std::ifstream f;
	f.open("Euler.txt");
	std::string value1Str, value2Str, value3Str, value4Str;
	f >> value1Str >> value2Str >> value3Str >> value4Str;
	PositiveNumber value1(value1Str);
	PositiveNumber value2(value2Str);
	PositiveNumber value3(value3Str);
	PositiveNumber value4(value4Str);

	CHECK(Euler(value1).toString() == "12");
	CHECK(Euler(value2).toString() == "4027392");
	CHECK(Euler(value3).toString() == "32");
	CHECK(Euler(value4).toString() == "1");
	f.close();
}

TEST_CASE("Carmichel")
{
	std::cout << "Carmichel" << std::endl;
	std::ifstream f;
	f.open("Carmichel.txt");
	std::string value1Str, value2Str, value3Str, value4Str;
	f >> value1Str >> value2Str >> value3Str >> value4Str;
	PositiveNumber value1("9");
	PositiveNumber value2("32");
	PositiveNumber value3("36");
	PositiveNumber value4("169");

	CHECK(Carmichel(value1).toString() == "6");
	CHECK(Carmichel(value2).toString() == "8");
	CHECK(Carmichel(value3).toString() == "6");
	CHECK(Carmichel(value4).toString() == "156");
	f.close();
}

TEST_CASE("Scan_Parse_OK")
{
	bool isOpened = false;
	std::string filename = "scan_parse.txt";
	std::istringstream stream = loadTestFile(filename, isOpened);
	CHECK(isOpened == true);
	MathBase::Interpreter i;
	i.switchInputStream(&stream);
	i.configLocation(filename, true, true);
	int res = i.parse();
	CHECK(res == 0);
	CHECK(i.hasError() == false);
	CHECK(i.total_asts() == 2);
	i.clear();
}

TEST_CASE("Reusable interpretation manager OK")
{
	bool isOpened = false;
	std::string filename = "interpreter.txt";
	std::vector<std::string> lines = readLines(filename, isOpened);
	InterpretationManager interpretationManager;
	merr::Errors errors;
	for (std::string line : lines) {
		std::optional<MathBase::AST*> ast = interpretationManager.parseInput(line, &errors);

		std::string err = "Error parsing " + line;
		CHECK_MESSAGE(errors.hasError() == false, err);

		err = "Expected to get Abstract Syntax Tree, but got none: " + line;
		CHECK_MESSAGE(ast.has_value() == true, err);
	}
}

TEST_CASE("Executor. Simple finite Field calculation OK")
{
	bool isOpened = false;
	std::string filename = "EXECUTE_simple.txt";
	std::vector<std::string> lines = readLines(filename, isOpened);
	Executor exec;
	std::string baseStr = lines[0];
	std::string expression = lines[1];
	std::string expectedStr = lines[2];

	PositiveNumber n(baseStr);
	FiniteField field(n);
	FiniteNumber expected(expectedStr, n);
	FiniteNumber result;
	merr::Errors errors;
	result = exec.finite_field(expression, &n, &errors);
	CHECK(result == expected);
}

TEST_CASE("Executor. Complex finite Field calculation")
{
	std::string filename = "EXECUTE_complex.txt";
	TestEngineFiniteField engine;
	TestExecutionResult res = engine.execute(filename);
	CHECK_MESSAGE(res.success() == true, res.str());
}

TEST_CASE("tonelli-shanks sqrt")
{
	merr::ErrorPicker picker;
	//Simple checks
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

	//Non-risidue checks
	n = FiniteNumber(7, 13);
	r = CalculationOfSquareRoot::tonelli_shanks(n, picker);
	CHECK(r.asPositive() == PositiveNumber(0));

	//Big Checks

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
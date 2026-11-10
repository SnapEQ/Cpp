#include <iostream>
#include <sstream>
#include <cmath>
#include <stdexcept>
#include "Complex.h"

int failed = 0;

void check(const char* name, bool condition) {
    if (condition) {
        std::cout<<"PASS: "<<name<<std::endl;
    } else {
        std::cout<<"FAIL: "<<name<<std::endl;
        failed++;
    }
}

bool isClose(double a, double b) {
    return std::fabs(a - b) < 1e-9;
}

bool isClose(const ComplexNumber& num, double realPart, double imaginaryPart) {
    return isClose(num.getRealPart(), realPart) && isClose(num.getImaginaryPart(), imaginaryPart);
}

void testInit() {
    ComplexNumber num(2, -3);

    check("init - real part is set", num.getRealPart() == 2);
    check("init - imaginary part is set", num.getImaginaryPart() == -3);
}

void testDefaultConstructor() {
    ComplexNumber num;

    check("default constructor - real part is 0", num.getRealPart() == 0);
    check("default constructor - imaginary part is 0", num.getImaginaryPart() == 0);
}

void testSetters() {
    ComplexNumber num(0, 0);

    num.setRealPart(4.5);
    num.setImaginaryPart(-1.5);

    check("setters - real part is changed", num.getRealPart() == 4.5);
    check("setters - imaginary part is changed", num.getImaginaryPart() == -1.5);
}

void testAddition() {
    ComplexNumber num1(2, -3);
    ComplexNumber num2(3, 2);

    ComplexNumber res = num1 + num2;

    check("addition - returns 5-1i", isClose(res, 5, -1));
    check("addition - first operand is untouched", isClose(num1, 2, -3));
    check("addition - second operand is untouched", isClose(num2, 3, 2));
}

void testSubtraction() {
    ComplexNumber num1(2, -3);
    ComplexNumber num2(3, 2);

    ComplexNumber res = num1 - num2;

    check("subtraction - returns -1-5i", isClose(res, -1, -5));
    check("subtraction - first operand is untouched", isClose(num1, 2, -3));
}

void testMultiplication() {
    ComplexNumber num1(2, -3);
    ComplexNumber num2(3, 2);

    ComplexNumber res = num1 * num2;

    check("multiplication - returns 12-5i", isClose(res, 12, -5));
    check("multiplication - i * i returns -1", isClose(ComplexNumber(0, 1) * ComplexNumber(0, 1), -1, 0));
}

void testDivision() {
    ComplexNumber num1(2, -3);
    ComplexNumber num2(3, 2);

    ComplexNumber res = num1 / num2;

    check("division - returns 0-1i", isClose(res, 0, -1));
    check("division - result times divisor gives dividend", isClose(res * num2, 2, -3));
    check("division - number divided by itself returns 1", isClose(num2 / num2, 1, 0));
}

void testDivisionByZero() {
    ComplexNumber num(2, -3);
    ComplexNumber zero;
    bool thrown;

    thrown = false;
    try {
        num / zero;
    } catch (const std::domain_error&) {
        thrown = true;
    }
    check("division by zero - complex / 0+0i throws", thrown);

    thrown = false;
    try {
        num / 0.0;
    } catch (const std::domain_error&) {
        thrown = true;
    }
    check("division by zero - complex / 0.0 throws", thrown);

    thrown = false;
    try {
        1 / zero;
    } catch (const std::domain_error&) {
        thrown = true;
    }
    check("division by zero - double / 0+0i throws", thrown);

    thrown = false;
    try {
        num /= zero;
    } catch (const std::domain_error&) {
        thrown = true;
    }
    check("division by zero - /= 0+0i throws", thrown);
    check("division by zero - /= complex leaves number untouched", isClose(num, 2, -3));

    thrown = false;
    try {
        num /= 0.0;
    } catch (const std::domain_error&) {
        thrown = true;
    }
    check("division by zero - /= 0.0 throws", thrown);
    check("division by zero - /= double leaves number untouched", isClose(num, 2, -3));

    check("division by zero - dividing zero is fine", isClose(zero / num, 0, 0));
}

void testDoubleOperators() {
    ComplexNumber num(2, -3);

    check("double addition - returns 4.5-3i", isClose(num + 2.5, 4.5, -3));
    check("double subtraction - returns -0.5-3i", isClose(num - 2.5, -0.5, -3));
    check("double multiplication - returns 4-6i", isClose(num * 2, 4, -6));
    check("double division - returns 1-1.5i", isClose(num / 2, 1, -1.5));
}

void testDoubleOperatorsReversed() {
    ComplexNumber num(2, 4);

    check("reversed addition - returns 3+4i", isClose(1 + num, 3, 4));
    check("reversed subtraction - returns -1-4i", isClose(1 - num, -1, -4));
    check("reversed multiplication - returns 3+6i", isClose(1.5 * num, 3, 6));
    check("reversed division - returns 0.1-0.2i", isClose(1 / num, 0.1, -0.2));
}

void testCompoundAssignment() {
    ComplexNumber num(2, -3);
    ComplexNumber other(3, 2);

    num += other;
    check("+= complex - returns 5-1i", isClose(num, 5, -1));

    num -= other;
    check("-= complex - returns 2-3i", isClose(num, 2, -3));

    num *= other;
    check("*= complex - returns 12-5i", isClose(num, 12, -5));

    num /= other;
    check("/= complex - returns 2-3i", isClose(num, 2, -3));

    check("compound assignment - other is untouched", isClose(other, 3, 2));
}

void testCompoundAssignmentDouble() {
    ComplexNumber num(2, -3);

    num += 1.5;
    check("+= double - returns 3.5-3i", isClose(num, 3.5, -3));

    num -= 1.5;
    check("-= double - returns 2-3i", isClose(num, 2, -3));

    num *= 2;
    check("*= double - returns 4-6i", isClose(num, 4, -6));

    num /= 2;
    check("/= double - returns 2-3i", isClose(num, 2, -3));
}

void testChainedAssignment() {
    ComplexNumber num1(1.0, 0.3);
    ComplexNumber num2(0.9, 0.1);
    ComplexNumber num3(0.8, 0.1);

    num1 += num2 += num3;

    check("chained += - right side is applied first", isClose(num2, 1.7, 0.2));
    check("chained += - left side gets the sum of all", isClose(num1, 2.7, 0.5));

    ComplexNumber num4(1.0, 0.3);
    ComplexNumber num5(0.9, 0.1);

    num4 *= num5 *= num3;

    check("chained *= - right side is applied first", isClose(num5, 0.71, 0.17));
    check("chained *= - left side gets the product of all", isClose(num4, 0.659, 0.383));
}

void testChainedAssignmentInBraces() {
    ComplexNumber num1(1.0, 0.3);
    ComplexNumber num2(0.9, 0.1);
    ComplexNumber num3(0.8, 0.1);

    (num1 += num2) += num3;

    check("braced += - left side gets the sum of all", isClose(num1, 2.7, 0.5));
    check("braced += - second number is untouched", isClose(num2, 0.9, 0.1));

    ComplexNumber num4(1.0, 0.3);
    (num4 *= num2) *= num3;

    check("braced *= - returns 0.659+0.383i", isClose(num4, 0.659, 0.383));
}

void testEquality() {
    ComplexNumber num1(1.5, 1.1);
    ComplexNumber num2(1.5, 1.1);
    ComplexNumber num3(1.5, 1.0);

    check("== complex - equal numbers", num1 == num2);
    check("== complex - different numbers", !(num1 == num3));
    check("!= complex - different numbers", num1 != num3);
    check("!= complex - equal numbers", !(num1 != num2));
}

void testEqualityDouble() {
    ComplexNumber real(1.5, 0.0);
    ComplexNumber notReal(1.5, 0.1);

    check("== double - real number equals double", real == 1.5);
    check("== double - imaginary part breaks equality", !(notReal == 1.5));
    check("!= double - imaginary part breaks equality", notReal != 1.5);
    check("!= double - real number equals double", !(real != 1.5));

    check("reversed == double - real number equals double", 1.5 == real);
    check("reversed == double - imaginary part breaks equality", !(1.5 == notReal));
    check("reversed != double - imaginary part breaks equality", 1.5 != notReal);
    check("reversed != double - real number equals double", !(1.5 != real));
}

void testAmplitude() {
    check("amplitude - 3+4i returns 5", isClose(ComplexNumber(3, 4).getAmplitude(), 5));
    check("amplitude - -3-4i returns 5", isClose(ComplexNumber(-3, -4).getAmplitude(), 5));
    check("amplitude - 0+2i returns 2", isClose(ComplexNumber(0, 2).getAmplitude(), 2));
    check("amplitude - 0+0i returns 0", isClose(ComplexNumber(0, 0).getAmplitude(), 0));
}

void testPhase() {
    check("phase - 1+1i returns pi/4", isClose(ComplexNumber(1, 1).getPhase(), M_PI / 4));
    check("phase - -1+1i returns 3pi/4", isClose(ComplexNumber(-1, 1).getPhase(), 3 * M_PI / 4));
    check("phase - -1-1i returns -3pi/4", isClose(ComplexNumber(-1, -1).getPhase(), -3 * M_PI / 4));
    check("phase - 1-1i returns -pi/4", isClose(ComplexNumber(1, -1).getPhase(), -M_PI / 4));
    check("phase - 0+2i returns pi/2", isClose(ComplexNumber(0, 2).getPhase(), M_PI / 2));
    check("phase - 2+0i returns 0", isClose(ComplexNumber(2, 0).getPhase(), 0));
}

std::string toString(const ComplexNumber& num) {
    std::ostringstream os;
    os << num;
    return os.str();
}

void testStreamInsertion() {
    check("<< - positive imaginary part", toString(ComplexNumber(3, 4)) == "3 + 4i");
    check("<< - negative imaginary part", toString(ComplexNumber(3, -4)) == "3 - 4i");
    check("<< - negative real part", toString(ComplexNumber(-1.5, 2)) == "-1.5 + 2i");
    check("<< - zero", toString(ComplexNumber(0, 0)) == "0 + 0i");
    check("<< - negative zero imaginary part", toString(ComplexNumber(3, -0.0)) == "3 + 0i");

    std::ostringstream os;
    os << ComplexNumber(1, 2) << " and " << ComplexNumber(3, -1);
    check("<< - chaining", os.str() == "1 + 2i and 3 - 1i");
}

int main() {

    testInit();
    testDefaultConstructor();
    testSetters();
    testAddition();
    testSubtraction();
    testMultiplication();
    testDivision();
    testDivisionByZero();
    testDoubleOperators();
    testDoubleOperatorsReversed();
    testCompoundAssignment();
    testCompoundAssignmentDouble();
    testChainedAssignment();
    testChainedAssignmentInBraces();
    testEquality();
    testEqualityDouble();
    testAmplitude();
    testPhase();
    testStreamInsertion();

    std::cout<<std::endl;

    if (failed == 0) {
        std::cout<<"All tests passed"<<std::endl;
    } else {
        std::cout<<failed<<" tests failed"<<std::endl;
    }

    return failed != 0;
}

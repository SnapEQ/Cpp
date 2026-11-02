#include <cstdlib>
#include <stdexcept>
#include <string>
#include "Complex.h"

// Every stub throws, so TestComplexStack.cpp reports it as FAIL instead of crashing.
// Remove the throwNotImplemented(...) line when you implement a function.
[[noreturn]] static void throwNotImplemented(const char* function) {
    throw std::logic_error(std::string(function) + " is not implemented");
}

// ---- given: constructor, getters, setters ----

ComplexNumber::ComplexNumber(double realPart, double imaginaryPart) {
    this->realPart = realPart;
    this->imaginaryPart = imaginaryPart;
}

double ComplexNumber::getRealPart() const {
    return this->realPart;
}

double ComplexNumber::getImaginaryPart() const {
    return this->imaginaryPart;
}

void ComplexNumber::setRealPart(double val) {
    this->realPart = val;
}

void ComplexNumber::setImaginaryPart(double val) {
    this->imaginaryPart = val;
}

// ---- your work starts here ----

ComplexNumber ComplexNumber::operator+(const ComplexNumber& other) const {
    ComplexNumber res = ComplexNumber(this->realPart+other.realPart, this->imaginaryPart+other.imaginaryPart);

    return res;
}

ComplexNumber ComplexNumber::operator+(double val) const {
    ComplexNumber res = ComplexNumber(this->realPart + val, this->imaginaryPart);
    return res;
}

ComplexNumber ComplexNumber::operator-(const ComplexNumber& other) const {
    ComplexNumber res = ComplexNumber(this->realPart-other.realPart, this->imaginaryPart-other.imaginaryPart);
    return res;
}

ComplexNumber ComplexNumber::operator-(double val) const {
    ComplexNumber res = ComplexNumber(this->realPart-val, this->imaginaryPart);
    return res;
}

ComplexNumber ComplexNumber::operator*(const ComplexNumber& other) const {
    double realRes = (this->realPart * other.realPart) - (this->imaginaryPart * other.imaginaryPart);
    double imaginaryRes = (this->realPart * other.imaginaryPart) + (this->imaginaryPart * other.realPart);
    ComplexNumber res = ComplexNumber(realRes, imaginaryRes);
    return res;
}

ComplexNumber ComplexNumber::operator*(double val) const {
    ComplexNumber res = ComplexNumber(this->realPart*val, this->imaginaryPart*val);
    return res;
}

ComplexNumber ComplexNumber::operator/(const ComplexNumber& other) const {
    ComplexNumber conjugate = ComplexNumber(other.realPart, -other.imaginaryPart);
    ComplexNumber enumerator = *this * conjugate;
    ComplexNumber denominator = other * conjugate;
    ComplexNumber res = ComplexNumber(enumerator.realPart/denominator.realPart, enumerator.imaginaryPart/denominator.realPart);
    return res;
}

ComplexNumber ComplexNumber::operator/(double val) const {
    ComplexNumber res = ComplexNumber(this->realPart/val, this->imaginaryPart/val);
    return res;
}

ComplexNumber& ComplexNumber::operator+=(const ComplexNumber& other) {
    *this = *this + other;
    return *this;
}

ComplexNumber& ComplexNumber::operator+=(double val) {
    *this = *this + val;
    return *this;
}

ComplexNumber& ComplexNumber::operator-=(const ComplexNumber& other) {
    *this = *this - other;
    return *this;
}

ComplexNumber& ComplexNumber::operator-=(double val) {
    *this = *this - val;
    return *this;
}

ComplexNumber& ComplexNumber::operator*=(const ComplexNumber& other) {
    *this = *this * other;
    return *this;
}

ComplexNumber& ComplexNumber::operator*=(double val) {
    *this = *this * val;
    return *this;
}

ComplexNumber& ComplexNumber::operator/=(const ComplexNumber& other) {
    *this = *this / other;
    return *this;
}

ComplexNumber& ComplexNumber::operator/=(double val) {
    *this = *this / val;
    return *this;
}

bool ComplexNumber::operator==(const ComplexNumber& other) const {
    return this->realPart == other.realPart && this->imaginaryPart == other.imaginaryPart;
}

bool ComplexNumber::operator==(double val) const {
    return this->realPart == val && this->imaginaryPart == 0.0;
}

bool ComplexNumber::operator!=(const ComplexNumber& other) const {
    return !(*this == other);
}

bool ComplexNumber::operator!=(double val) const {
    return !(*this == val);
}

ComplexNumber operator+(double lhs, const ComplexNumber& rhs) {
    ComplexNumber res = rhs + lhs;
    return res;
}

ComplexNumber operator-(double lhs, const ComplexNumber& rhs) {

    ComplexNumber res = ComplexNumber(-rhs.getRealPart(), -rhs.getImaginaryPart());
    res += lhs;
    return res;
}

ComplexNumber operator*(double lhs, const ComplexNumber& rhs) {
    ComplexNumber res = rhs * lhs;
    return res;
}

ComplexNumber operator/(double lhs, const ComplexNumber& rhs) {
    ComplexNumber conjugate = ComplexNumber(rhs.getRealPart(), -rhs.getImaginaryPart());
    ComplexNumber res = (conjugate*lhs)/(rhs*conjugate);
    return res;
}

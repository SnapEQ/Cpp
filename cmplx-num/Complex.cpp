#include "Complex.h"
#include <cmath>
#include <stdexcept>

void throwIfZero(double val) {
    if (val == 0.0) {
        throw std::domain_error("Division by zero");
    }
}

ComplexNumber::ComplexNumber(double realPart, double imaginaryPart) {
    this->realPart = realPart;
    this->imaginaryPart = imaginaryPart;
}

double ComplexNumber::getRealPart() const{
    return this->realPart;
}

double ComplexNumber::getImaginaryPart() const{
    return this->imaginaryPart;
}

void ComplexNumber::setRealPart(double val) {
    this->realPart = val;
}

void ComplexNumber::setImaginaryPart(double val) {
    this->imaginaryPart = val;
}

ComplexNumber ComplexNumber::operator+(double val) const{
    return ComplexNumber(realPart+val, imaginaryPart);
}

ComplexNumber ComplexNumber::operator-(double val) const{
    return ComplexNumber(realPart-val, imaginaryPart);
}

ComplexNumber ComplexNumber::operator*(double val) const{
    return ComplexNumber(realPart * val, imaginaryPart * val);
}

ComplexNumber ComplexNumber::operator/(double val) const{
    throwIfZero(val);
    return ComplexNumber(realPart/val, imaginaryPart/val);
}

ComplexNumber& ComplexNumber::operator+=(const ComplexNumber& other) {

    *this = *this + other;

    return *this;
}

ComplexNumber& ComplexNumber::operator+=(double val) {
    this->realPart += val;

    return *this;
}

ComplexNumber& ComplexNumber::operator-=(const ComplexNumber& other) {

    *this = *this - other;

    return *this;
}

ComplexNumber& ComplexNumber::operator-=(double val) {
    this->realPart -= val;

    return *this;
}

ComplexNumber& ComplexNumber::operator*=(const ComplexNumber& other) {

    *this = *this * other;

    return *this;
}


ComplexNumber& ComplexNumber::operator*=(double val) {
    this->realPart *= val;
    this->imaginaryPart *= val;

    return *this;
}

ComplexNumber& ComplexNumber::operator/=(const ComplexNumber& other) {
    *this = *this / other;

    return *this;
}

ComplexNumber& ComplexNumber::operator/=(double val) {
    throwIfZero(val);
    this->realPart /= val;
    this->imaginaryPart /= val;

    return *this;
}

bool ComplexNumber::operator==(double val) const{
    return realPart == val && imaginaryPart == 0.0;
}

bool ComplexNumber::operator!=(double val) const {
    return !(*this == val);
}

double ComplexNumber::getAmplitude() const{
    return std::sqrt(this->realPart*this->realPart + this->imaginaryPart*this->imaginaryPart);
}

double ComplexNumber::getPhase() const {
    return std::atan2(this->imaginaryPart, this->realPart);
}

ComplexNumber operator+(const ComplexNumber& lhs, const ComplexNumber& rhs) {
    double realRes = lhs.getRealPart() + rhs.getRealPart();
    double imaginaryRes = lhs.getImaginaryPart() + rhs.getImaginaryPart();
    return ComplexNumber(realRes, imaginaryRes);
}

ComplexNumber operator-(const ComplexNumber& lhs, const ComplexNumber& rhs) {
    double realRes = lhs.getRealPart() - rhs.getRealPart();
    double imaginaryRes = lhs.getImaginaryPart() - rhs.getImaginaryPart();
    return ComplexNumber(realRes, imaginaryRes);
}

ComplexNumber operator*(const ComplexNumber& lhs, const ComplexNumber& rhs) {
    double realP = (lhs.getRealPart() * rhs.getRealPart()) - (lhs.getImaginaryPart() * rhs.getImaginaryPart());
    double imaginaryP = (lhs.getRealPart() * rhs.getImaginaryPart()) + (rhs.getRealPart() * lhs.getImaginaryPart());
    return ComplexNumber(realP, imaginaryP);
}

ComplexNumber operator/(const ComplexNumber& lhs, const ComplexNumber& rhs) {

    ComplexNumber conjugate = ComplexNumber(rhs.getRealPart(), -rhs.getImaginaryPart());

    ComplexNumber enumerator = lhs * conjugate;
    ComplexNumber denominator = rhs * conjugate;

    throwIfZero(denominator.getRealPart());

    return ComplexNumber(enumerator.getRealPart()/denominator.getRealPart(), enumerator.getImaginaryPart()/denominator.getRealPart());
}

bool operator==(const ComplexNumber& lhs, const ComplexNumber& rhs) {
    return lhs.getRealPart() == rhs.getRealPart() && lhs.getImaginaryPart() == rhs.getImaginaryPart();
}

bool operator!=(const ComplexNumber& lhs, const ComplexNumber& rhs) {
    return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& os, const ComplexNumber& num) {
    double imaginaryPart = num.getImaginaryPart();
    char sign = imaginaryPart < 0 ? '-' : '+';
    os << num.getRealPart() << ' ' << sign << ' ' << std::fabs(imaginaryPart) << 'i';
    return os;
}

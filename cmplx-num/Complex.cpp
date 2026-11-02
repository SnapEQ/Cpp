#include "Complex.h"
#include <cmath>

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

ComplexNumber ComplexNumber::operator+(const ComplexNumber &other) const{
    double realRes = realPart + other.realPart;
    double imaginaryRes = imaginaryPart + other.imaginaryPart;
    return ComplexNumber(realRes, imaginaryRes); 
}

ComplexNumber ComplexNumber::operator+(double val) const{
    return ComplexNumber(realPart+val, imaginaryPart);
}

ComplexNumber ComplexNumber::operator-(const ComplexNumber &other) const{
    double realRes = realPart - other.realPart;
    double imaginaryRes = imaginaryPart - other.imaginaryPart;
    return ComplexNumber(realRes, imaginaryRes);
}

ComplexNumber ComplexNumber::operator-(double val) const{
    return ComplexNumber(realPart-val, imaginaryPart);
}

ComplexNumber ComplexNumber::operator*(const ComplexNumber &other) const{
    double realP = (realPart * other.realPart) - (imaginaryPart * other.imaginaryPart);
    double imaginaryP = (realPart * other.imaginaryPart) + (other.realPart * imaginaryPart);
    return ComplexNumber(realP, imaginaryP);
}

ComplexNumber ComplexNumber::operator*(double val) const{
    return ComplexNumber(realPart * val, imaginaryPart * val);
}

ComplexNumber ComplexNumber::operator/(const ComplexNumber &other) const{
 
    ComplexNumber enumerator = ComplexNumber(realPart, imaginaryPart);
    ComplexNumber conjugate = ComplexNumber(other.realPart, -other.imaginaryPart);
    ComplexNumber denominator = ComplexNumber(other.realPart, other.imaginaryPart);

    enumerator = enumerator * conjugate;
    denominator = denominator * conjugate;

    return ComplexNumber(enumerator.realPart/denominator.realPart, enumerator.imaginaryPart/denominator.realPart);
}

ComplexNumber ComplexNumber::operator/(double val) const{
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
    this->realPart /= val;
    this->imaginaryPart /= val;

    return *this;
}

bool ComplexNumber::operator==(const ComplexNumber& other) const{
    return realPart == other.realPart && imaginaryPart == other.imaginaryPart;
}

bool ComplexNumber::operator==(double val) const{
    return realPart == val && imaginaryPart == 0.0;
}

bool ComplexNumber::operator!=(const ComplexNumber& other) const{
    return realPart != other.realPart || imaginaryPart != other.imaginaryPart;
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

ComplexNumber operator+(double lhs, const ComplexNumber& rhs) {
    return rhs + lhs;
}

ComplexNumber operator-(double lhs, const ComplexNumber& rhs) {
    return ComplexNumber(lhs, 0.0) - rhs;
}

ComplexNumber operator*(double lhs, const ComplexNumber& rhs) {
    return rhs * lhs;
}

ComplexNumber operator/(double lhs, const ComplexNumber& rhs) {
    ComplexNumber lhsCmplx = ComplexNumber(lhs, 0.0);
    return lhsCmplx / rhs;
}



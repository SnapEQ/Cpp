#pragma once

#include <ostream>

class ComplexNumber {
    private:
        double realPart;
        double imaginaryPart;

    public:
        ComplexNumber(double realPart = 0, double imaginaryPart = 0);
        double getRealPart() const;
        double getImaginaryPart() const;
        void setRealPart(double val);
        void setImaginaryPart(double val);
        ComplexNumber operator+(double val) const;
        ComplexNumber operator-(double val) const;
        ComplexNumber operator*(double val) const;
        ComplexNumber operator/(double val) const;
        ComplexNumber& operator+=(const ComplexNumber& other);
        ComplexNumber& operator+=(double val);
        ComplexNumber& operator-=(const ComplexNumber& other);
        ComplexNumber& operator-=(double val);
        ComplexNumber& operator*=(const ComplexNumber& other);
        ComplexNumber& operator*=(double val);
        ComplexNumber& operator/=(const ComplexNumber& other);
        ComplexNumber& operator/=(double val);
        bool operator==(double val) const;
        bool operator!=(double val) const;
        double getAmplitude() const;
        double getPhase() const;

};

ComplexNumber operator+(const ComplexNumber& lhs, const ComplexNumber& rhs);
ComplexNumber operator-(const ComplexNumber& lhs, const ComplexNumber& rhs);
ComplexNumber operator*(const ComplexNumber& lhs, const ComplexNumber& rhs);
ComplexNumber operator/(const ComplexNumber& lhs, const ComplexNumber& rhs);
bool operator==(const ComplexNumber& lhs, const ComplexNumber& rhs);
bool operator!=(const ComplexNumber& lhs, const ComplexNumber& rhs);
std::ostream& operator<<(std::ostream& os, const ComplexNumber& num);

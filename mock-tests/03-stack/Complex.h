#pragma once

// DO NOT change the public interface - TestComplexStack.cpp depends on it.

class ComplexNumber {
    private:
        double realPart;
        double imaginaryPart;

    public:
        // default arguments let you create arrays: new ComplexNumber[n]
        ComplexNumber(double realPart = 0.0, double imaginaryPart = 0.0);
        double getRealPart() const;
        double getImaginaryPart() const;
        void setRealPart(double val);
        void setImaginaryPart(double val);

        ComplexNumber operator+(const ComplexNumber& other) const;
        ComplexNumber operator+(double val) const;
        ComplexNumber operator-(const ComplexNumber& other) const;
        ComplexNumber operator-(double val) const;
        ComplexNumber operator*(const ComplexNumber& other) const;
        ComplexNumber operator*(double val) const;
        ComplexNumber operator/(const ComplexNumber& other) const;
        ComplexNumber operator/(double val) const;
        ComplexNumber& operator+=(const ComplexNumber& other);
        ComplexNumber& operator+=(double val);
        ComplexNumber& operator-=(const ComplexNumber& other);
        ComplexNumber& operator-=(double val);
        ComplexNumber& operator*=(const ComplexNumber& other);
        ComplexNumber& operator*=(double val);
        ComplexNumber& operator/=(const ComplexNumber& other);
        ComplexNumber& operator/=(double val);
        bool operator==(const ComplexNumber& other) const;
        bool operator==(double val) const;
        bool operator!=(const ComplexNumber& other) const;
        bool operator!=(double val) const;
};

ComplexNumber operator+(double lhs, const ComplexNumber& rhs);
ComplexNumber operator-(double lhs, const ComplexNumber& rhs);
ComplexNumber operator*(double lhs, const ComplexNumber& rhs);
ComplexNumber operator/(double lhs, const ComplexNumber& rhs);

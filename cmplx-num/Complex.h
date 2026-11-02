#pragma once

class ComplexNumber {
    private:
        double realPart;
        double imaginaryPart;

    public:
        ComplexNumber(double realPart, double imaginaryPart);
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
        double getAmplitude() const;
        double getPhase() const;

};

ComplexNumber operator+(double lhs, const ComplexNumber& rhs);
ComplexNumber operator-(double lhs, const ComplexNumber& rhs);
ComplexNumber operator*(double lhs, const ComplexNumber& rhs);
ComplexNumber operator/(double lhs, const ComplexNumber& rhs);


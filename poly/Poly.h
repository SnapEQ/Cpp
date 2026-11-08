#pragma once

#include <map>
#include <functional>
#include <ostream>

class Poly {

    std::map<int, double, std::greater<int>> coefficients;

    void removeZeros();

    public:


        class CoefficientRef {
            Poly& poly;
            int exponent;

            public:

                CoefficientRef(Poly& poly, int exponent);
                operator double() const;
                CoefficientRef& operator=(double val);
                CoefficientRef& operator=(const CoefficientRef& other);
                CoefficientRef& operator+=(double val);
                CoefficientRef& operator-=(double val);
        };

        Poly() = default;
        Poly(double constant);
        CoefficientRef operator[](int exponent);
        double operator[](int exponent) const;
        Poly operator+(const Poly& other) const;
        Poly operator+(double val) const;
        Poly operator-(const Poly& other) const;
        Poly operator-(double val) const;
        Poly operator*(const Poly& other) const;
        Poly operator*(double val) const;
        Poly operator-() const;
        double operator()(double x) const;
        friend std::ostream& operator<<(std::ostream& out, const Poly& p);
};

Poly operator+(double val, const Poly& poly);
Poly operator-(double val, const Poly& poly);
Poly operator*(double val, const Poly& poly);



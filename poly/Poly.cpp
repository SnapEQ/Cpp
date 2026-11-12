#include "Poly.h"
#include <ostream>
#include <cmath>

Poly::CoefficientRef::CoefficientRef(Poly& poly, int exponent)
    : poly(poly), exponent(exponent) {}

Poly::CoefficientRef::operator double() const {
    return static_cast<const Poly&>(poly)[exponent];
}

Poly::CoefficientRef& Poly::CoefficientRef::operator=(double val) {
    if (val == 0.0)
        poly.coefficients.erase(exponent);
    else
        poly.coefficients[exponent] = val;

    return *this;
}

Poly::CoefficientRef& Poly::CoefficientRef::operator=(const CoefficientRef& other) {
    return *this = static_cast<double>(other);
}

Poly::CoefficientRef& Poly::CoefficientRef::operator+=(double val) {
    return *this = static_cast<double>(*this) + val;
}

Poly::CoefficientRef& Poly::CoefficientRef::operator-=(double val) {
    return *this = static_cast<double>(*this) - val;
}

void Poly::removeZeros() {
    for (auto it = coefficients.begin(); it != coefficients.end();) {
        if (it->second == 0.0)
            it = coefficients.erase(it);
        else
            ++it;
    }
}

Poly::Poly(double constant) {
    (*this)[0] = constant;
}

Poly::CoefficientRef Poly::operator[](int exponent) {
    return CoefficientRef(*this, exponent);
}

double Poly::operator[](int exponent) const {
    auto it = coefficients.find(exponent);
    return it == coefficients.end() ? 0.0 : it->second;
}

Poly Poly::operator+(const Poly &other) const{
    Poly res = *this;
    for (const auto& [exponent, coefficient] : other.coefficients) {
        res.coefficients[exponent] += coefficient;
    }

    res.removeZeros();
    return res;
}

Poly Poly::operator+(double val) const {
    Poly res = *this;
    res[0] += val;

    res.removeZeros();
    return res;
}

Poly Poly::operator-(const Poly& other) const {
    Poly res = *this;
    for (const auto& [exponent, coefficient] : other.coefficients) {
        res.coefficients[exponent] -= coefficient;
    }

    res.removeZeros();
    return res;
}

Poly Poly::operator-(double val) const {
    Poly res = *this;
    res[0] -= val;

    res.removeZeros();
    return res;
}

Poly Poly::operator*(const Poly& other) const {
    Poly res;

    for (const auto& [exponent1, coefficient1] : this->coefficients) {
        for (const auto& [exponent2, coefficient2] : other.coefficients) {
            res.coefficients[exponent1 + exponent2] += coefficient1  * coefficient2;
        }
    }

    res.removeZeros();
    return res;
}

Poly Poly::operator*(double val) const {
    Poly res = *this;

    for (auto& [exponent, coefficient] : res.coefficients) {
        coefficient *= val;
    }

    res.removeZeros();
    return res;
}

Poly Poly::operator-() const {
    Poly res = *this;

    for (auto& [exponent, coefficient] : res.coefficients) {
        coefficient = -coefficient;
    }

    return res;
}

double Poly::operator()(double x) const {
    double res = 0.0;

    for (const auto& [exponent, coefficient] : coefficients) {
        res += coefficient * std::pow(x, exponent);
    }

    return res;
}

std::ostream& operator<<(std::ostream& out, const Poly& p) {
    if (p.coefficients.empty())
        return out << 0;

    bool first = true;

    for (const auto& [exponent, coefficient] : p.coefficients) {
        if (!first && coefficient > 0)
            out << "+";

        out << coefficient;

        if (exponent == 1)
            out << "x";
        else if (exponent > 1)
            out << "x^" << exponent;

        first = false;
    }

    return out;
}

Poly operator+(double val, const Poly& poly) {
    return poly + val;
}

Poly operator-(double val, const Poly& poly) {
    return -poly + val;
}

Poly operator*(double val, const Poly& poly) {
    return poly * val;
}

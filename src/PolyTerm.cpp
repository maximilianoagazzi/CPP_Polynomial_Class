#include <iostream>
#include "../include/PolyTerm.hpp"

PolyTerm::PolyTerm(double C, int E) : Coef(C), Exp(E) {
    if(E < 0) throw std::invalid_argument("Exponent cannot be negative.");
}

PolyTerm::PolyTerm(const PolyTerm& p) : Coef(p.Coef), Exp(p.Exp) {}

double PolyTerm::GetCoef() const {
    return Coef;
}

int PolyTerm::GetExp() const {
    return Exp;
}

PolyTerm& PolyTerm::operator=(const PolyTerm& p) {
    if(this != &p) {
        Coef = p.Coef;
        Exp = p.Exp;
    }

    return *this;
}

PolyTerm& PolyTerm::operator+=(const PolyTerm& p) {
    if (Exp != p.Exp) throw std::invalid_argument("PolTerms must have the same exponent in order to be added");
    
    Coef += p.Coef;
    return *this;
}

PolyTerm& PolyTerm::operator-=(const PolyTerm& p) {
    if (Exp != p.Exp) throw std::invalid_argument("PolTerms must have the same exponent in order to be added");
    
    Coef -= p.Coef;
    return *this;
}

PolyTerm& PolyTerm::operator*=(const PolyTerm& p) {
    Coef *= p.Coef;
    Exp += p.Exp;
    return *this;
}

PolyTerm& PolyTerm::operator*=(const double c) {
    Coef *= c;
    return *this;
}

PolyTerm& PolyTerm::operator/=(const PolyTerm& p) {
    if(Exp < p.Exp) throw std::invalid_argument("PolTerms are only divisible if the exponent of the denominator is smaller than that of the numerator");

    if (p.Coef == 0.0f) throw std::invalid_argument("Cannot divide by a term with a coefficient of zero");

    Coef /= p.Coef;
    Exp -= p.Exp;
    return *this;
}

PolyTerm& PolyTerm::operator/=(const double c) {
    if(c == 0.0f) throw std::invalid_argument("Cannot divide by zero");

    Coef /= c;
    return *this;
}

PolyTerm PolyTerm::operator+(const PolyTerm& p) const {
    if (Exp != p.Exp) throw std::invalid_argument("PolTerms must have the same exponent in order to be added");

    return PolyTerm(Coef + p.Coef, Exp);
}

PolyTerm PolyTerm::operator-(const PolyTerm& p) const {
    if (Exp != p.Exp) throw std::invalid_argument("PolTerms must have the same exponent in order to be added");

    return PolyTerm(Coef - p.Coef, Exp);
}

PolyTerm PolyTerm::operator*(const PolyTerm& p) const {
    return PolyTerm(Coef * p.Coef, Exp + p.Exp);
}

PolyTerm PolyTerm::operator*(double c) const {
    return PolyTerm(Coef * c, Exp);
}

PolyTerm operator*(double c, const PolyTerm& p) {
    return PolyTerm(c * p.Coef, p.Exp);
}

PolyTerm PolyTerm::operator/(const PolyTerm& p) const {
    if(Exp < p.Exp) throw std::invalid_argument("PolTerms are only divisible if the exponent of the denominator is smaller than that of the numerator");

    if (p.Coef == 0.0f) throw std::invalid_argument("Cannot divide by a term with a coefficient of zero");

    return PolyTerm(Coef / p.Coef, Exp - p.Exp);
}

PolyTerm PolyTerm::operator/(double c) const {
    if (c == 0.0f) throw std::invalid_argument("Cannot divide by zero");

    return PolyTerm(Coef / c, Exp);
}

bool PolyTerm::operator==(const PolyTerm& p) const {
    return Exp == p.Exp && Coef == p.Coef;
}

bool PolyTerm::operator!=(const PolyTerm& p) const {
    return Exp != p.Exp || Coef != p.Coef;
}

bool PolyTerm::operator<(const PolyTerm& p) const {
    if(Exp == p.Exp) return Coef < p.Coef;
    return Exp < p.Exp;

}

bool PolyTerm::operator<=(const PolyTerm& p) const {
    if(Exp == p.Exp) return Coef <= p.Coef;
    return Exp < p.Exp;
}

bool PolyTerm::operator>(const PolyTerm& p) const {
    if(Exp == p.Exp) return Coef > p.Coef;
    return Exp > p.Exp;
}

bool PolyTerm::operator>=(const PolyTerm& p) const {
    if(Exp == p.Exp) return Coef >= p.Coef;
    return Exp > p.Exp;
}

bool PolyTerm::operator!() const {
    return Coef == 0;
}

PolyTerm::operator bool() const {
    return Coef != 0;
}

std::istream& operator>>(std::istream& is, PolyTerm& p) {
    float C;
    int E;
    char sep;

    is >> C >> sep >> E;

    if(sep != '_' && sep != '|' && sep != '^' && sep != ';' && sep != ':') {
        is.setstate(std::ios::failbit);
        return is;
    }

    if(E < 0) {
        is.setstate(std::ios::failbit);
        return is;
    } else {
        p.Coef = C;
        p.Exp = E;
    }

    return is;
}

std::ostream& operator<<(std::ostream& os, const PolyTerm& p) {
    if(p.Exp == 0 || p.Coef == 0) {
        if(p.Coef < 0) os << "- " << -p.Coef;
        else os << p.Coef;
    } else if(p.Exp == 1) {
        if(p.Coef < 0) os << "- " << -p.Coef << "x";
        else os << p.Coef << "x";
    } else if(p.Coef == 1) {
        os << "x^(" << p.Exp << ")";
    } else if(p.Coef == -1) {
        os << "- x^(" << p.Exp << ")";
    } else if(p.Coef < -1) {
        os << "- " << -p.Coef << "x^(" << p.Exp << ")";
    } else {
        os << p.Coef << "x^(" << p.Exp << ")";
    }

    return os;
}
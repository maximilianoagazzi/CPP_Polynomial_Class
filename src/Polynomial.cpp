#include <iostream>
#include <algorithm>
#include "../include/Polynomial.hpp"

//PolTerm

Polynomial::PolyTerm::PolyTerm(float C, int E) : Coef(C), Exp(E) {
    if(E < 0) throw std::invalid_argument("Exponent cannot be negative.");
}

Polynomial::PolyTerm::PolyTerm(const PolyTerm& p) : Coef(p.Coef), Exp(p.Exp) {}

float Polynomial::PolyTerm::GetCoef() const {
    return Coef;
}

int Polynomial::PolyTerm::GetExp() const {
    return Exp;
}

Polynomial::PolyTerm& Polynomial::PolyTerm::operator=(const PolyTerm& p) {
    if(this != &p) {
        Coef = p.Coef;
        Exp = p.Exp;
    }

    return *this;
}

Polynomial::PolyTerm& Polynomial::PolyTerm::operator+=(const PolyTerm& p) {
    if (Exp != p.Exp) throw std::invalid_argument("PolTerms must have the same exponent in order to be added");
    
    Coef += p.Coef;
    return *this;
}

Polynomial::PolyTerm& Polynomial::PolyTerm::operator-=(const PolyTerm& p) {
    if (Exp != p.Exp) throw std::invalid_argument("PolTerms must have the same exponent in order to be added");
    
    Coef -= p.Coef;
    return *this;
}

Polynomial::PolyTerm& Polynomial::PolyTerm::operator*=(const PolyTerm& p) {
    Coef *= p.Coef;
    Exp += p.Exp;
    return *this;
}

Polynomial::PolyTerm& Polynomial::PolyTerm::operator*=(const float c) {
    Coef *= c;
    return *this;
}

Polynomial::PolyTerm& Polynomial::PolyTerm::operator/=(const PolyTerm& p) {
    if(Exp < p.Exp) throw std::invalid_argument("PolTerms are only divisible if the exponent of the denominator is smaller than that of the numerator");

    if (p.Coef == 0.0f) throw std::invalid_argument("Cannot divide by a term with a coefficient of zero");

    Coef /= p.Coef;
    Exp -= p.Exp;
    return *this;
}

Polynomial::PolyTerm& Polynomial::PolyTerm::operator/=(const float c) {
    if(c == 0.0f) throw std::invalid_argument("Cannot divide by zero");

    Coef /= c;
    return *this;
}

Polynomial::PolyTerm Polynomial::PolyTerm::operator+(const PolyTerm& p) const {
    if (Exp != p.Exp) throw std::invalid_argument("PolTerms must have the same exponent in order to be added");

    return PolyTerm(Coef + p.Coef, Exp);
}

Polynomial::PolyTerm Polynomial::PolyTerm::operator-(const PolyTerm& p) const {
    if (Exp != p.Exp) throw std::invalid_argument("PolTerms must have the same exponent in order to be added");

    return PolyTerm(Coef - p.Coef, Exp);
}

Polynomial::PolyTerm Polynomial::PolyTerm::operator*(const PolyTerm& p) const {
    return PolyTerm(Coef * p.Coef, Exp + p.Exp);
}

Polynomial::PolyTerm Polynomial::PolyTerm::operator*(float c) const {
    return PolyTerm(Coef * c, Exp);
}

Polynomial::PolyTerm Polynomial::PolyTerm::operator/(const PolyTerm& p) const {
    if(Exp < p.Exp) throw std::invalid_argument("PolTerms are only divisible if the exponent of the denominator is smaller than that of the numerator");

    if (p.Coef == 0.0f) throw std::invalid_argument("Cannot divide by a term with a coefficient of zero");

    return PolyTerm(Coef / p.Coef, Exp - p.Exp);
}

Polynomial::PolyTerm Polynomial::PolyTerm::operator/(float c) const {
    if (c == 0.0f) throw std::invalid_argument("Cannot divide by zero");

    return PolyTerm(Coef / c, Exp);
}

bool Polynomial::PolyTerm::operator==(const PolyTerm& p) const {
    return Exp == p.Exp && Coef == p.Coef;
}

bool Polynomial::PolyTerm::operator!=(const PolyTerm& p) const {
    return Exp != p.Exp || Coef != p.Coef;
}

bool Polynomial::PolyTerm::operator<(const PolyTerm& p) const {
    if(Exp == p.Exp) return Coef < p.Coef;
    return Exp < p.Exp;

}

bool Polynomial::PolyTerm::operator<=(const PolyTerm& p) const {
    if(Exp == p.Exp) return Coef <= p.Coef;
    return Exp < p.Exp;
}

bool Polynomial::PolyTerm::operator>(const PolyTerm& p) const {
    if(Exp == p.Exp) return Coef > p.Coef;
    return Exp > p.Exp;
}

bool Polynomial::PolyTerm::operator>=(const PolyTerm& p) const {
    if(Exp == p.Exp) return Coef >= p.Coef;
    return Exp > p.Exp;
}

bool Polynomial::PolyTerm::operator!() const {
    return Coef == 0;
}

Polynomial::PolyTerm::operator bool() const {
    return Coef != 0;
}

//Polynomial

Polynomial::Polynomial() : degree(0), Amount_missing_terms(0) {
    Poly.push_back(PolyTerm(0, 0));  //Make the null polynomial
}

Polynomial::Polynomial(const Polynomial& p) : degree(p.degree), Amount_missing_terms(p.Amount_missing_terms), Poly(p.Poly) {}

void Polynomial::correct_grade() {
    if (!Poly.empty()) {
        degree = Poly[0].GetExp();
        Amount_missing_terms = degree - Poly.size() + 1;
    } else {
        degree = 0;
        Amount_missing_terms = 0;
        Poly.push_back(PolyTerm(0, 0));
    }
}

void Polynomial::sort_by_exponent() {
    if (Poly.empty()) return;
    std::sort(Poly.begin(), Poly.end(), std::greater<PolyTerm>());  //sort the polynomial

    for(std::size_t i=0; i<Poly.size()-1;) {
        if(Poly[i].GetExp() == Poly[i+1].GetExp()) {
            Poly[i] += Poly[i+1];  //Add the terms with the same exponent

            Poly.erase(Poly.begin() + i + 1);  //erase the invalid term
        } else {
            i++;
        }
    }

    for(int i=0; i<Poly.size();) {  //Delete nulls terms
        if(!Poly[i]) Poly.erase(Poly.begin() + i);
        else i++;
    }
}

void Polynomial::complete_polynomial() {
    for(int i=1; i<=degree; i++) {
        if(i >= Poly.size() || Poly[i].GetExp() != degree - i) {
            Poly.insert(Poly.begin() + i, PolyTerm(0, degree - i));
        }
    }
    Amount_missing_terms = 0;
}

void Polynomial::SetPolyTerms() {  //Set the polynomial by adding terms as many as the user wants
    std::cout << "Enter a coefficient first, then its exponent separated by (^, |, _, :, or ;)" << std::endl;
    char ccontinue = 's';

    Poly.clear();

    while(ccontinue == 's' || ccontinue == 'S') {
        PolyTerm tempTerm(0, 0); 
        std::cin >> tempTerm; 
        
        Poly.push_back(tempTerm); 

        std::cout << "\nThere are more terms not null? (s/n): ";
        std::cin >> ccontinue;
    }

    sort_by_exponent(); 
    correct_grade();
}

void Polynomial::SetPolyTerms(int d) {  //Set the polynomial by adding terms as many as the user wants but predefining the degree
    if(d < 0) throw std::invalid_argument("Degree cannot be negative.");
    degree = d;
    Poly.clear();

    int C;
    std::cout << "First enter the coefficient of the degree term" << degree << std::endl;
    std::cin >> C;
    if(C == 0) throw std::invalid_argument("The coefficient of the degree term cannot be zero");

    Poly.push_back(PolyTerm(C, degree));

    if(degree != 0) {
        char ccontinue = 's';

        std::cout << "Enter a coefficient first, then its exponent separated by (^, |, _, :, or ;)" << std::endl;

        while(ccontinue == 's' || ccontinue == 'S') {
            PolyTerm tempTerm(0, 0); 
            std::cin >> tempTerm;
            if(tempTerm.GetExp() > degree) throw std::invalid_argument("An exponent cannot be bigger than the polynomial degree");

            Poly.push_back(tempTerm);

            std::cout << "\nThere are more terms not null? (s/n): ";
            std::cin >> ccontinue;
        }
        sort_by_exponent();
    }

    Amount_missing_terms = degree - Poly.size() + 1;
}

void Polynomial::SetPolyTerms(const std::vector<float>& C, const std::vector<int>& E) {
    if(C.size() != E.size()) throw std::invalid_argument("Coefficient vector and exponent vector must have the same size");

    Poly.clear();
    for(std::size_t i=0; i<C.size(); i++) {
        if(E[i] < 0) throw std::invalid_argument("Exponents cannot be negative");
        Poly.push_back(PolyTerm(C[i], E[i]));
    }

    sort_by_exponent();
    correct_grade();
}

int Polynomial::GetDegree() const {
    return degree;
}

bool Polynomial::Is_complete() const {
    return Amount_missing_terms == 0;
}

float Polynomial::operator[](int Exp) const {
    if(Exp > degree) return 0.0;

    int finded = -1;
    float result = 0.0;

    for(std::size_t i=0; i<Poly.size() && finded == -1; i++) {
        if(Exp == Poly[i].GetExp()) finded = i;
    }

    if(finded != -1) result = Poly[finded].GetCoef();

    return result;
}

Polynomial& Polynomial::operator=(const Polynomial& p) {
    if (this != &p) {
        Poly = p.Poly;
        degree = p.degree;
        Amount_missing_terms = p.Amount_missing_terms;
    }

    return *this;
}

Polynomial& Polynomial::operator+=(const Polynomial& p) {
    for(std::size_t i=0; i<p.Poly.size(); i++) {
        Poly.push_back(PolyTerm(p.Poly[i].GetCoef(), p.Poly[i].GetExp()));
    }

    sort_by_exponent();
    correct_grade();

    return *this;
}

Polynomial& Polynomial::operator-=(const Polynomial& p) {
    for(std::size_t i=0; i<p.Poly.size(); i++) {
        Poly.push_back(PolyTerm(-p.Poly[i].GetCoef(), p.Poly[i].GetExp()));
    }

    sort_by_exponent();
    correct_grade();

    return *this;
}

Polynomial& Polynomial::operator*=(const Polynomial& p) {
    std::vector<PolyTerm> temp;

    for(std::size_t i=0; i<p.Poly.size(); i++) {
        for(std::size_t j=0; j<Poly.size(); j++) {
            temp.push_back(Poly[j] * p.Poly[i]);
        }
    }

    Poly = temp;

    sort_by_exponent();
    correct_grade();

    return *this;
}

Polynomial& Polynomial::operator*=(const float c) {
    for(std::size_t i=0; i<Poly.size(); i++) {
        Poly[i] *= c;
    }

    sort_by_exponent();
    correct_grade();

    return *this;
}

Polynomial& Polynomial::operator/=(const float c) {
    if(c == 0) throw std::invalid_argument("You cannot divide by zero");

    for(std::size_t i=0; i<Poly.size(); i++) {
        Poly[i] /= c;
    }

    sort_by_exponent();
    correct_grade();

    return *this;
}

Polynomial Polynomial::operator+(const Polynomial& p) const {
    Polynomial result = *this;
    result += p;
    return result;
}

Polynomial Polynomial::operator-(const Polynomial& p) const {
    Polynomial result = *this;
    result -= p;
    return result;
}

Polynomial Polynomial::operator*(const Polynomial& p) const {
    Polynomial result = *this;
    result *= p;
    return result;
}

Polynomial Polynomial::operator*(float c) const {
    Polynomial result = *this;
    result *= c;
    return result;
}

Polynomial operator*(float c, const Polynomial& p) {
    return p * c;
}

Polynomial& Polynomial::Division_algorithm(const Polynomial& p, Polynomial& c) {
    if (p.Poly.empty() || (p.Poly.size() == 1 && p.Poly[0].GetCoef() == 0)) {
        throw std::invalid_argument("Cannot divide by zero polynomial.");
    }

    correct_grade();

    if (degree < p.degree) return *this;

    c.Poly.push_back(Poly[0] / p.Poly[0]);

    Polynomial aux;
    aux.Poly.clear();
    aux.Poly.push_back(c.Poly.back());

    aux *= p;

    *this -= aux;
    sort_by_exponent();
    correct_grade();

    return Division_algorithm(p, c);
}

Polynomial Polynomial::operator/(const Polynomial& p) const {
    Polynomial R = *this;
    Polynomial c;

    c.Poly.clear();
    R.complete_polynomial();
    R.Division_algorithm(p, c);
    c.correct_grade();

    return c;
}

Polynomial Polynomial::operator/(float c) const {
    Polynomial result = *this;
    result /= c;
    return result;
}

Polynomial Polynomial::operator%(const Polynomial& p) const {
    Polynomial R = *this;
    Polynomial c;

    c.Poly.clear();
    R.complete_polynomial();
    R.Division_algorithm(p, c);
    R.correct_grade();

    return R;
}

bool Polynomial::operator==(const Polynomial& p) const {
    if (degree != p.degree) return false;

    return Poly == p.Poly;
}

bool Polynomial::operator!=(const Polynomial& p) const {
    return !(*this == p);
}

bool Polynomial::operator<(const Polynomial& p) const {
    if(degree == p.degree) return Poly < p.Poly;
    return degree < p.degree;
}

bool Polynomial::operator<=(const Polynomial& p) const {
    if(degree == p.degree) return Poly <= p.Poly;
    return degree < p.degree;
}

bool Polynomial::operator>(const Polynomial& p) const {
    if(degree == p.degree) return Poly > p.Poly;
    return degree > p.degree;
}

bool Polynomial::operator>=(const Polynomial& p) const {
    if(degree == p.degree) return Poly >= p.Poly;
    return degree > p.degree;
}

bool Polynomial::operator!() const {
    if(degree == 0) return Poly[0].GetCoef() == 0;
    return false;
}

Polynomial::operator bool() const {
    if(degree == 0) return Poly[0].GetCoef() != 0;
    return true;
}

std::ostream& operator<<(std::ostream& os, const Polynomial& p) {
    if (p.Poly.empty()) return os << "0";

    os << p.Poly[0];

    for(std::size_t i=1; i<p.Poly.size(); i++) {
        if (p.Poly[i].GetCoef() < 0) {
            os << " " << p.Poly[i]; 
        } else {
            os << " + " << p.Poly[i];
        }
    }

    os << std::endl;

    return os;
}
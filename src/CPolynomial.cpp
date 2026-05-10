#include <iostream>
#include <algorithm>
#include <cmath>
#include "../include/CPolynomial.hpp"

int aux(PolyTerm a, PolyTerm b) {
    int expa = a.GetExp();
    int expb = b.GetExp();

    return expb - expa;
}

CPolynomial::CPolynomial() : degree(0), Amount_missing_terms(0) {
    Poly.push_back(PolyTerm(0, 0));  //Make the null polynomial
}

CPolynomial::CPolynomial(const CPolynomial& p) : degree(p.degree), Amount_missing_terms(p.Amount_missing_terms), Poly(p.Poly) {}

void CPolynomial::correct_grade() {
    if (!Poly.is_empty()) {
        degree = Poly[0].GetExp();
        Amount_missing_terms = degree - Poly.size() + 1;
    } else {
        degree = 0;
        Amount_missing_terms = 0;
        Poly.push_back(PolyTerm(0, 0));
    }
}

void CPolynomial::sort_by_exponent() {
    if (Poly.is_empty()) return;
    Poly.sort(aux);  //sort the polynomial

    for(std::size_t i=0; i<Poly.size()-1;) {
        if(Poly[i].GetExp() == Poly[i+1].GetExp()) {
            Poly[i] += Poly[i+1];  //Add the terms with the same exponent

            Poly.erase(i + 1);  //erase the invalid term
        } else {
            i++;
        }
    }

    for(int i=0; i<Poly.size();) {  //Delete nulls terms
        if(!Poly[i]) Poly.erase(i);
        else i++;
    }
}

void CPolynomial::complete_polynomial() {
    for(int i=1; i<=degree; i++) {
        if(i >= Poly.size() || Poly[i].GetExp() != degree - i) {
            Poly.insert(PolyTerm(0, degree - i), i);
        }
    }
    Amount_missing_terms = 0;
}

void CPolynomial::AddPolyTerms() {  //Set the polynomial by adding terms as many as the user wants
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

void CPolynomial::AddPolyTerms(int d) {  //Set the polynomial by adding terms as many as the user wants but predefining the degree
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

void CPolynomial::AddPolyTerms(const std::vector<float>& C, const std::vector<int>& E) {
    if(C.size() != E.size()) throw std::invalid_argument("Coefficient vector and exponent vector must have the same size");

    Poly.clear();
    for(std::size_t i=0; i<C.size(); i++) {
        if(E[i] < 0) throw std::invalid_argument("Exponents cannot be negative");
        Poly.push_back(PolyTerm(C[i], E[i]));
    }

    sort_by_exponent();
    correct_grade();
}

int CPolynomial::GetDegree() const {
    return degree;
}

int CPolynomial::GetAmountTerms() const {
    return Poly.size();
}

bool CPolynomial::Is_complete() const {
    return Amount_missing_terms == 0;
}

float CPolynomial::operator[](int Exp) const {
    if(Exp > degree) return 0.0;

    int finded = -1;
    float result = 0.0;

    for(std::size_t i=0; i<Poly.size() && finded == -1; i++) {
        if(Exp == Poly[i].GetExp()) finded = i;
    }

    if(finded != -1) result = Poly[finded].GetCoef();

    return result;
}

double CPolynomial::operator()(float x) const {
    double result = 0.0;

    for(std::size_t i=0; i<Poly.size(); i++)
        result += Poly[i].GetCoef() * std::pow(x, Poly[i].GetExp());

    return result;
}

CPolynomial::operator double() const {
    return (*this)(1.0);
}

CPolynomial& CPolynomial::operator=(const CPolynomial& p) {
    if (this != &p) {
        Poly = p.Poly;
        degree = p.degree;
        Amount_missing_terms = p.Amount_missing_terms;
    }

    return *this;
}

CPolynomial& CPolynomial::operator+=(const CPolynomial& p) {
    for(std::size_t i=0; i<p.Poly.size(); i++) {
        Poly.push_back(PolyTerm(p.Poly[i].GetCoef(), p.Poly[i].GetExp()));
    }

    sort_by_exponent();
    correct_grade();

    return *this;
}

CPolynomial& CPolynomial::operator-=(const CPolynomial& p) {
    for(std::size_t i=0; i<p.Poly.size(); i++) {
        Poly.push_back(PolyTerm(-p.Poly[i].GetCoef(), p.Poly[i].GetExp()));
    }

    sort_by_exponent();
    correct_grade();

    return *this;
}

CPolynomial& CPolynomial::operator*=(const CPolynomial& p) {
    CVector temp;

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

CPolynomial& CPolynomial::operator*=(const float c) {
    for(std::size_t i=0; i<Poly.size(); i++) {
        Poly[i] *= c;
    }

    sort_by_exponent();
    correct_grade();

    return *this;
}

CPolynomial& CPolynomial::operator/=(const float c) {
    if(c == 0) throw std::invalid_argument("You cannot divide by zero");

    for(std::size_t i=0; i<Poly.size(); i++) {
        Poly[i] /= c;
    }

    sort_by_exponent();
    correct_grade();

    return *this;
}

CPolynomial CPolynomial::operator+(const CPolynomial& p) const {
    CPolynomial result = *this;
    result += p;
    return result;
}

CPolynomial CPolynomial::operator-(const CPolynomial& p) const {
    CPolynomial result = *this;
    result -= p;
    return result;
}

CPolynomial CPolynomial::operator*(const CPolynomial& p) const {
    CPolynomial result = *this;
    result *= p;
    return result;
}

CPolynomial CPolynomial::operator*(float c) const {
    CPolynomial result = *this;
    result *= c;
    return result;
}

CPolynomial operator*(float c, const CPolynomial& p) {
    return p * c;
}

CPolynomial& CPolynomial::Division_algorithm(const CPolynomial& p, CPolynomial& c) {
    if (p.Poly.is_empty() || (p.Poly.size() == 1 && p.Poly[0].GetCoef() == 0)) {
        throw std::invalid_argument("Cannot divide by zero polynomial.");
    }

    correct_grade();

    if (degree < p.degree) return *this;

    c.Poly.push_back(Poly[0] / p.Poly[0]);

    CPolynomial aux;
    aux.Poly.clear();
    aux.Poly.push_back(c.Poly[c.Poly.size()-1]);

    aux *= p;

    *this -= aux;
    sort_by_exponent();
    correct_grade();

    return Division_algorithm(p, c);
}

CPolynomial CPolynomial::operator/(const CPolynomial& p) const {
    CPolynomial R = *this;
    CPolynomial c;

    c.Poly.clear();
    R.complete_polynomial();
    R.Division_algorithm(p, c);
    c.correct_grade();

    return c;
}

CPolynomial CPolynomial::operator/(float c) const {
    CPolynomial result = *this;
    result /= c;
    return result;
}

CPolynomial CPolynomial::operator%(const CPolynomial& p) const {
    CPolynomial R = *this;
    CPolynomial c;

    c.Poly.clear();
    R.complete_polynomial();
    R.Division_algorithm(p, c);
    R.correct_grade();

    return R;
}

bool CPolynomial::operator==(const CPolynomial& p) const {
    if (degree != p.degree) return false;

    return Poly == p.Poly;
}

bool CPolynomial::operator!=(const CPolynomial& p) const {
    return !(*this == p);
}

bool CPolynomial::operator<(const CPolynomial& p) const {
    if(degree == p.degree) return Poly < p.Poly;
    return degree < p.degree;
}

bool CPolynomial::operator<=(const CPolynomial& p) const {
    if(degree == p.degree) return Poly <= p.Poly;
    return degree < p.degree;
}

bool CPolynomial::operator>(const CPolynomial& p) const {
    if(degree == p.degree) return Poly > p.Poly;
    return degree > p.degree;
}

bool CPolynomial::operator>=(const CPolynomial& p) const {
    if(degree == p.degree) return Poly >= p.Poly;
    return degree > p.degree;
}

bool CPolynomial::operator!() const {
    if(degree == 0) return Poly[0].GetCoef() == 0;
    return false;
}

CPolynomial::operator bool() const {
    if(degree == 0) return Poly[0].GetCoef() != 0;
    return true;
}

std::ostream& operator<<(std::ostream& os, const CPolynomial& p) {
    if (p.Poly.is_empty()) return os << "0";

    os << p.Poly[0];

    for(std::size_t i=1; i<p.Poly.size(); i++) {
        if (p.Poly[i].GetCoef() < 0) {
            os << " " << p.Poly[i]; 
        } else {
            os << " + " << p.Poly[i];
        }
    }

    return os;
}
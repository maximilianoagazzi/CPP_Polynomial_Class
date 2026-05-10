#ifndef CPOLYNOMIAL_HPP
#define CPOLYNOMIAL_HPP
#include <vector>
#include "CVector.hpp"

class CPolynomial {
    private:
        CVector Poly;
        int degree;
        unsigned int Amount_missing_terms;

        //methods of operation
        void correct_grade();
        void sort_by_exponent();
        void complete_polynomial();
        CPolynomial& Division_algorithm(const CPolynomial& p, CPolynomial& c);
    public:
        CPolynomial();
        CPolynomial(const CPolynomial& p);

        //Setters of polynomials
        void AddPolyTerms();
        void AddPolyTerms(int d);
        void AddPolyTerms(const std::vector<float>& C, const std::vector<int>& Exp);

        //Getters
        int GetDegree() const;
        int GetAmountTerms() const;
        bool Is_complete() const;

        //indexing operator (only to see the coefficient)
        float operator[](int Exp) const;

        //Function call operator (to evaluate the polynomial at a given x)
        double operator()(float x) const;

        //Conversion operator (evaluates the polynomial at x = 1)
        explicit operator double() const;

        //Equalizations operators
        CPolynomial& operator=(const CPolynomial& p);
        CPolynomial& operator+=(const CPolynomial& p);
        CPolynomial& operator-=(const CPolynomial& p);
        CPolynomial& operator*=(const CPolynomial& p);
        CPolynomial& operator*=(const float c);
        CPolynomial& operator/=(const float c);

        //Algebraic operators
        CPolynomial operator+(const CPolynomial& p) const;

        CPolynomial operator-(const CPolynomial& p) const;
        
        CPolynomial operator*(const CPolynomial& p) const;
        CPolynomial operator*(float c) const;
        friend CPolynomial operator*(float c, const CPolynomial& p);
        
        CPolynomial operator/(const CPolynomial& p) const;
        CPolynomial operator/(float c) const;

        CPolynomial operator%(const CPolynomial& p) const;

        //Boolean operators
        bool operator==(const CPolynomial& p) const;
        bool operator!=(const CPolynomial& p) const;
        bool operator<(const CPolynomial& p) const;
        bool operator<=(const CPolynomial& p) const;
        bool operator>(const CPolynomial& p) const;
        bool operator>=(const CPolynomial& p) const;
        bool operator!() const;
        explicit operator bool() const;

        //Streams operators
        friend std::ostream& operator<<(std::ostream& os, const CPolynomial& p);
};

#endif
#ifndef POLYNOMIAL_HPP
#define POLYNOMIAL_HPP
#include <iostream>
#include <vector>

class Polynomial {
    private:
        class PolyTerm {
            private:
                float Coef;
                int Exp;
            public:
                //Builder
                PolyTerm(float Coef = 0.0, int Exp = 0);

                //Getters
                float GetCoef() const;
                int GetExp() const;

                //Equalizations operators
                PolyTerm& operator=(const PolyTerm& p);
                PolyTerm& operator+=(const PolyTerm& p);
                PolyTerm& operator-=(const PolyTerm& p);
                PolyTerm& operator*=(const PolyTerm& p);
                PolyTerm& operator*=(const float c);
                PolyTerm& operator/=(const PolyTerm& p);
                PolyTerm& operator/=(const float c);

                //Algebraic operators
                PolyTerm operator+(const PolyTerm& p) const;

                PolyTerm operator-(const PolyTerm& p) const;
        
                PolyTerm operator*(const PolyTerm& p) const;
                PolyTerm operator*(float c) const;
                friend PolyTerm operator*(float c, const PolyTerm& p) {
                    return PolyTerm(c * p.Coef, p.Exp);
                }
        
                PolyTerm operator/(const PolyTerm& p) const;
                PolyTerm operator/(float c) const;

                //Boolean operators
                bool operator==(const PolyTerm& p) const;
                bool operator!=(const PolyTerm& p) const;
                bool operator<(const PolyTerm& p) const;
                bool operator<=(const PolyTerm& p) const;
                bool operator>(const PolyTerm& p) const;
                bool operator>=(const PolyTerm& p) const;
                bool operator!() const;
                explicit operator bool() const;

                //Streams operator
                friend std::istream& operator>>(std::istream& is, PolyTerm& p) {
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
                friend std::ostream& operator<<(std::ostream& os, const PolyTerm& p) {
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
        };
        
        std::vector<PolyTerm> Poly;
        int degree;
        unsigned int Amount_missing_terms;

        //methods of operation
        void correct_grade();
        void sort_by_exponent();
        void complete_polynomial();
        Polynomial& Division_algorithm(const Polynomial& p, Polynomial& c);
    public:
        Polynomial();
        Polynomial(const Polynomial& p);

        //Setters of polynomials
        void SetPolyTerms();
        void SetPolyTerms(int d);
        void SetPolyTerms(const std::vector<float>& C, const std::vector<int>& Exp);

        //Getters
        int GetDegree() const;
        bool Is_complete() const;

        //indexing operator (only to see the coefficient)
        float operator[](int Exp) const;

        //Equalizations operators
        Polynomial& operator=(const Polynomial& p);
        Polynomial& operator+=(const Polynomial& p);
        Polynomial& operator-=(const Polynomial& p);
        Polynomial& operator*=(const Polynomial& p);
        Polynomial& operator*=(const float c);
        Polynomial& operator/=(const float c);

        //Algebraic operators
        Polynomial operator+(const Polynomial& p) const;

        Polynomial operator-(const Polynomial& p) const;
        
        Polynomial operator*(const Polynomial& p) const;
        Polynomial operator*(float c) const;
        friend Polynomial operator*(float c, const Polynomial& p);
        
        Polynomial operator/(const Polynomial& p) const;
        Polynomial operator/(float c) const;

        Polynomial operator%(const Polynomial& p) const;

        //Boolean operators
        bool operator==(const Polynomial& p) const;
        bool operator!=(const Polynomial& p) const;
        bool operator<(const Polynomial& p) const;
        bool operator<=(const Polynomial& p) const;
        bool operator>(const Polynomial& p) const;
        bool operator>=(const Polynomial& p) const;
        bool operator!() const;
        explicit operator bool() const;

        //Streams operators
        friend std::ostream& operator<<(std::ostream& os, const Polynomial& p);
};

#endif
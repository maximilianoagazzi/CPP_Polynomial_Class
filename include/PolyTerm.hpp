#ifndef POLYTERM_HPP
#define POLYTERM_HPP

class PolyTerm {
    private:
        double Coef;
        int Exp;
    public:
        //Builder
        PolyTerm(double Coef = 0.0, int Exp = 0);
        PolyTerm(const PolyTerm& p);

        //Getters
        double GetCoef() const;
        int GetExp() const;

        //Equalizations operators
        PolyTerm& operator=(const PolyTerm& p);
        PolyTerm& operator+=(const PolyTerm& p);
        PolyTerm& operator-=(const PolyTerm& p);
        PolyTerm& operator*=(const PolyTerm& p);
        PolyTerm& operator*=(const double c);
        PolyTerm& operator/=(const PolyTerm& p);
        PolyTerm& operator/=(const double c);

        //Algebraic operators
        PolyTerm operator+(const PolyTerm& p) const;
        
        PolyTerm operator-(const PolyTerm& p) const;
        
        PolyTerm operator*(const PolyTerm& p) const;
        PolyTerm operator*(double c) const;
        friend PolyTerm operator*(double c, const PolyTerm& p);
        
        PolyTerm operator/(const PolyTerm& p) const;
        PolyTerm operator/(double c) const;

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
        friend std::istream& operator>>(std::istream& is, PolyTerm& p);
        friend std::ostream& operator<<(std::ostream& os, const PolyTerm& p);
};

#endif
#ifndef CVECTOR_HPP
#define CVECTOR_HPP
#include "PolyTerm.hpp"

class CVector {
    private:
        PolyTerm* Data;
        std::size_t s;
        std::size_t c;
    public:
        //Builders - Destroyers
        CVector();
        CVector(std::size_t ini_capacity);
        CVector(const CVector& v);
        ~CVector();

        //Methods
        std::size_t size() const;
        std::size_t capacity() const;
        bool is_empty() const;
        bool is_full() const;
        void push_back(PolyTerm elem);
        void insert(PolyTerm elem, int index);
        void erase(int index);
        void clear();
        void set_empty();
        void sort(int (*ord)(PolyTerm , PolyTerm));

        //indexing operator
        PolyTerm& operator[](int index) const;

        //Equalizations operators
        CVector& operator=(const CVector& v);
        CVector& operator+=(const CVector& v);

        //Algebraic operators
        CVector operator+(const CVector& v) const;

        //Boolean operators
        bool operator==(const CVector& v) const;
        bool operator!=(const CVector& v) const;
        bool operator<(const CVector& v) const;
        bool operator<=(const CVector& v) const;
        bool operator>(const CVector& v) const;
        bool operator>=(const CVector& v) const;
        bool operator!() const;
        explicit operator bool() const;

        //Extract and insert operators
        friend std::istream& operator>>(std::istream& is, CVector& v);
        friend std::ostream& operator<<(std::ostream& os, const CVector& v);
};

#endif
#include <iostream>
#include "../include/CVector.hpp"

CVector::CVector() : s(0), c(1), Data(nullptr) {}

CVector::CVector(std::size_t ini_capacity) : s(0), c(ini_capacity) {
    Data = new PolyTerm[c];
}

CVector::CVector(const CVector& v) : s(v.s), c(v.c) {
    Data = new PolyTerm[c];
    for(std::size_t i=0; i<s; i++) Data[i] = v.Data[i];
}

CVector::~CVector() {
    if(Data != nullptr) delete[] Data;
}

std::size_t CVector::size() const {
    return s;
}

std::size_t CVector::capacity() const {
    return c;
}

bool CVector::is_empty() const {
    return s == 0;
}

bool CVector::is_full() const {
    return s == c;
}

void CVector::push_back(PolyTerm elem) {
    if(Data == nullptr) Data = new PolyTerm[c];
    
    if(s < c) {
        Data[s] = elem;
        s++;
    } else {
        PolyTerm* new_data = new PolyTerm[c*2];

        for(std::size_t i=0; i<s; i++) new_data[i] = Data[i];

        delete[] Data;
        new_data[s] = elem;
        
        Data = new_data;
        c *= 2;
        s++;
    }
}

void CVector::insert(PolyTerm elem, int index) {
    if(index > s || index < 0) return;

    if(Data == nullptr) Data = new PolyTerm[c];

    if(s < c) {
        for(std::size_t i=s; i>index; i--) {
            Data[i] = Data[i-1];
        }
        Data[index] = elem;
        s++;
    } else {
        PolyTerm* new_data = new PolyTerm[c * 2];

        for(std::size_t i=0; i<index; i++) new_data[i] = Data[i];
        
        for(std::size_t i=index; i<s; i++) new_data[i+1] = Data[i];

        delete[] Data;
        new_data[index] = elem;

        Data = new_data;
        c *= 2;
        s++;

    }
}

void CVector::erase(int index) {
    if(index >= s || index < 0) return;

    for(std::size_t i=index; i<s-1; i++) Data[i] = Data[i+1];
    
    s--;
}

void CVector::clear() {
    if(Data == nullptr) return;
    
    delete[] Data;
    Data = nullptr;
    s = 0;
    c = 1;
}

void CVector::set_empty() {
    if(Data == nullptr) return;

    for(std::size_t i=0; i<s; i++) Data[i] = 0;
}

void CVector::sort(int (*ord)(PolyTerm , PolyTerm)) {
    char swapped = 1;
    int siz = s;

    while ((siz > 1) && (swapped != 0)) {
        swapped = 0;
        for (std::size_t i=1; i<siz; i++) {
            if (ord(Data[i-1], Data[i]) > 0) {
                PolyTerm aux = Data[i-1];

                Data[i-1] = Data[i];
                Data[i] = aux;

                swapped = 1;
            }
        }
        siz--;
    }
}

PolyTerm& CVector::operator[](int index) const {
    if(Data == nullptr || index >= s || index < 0) throw std::invalid_argument("Wrong index");

    return Data[index];
}

CVector& CVector::operator=(const CVector& v) {
    if(this != &v) {
        if(Data == nullptr) Data = new PolyTerm[c];

        if(c > v.s) {
            for(std::size_t i=0; i<v.s; i++) Data[i] = v.Data[i];

            s = v.s;
        } else {
            PolyTerm* new_data = new PolyTerm[v.c];
            for(std::size_t i=0; i<v.s; i++) new_data[i] = v.Data[i];

            delete[] Data;
            Data = new_data;
            s = v.s;
            c = v.c;
        }
    }

    return *this;
}

CVector& CVector::operator+=(const CVector& v) {
    if(Data == nullptr) Data = new PolyTerm[c];

    if(c > v.s + s) {
        for(std::size_t i=s; i<v.s+s; i++) Data[i] = v.Data[i-s];

        s += v.s;
    } else {
        PolyTerm* new_data = new PolyTerm[v.c+c];
        for(std::size_t i=0; i<s; i++) new_data[i] = Data[i];
        for(std::size_t i=s; i<v.s+s; i++) new_data[i] = v.Data[i-s];

        delete[] Data;
        Data = new_data;
        s += v.s;
        c += v.c;
    }

    return *this;
}

CVector CVector::operator+(const CVector& v) const {
    CVector v1(*this);
    v1 += v;

    return v1;
}

bool CVector::operator==(const CVector& v) const {
    bool result = false;

    if(s == v.s) {
        result = true;

        for(std::size_t i=0; i<s && result == true; i++)
            if(Data[i] != v.Data[i]) result = false;
    }
    
    return result;
}

bool CVector::operator!=(const CVector& v) const {
    return !(*this == v);
}

bool CVector::operator<(const CVector& v) const {
    int r = 0;
    int minLog = s < v.s ? s : v.s;
    for(int i=0; i<minLog && r == 0; i++) {
        if(Data[i] < v.Data[i]) r = -1;
        else if(Data[i] > v.Data[i]) r = 1;
    }
    if(r == 0) {
        if(s < v.s) r = -1;
        else if(s > v.s) r = 1;
    }
    return r < 0;
}

bool CVector::operator<=(const CVector& v) const {
    int r = 0;
    int minLog = s < v.s ? s : v.s;
    for(int i=0; i<minLog && r == 0; i++) {
        if(Data[i] <= v.Data[i]) r = -1;
        else if(Data[i] >= v.Data[i]) r = 1;
    }
    if(r == 0) {
        if(s <= v.s) r = -1;
        else if(s >= v.s) r = 1;
    }
    return r < 0;
}

bool CVector::operator>(const CVector& v) const {
    return v < *this;
}

bool CVector::operator>=(const CVector& v) const {
    return v <= *this;
}

bool CVector::operator!() const {
    bool r = true;

    for(std::size_t i=0; i<s && r == true; i++)
        if(Data[i] != 0) r = false;
    
    return r;
}

CVector::operator bool() const {
    return !(!*this);
}

std::istream& operator>>(std::istream& is, CVector& v) {
    char sep;
    PolyTerm num;
    
    do {
        is >> num;

        v.push_back(num);

        if(is.peek() == '\n') break;

        is >> sep;

    } while(sep == ',');

    return is;
}

std::ostream& operator<<(std::ostream& os, const CVector& v) {
    if(v.Data == nullptr) {
        os << "The vector is Null";
        return os;
    }

    if(v.s != 0) {
        os << "[";
        
        for(std::size_t i=0; i<v.s-1; i++) os << v.Data[i] << " ,";

        os << v.Data[v.s-1] << "]";
    } else {
        os << "[]";
    }

    return os;
}
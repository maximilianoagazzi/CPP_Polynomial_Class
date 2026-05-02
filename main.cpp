#include <iostream>
#include "include/Polynomial.hpp"

int main() {
    Polynomial p1, p2;

    p1.AddPolyTerms({5, 6, 8, 10}, {6, 3, 7, 1});
    std::cout << p1 << std::endl;
    p2.AddPolyTerms({7, 3, 11}, {3, 5, 0});
    std::cout << p2 << std::endl;
    
    std::cout << "El grado de p1 es: " << p1.GetDegree() << std::endl;
    if(p1.Is_complete() == true) std::cout << "El polinomio p1 esta completo" << std::endl;
    else std::cout << "El polinomio p1 no esta completo" << std::endl;
    std::cout << "p1 + p2: " << p1 + p2 << std::endl;
    std::cout << "p1 - p2: " << p1 - p2 << std::endl;
    std::cout << "p1 * p2: " << p1 * p2 << std::endl;
    std::cout << "p1 / p2: " << p1 / p2 << std::endl;
    std::cout << "p1 mod p2: " << p1 % p2 << std::endl;
    std::cout << "p1 / 3: " << p1 / 3.0 << std::endl;
    if(p1 >= p2) std::cout << "p1 es mayor a p2" << std::endl;

    return 0;
}
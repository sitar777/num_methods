#ifndef polynom
#define polynom

#include <vector>
#include <iostream>
#include <cmath>
#include <string>

class poly{
    std::vector<double> coeffs; //polynomial coefficients
    public:
    
    poly();
    poly(std::vector<double> vec); //initialitation of polynom
    
    // methods 
    int polyDeg(); //returns the degree of polynom
    void printPoly(); //printing the polynom
    double val(double x); //returns the value of polynom in point x
    poly der(); //returns the first order derivative (dP/dx) of polynom
    
    // operators
    poly operator=(poly poly1);
    friend bool operator==(poly poly1, poly poly2);
    friend bool operator!=(poly poly1, poly poly2);
    friend poly operator^(poly poly1, double lambda);
    friend poly operator+(poly poly1, poly poly2);
    friend poly operator*(poly poly1, double lambda);
    friend poly operator*(double lambda, poly poly1);
    friend poly operator*(poly poly1, poly poly2);
    friend poly operator-(poly poly1, poly poly2);
    friend poly operator/(poly poly1, double lambda);
    friend poly operator/(double lambda, poly poly1);
};
    
#endif


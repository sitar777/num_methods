#include "polynom.h"
#include <armadillo>

/*
Conrad Sanderson and Ryan Curtin.
Armadillo: a template-based C++ library for linear algebra.
Journal of Open Source Software, Vol. 1, pp. 26, 2016.

Conrad Sanderson and Ryan Curtin.
A User-Friendly Hybrid Sparse Matrix Class in C++.
Lecture Notes in Computer Science (LNCS), Vol. 10931, pp. 422-430, 2018. 
*/

using namespace arma;

double a = -1; 
double b = 1;

double fun(double x){
	return sin(x) - 7/(2*x + 6);
} // Function for interpolation;
unsigned int fac(int n){
    int fact = 1;
    if(n == 0){
        fact = 1;
    }
    else if(n < 0){
        n = abs(n);
        for (int i = 1;i <= n;i++){
            fact *= i; 
        }
    }
    else{
        for (int i = 1;i <= n;i++){
            fact *= i; 
        }
    }
    return fact;
} // Factorial function
poly fi_i(double n){   
    std::vector<double> coeffs;
    coeffs.push_back(1);
    for(int j = 0;j < n ;j++){
        coeffs.push_back(0);
    }
    return poly(coeffs);
} // Returns fi_i = x^i
std::vector<double> nodesChoice(int n){
	std::vector<double> nodes;
	double point = (double)a;
    double delta = (double)(b - a)/(n-1);
    while (point <= b){
        nodes.push_back(point);
        point += (double)delta;
    }
    return nodes;
} // Choice of nodes for f(x)
void boundCheck(){
    if (b < a){
        double tmp = a;
        a = b;
        b = tmp;
    }
} // Checking if a < b, if not swap them;
void printNodes(std::vector<double> nodes,double f(double x)){
    printf("%-6s | %-15s | %-15s\n","","X","F(X)");
    printf("---------------------------------------\n");
    for (int i = 0;i < nodes.size();i++){ 
        printf("%-6i | %-15lf | %-15lf\n", i+1 ,nodes[i],f(nodes[i]));
    }
} // Nodes printing in a table
vec fiCount(double x,int n){
    vec fi_iVal(n);
    for (int i = 0;i < n; i++){
        fi_iVal(i) = fi_i(i).val(x); 
    }
    return fi_iVal;
} // Counts the vector fi = (fi_1 fi_2 ... fi_n)^T
poly OLS(std::vector<double> nodes,int n,double f(double x)){
    poly P = poly({0});
    mat H(nodes.size(),nodes.size());
    vec a(n); // P coeffs
    vec y(nodes.size()); // f(x) values
    for(int i = 0; i < nodes.size(); i++){
        y[i] = f(nodes[i]); 
    }; // counts y
    mat Q = mat(fiCount(nodes[0],n)); // Q matrix
    for(int i = 1; i < nodes.size(); i++){
        Q = join_rows(Q,mat(fiCount(nodes[i],n)));
    };
    H = Q * trans(Q);// counts H
    mat b = Q * y; //counts b
    a = inv(H) * b; //counts a
    for (int i = 0;i < n;i++){
        P = P + a[i] * fi_i(i);
    }
    return P;
} // Ordinary Least Squares method of extrapolation
void errorVal(poly Ln, double f(double x)){
    double maxError = __DBL_MIN__;
    double minError = __DBL_MAX__;
    double delta = 0.001;
    double sumOfErr = 0;
    double leftbound = a;
    int counter = 0;
    while(leftbound <= b){
        double err = abs(f(leftbound) - Ln.val(leftbound));
        sumOfErr += pow(err,2);
        if (err > maxError){
            maxError = err;
        }
        if (err < minError){
            minError = err;
        }
        leftbound += delta;
        ++counter; 
    }
    printf("Averaged error is: %lf\n",sqrt(sumOfErr)/counter);
    printf("Minimum error is: %lf\n",minError);
    printf("Maximum error is: %lf\n",maxError);
} // Error values printing
double integral(double leftBound, double rightBound, double f(double x)){
    double val = 0;
    double step = 0.0001;
    while (leftBound <= rightBound){
        val += step*f(leftBound);
        leftBound += step;
    }
    return val;
} // Calculates the definite integral of f(x) from a to b
poly legendrePoly(int n){
    if(n > 0){
        poly temp = poly({1,0,-1})^n;
        for(int i = 0; i < n; i++){
            temp = temp.der();
        }
        double coef = (double) fac(n)*pow(2,n);
        poly P = temp/coef;
        return P;
    }
    else if (n == 0){
        return poly({1});
    }
    else{
        std::cout<<"n can't be < 0.\nn is set to abs(n).\n";
        n = abs(n);
        poly temp = poly({-1,0,1})^n;
        for(int i = 0; i < n; i++){
            temp = temp.der();
        }
        double coef = (double) 1/fac(n)*pow(2,n);
        poly P = coef*temp;
        return P;
    }
} // Calculates the n_th Legendre polynom (1/(n!*2^n))*d^n/dx^n((1 - x^2)^n)
double polyApproxNum(double x,int n,double f(double x)){
    return f(x)*legendrePoly(n).val(x);
} // Numerator for integral in polynomial approximation
double polyApproxDenom(double x, int n){
    return pow(legendrePoly(n).val(x),2);
} // Denominator for integral in polynomial approximation
poly polyApprox(int n,double num(double x,int n,double f(double x)),double denom(double x, int n)){
    n = n + 1;
    std::vector<double> c;
    poly approx = poly({0});
    for(int i = 0;i < n;i++){
        double numVal = 0;
        double denomVal = 0;
        double leftN = a;
        double leftD = a;
        double step = 0.0001;
        while (leftN <= b){
            numVal += step*num(leftN,i,*fun);
            leftN += step;
        }
        while (leftD <= b){
            denomVal += step*denom(leftD,i);
            leftD += step;
        }
        c.push_back(numVal/denomVal);
    }
    for(int i = 0;i<n;i++){
        approx = approx + legendrePoly(i)*c[i];
    }
    return approx;
} // Polynomial approximation of f(x)

int main() {
	std::cout << "Ordinary Least Squares method\n\n";
    std::vector<double> nodes = nodesChoice(5);
    printNodes(nodes,*fun);
    poly sqrsApprox = OLS(nodes,4,*fun);
    sqrsApprox.printPoly();
    errorVal(sqrsApprox,*fun);
    std::cout << "------------------------------------------\n";
    std::cout << "Polynom approximation using Legendre polynoms\n\n";
    poly plnmApprox = polyApprox(3,*polyApproxNum,*polyApproxDenom);
    plnmApprox.printPoly();
    errorVal(plnmApprox,*fun);
    return 0;
}
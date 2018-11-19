#include <iostream>
#include <cmath>
#include <vector>
#include <armadillo>

using namespace arma;

/*
Conrad Sanderson and Ryan Curtin.
Armadillo: a template-based C++ library for linear algebra.
Journal of Open Source Software, Vol. 1, pp. 26, 2016.

Conrad Sanderson and Ryan Curtin.
A User-Friendly Hybrid Sparse Matrix Class in C++.
Lecture Notes in Computer Science (LNCS), Vol. 10931, pp. 422-430, 2018. 
*/

int N = 5;
double epsilon = pow(10,-6);
mat A = {{4,1,1},{1,2*(3+0.1*N),-1},{1,-1,2*(4+0.1*N)}};
vec B = {1, -2, 3};
int iterations = 0;
mat D = diagmat(A);
double delta = as_scalar(min(diagvec(A) - trans((sum((A - D))))));

double fun(vec3 X){ 
    double f = as_scalar((trans(X) * A * X)/2 + trans(X) * B + N); 
    return f;
}

mat gradCount(vec3 x){
    mat grad = trans(A*x + B);
    return grad;
}

double difference(mat A,vec x){
    double d = pow(norm(A*x+B),2)/delta; 
    return d;
}

mat gradMethod(){
    vec X = inv(diagmat(A))*(-B);
    iterations = 0;
    double diff = INT_MAX;
    while(diff >= epsilon){
        double mu = (as_scalar(-(trans(A*X+B)*(A*X+B))))/(as_scalar(trans(A*X+B)*A*(A*X+B)));
        mat X_new = X + mu*(A*X+B);
        diff = difference(A,X_new);
        X = X_new;
        iterations++;
        std::cout << "Step " << iterations << std::endl << std::endl;
        std::cout << "Point: " << trans(X);
        std::cout << "Gradient norm: " << as_scalar(trans(A*X+B)*(A*X+B)) << std::endl;  
        std::cout << "Value:   " << fun(X) << std::endl <<"-----------"<<std::endl;
    };
    return X;
}

mat coordMethod(){
    vec X = inv(diagmat(A))*(-B);
    iterations = 0;
    double diff = INT_MAX;
    colvec e = {0,0,0};
    int i = 0;
    while(diff >= epsilon){
        e(i) = 1;
        double mu = - (as_scalar(trans(e)*(A*X + B)))/(as_scalar(trans(e)*A*e));
        vec X_new = X + mu * e;
        diff = difference(A,X_new);
        X = X_new;
        iterations++;
        if(i < X.size() - 1){
            e = {0,0,0};
            i++;
            }
        else if(i >= X.size() - 1){
            e = {0,0,0};
            i = 0;
        };
        std::cout << "Step " << iterations << std::endl << std::endl;
        std::cout << "Point: " << trans(X);
        std::cout << "Value:   " << fun(X) << std::endl <<"-----------"<<std::endl;
    }  
    return X;
}

int main(){
    std::cout << std::endl <<"---------------------------------------" <<std::endl;
    std::cout << std::endl << "GRADIENT METHOD" << std::endl;
    std::cout << std::endl <<"---------------------------------------" <<std::endl;
    vec Xg = gradMethod();
    std::cout << std::endl << "Function minimum is in the point: " << trans(Xg);
    std::cout <<  "Function value is: " << fun(Xg) << std::endl;
    std::cout << "Number of iterations is: " << iterations << std::endl;
    std::cout <<"---------------------------------------" <<std::endl<<std::endl;
    std::cout << "COORDINATE METHOD" << std::endl;
    std::cout << std::endl <<"---------------------------------------" <<std::endl;
    vec Xc = coordMethod();
    std::cout << std::endl << "Function minimum is in the point: " << trans(Xc);
    std::cout <<  "Function value is: " << fun(Xc) << std::endl;
    std::cout << "Number of iterations is: " << iterations << std::endl;
    return 0;
};


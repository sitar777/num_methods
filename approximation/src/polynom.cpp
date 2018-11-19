#include "polynom.h"

std::string signPrint(double coef){
    std::string s;
    if(coef < 0){
        s = " - ";
    }
    else{
        s = " + ";
    };
    return s;
}

poly::poly(std::vector<double> vec){
    coeffs = vec;
    if (coeffs.size() != 1){
        while(coeffs[0]==0){
            coeffs.erase(coeffs.begin());
        }
    }    
}
int poly::polyDeg(){
    return coeffs.size() - 1;
}
void poly::printPoly(){
    int size = coeffs.size();
    std::cout << "P(x) =";
    if(size == 1){
        if (coeffs[0] < 0){
            std::cout << signPrint(coeffs[0]) << abs(coeffs[0]) << '\n';
        }
        else {
            std::cout << " " << coeffs[0] << '\n';
        };
    }
    else if(coeffs.size() == 2){
        if(coeffs[0] == 1){
            std::cout << " x";
        }
        else if(coeffs[0] == -1){
            std::cout << " - x";
        }
        else{
            if (coeffs[0] < 0){
                std::cout << signPrint(coeffs[0]) << abs(coeffs[0]) << "x";
            }
            else{
                std::cout << " " << abs(coeffs[0]) << "x";
            }
        };
        if(coeffs[1] == 0){
        std::cout << '\n';
        }
        else{
            std::cout << signPrint(coeffs[1]) << abs(coeffs[1]) << '\n';
        };
    }   
    else{
        for(int i = 0;i < coeffs.size();i++){
            if(i == 0){
                if(coeffs[i] == 1){
                    std::cout << " x^" << coeffs.size() - (i + 1);
                }
                else if(coeffs[i] == -1){
                    std::cout << " - x^" << coeffs.size() - (i + 1);
                }
                else{
                    if(coeffs[i] < 0){
                        std::cout << signPrint(coeffs[i]) << abs(coeffs[i]) << "x^" << coeffs.size() - (i + 1);
                    }
                    else{
                        std::cout << " " << abs(coeffs[i]) << "x^" << coeffs.size() - (i + 1);
                    }
                };
            }
            else if(coeffs.size() - (i + 1) > 1){
                if(coeffs[i] == 0){}
                else if(coeffs[i] == 1 or coeffs[i] == -1){
                    std::cout << signPrint(coeffs[i]) << "x^" << coeffs.size() - (i + 1);
                }
                else{
                    std::cout << signPrint(coeffs[i]) << abs(coeffs[i]) << "x^" << coeffs.size() - (i + 1);
                };
            }
            else if(coeffs.size() - (i + 1) == 1){
                if(coeffs[i] == 0){}
                else if(coeffs[i] == 1 or coeffs[i] == -1){
                    std::cout << signPrint(coeffs[i]) << "x";
                }
                else{
                    std::cout << signPrint(coeffs[i]) << abs(coeffs[i]) << "x";
                }; 
            }
            else{
                if(coeffs[i] == 0){
                    std::cout << '\n';
                }
                else{
                    std::cout << signPrint(coeffs[i]) << abs(coeffs[i]) << '\n';
                }; 
            };
        };
    }
}
double poly::val(double x){
    double value = 0;
    for (int i = 0;i < coeffs.size();i++){
        value += pow(x,coeffs.size() - i - 1)*coeffs[i];
    }
    return value;
}
poly poly::der(){
    std::vector<double> derivative;
    for(int i = 0;i < coeffs.size()-1;i++){
        derivative.push_back(0);
    }
    for(int i = 0;i < derivative.size();i++){
        derivative[i] += coeffs[i]*(derivative.size()-i);
    }
    return poly(derivative);
}
poly poly::operator=(poly poly1){
    if(this == &poly1){
        return *this;
    }
    coeffs = poly1.coeffs;
    return *this;
}
bool operator==(poly poly1, poly poly2){
    return poly1.coeffs == poly2.coeffs;
}
bool operator!=(poly poly1, poly poly2){
    return poly1.coeffs != poly2.coeffs;
}
poly operator^(poly poly1, double lambda){
    if (lambda > 1){
        poly temp = poly({1});
        for(int i = 0;i < lambda;i++){
        temp = temp * poly1;
        }
    return temp;
    }
    else if (lambda == 1){
        return poly1;
    }
    else if (lambda == 0){
        return poly({1});
    }
    else{
        std::cout << "Wrong degree, sould be >= 0.\nLambda is set to 1.\n";
        return poly1;
    }
}
poly operator+(poly poly1, poly poly2){
    std::vector<double> sum;
    std::vector<double> coeffs1 = poly1.coeffs;
    std::vector<double> coeffs2 = poly2.coeffs;
    int degdiff = coeffs1.size() - coeffs2.size();
    if (degdiff == 0){
        for (int i = 0;i < coeffs1.size();i++){
            double val = coeffs1[i] + coeffs2[i];
            sum.push_back(val);
        };
    }
    else if (degdiff < 0){
        for (int i = 0;i < abs(degdiff);i++){
            double val = coeffs2[i];
            sum.push_back(val);
        };
        for (int i = abs(degdiff);i < coeffs2.size();i++){
            double val = coeffs2[i] + coeffs1[i - abs(degdiff)];
            sum.push_back(val);
        };
    }
    else{
        for (int i = 0;i < abs(degdiff);i++){
            double val = coeffs1[i];
            sum.push_back(val);
        };
        for (int i = abs(degdiff);i < coeffs1.size();i++){
            double val = coeffs1[i] + coeffs2[i - abs(degdiff)];
            sum.push_back(val);
        };
    };
    return poly(sum);
}
poly operator*(poly poly1,double lambda){
    for (int i = 0;i < poly1.polyDeg()+1;i++){
        poly1.coeffs[i] *= lambda;
    }
    return poly1;
}
poly operator*(double lambda,poly poly1){
    for (int i = 0;i < poly1.polyDeg()+1;i++){
        poly1.coeffs[i] *= lambda;
    };
    return poly1;
}
poly operator*(poly poly1,poly poly2){
    std::vector<double> mult;
    int multdeg = poly1.polyDeg() + poly2.polyDeg();
    for (int i = 0;i < multdeg + 1; i++){
        mult.push_back(0);
    }
    for(int i = 0;i < poly1.polyDeg() + 1; i++){
        for(int j = 0;j < poly2.polyDeg() + 1; j++){
            double val = poly1.coeffs[i] * poly2.coeffs[j];
            mult[i+j] += val; 
        };
    };
    return mult;
}
poly operator-(poly poly1, poly poly2){
    return poly1 + (-1)*poly2;
}
poly operator/(poly poly1,double lambda){
    for (int i = 0;i < poly1.polyDeg()+1;i++){
        poly1.coeffs[i] /= lambda;
    }
    return poly1;
}
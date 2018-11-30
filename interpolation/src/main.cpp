#include "polynom.h"

double a = 1;
double b = 10;

double fun(double x){
    return log10(x) + 7/(2*x + 6);
} // function for interpolation f(x)
double funWithAbs(double x){
    return abs(x)*(log10(x) + 7/(2*x + 6));
} // function for interpolation |x|*f(x)
std::vector<double> nodesChoice(int n, char step){
    std::vector<double> nodes;
    if (step == 'f'){
        double point = (double)a;
        double delta = (double)(b - a)/(n-1);
        while (point <= b){
            nodes.push_back(point);
            point += (double)delta;
        }
    }
    else if (step == 'm'){
        for (int i = 0; i < n; i++){
            double arg = (double)(2*i + 1)/(2*(n+1))*M_PI;
            double x_i = (double)1/2*((b - a)*cos(arg)+ (b + a));
            nodes.push_back(x_i);
        }
    }
    else{
        std::cout << "ERROR: Unknown type of step.\nStep is set to methodicaly defined.";
    }
    return nodes;
}
// choice of nodes for function f, where n is number of nodes, step is the type of step:
//  'f' for fixed step, 'm' for methodicaly defined step.
void boundCheck(){
    if (b < a){
        double tmp = a;
        a = b;
        b = tmp;
    };
} // checking if a < b, if not swap them;
void printNodes(std::vector<double> nodes,double f(double x)){
    printf("%-6s | %-15s | %-15s\n","","X","F(X)");
    printf("---------------------------------------\n");
    for (int i = 0;i < nodes.size();i++){ 
        printf("%-6i | %-15lf | %-15lf\n", i+1 ,nodes[i],f(nodes[i]));
    }
} // nodes printing in a table
poly omega(std::vector<double> nodes,int n){
    if(n > nodes.size()){
        std::cout << "ERROR: Wrong order of omega.\nOrder is set to " << nodes.size() << ".\n";
        n = nodes.size();
    }
    poly omegaPoly = poly({1,-nodes[0]});
    for(int i = 1;i < n;i++){
        omegaPoly = omegaPoly*poly({1,-nodes[i]});
    }
    return omegaPoly;
} // calculates the polynom omega = (x - x_0)(x - x_1)...(x - x_n) 
poly lagrange(std::vector<double> nodes, double f(double x)){
    poly Ln = poly({0});
    for(int i = 0; i < nodes.size(); i++){
        std::vector<double> temp1;
        std::vector<double> temp2;
        if(i == 0){ 
            for(int j = 1; j < nodes.size(); j++){
                temp1.push_back(nodes[j]);
            }
            Ln = Ln + (omega(temp1,temp1.size())/omega(temp1,temp1.size()).val(nodes[i]))*f(nodes[i]);  
            temp1.clear();         
        }
        else if(0< i and i < nodes.size() - 1){
            for(int j = 0;j <= i - 1;j++){
                temp1.push_back(nodes[j]);
            }
            for(int k = i + 1;k < nodes.size();k++){
                temp2.push_back(nodes[k]);
            }
            poly w_k = omega(temp1,temp1.size())*omega(temp2,temp2.size());
            Ln = Ln + (w_k/w_k.val(nodes[i]))*f(nodes[i]);
            temp1.clear();
            temp2.clear();
        }
        else{
            for(int j = 0; j < nodes.size()-1; j++){
                temp1.push_back(nodes[j]);
            }
            Ln = Ln + (omega(temp1,temp1.size())/omega(temp1,temp1.size()).val(nodes[i]))*f(nodes[i]);  
            temp1.clear();         
        }
    }
    return Ln;
} // interpolation by Lagrange polynom 
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
int main(){
    boundCheck();
    std::vector<double> nodes = nodesChoice(10,'m');
    printNodes(nodes,*funWithAbs);
    poly Ln = lagrange(nodes,*funWithAbs);
    Ln.printPoly();
    errorVal(Ln,*funWithAbs);
    return 0;
};
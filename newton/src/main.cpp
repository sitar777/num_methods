#include <iostream>
#include <cmath>
#include <vector>

using namespace std;
double delta = pow(10, -50);// function increment
int counter = 0;

double f(double x) // function which is solved
{
    double y = tan(x) - 1 / x;
    return y;
}

double firstDer(double x) // first derivative
{
    return 1 / (x * x) + 1 / (cos(x) * cos(x));
}

double secondDer(double x) // second derivative
{
    double der2 = 2 / (x * x * x) + 2 * sin(x) / (cos(x) * cos(x) * cos(x));
    return der2;
}

double sign(double x) // signum function
{
    int s;
    if (x == 0) { s = 0; }
    else { s = x / abs(x); };
    return s;
}

double absMin(double (*f)(double x), double a, double b) {
    int j = 0;
    vector<double> values;
    for (double i = a; i <= b; i = i + pow(10, -4)) {
        double val = f(i);
        double absF = abs(val);
        values.push_back(absF);
        j++;
    }
    double minval = UINT64_MAX;
    for (unsigned long long int i = 0; i < size(values); i++) {
        if (values[i] < minval) {
            minval = values[i];
        }
    }
    return minval;
}

double absMax(double (*f)(double x), double a, double b) {
    unsigned long long int j = 0;
    vector<double> values;
    for (double i = a; i <= b; i = i + pow(10, -2)) {
        double val = f(i);
        double absF = abs(val);
        values.push_back(absF);
        j++;
    }
    double maxval = UINT64_MAX;
    for (unsigned long long int i = 0; i < size(values); i++) {
        if (values[i] > maxval) {
            maxval = values[i];
        }
    }
    return maxval;
}

bool newtonMethod(double (*f)(double x), double a, double b, double x0,
                  double &res) // a - left boundary, b - right boundary, x0 - root aproximation
{

    if (f(a) * f(b) >= 0) // f(a)*f(b) < 0;
    {
        cout << "Newton method can't converge" << endl;
        return false;
    } else if (sign(firstDer(a)) != sign(firstDer(b)) and sign(secondDer(a)) != sign(secondDer(b)))
        // sign f'(x) = const and sign f''(x) = const on [a, b]
    {
        cout << "Newton method can't converge" << endl;
        return false;
    } else if (f(x0) * secondDer(x0) <= 0) // f(x0)*f''(x0) > 0
    {
        cout << "Newton method can't converge" << endl;
        return false;
    } else {
        double m_1 = absMin(firstDer, a, b);
        double m_2 = absMax(secondDer, a, b);

        double epsilon = sqrt((2 * m_1 * delta) / m_2);

        while (abs(f(x0)) >= epsilon) {
            double c1 = f(x0);
            double c2 = firstDer(x0);
            x0 = x0 - c1 / c2;
            counter++;
        };
        cout << "Number of steps = " << counter<< endl;
        res = x0;
        return true;
    }
}

int main() {
    double d = 0;
    bool m_1 = newtonMethod(f, 0.5, 1.5, 1.2, d);
    if (m_1) {
        cout << "x0 = " << d << endl;
    }
    return 0;
};
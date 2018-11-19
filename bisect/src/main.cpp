#include <iostream>
#include <cmath>

using namespace std;

double f(double x) {
    double y = tan(x) - 1 / x;
    return y;
};

double a, b, x0;
double difference = 1;
double epsilon = pow(10, -50);
int counter = 0;

int main() {
    cout << "Enter a: ";
    cin >> a;
    cout << "Enter b: ";
    cin >> b;

    while (difference > epsilon) {
        double c = (a + b) / 2;
        if (f(c) == 0) {
            difference = 0;
        } else if (f(a) * f(c) < 0) {
            b = c;
            difference = abs(a - b);
        } else {
            a = c;
            difference = abs(a - b);
        };
        counter = counter + 1;
    };
    x0 = (a + b) / 2;
    cout << "Root is: " << x0 << endl << "Number of steps: " << counter;
    return 0;
}

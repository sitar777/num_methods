#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

double epsilon = pow(10,-20);
double eps = pow(10,-5);
int N = 5;
double x1, x2, x3;
int a = 1;

/*
 *
 * A * x = B
 *
 *  2  -3   1     x1     7
 *  1   4  -1  *  x2  =  6  - solved matrix
 *  3  -2   2     x3     14
 *
 */

void matrixOnConstMultiply(vector<vector<double>> &G, double lambda)
{
    for (auto it = G.begin(); it != G.end(); it++) {
        for (auto val = (*it).begin(); val != (*it).end(); val++) {
            (*val) *= lambda;
        }
    }
}

void matrixSum(vector<vector<double>> &G, vector<vector<double>> &M)
{
            for (int i = 0; i < size(G); ++i) {
                for (int j = 0;j < size(G[i]); j++) {
                   G[i][j] += M[i][j];
                }
            }
}

void printMatrix(vector<vector<double>> &A){
    for (auto it = A.begin(); it != A.end(); it++) {
        for (auto val = (*it).begin(); val != (*it).end(); val++) {
            cout << *val << "\t";
        }
        cout << endl;
    }
}

void gauss(vector<vector<double>> &A, vector<double> &B) {
    double A1[3][3] =
            {
                    A[0][0] / A[0][0],
                    A[0][1] / A[0][0],
                    A[0][2] / A[0][0],
                    A[1][0] - A1[0][0] * A[1][0],
                    A[1][1] - A1[0][1] * A[1][0],
                    A[1][2] - A1[0][2] * A[1][0],
                    A[2][0] - A1[0][0] * A[2][0],
                    A[2][1] - A1[0][1] * A[2][0],
                    A[2][2] - A1[0][2] * A[2][0]
            };
    double B1[3] = {B[0] / A[0][0], B[1] - B1[0] * A[1][0], B[2] - B1[0] * A[2][0]};

    double A2[3][3] =
            {
                    A1[0][0],
                    A1[0][1],
                    A1[0][2],
                    A1[1][0],
                    A1[1][1] / A1[1][1],
                    A1[1][2] / A1[1][1],
                    A1[2][0] - A2[1][0] * A1[2][1],
                    A1[2][1] - A2[1][1] * A1[2][1],
                    A1[2][2] - A2[1][2] * A1[2][1]
            };
    double B2[3] = {B1[0], B1[1] / A1[1][1], B1[2] - B2[1] * A1[2][1]};

    double A3[3][3] =
            {
                    A2[0][0],
                    A2[0][1],
                    A2[0][2],
                    A2[1][0],
                    A2[1][1],
                    A2[1][2],
                    A2[2][0] / A2[2][2],
                    A2[2][1] / A2[2][2],
                    A2[2][2] / A2[2][2]

            };
    double B3[3] = {B2[0], B2[1], B2[2] / A2[2][2]};

/*
 *
 *    1 a b     x1     b1
 *    0 1 c  *  x2  =  b2
 *    0 0 1     x3     b3
 *
 */

    x3 = B3[2];
    x2 = B3[1] - A3[1][2] * x3;
    x1 = B3[0] - A3[0][1] * x2 - A3[0][2] * x3;

/*
     *
     * x1 = 4
     * x2 = 1
     * x3 = 2
     *
*/

}

    int zeidel(vector<vector<double >> &A, vector<double> &B)
    {
        if (A[0][0] == 0 or A[1][1] == 0 or A[2][2] == 0)
        {
            cout << "Zeidel method can't be used!";
        }
        else
        {
            cout << "Enter approximate roots: " << endl << "x1 = ";
            cin >> x1;
            cout << "x2 = ";
            cin >> x2;
            cout << "x3 = ";
            cin >> x3;



            double diff1 = 1;
            double diff2 = 1;
            double diff3 = 1;

            while (diff1 >= epsilon and diff2 >= epsilon and diff3 >= epsilon)
                //diff1 >= epsilon and diff2 >= epsilon and diff3 >= epsilon or k < 20
            {
                double x1_old = x1;
                double x2_old = x2;
                double x3_old = x3;

                x1 = (-A[0][1] / A[0][0]) * x2 +
                        (-A[0][2] / A[0][0]) * x3 +
                        (B[0] / A[0][0]);
                x2 = (-A[1][0] / A[1][1]) * x1 +
                        (-A[1][2] / A[1][1]) * x3 +
                        (B[1] / A[1][1]);
                x3 = (-A[2][0] / A[2][2]) * x1 +
                        (-A[2][1] / A[2][2]) * x2 +
                        (B[2] / A[2][2]);

                diff1 = abs(x1 - x1_old);
                diff2 = abs(x2 - x2_old);
                diff3 = abs(x3 - x3_old);
            }
        }
    }

int main()
{
    vector<vector<double >> D = {{2,-3,1},{1,4,-1},{3,-2,2}};
    vector<vector<double >> C = {{1,-1,-1},{0,1,-1},{0,0,1}};
    vector<vector<double >> M = {{1,-1,-1},{1,1,-1},{1,1,1}};
    vector<vector<double >> A = {{5,11,2},{1,3,4},{7,-5,3}};
    vector<double> B = {7, 6, 14};
    vector<double> B1 = {-1,-1,1};

    printMatrix(D);
    cout << endl;
    gauss(D,B);
    cout << x1 <<" "<< x2 <<" "<< x3 << endl << endl;
    zeidel(D,B);
    cout << x1 <<" "<< x2 <<" "<< x3 << endl;
    matrixOnConstMultiply(M,eps*N);
    matrixSum(M,C);
    printMatrix(M);
    gauss(M,B1);
    cout << x1 <<" "<< x2 <<" "<<x3<< endl;
    zeidel(M,B1);
    cout << x1 <<" "<< x2 <<" "<<x3<< endl;
    return 0;
}
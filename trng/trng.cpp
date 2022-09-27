#include <iostream>
#include <cmath>
#include <fstream>
#include <omp.h>

using namespace std;

void trueRandomNumberGenerator(double& x, double& r, int& alpha, int& beta, int& gamma, int& c);

int main()
{
    //ofstream MyFile("randomNumbers.txt");

    unsigned char result;

    int alpha = int(8);
    int beta = int(5);
    int gamma = int(5);
    double x = double(0.352346764576);
    double r = double(3.86);
    int quantity = 10000;

    for (int i = 0; i < 20; i++) {
        int c = 0;

        trueRandomNumberGenerator(ref(x), ref(r), ref(alpha), ref(beta), ref(gamma), ref(c));

        if (x == 0) {
            x = double(0.352346764576);
            continue;
        }
    }

    for (int j = 0; j < quantity; j++) {
        int c = 0;

        trueRandomNumberGenerator(ref(x), ref(r), ref(alpha), ref(beta), ref(gamma), ref(c));

        if (x == 0) {
            x = double(0.352346764576);
            continue;
        }
        result = x * 256;

        //MyFile << int(result) << endl;

    }

    cout << int(result);

    return 0;
}

void trueRandomNumberGenerator(double& x, double& r, int& alpha, int& beta, int& gamma, int& c) {

    double y[5];
    double rp[5];

#pragma omp parallel num_threads(alpha)
    while (c <= alpha) {

        c++;
        rp[0] = r;
        for (int i = 1; i <= 4; i++) {
            for (int j = 1; j <= gamma; j++) {
                x = x * rp[0] * (1 - x);
                x = (x * 1000) - floor(x * 1000);
            }
            y[i] = 3.86 + (x * 0.14);
        }

        for (int k = 2; k <= beta; k++) {
            if (x >= 0.5) {
                rp[1] = (y[1] + y[3]) / 2;
                rp[2] = (y[1] + y[3]) / 2;
                rp[3] = (y[2] + y[4]) / 2;
                rp[4] = (y[2] + y[4]) / 2;
            }
            else {
                rp[1] = (y[1] + y[3] + y[2] + y[4]) / 4;
                rp[2] = (y[1] + y[3] + y[2] + y[4]) / 4;
                rp[3] = (y[1] + y[3] + y[2] + y[4]) / 4;
                rp[4] = (y[1] + y[3] + y[2] + y[4]) / 4;
            }
            for (int i = 1; i <= 4; i++) {
                for (int j = 1; j <= gamma; j++) {
                    x = x * rp[i] * (1 - x);
                    x = (x * 1000) - floor(x * 1000);
                }
                y[i] = 3.86 + (x * 0.14);
            }
        }
        r = (y[1] + y[3] + y[2] + y[4]) / 4;
    }
#pragma omp barrier  
}
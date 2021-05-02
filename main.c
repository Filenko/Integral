#include <stdio.h>
#include <math.h>

double f1(double x) {
    return pow(x, 5);
}

double f2(double x) {
    return -1 / x;
}

double f3(double x) {
    return sin(x) + cos(x)/3;
}

double g1(double x) {
    return x + 3;
}

double g2(double x) {
    return pow(x - 2, 3) - 1;
}

double g3(double x) {
    return -2 * x + 8;
}

// Find root of f(x) == g(x) in [a, b]
// f and g must be determine on [a, b]
// f and g should have only one root

double root(double (*f)(double), double (*g)(double), double a, double b, double eps1) {
    double m;
    double x_m;
    while (b - a > eps1) {
        m = (b - a) / 2;
        x_m = a + m;
        //printf("%f %f\n", f(a), f(x_m));
        if ( (f(a) - g(a) >= 0 && f(x_m) - g(x_m) <= 0)
                || (f(a) - g(a) <= 0 && f(x_m) - g(x_m) >= 0) ) {
            b = x_m;
        }
        else {
            a = x_m;
        }
    }
    return x_m;
}

// Find definite integral of the function F from a to b
// f must be determine on [a, b]
double integral(double (*f)(double), double a, double b, double eps2) {
    int N = 10;
    double I1 = 0;
    double I2 = 0;
    double h = (b - a) / N;
    for (int i = 0; i < N; i++) {
        I1 += f(a + h * (i + 0.5));
    }
    I1 *= h;
    N *= 2;
    h = (b - a) / N;
    for (int i = 0; i < N; i++) {
        I2 += f(a + h * (i + 0.5));
    }
    I2 *= h;
    //Сalculating the integral up to a given accuracy using the Rung's rule
    while (fabs(I2 - I1) > 3 * eps2) {
        I1 = I2;
        N *= 2;
        h = (b - a) / N;
        I2 = 0.0;
        for (int i = 0; i < N; i++) {
            I2 += f(a + h * (i + 0.5));
        }
        I2 *= h;
    }
    return I2;
}

int main(void) {

    printf("This program calculates the definite integral and finds the intersection points of the functions.\n");
    printf("Integral of the x^5 from 0 to 5: %f\n", integral(f1, 0, 5, 0.000001));
    printf("WolframAlpha ans: 2604.16666666667\n");
    //WolframAlpha integral_0^5 x^5 dx = 15625/6≈2604.16666666667
    printf("Integral of the -1/x from 1 to 5: %f\n", integral(f2, 1, 5, 0.000001));
    printf("WolframAlpha ans: -1.60943791243410\n");
    //WolframAlpha "integral -1/x from 1 to 5" ans : -1.60943791243410
    printf("Integral of the sin(x) + cos(x)/3 from 0 to 10: %f\n", integral(f3, 0, 10, 0.000001));
    printf("WolframAlpha ans: 1.65773115878000\n");
    //WolframAlpha integral_0^10 (sin(x) + cos(x)/3) dx ≈1.65773115878000
    printf("Root of x^5 = x+3 on [0, 5] : %f\n", root(f1, g1, 0, 5, 0.000001));
    printf("WolframAlpha ans : x≈1.3412935\n");
    //WolframAlpha x≈1.3412935
    printf("Root of -1/x = (x-2)^3 - 1 on [1, 5]: %f\n", root(f2, g2, 1, 5, 0.000001));
    printf("WolframAlpha ans : x≈2.8668\n");
    //WolframAlpha x≈2.8668

    printf("Root of sin(x) + cos(x)/3 = -2*x + 8 on [1, 5] : %f\n", root(f3, g3, 1, 5, 0.000001));
    printf("WolframAlpha ans : x≈4.5224727950649938504\n");
    //WolframAlpha x≈4.5224727950649938504
    return 0;
}
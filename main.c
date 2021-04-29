#include <stdio.h>
#include <math.h>

double f1(double x) {
    return pow(x, 5);
}

double f2(double x) {
    return -1 / x;
}

double f3(double x) {
    return 0.35 * x * x - 0.95 * x + 2.7;
}

double g1(double x) {
    return x + 3;
}

double g2(double x) {
    return pow(x - 2, 3) - 1;
}

double g3(double x){
    return -2*x + 8;
}

//Функция считает точку пересечения заданных фукций на отрезке
//Необзодимо, чтобы функции были определены на отрезке

double root(double (*f)(double), double (*g)(double), double a, double b, double eps1) {
    double length = b - a;
    double m;
    double x_m;
    while (b - a > eps1) {
        m = (b - a) / 2;
        x_m = a + m;
        //printf("%f %f\n", f(a), f(x_m));
        if (f(a) - g(a) >= 0 && f(x_m) - g(x_m) <= 0
                || f(a) - g(a) <= 0 && f(x_m) - g(x_m) >= 0) {
            b = x_m;
        }
        else {
            a = x_m;
        }
    }
    return x_m;
}

//Считает определенный интеграл функции f от a до b
//Необходимо, чтобы функция была определена на [a,b]
double integral(double (*f)(double), double a, double b, double eps2) {
    double x;
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
    //Вычисляем интеграл до заданной точности, пользуясь правилом Рунга
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


    printf("%f\n", integral(f1, 0, 5, 0.00001));
    //WolframAlpha integral_0^5 x^5 dx = 15625/6≈2604.16666666667
    printf("%f\n", integral(f2, 1, 5, 0.00001));
    //WolframAlpha "integral -1/x from 1 to 5" ans : -1.60943791243410
    printf("%f\n", integral(f3, 0, 10, 0.0001));
    //WolframAlpha integral_0^10 (0.35 x^2 - 0.95 x + 2.7) dx = 96.1667
    printf("%f\n", root(f1, g1, 0, 5, 0.0001));
    //WolframAlpha x≈1.3412935
    printf("%f\n", root(f2, g2, 1, 5, 0.0001));
    //WolframAlpha x≈2.8668
    printf("%f\n", root(f3, g3, 1, 5, 0.0001));
    //WolframAlpha x≈2.67047
    return 0;
}
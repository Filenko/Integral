#include <stdio.h>
#include <math.h>
#include <string.h>

double atof(char * s);
extern double f1(double x);
extern double f2(double x);
extern double f3(double x);

double root_f1(double x) {
    return x - x + 0.5;
}
double root_f2(double x) {
    return cos(x);
}
double root_f3(double x) {
    return log(x) - 1;
}

double integral_f1(double x) {
    return x;
}
double integral_f2(double x) {
    return pow(x, 2) + 2;
}
double integral_f3(double x) {
    return sqrt(x);
}

// Find root of f(x) == g(x) in [a, b]
// f and g must be determine on [a, b]
// f and g should have only one root
int counter = 0;
double root(double (*f)(double), double (*g)(double), double a, double b, double eps1) {
    double m;
    double x_m = a;
    while (b - a > eps1) {
        counter++;
        m = (b - a) / 2;
        x_m = a + m;
        if ( (f(a) - g(a) >= 0 && f(x_m) - g(x_m) <= 0)
                || (f(a) - g(a) <= 0 && f(x_m) - g(x_m) >= 0) ) {
            b = x_m;
            if (f(a) - g(a) == 0)
                return a;
            if (f(x_m) - g(x_m) == 0)
                return x_m;
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

void print_help() {
    printf("HELP:\n");
    printf("-intersection  -  Print the coordinates of the intersection points of the functions\n\n");
    printf("-iterations - Print the number of iterations when looking for intersection points of the functions\n\n");
    printf("-test_root - Calculate and print the intersection point of functions with given accuracy. \nUser input: after -test_root program is waiting for 5 numbers (for example -test_root 1 2 -2 3 0.0001): first function (from 1 to 3), second function (from 1 to 3), a, b - segment coordinates (a must be <= b), eps - calculation accuracy.\n\n");
    printf("-test_integral - Calculate and print the definite integral of the function a on the segment [a, b] with given accuracy. \nUser input: after -test_integral program is waiting for 4 numbers (for example -test_integral 1 -1 1 0.001): function (from 1 to 3), a, b - segment coordinates (a must be <= b), eps - calculation accuracy\n\n");
    printf("-v to see how program works\n");
    printf("Function for root testing 1: 0.5\n");
    printf("Function for root testing 2: cos(x)\n");
    printf("Function for root testing 3: ln(x) - 1\n");
    printf("\n");
    printf("Function for integral testing 1: x\n");
    printf("Function for integral testing 1: x^2 + 2\n");
    printf("Function for integral testing 1: sqrt(x)\n");
    printf("1\n");
}

int argument_check(double x, char * s) {
    int len = strlen(s);
    for (int i = 0; i < len; i++) {
        if ( !(s[i] >= '0' && s[i] <= '9') && s[i] != '-' && s[i] != '.') {
            printf("Invalid argument!\n\n");
            print_help();
            return 0;
        }
        if(s[i] == '-' && i != 0){
            printf("Invalid argument!\n\n");
            print_help();
            return 0;
        }
    }
    if ((fabs(x) - 0.0 <= 0.0000001) && s[0] != '0') {
        printf("Invalid argument.\n\n");
        print_help();
        return 0;
    }
    else return 1;
}

int main(int argc, char** argv) {

    int test_flag = 0;
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-help") == 0) {
            print_help();
            return 0;
        }
        if ((strcmp(argv[i], "-test_root") == 0) || (strcmp(argv[i], "-test_integral") == 0)) {
            test_flag = 1;
        }
        if (strcmp(argv[i], "-v") == 0) {
            printf("The program finds the area of ​​a curve limited by three functions with an accuracy of 0.001\n");
            printf("To calculate integral program uses rectangle method, to find intersection points of functions program uses bisection method.\n");
            return 0;
        }
    }

    if (test_flag == 0) {
        int counter1 = 0;
        int counter2 = 0;
        int counter3 = 0;
        double x1 = root(f1, f3, 1, 5, 0.00001);
        counter1 = counter;
        double x2 = root(f2, f3, 1, 10, 0.00001);
        counter2 = counter - counter1;
        double x3 = root(f1, f2, 0, 10, 0.00001);
        counter3 = counter - counter1 - counter2;

        double Sum = integral(f1, x1, x3, 0.00001) - integral(f2, x2, x3, 0.00001) - integral(f3, x1, x2, 0.00001);
        printf("Area of the figure: %lf \n\n", Sum);

        for (int i = 1; i < argc; i++) {
            if (strcmp(argv[i], "-intersection") == 0) {
                printf("Intersections: \n");
                printf("intersection point of f1 and f3: %lf\n", x1);
                printf("intersection point of f2 and f3: %lf\n", x2);
                printf("intersection point of f1 and f2: %lf\n", x3);
                printf("\n\n");
            }
            else if (strcmp(argv[i], "-iterations") == 0) {
                printf("Iterations:\n");
                printf("f1 and f3 iterations: %d\n", counter1);
                printf("f2 and f3 iterations: %d\n", counter2);
                printf("f1 and f2 iterations: %d\n", counter3);
                printf("Sum is : %d\n\n", counter);
                printf("\n\n");
            }
            else {
                printf("Invalid argument: %s\n\n", argv[i]);
                print_help();
            }
        }
        return 0;
    }

    double tmp_a = 0.0;
    double tmp_b = 0.0;
    double tmp_eps = 0.0;
    double ans = 0.0;
    double (*func_root[3])(double);
    double (*func_integral[3])(double);
    func_root[0] = root_f1;
    func_root[1] = root_f2;
    func_root[2] = root_f3;
    func_integral[0] = integral_f1;
    func_integral[1] = integral_f2;
    func_integral[2] = integral_f3;

    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-test_root") == 0) {
            int first_f = 0;
            int second_f = 0;
            printf("Root test: \n");
            //-test-root 1 1 2 0.001
            if (i + 5 >= argc) {
                printf("Invalid argument!\n\n");
                print_help();
                return 0;
            }
            first_f = atof(argv[i + 1]);
            if (argument_check(first_f, argv[i + 1]) == 0) {
                return 0;
            }
            second_f = atof(argv[i + 2]);
            if (argument_check(second_f, argv[i + 2]) == 0) {
                return 0;
            }
            tmp_a = atof(argv[i + 3]);
            if (argument_check(tmp_a, argv[i + 3]) == 0) {
                return 0;
            }
            tmp_b = atof(argv[i + 4]);
            if (argument_check(tmp_b, argv[i + 4]) == 0) {
                return 0;
            }
            if (tmp_a - tmp_b > 0.000001) {
                printf("a must be less/equal than b!\n");
                return 0;
            }
            tmp_eps = atof(argv[i + 5]);
            if (argument_check(tmp_eps, argv[i + 5]) == 0) {
                return 0;
            }
            double (*ff1)(double) = func_root[first_f - 1];
            double (*ff2)(double) = func_root[second_f - 1];
            ans = root(ff1, ff2, tmp_a, tmp_b, tmp_eps);
            printf("Root is %lf\n", ans);
            printf("\n\n");
            i += 5;
        }
        else if (strcmp(argv[i], "-test_integral")  == 0) {
            int ff = 0;
            printf("Integral test: \n");
            if (i + 4 >= argc) {
                printf("Invalid argument!\n\n");
                print_help();
                return 0;
            }
            ff = atof(argv[i + 1]);
            if (argument_check(ff, argv[i + 1]) == 0) {
                return 0;
            }
            tmp_a = atof(argv[i + 2]);
            if (argument_check(tmp_a, argv[i + 2]) == 0) {
                return 0;
            }
            tmp_b = atof(argv[i + 3]);
            if (argument_check(tmp_b, argv[i + 3]) == 0) {
                return 0;
            }
            if (tmp_a - tmp_b > 0.000001) {
                printf("a must be less/equal than b!\n");
                return 0;
            }
            tmp_eps = atof(argv[i + 4]);
            if (argument_check(tmp_eps, argv[i + 4]) == 0) {
                return 0;
            }
            ans = integral(func_integral[ff - 1], tmp_a, tmp_b, tmp_eps);
            printf("Integral is : %lf", ans);
            printf("\n\n");
            i += 4;
        }
        else {
            printf("Invalid argument: %s\n\n", argv[i]);
            print_help();
        }
    }
    return 0;
}

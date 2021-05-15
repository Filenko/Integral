#include <stdio.h>
#include <math.h>
#include <string.h>

int main(int argc, char** argv) {

    double x = 2.00001;
    if ((int)x != x)
        printf("7\n");

    return 0;
}

#include <stdio.h>

double pot_rapida(double a, int b) {
    /*
    pesquisei
    */
    if (b == 0) {
        return 1;
    }
    double res = pot_rapida(a, b/2);
    if (b % 2 == 0) {
        return res * res;
    } else {
        return a * res * res;
    }    
}

int main() {
    double res = 0;
    double a;
    int b;
    scanf("%lf %d", &a, &b);
    res = pot_rapida(a, b);
    printf("%.2lf\n", res);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>

void f(int a, int b) {
    int c = a;
    a = b;
    b = c;
}

int * g(int *c, int n) {
    c = malloc(sizeof(int) * n);
    return c; // sem o return, o ponteiro é mudado apenas localmente
}

void h(int *h) {
    *h = 100;
}

int main() {
    int a = 1, b = 2, c= 3;
    int **d;
    d = malloc(sizeof(int*));
    f(a, b); // não modifica os valores de a e de b
    d[0] = g(d[0], 1);
    h(&d[0][0]);
    
    printf("%d, %d, %d\n", a, c, d[0][0]);

    free(d[0]);
    free(d);
    return 0;
}
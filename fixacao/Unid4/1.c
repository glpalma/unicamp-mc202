#include <stdio.h>
#include <math.h>

typedef struct complexo {
    double real, img;
} Complexo;

Complexo inicializar_cpx(double real, double img) {
    Complexo z;
    z.real = real;
    z.img = img;

    return z;
}

void imprimir_cpx(Complexo a) {
    printf("%.2lf %.2lfi\n", a.real, a.img);
}

// Devolve a soma do complexo a com o b.
Complexo somar_cpx(Complexo a, Complexo b) {
    Complexo z;
    z.real = a.real + b.real;
    z.img = a.img + b.img;

    return z;
}

// Devolve a subtração do complexo a pelo b.
Complexo subtrair_cpx(Complexo a, Complexo b) {
    Complexo z;
    z.real = a.real - b.real;
    z.img = a.img - b.img;

    return z;
}

Complexo prod_cpx(Complexo a, Complexo b) {
    Complexo z;

    z.real = ((a.real * b.real) - (a.img * b.img));
    z.img = ((a.real * b.img) + (a.img * b.real));

    return z;
}

// Devolve 1 se a parte real de a for maior que a de b.
int comparar_cpxr(Complexo a, Complexo b) {
    if (a.real > b.real)
        return 1;
    else
        return 0;
}

// Devolve 1 se a parte imaginária de a for maior que a de b.
int comparar_cpxi(Complexo a, Complexo b) {
    if (a.img > b.img)
        return 1;
    else
        return 0;
}

// Devolve o conjugado do número complexo z.
double conjugado_cpx(Complexo a) {
    double auxiliar;
    auxiliar = pow(a.real, 2) + pow(a.img, 2);

    return sqrt(auxiliar);
}

// Devolve um número complexo dividido por um número real
Complexo dividir_cpx(Complexo a, double n) {
    Complexo z;

    z.real = (a.real/n);
    z.img = (a.img/n);

    return z;
}

int main() {
    Complexo a, b, c;
    a = inicializar_cpx(2, 1);
    b = inicializar_cpx(5, 9);
    c = prod_cpx(a, b);
    imprimir_cpx(c);
}
#include <stdio.h>

double potR(double base, int exp) {
    if (exp == 0) {
        return 1;
    } else {
        return base * potR(base, exp - 1);
    }
}

double potI(double base, int exp) {
    double prod = 1;
    int i;

    for (i = 0; i < exp; i++) {
        prod *= base;
    }
    return prod;
}

int main() {
    double teste;
    teste = potI(123456, 2);
    printf("%.2lf\n", teste);

    return 0;
}

/*
Resposta das perguntas:

Na maneira em que estão implementadas, as duas funções realizam o mesmo número de multiplicações,
mas a versão recursiva utiliza mais memória, pois precisa lidar com várias chamadas simultâneas ao
mesmo tempo, que podem ser resolvidas com apenas uma chamada da função iterativa.

*/
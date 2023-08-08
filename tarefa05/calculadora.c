// Este arquivo representa o cliente
#include <stdio.h>
#include "inteiros_grandes.h"

int main() {
    int n;
    char operador;
    p_num num1, num2, resultado;
    num1 = criar_numero();
    num2 = criar_numero();
    resultado = criar_numero();

    scanf("%d", &n); // recebe o número de operações a serem realizadas

    for (int operacao = 0; operacao < n; operacao++) {
        scanf(" %c", &operador);
        num1 = ler_numero(num1);
        num2 = ler_numero(num2);
        resultado = executar_operacao(num1, num2, operador, resultado);

        imprimir_numero(resultado);

        reciclar_numero(num1);
        reciclar_numero(num2);
        reciclar_numero(resultado);
    }
    destruir_numero(num1);
    destruir_numero(num2);
    destruir_numero(resultado);
    return 0;
}
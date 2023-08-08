#include "arvore_listas_legais.h"

int main() {
    p_no lista_legal = criar_arvore();
    numLegal num = 0;
    int qtd_num = 0, qtd_op = 0;
    int operacao = 0, resultado = 0;

    // lê o número de números a serem lidos e de operações 
    ler_dados(&qtd_num, &qtd_op);
    // lê os números e os adiciona à arvore
    lista_legal = ler_numeros(lista_legal, qtd_num);

    for (int i = 0; i < qtd_op; i++) {
        ler_operacao(&operacao, &num); // lê a operação e o número a ser operado
        lista_legal = executar_operacao(lista_legal, operacao, num, &resultado);
        imprimir_resultado(resultado); // imprime o resultado da operação escolhida
    }
    destruir_arvore(lista_legal); // libera a memória utilizada pela lista

    return 0;
}
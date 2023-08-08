#include "dicionario.h"
#include <stdio.h>
#include <stdlib.h>

void ler_info(int* n1, int* n2) {
    scanf(" %d %d", n1, n2);
}

char* ler_palavra_dicio() {
    // aloca, lê e retorna uma palavra a ser adicionada no dicionário
    char* palavra;
    palavra = malloc(MAX_PALAVRA * sizeof(char));
    scanf(" %s", palavra);
    return palavra;
}

void ler_palavra(char* palavra) {
    scanf(" %s", palavra);
}

int main() {
    p_hash dicio = criar_dicionario();
    int qtd_dicio = 0, qtd_palavras = 0;
    int correcao = 0;
    char* pdicio; // palavra armazenada no dicionário
    char palavra[MAX_PALAVRA];

    ler_info(&qtd_dicio, &qtd_palavras);
    
    // para cada palavra do dicionário
    for (int i = 0; i < qtd_dicio; i++) {
        pdicio = ler_palavra_dicio();
        inserir_palavra(dicio, pdicio);
    }
    // para cada palavra a ser verificada
    for (int i = 0; i < qtd_palavras; i++) {
        ler_palavra(palavra);
        correcao = verificar_correcao(dicio, palavra);
        imprimir_correcao(correcao);
    }

    destruir_dicionario(dicio);
    return 0;
}

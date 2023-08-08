#include <stdio.h>
#include "planilha.h"
#define MAX_NOME 128

void ler_nome(char* nome) {
    scanf("%s", nome);
}

void ler_dimensoes(int* n_linhas, int* n_colunas) {
    scanf(" %d %d", n_colunas, n_linhas);
}

char ler_operacao() {
    char operacao;
    if (scanf(" %c", &operacao) == EOF) {
        return 'F';
    } else {
        return operacao;
    }
}

int main() {
    p_pln planilha;
    int n_linhas = 0, n_colunas = 0;
    char operacao;
    char nome_planilha[MAX_NOME];
    
    ler_nome(nome_planilha);
    ler_dimensoes(&n_linhas, &n_colunas);

    planilha = alocar_planilha(n_linhas, n_colunas);
    ler_planilha_disco(planilha, nome_planilha);

    // enquanto a entrada não tiver acabado
    while (1) {
        operacao = ler_operacao();
        if (operacao == 'F') {
            break;
        }
        operacao_planilha(planilha, operacao);
    }

    destruir_planilha(planilha);

    return 0;
}
#include "dicionario.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define M 433 // tamanho do vetor do hash

void checar_alocacao(void* ponteiro) {
    if (ponteiro == NULL) {
        printf("Falta de memória! Encerrando o programa...\n");
        exit(1);
    }
}

p_hash criar_dicionario() {
    p_hash dicio;
    // alocação da estrutura do hash
    dicio = malloc(sizeof(Hash));
    checar_alocacao(dicio);
    // alocação do vetor do hash
    dicio->v = malloc(M * sizeof(p_no));
    checar_alocacao(dicio->v);
    // inicialização dos ponteiros das listas no vetor
    for (int i = 0; i < M; i++) {
        dicio->v[i] = NULL;
    }
    // inicialização dos valores do hash
    dicio->tam = M;
    dicio->qtd = 0;

    return dicio;
}

void destruir_lista_str(p_no lista) {
    if (lista != NULL) {
        destruir_lista_str(lista->prox);
        free(lista->palavra);
        free(lista);
    }
}

void destruir_dicionario(p_hash dicio) {
    for (int i = 0; i < M; i++) {
        destruir_lista_str(dicio->v[i]);
    }
    free(dicio->v);
    free(dicio);
}

int hash(char* palavra) {
    // método da divisão
    int i;
    int n = 0;
    for (i = 0; i < strlen(palavra); i++) {
        n = (256 * n + palavra[i]) % M;
    }

    return n;
}

p_no inserir_palavra_lista(p_no lista, char* palavra) {
    // insere no início
    p_no novo;
    novo = malloc(sizeof(*novo));
    checar_alocacao(novo);

    novo->palavra = palavra;
    novo->prox = lista;

    return novo;
}

void inserir_palavra(p_hash dicio, char* palavra) {
    int pos;
    pos = hash(palavra);
    dicio->v[pos] = inserir_palavra_lista(dicio->v[pos], palavra);
    dicio->qtd += 1;
}

int contar_erros(char* p1, char* p2) {
    int len1 = strlen(p1);
    int len2 = strlen(p2);
    int len_maior = len1 >= len2 ? len1 : len2;
    int len_menor = len1 < len2 ? len1 : len2;
    char* maior = len1 >= len2 ? p1 : p2; // palavra com maior comprimento
    char* menor = len1 < len2 ? p1 : p2;

    int contador = 0;
    int i1 = 0; // percorre a palavra maior
    int i2 = 0; // percorre a palavra menor

    // encontra o número de caracteres distintos na mesma posição
    while (maior[i1] != '\0' && menor[i2] != '\0') {
        if (maior[i1] != menor[i2]) {
            contador += 1;
            if (len_maior != len_menor) {
                // caso haja um caractere "intruso"
                if (i1 + 1 < len_maior && maior[i1 + 1] == menor[i2]) {
                    i1++;
                }
                else if (i2 + 1 < len_menor && menor[i2 + 1] == maior[i1]) {
                    i2++;
                }
            }
        }
        i1++;
        i2++;
    }

    // se apenas uma palavra tiver acabado no while
    if ((maior[i1] == '\0' && menor[i2] != '\0') || (maior[i1] != '\0' && menor[i2] == '\0')) {
        contador += abs(len1 - len2);
    }

    return contador;
}

int obter_menor(int* v, int n) {
    if (v != NULL) {
        int menor = v[0];
        for (int i = 0; i < n; i++) {
            if (v[i] < menor) {
                menor = v[i];
            }
        }
        return menor;
    }
    else {
        return -1;
    }
}

int verificar_correcao(p_hash dicio, char* palavra) {
    int num_erros = 0;
    int pos = hash(palavra);

    // verifica se a equivalente correta da palavra está na
    // posição fornecida pelo hash
    for (p_no aux = dicio->v[pos]; aux != NULL; aux = aux->prox) {
        if (strcmp(palavra, aux->palavra) == 0) {
            return 0; // achou a palavra equivalente
        }
    }

    // se não encontrar a palavra na posição dada pelo hash
    int* erros;
    int i_erros = 0; // indice do vetor
    erros = calloc(dicio->qtd, sizeof(int)); // vetor auxiliar
    for (int i = 0; i < dicio->tam; i++) { // percorre o vetor
        for (p_no no = dicio->v[i]; no != NULL; no = no->prox) { // percorre a lista ligada
            num_erros = contar_erros(no->palavra, palavra);
            erros[i_erros] = num_erros;
            i_erros += 1;
        }
    }
    // encontra o menor número de erros (palavra mais similar)
    num_erros = obter_menor(erros, dicio->qtd);
    free(erros);

    return num_erros;
}

void imprimir_correcao(int nerr) {
    switch (nerr) {
    case (0):
        printf("verde\n");
        break;
    case (1):
        printf("amarelo\n");
        break;
    default:
        printf("vermelho\n");
        break;
    }
}

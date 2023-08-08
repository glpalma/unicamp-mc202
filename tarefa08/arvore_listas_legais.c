#include <stdio.h>
#include <stdlib.h>
#include "arvore_listas_legais.h"

void checar_alocacao(void* ponteiro) {
    if (ponteiro == NULL) {
        printf("Falta de memória! Encerrando o programa...\n");
        exit(1);
    }
}

p_no criar_arvore() {
    return NULL;
}

void destruir_arvore(p_no raiz) {
    if (raiz != NULL) {
        destruir_arvore(raiz->esq);
        destruir_arvore(raiz->dir);
        free(raiz);
    }
}

void ler_dados(int* qtd_num, int* qtd_op) {
    scanf("%d %d", qtd_num, qtd_op);
}

int ehVermelho(p_no no) {
    if (no == NULL) {
        return 0;
    }
    return no->cor == VERMELHO;
}

int ehPreto(p_no no) {
    if (no == NULL) {
        return 1;
    }
    return no->cor == PRETO;
}

p_no rotaciona_para_esquerda(p_no raiz) {
    p_no x = raiz->dir;
    raiz->dir = x->esq;
    x->esq = raiz;
    x->cor = raiz->cor;
    raiz->cor = VERMELHO;

    return x;
}

p_no rotaciona_para_direita(p_no raiz) {
    p_no x = raiz->esq;
    raiz->esq = x->dir;
    x->dir = raiz;
    x->cor = raiz->cor;
    raiz->cor = VERMELHO;

    return x;
}

void sobe_vermelho(p_no raiz) {
    if (raiz != NULL) {
        raiz->cor = VERMELHO;
        raiz->esq->cor = PRETO;
        raiz->dir->cor = PRETO;
    }
}

p_no contar_ocorrencia(p_no raiz, numLegal num) {
    p_no novo;
    if (raiz == NULL) { // caso o número não exista na lista
        novo = malloc(sizeof(No));
        checar_alocacao(novo);
        novo->esq = NULL;
        novo->dir = NULL;
        novo->num = num;
        novo->ocorrencias = 1;
        novo->cor = VERMELHO;
        return novo;
    }
    else if (raiz->num == num) { // caso ele já exista
        raiz->ocorrencias += 1;
        return raiz;
    }

    if (num < raiz->num) {
        raiz->esq = contar_ocorrencia(raiz->esq, num);
    }
    else {
        raiz->dir = contar_ocorrencia(raiz->dir, num);
    }
    // rebalanceia a árvore
    if (ehVermelho(raiz->dir) && ehPreto(raiz->esq)) {
        raiz = rotaciona_para_esquerda(raiz);
    }
    if (ehVermelho(raiz->esq) && ehVermelho(raiz->esq->esq)) {
        raiz = rotaciona_para_direita(raiz);
    }
    if (ehVermelho(raiz->esq) && ehVermelho(raiz->dir)) {
        sobe_vermelho(raiz);
    }
    return raiz;
}

p_no buscar_numero(p_no raiz, numLegal num) {
    if (raiz == NULL || raiz->num == num) {
        return raiz;
    }
    else if (raiz->num < num) {
        return buscar_numero(raiz->dir, num);
    }
    else {
        return buscar_numero(raiz->esq, num);
    }
}

int numero_ocorrencias(p_no raiz, numLegal num) {
    p_no numero = buscar_numero(raiz, num);

    if (numero == NULL) {
        return 0;
    }
    else {
        return numero->ocorrencias;
    }
}

int contar_ilegaisR(p_no raiz, int contador) {
    if (raiz != NULL) {
        contador = contar_ilegaisR(raiz->esq, contador);
        if (raiz->num > raiz->ocorrencias) { // considera todas as ocorrências
            contador += raiz->ocorrencias;
        }
        else if (raiz->num < raiz->ocorrencias) { // considera as ocorrências excessivas
            contador += (raiz->ocorrencias - raiz->num);
        }
        contador = contar_ilegaisR(raiz->dir, contador);
    }
    return contador;
}

int contar_ilegais(p_no raiz) {
    int contador = 0;
    contador = contar_ilegaisR(raiz, contador);

    return contador;
}

void ler_operacao(int* operacao, numLegal* num) {
    scanf(" %d", operacao);
    // só lê o número caso a operação não seja 3
    if ((*operacao) == 3) {
        (*num) = -1;
    }
    else {
        scanf("%ld", num);
    }
}

p_no executar_operacao(p_no raiz, int operacao, numLegal num, int* resultado) {

    switch (operacao) {
    case (1): // adicionar número à lista
        raiz = contar_ocorrencia(raiz, num);
        *resultado = -1;
        break;
    case (2): // número de ocorrências do número fornecido
        *resultado = numero_ocorrencias(raiz, num);
        break;
    case (3): // quantidade de números que não satisfazem a lista legal
        *resultado = contar_ilegais(raiz);
        break;
    default:
        printf("Operação ainda não implementada.\n");
        break;
    }

    return raiz;
}

p_no ler_numeros(p_no raiz, int qtd_num) {
    numLegal num = 0;
    for (int i = 0; i < qtd_num; i++) {
        scanf("%ld", &num); // lê o número
        raiz = contar_ocorrencia(raiz, num); // insere na ABB balanceada
    }
    return raiz;
}

void imprimir_resultado(int resultado) {
    if (resultado != -1) {
        printf("%d\n", resultado);
    }
}
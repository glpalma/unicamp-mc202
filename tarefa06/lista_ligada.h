#ifndef LISTA_LIGADA
#define LISTA_LIGADA
#include <stdio.h>

typedef struct no* p_no;

typedef struct no {
    int dado;
    p_no prox;
} No;

typedef struct lista {
    p_no ini, fim;
} Lista;

typedef Lista* p_lista;

/**
 * Exibe uma mensagem de erro para o usuário e encerra o programa com erro 1
 * */
void erro_memoria();

/**
 * Cria e aloca a cabeça de uma lista ligada de inteiros.
 * */
p_lista criar_lista();

/**
 * Adiciona um número a uma lista ligada de inteiros.
 * */
p_lista adiciona_fim(p_lista lista, int dado);

/**
 * Remove o primeiro item de uma lista ligada de inteiros.
 * */
p_lista remove_inicio(p_lista lista);

/**
 * Destrói uma lista lidada de inteiros.
 * */
void destruir_lista(p_lista lista);

#endif
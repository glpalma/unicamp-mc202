// exercícios de lista ligada
#include <stdlib.h>
#include <stdio.h>

typedef struct no {
    int chave;
    struct no* prox;
} No;

typedef No* p_no;

// a
p_no inserir_ordenada(p_no lista, int x) {
    p_no novo = malloc(sizeof(No));
    novo->chave = x;
    if (lista == NULL) { // lista vazia
        novo->prox = NULL;
        return novo;
    }
    else { // lista com n elementos
        if (x < lista->chave) {
            novo->prox = lista;
            return novo;
        }
        else {
            p_no atual = lista;
            while (atual->prox != NULL && x > atual->prox->chave) {
                atual = atual->prox;
            }
            novo->prox = atual->prox;
            atual->prox = novo;
            return lista;
        }
    }
}

// b
p_no uniao(p_no lista1, p_no lista2) {
    // possui O(n), sendo n o comprimento da lista1
    p_no atual = lista1;

    while (atual->prox != NULL) {
        atual = atual->prox;
    }
    atual->prox = lista2;

    return lista1;
}

void imprimir_lista(p_no lista) {
    if (lista != NULL) {
        printf("%d ", lista->chave);
        imprimir_lista(lista->prox);
    }
}

// c
p_no concatord(p_no lista1, p_no lista2) {
    // possui complexidade O(n + m) ?
    // sendo n = len(lista1) e m = len(lista2)
    for (p_no atual = lista2; atual != NULL; atual = atual->prox) {
        inserir_ordenada(lista1, atual->chave);
    }
    return lista1;
}

int main() {
    p_no lista1 = NULL;
    p_no lista2 = NULL;
    lista1 = inserir_ordenada(lista1, 3);
    lista1 = inserir_ordenada(lista1, 8);
    lista1 = inserir_ordenada(lista1, 1);
    lista1 = inserir_ordenada(lista1, 23);
    lista1 = inserir_ordenada(lista1, 7);
    imprimir_lista(lista1);
    printf("\n");

    lista2 = inserir_ordenada(lista2, 50);
    lista2 = inserir_ordenada(lista2, 6);
    lista2 = inserir_ordenada(lista2, 12);
    lista2 = inserir_ordenada(lista2, 28);
    lista2 = inserir_ordenada(lista2, 9);
    lista1 = concatord(lista1, lista2);
    imprimir_lista(lista1);
    printf("\n");
    return 0;
}
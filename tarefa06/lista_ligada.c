#include "lista_ligada.h"
#include <stdlib.h>

void erro_memoria() {
    printf("Não há memória suficiente!\n");
    exit(1);
}

p_lista criar_lista() {
    p_lista nova;
    nova = malloc(sizeof(Lista));
    if (nova == NULL) {
        erro_memoria();
    }
    nova->ini = NULL;
    nova->fim = NULL;

    return nova;
}

p_lista adiciona_fim(p_lista lista, int x) {
    p_no novo = malloc(sizeof(*novo));
    if (novo == NULL) {
        erro_memoria();
    }
    novo->dado = x;

    if (lista->ini == NULL && lista->fim == NULL) { // caso a lista seja vazia
        lista->ini = novo;
        lista->fim = novo;
        novo->prox = NULL;
    }
    else {
        lista->fim->prox = novo;
        novo->prox = NULL;
        lista->fim = novo;
    }

    return lista;
}

p_lista remove_inicio(p_lista lista) {
    if (lista != NULL) {
        p_no prim = lista->ini;
        lista->ini = prim->prox;
        free(prim);
    }
    return lista;
}

void destruir_corpo_lista(p_no no) {
    if (no != NULL) {
        destruir_corpo_lista(no->prox);
        free(no);
    }
}

void destruir_lista(p_lista lista) {
    if (lista != NULL) {
        destruir_corpo_lista(lista->ini);
        free(lista);
    }
}

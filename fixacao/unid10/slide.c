#include <stdio.h>
#include <stdlib.h>

typedef struct no * p_no;

typedef struct no  {
    int dado;
    p_no prox;
} No;

p_no busca_elemento(p_no lista, int dado) {
    p_no procurado = NULL;
    p_no atual = lista;

    while (atual != NULL) {
        if (atual->dado == dado) {
            procurado = atual;
            break;
        }
        atual = lista->prox;
    }
    return procurado;
}

void remove_prim_ocorrencia(p_no lista, int procurado) {
    p_no ant, atual;
    atual = lista;

    while (atual != NULL) {
        if (atual->dado == procurado) {
           ant->prox = atual->prox;
           free(atual);
           break;
        }
        ant = atual;
        atual = lista->prox;
    }
}

void remove_todas_ocorrencias(p_no lista, int procurado) { // essa função pode ser facilmente otimizada, mas preguiça
    if (lista == NULL) {
		return;
	} else {
		remove_prim_ocorrencia(lista, procurado);
		remove_todas_ocorrencias(lista->prox, procurado);
	}
}
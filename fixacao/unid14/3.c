#include <stdlib.h>

struct no {
    int valor;
    struct no* esq, dir;
};

typedef struct no* p_no;

void contar_nos_nivelR(p_no raiz, int nivel_atual, int nivel_buscado, int* nnos) {
    if (raiz != NULL) {
        if (nivel_atual == nivel_buscado) {
            *nnos += 1;
        }
        else if (nivel_atual < nivel_buscado) {
            contar_nos_nivelR(raiz->esq, nivel_atual + 1, nivel_buscado, nnos);
            contar_nos_nivelR(raiz->dir, nivel_atual + 1, nivel_buscado, nnos);
        }
    }
}

int contar_nos_nivel(p_no raiz, int nivel) {
    int nos = 0;

    contar_nos_nivelR(raiz, 1, nivel, &nos);

    return nos;
}

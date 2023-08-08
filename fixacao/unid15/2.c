struct no {
    int dado;
    struct no* esq, * dir;
};

typedef struct no* p_no;

void imprime_inversa(p_no raiz) {
    if (raiz != NULL) {
        imprime_inversa(raiz->dir);
        printf("%d ", raiz->dado);
        imprime_inversa(raiz->esq);
    }
}

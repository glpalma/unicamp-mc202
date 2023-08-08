struct no {
    int dado;
    struct no* esq, * dir;
};

typedef struct no* p_no;

p_no remover_chave(p_no raiz, int num) {
    p_no no;
    if (raiz == NULL) {
        return raiz;
    }
    if (num < raiz->dado) {
        raiz->esq = remover_chave(raiz->esq, num);
    }
    else if (num > raiz->dado) {
        raiz->dir = remover_chave(raiz->dir, num);
    }
    else if (raiz->esq == NULL) {
        no = raiz->dir;
        free(raiz);
        return no;
    }
    else if (raiz->dir == NULL) {
        no = raiz->esq;
        free(raiz);
        return no;
    }
    else {
        substituir_por_sucessor(raiz);
    }
    return raiz;
}

p_no inserir_chave(p_no raiz, int num) {
    p_no novo;
    if (raiz == NULL) {
        novo = malloc(sizeof(No));
        checar_alocacao(novo);
        novo->esq = NULL;
        novo->dir = NULL;
        novo->dado = num;
        return novo;
    }
    if (num < raiz->dado) {
        raiz->esq = inserir_chave(raiz->esq, num);
    }
    else {
        raiz->dir = inserir_chave(raiz->dir, num);
    }
    return raiz;
}

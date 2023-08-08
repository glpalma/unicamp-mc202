// exercício 3
#include <stdlib.h>
#include <stdio.h>

struct no {
    int i, j; // coordenadas
    double valor;
    struct no* vt; // navegação vertical 
    struct no* hz; // navegação hotizontal
};

typedef struct no* p_no;

typedef struct matriz {
    int m, n; // linhas e colunas
    p_no* linhas, colunas; // vetor
} Matriz;

typedef Matriz* p_mx;

void checar_alocacao(void* ponteiro) {
    if (ponteiro == NULL) {
        printf("Falta de memória! Encerrando o programa...\n");
        exit(1);
    }
}

p_no buscar_na_coluna(p_mx matriz, int i, int j) {
    p_no atual = matriz->colunas[j]->vt; // último nó

    while (atual->i != -1 && atual->i > i) {
        atual = atual->vt;
    }

    if (atual->i == -1 || atual->i < i) {
        // não achou
        return NULL;
    }
    else {
        return atual;
    }
}

p_no buscar_na_linha(p_mx matriz, int i, int j) {
    p_no atual = matriz->linhas[i]->hz; // último nó

    while (atual->j != -1 && atual->j > j) {
        atual = atual->hz;
    }

    if (atual->j == -1 || atual->j < j) {
        // não achou
        return NULL;
    }
    else {
        return atual;
    }
}

p_no buscar_no(p_mx matriz, int i, int j) {
    p_no procurado = NULL;
    // condicional evita que a função navegue
    // nós desnecessários
    if (i >= j) {
        // busca a partir do último nó presente
        // na coluna
        // devolve NULL se não encontrar
        procurado = buscar_na_coluna(matriz, i, j);
    }
    else {
        // busca a partir do último nó presente
        // na linha
        // devolve NULL se não encontrar
        procurado = buscar_na_linha(matriz, i, j);
    }
    // devolve o nó inteiro
    return procurado;
}

// aloca e devolve o ponteiro
p_mx criar_matriz(int linhas, int colunas) {
    p_mx matriz;
    matriz = malloc(sizeof(Matriz));
    checar_alocacao(matriz);

    matriz->m = linhas;
    matriz->n = colunas;

    matriz->linhas = malloc(linhas * sizeof(p_no));
    matriz->colunas = malloc(colunas * sizeof(p_no));
    checar_alocacao(matriz->linhas);
    checar_alocacao(matriz->colunas);

    // inicializa as linhas
    for (int i = 0; i < linhas; i++) {
        matriz->linhas[i] = malloc(sizeof(struct no));
        checar_alocacao(matriz->linhas[i]);
        matriz->linhas[i]->i = i;
        matriz->linhas[i]->j = -1;
        matriz->linhas[i]->vt = NULL;
        matriz->linhas[i]->hz = matriz->linhas[i];
    }

    // inicializa as colunas
    for (int i = 0; i < colunas; i++) {
        matriz->colunas[i] = malloc(sizeof(struct no));
        checar_alocacao(matriz->colunas[i]);
        matriz->colunas[i]->j = j;
        matriz->colunas[i]->i = -1;
        matriz->colunas[i]->hz = NULL;
        matriz->colunas[i]->vt = matriz->colunas[i];
    }

    return matriz;
}

p_no atribuir_por_coluna(p_mx matriz, p_no no, int i, int j, double valor) {

    if (no->i < i) {
        p_no novo = malloc(sizeof(*novo));
        checar_alocacao(novo);
        novo->i = i;
        novo->j = j;
        novo->valor = valor;
        novo->vt = no;
        religar_linha(matriz, novo);
        return novo;
    }
    else if (no->i == i) { // nó já existe
        no->valor = valor
    }
    else { // buscar no resto da coluna
        no->vt = atribuir_por_coluna(no->vt, i, j, valor);
    }
    return no;
}

// insere/altera um valor na matriz
void atribuir_valor(p_mx matriz, int i, int j, double valor) {
    if (i >= j) {
        matriz->colunas[j] = atribuir_por_coluna(matriz, matriz->colunas[j], i, j, valor);
    }
    else {
        // função de atribuir por linha é análoga
        matriz->linhas[i] = atribuir_por_linha(matriz, matriz->linhas[i], i, j, valor);
    }
}

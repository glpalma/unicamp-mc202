#include <stdlib.h>

// a
struct no {
    int i, j; // coordenadas
    double valor;
    struct no* vt; // navegação vertical 
    struct no* hz; // navegação hotizontal
};

typedef struct no* p_no;

/*
questão b

Os nós dummies apontam para o final do conjunto que
representam. Por exemplo, os nós dummies de coluna
apontam para o último nó presente nessa coluna.
Isso entra em contradição com as listas ligadas comuns,
cujo ponteiro correspondente aponta para o início
da lista.

Além disso, o último nó de uma lista ligada aponta
para NULL, ou seja, não está conectado ao início,
enquanto no caso da matriz, existe um loop de nós.
*/

// questão c

/*
Sobre a complexidade do algoritmo
Como a navegação pela matriz se dá
horizontal e verticalmente, a complexidade
do algoritmo de busca é de O(n + m), sendo
n o número de linhas e m o de colunas.
*/

typedef struct matriz {
    int m, n; // linhas e colunas
    p_no linhas, colunas; // vetor
} Matriz;

typedef Matriz* p_mx;

p_no buscar_na_coluna(p_mx matriz, int i, int j) {
    p_no atual = matriz->colunas[j].vt; // último nó

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
    p_no atual = matriz->linhas[i].hz; // último nó

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
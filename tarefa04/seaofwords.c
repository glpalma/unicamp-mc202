#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LIN 100
#define MAX_COL 100
#define MAX_PALAVRAS 10
#define MAX_CARAC 20

void ler_matriz_char(char matriz[MAX_LIN][MAX_COL], int l, int c) {
    char caractere;
    int i, j;

    for (i = 0; i < l; i++) {
        for (j = 0; j < c; j++) {
            scanf(" %c", &caractere);
            matriz[i][j] = caractere;
        }
        matriz[i][j] = '\0';
    }
}

void ler_palavras(char palavras[MAX_PALAVRAS][MAX_CARAC], int n) {

    for (int i = 0; i < n; i++) {
        scanf(" %s", palavras[i]);
    }
}

int coordenada_eh_valida(int l, int c, int i, int j, int usado[MAX_LIN][MAX_COL]) {
    if ((i >= 0 && i < l) && (j >= 0 && j < c)) {
        if (!(usado[i][j])) {
            return 1;
        } else {
            return 0;
        }
    } else {
        return 0;
    }
}

void zera_matriz(int matriz[MAX_LIN][MAX_COL], int l, int c) {
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < c; j++) {
            matriz[i][j] = 0;
        }
    }
}

int pista_no_textoR(char matriz[MAX_LIN][MAX_COL], int l, int c, int i, int j, char palavra[MAX_CARAC], int idx, int usado[MAX_LIN][MAX_COL]) {
    int len;
    len = strlen(palavra);
    int achou = 0;

    if (idx == len) { // caso base
        achou = 1;
    } else { // caso geral
        if (coordenada_eh_valida(l, c, i, j, usado) && matriz[i][j] == palavra[idx]) {
            usado[i][j] = 1;
            if (pista_no_textoR(matriz, l, c, i - 1, j, palavra, idx + 1, usado) || // para cima
                pista_no_textoR(matriz, l, c, i + 1, j, palavra, idx + 1, usado) || // para baixo
                pista_no_textoR(matriz, l, c, i, j - 1, palavra, idx + 1, usado) || // para a esquerda
                pista_no_textoR(matriz, l, c, i, j + 1, palavra, idx + 1, usado)) { // para a direita
                achou = 1;
            }
            usado[i][j] = 0;
        } else {
            achou = 0; 
        }
    }
    return achou;
}

int pista_no_texto(char matriz[MAX_LIN][MAX_COL], int l, int c, char palavra[MAX_CARAC]) {
    int usado[MAX_LIN][MAX_COL];
    int i, j;

    zera_matriz(usado, l, c);

    for (i = 0; i < l; i++) {
        for (j = 0; j < c; j++) {
            if (matriz[i][j] == palavra[0]) { // procura a 1ª letra da palavra na matriz
                if ((pista_no_textoR(matriz, l, c, i, j, palavra, 0, usado))) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

void encontrar_palavras(char matriz[MAX_LIN][MAX_COL], int l, int c, char palavras[MAX_PALAVRAS][MAX_CARAC], int num_palavras, int presenca[MAX_PALAVRAS]) {
    int i;

    for (i = 0; i < num_palavras; i++) {
        if (pista_no_texto(matriz, l, c, palavras[i])) {
            presenca[i] = 1;
        } else {
            presenca[i] = 0;
        }
    }
}

void imprimir_resultado(int presenca[MAX_PALAVRAS], int n) {

    for (int i = 0; i < n; i++) {
        if (presenca[i]) {
            printf("sim\n");
        } else {
            printf("nao\n");
        }
    }
}

int main() {
    int l, c, num_palavras;
    char matriz[MAX_LIN][MAX_COL];
    char palavras[MAX_PALAVRAS][MAX_CARAC];
    int presenca[MAX_PALAVRAS];

    scanf("%d %d", &l, &c);
    scanf("%d", &num_palavras);

    ler_matriz_char(matriz, l, c);
    ler_palavras(palavras, num_palavras);

    encontrar_palavras(matriz, l, c, palavras, num_palavras, presenca);
    imprimir_resultado(presenca, num_palavras);
    return 0;
}
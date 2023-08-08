#include <stdio.h>
#include <string.h>
#define MAX_LIN 100
#define MAX_COL 100
#define MAX_PALAVRAS 10
#define MAX_CARAC 20

struct posicao {
    int i, j;
};

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

int movimento_eh_valido(int l, int c, int i, int j) {
    if ((i >= 0 && i < l) && (j >= 0 && j < c)) {
        return 1;
    } else {
        return 0;
    }
}

struct posicao pos_prox_letra(char matriz[MAX_LIN][MAX_COL], int i, int j, int l, int c, char prox_letra, int analisado[MAX_LIN][MAX_COL]) {
    static int movimentos[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // movimentos permitidos na matriz
    struct posicao pos;
    int i_mov, j_mov;
    pos.i = pos.j = -1;

    for (int mov = 0; mov < 4; mov++) {
        i_mov = i + movimentos[mov][0];
        j_mov = j + movimentos[mov][1];
        if (movimento_eh_valido(l, c, i_mov, j_mov)) {
            if ((matriz[i_mov][j_mov] == prox_letra) && !(analisado[i_mov][j_mov])) {
                pos.i = i_mov;
                pos.j = j_mov;
                break;
            }
        }
    }
    return pos;
}

void zera_matriz(int matriz[MAX_LIN][MAX_COL], int l, int c) {
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < c; j++) {
            matriz[i][j] = 0;
        }
    }
}

void imprime_matriz(int matriz[MAX_LIN][MAX_COL], int l, int c) { // APAGAR ESSA FUNÇÃO
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < c; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n"); 
    }
}

int pista_no_textoR(char matriz[MAX_LIN][MAX_COL], int pos_l, int pos_c, int l, int c,
    char palavra[MAX_CARAC], int idx_letra, int analisado[MAX_LIN][MAX_COL]) {

    int i, j, passou_inicio = 0;
    int n = strlen(palavra);
    char letra, prox_letra;
    struct posicao prox;
    letra = palavra[idx_letra];
    prox_letra = palavra[idx_letra + 1];

    if ((n == idx_letra + 1) && (palavra[n - 1] == palavra[idx_letra]) && !(analisado[pos_l][pos_c])) {
        return 1;
    }

    for (i = pos_l; i < l; i++) {
        for (j = 0; j < c; j++) {
            if (i == pos_l && (!(passou_inicio))) {
                j = pos_c;
                passou_inicio = 1;
            }
            if (matriz[i][j] == letra) {
                analisado[i][j] = 1;
                prox = pos_prox_letra(matriz, i, j, l, c, prox_letra, analisado); // retorna -1 caso não ache
                if ((prox.i >= 0) && (prox.j >= 0)) {
                    return pista_no_textoR(matriz, prox.i, prox.j, l, c, palavra, idx_letra + 1, analisado);
                }
                analisado[i][j] = 0;
            }
        }
    }
    return 0;
}

int pista_no_texto(char matriz[MAX_LIN][MAX_COL], int l, int c, char palavra[MAX_CARAC]) {
    int analisado[MAX_LIN][MAX_COL];
    zera_matriz(analisado, l, c);
    return pista_no_textoR(matriz, 0, 0, l, c, palavra, 0, analisado);
}

void encontrar_palavras(char matriz[MAX_LIN][MAX_COL], int l, int c, char palavras[MAX_PALAVRAS][MAX_CARAC], int num_palavras, int presenca[MAX_PALAVRAS]) {
    int i;

    for (i = 0; i < num_palavras; i++) {
        if (pista_no_texto(matriz, l, c, palavras[i])) { // só falta um jeito de catalogar as letras que já foram
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
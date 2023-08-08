#include <stdio.h>

#define MAX_SORTEADOS 10
#define MAX_PESSOAS 1000
#define NUM_COLUNAS 10
#define NUM_LINHAS 6

void preencher_matriz(int matriz[][NUM_COLUNAS], int altura, int largura, int numero) {
    int i, j;

    for (i = 0; i < altura; i++) {
        for (j = 0; j < largura; j++) {
            matriz[i][j] = numero;
        }
    }
}

void marcar_sorteados(int solucao[][NUM_COLUNAS], int sorteados[], int n_sorteados) {
    int linha, coluna, p;
    int numero;

    for (p = 0; p < n_sorteados; p++) {
        numero = sorteados[p];

        linha = numero / NUM_COLUNAS; /* Divisão inteira */
        coluna = (numero - linha * NUM_COLUNAS - 1);
        solucao[linha][coluna] = 1;
    }
}

void imprimir_apostas(int n, int apostas[][NUM_COLUNAS]) {
        for (int i = 0; i < NUM_LINHAS; i++) {
            for (int j = 0; j < NUM_COLUNAS; j++) {
                printf("%d ", apostas[i][j]);
            }
            printf("\n");
        }
}

void calcular_numero_acertos(int n_apostas, int apostas[][NUM_COLUNAS],
    int n_sorteados, int sorteados[MAX_SORTEADOS], int num_acertos[MAX_PESSOAS]) {

    int solucao[NUM_LINHAS][NUM_COLUNAS];
    int idx_aposta, i, j;
    int pontos, linha;

    preencher_matriz(solucao, NUM_LINHAS, NUM_COLUNAS, 0); /* Preenche a matriz com zeros */

    marcar_sorteados(solucao, sorteados, n_sorteados); /* Marca os números sorteados na matriz solucao */

    for (idx_aposta = 0; idx_aposta < n_apostas; idx_aposta++) { /* Percorre cada aposta */
        pontos = 0;
        for (i = 0; i < NUM_LINHAS; i++) {
            for (j = 0; j < NUM_COLUNAS; j++) {
                linha = (i + idx_aposta * NUM_LINHAS);
                if ((solucao[i][j] == apostas[linha][j]) && (solucao[i][j] == 1)) {
                    pontos += 1;
                }
            }
        }
        num_acertos[idx_aposta] = pontos;
    }
}

int main() {
    int solucao[NUM_LINHAS][NUM_COLUNAS];
    int sorteados[6] = {25, 6, 2, 51, 15, 16};
    int num_acertos[MAX_PESSOAS];
    int aposta[NUM_LINHAS][NUM_COLUNAS] = {
        {1,1,0,0,0,1,0,0,0,0}, 
        {0,0,0,0,1,1,0,0,0,0},
        {0,0,0,0,1,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0}
    };

    calcular_numero_acertos(1, aposta, 6, sorteados, num_acertos);
    

    preencher_matriz(solucao, NUM_LINHAS, NUM_COLUNAS, 0);
    marcar_sorteados(solucao, sorteados, 6);
    imprimir_apostas(1, solucao);

    printf("%d\n", num_acertos[0]);

    return 0;


}
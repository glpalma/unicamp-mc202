#include <stdio.h>

#define MAX_SORTEADOS 10
#define MAX_PESSOAS 1000
#define NUM_COLUNAS 10
#define NUM_LINHAS 6

void ler_apostas(int n, int apostas[][NUM_COLUNAS]) {
    int linha;

    for (int contador = 0; contador < n; contador++) {
        for (int i = 0; i < NUM_LINHAS; i++) {
            linha = (i + contador * NUM_LINHAS);
            for (int j = 0; j < NUM_COLUNAS; j++) {
                apostas[linha][j] = 0;
                scanf("%d ", &apostas[linha][j]);
            }
        }
    }
}

void ler_numeros_sorteados(int n, int sorteados[]) {
    for (int i = 0; i < n; i++) {
        scanf("%d", &sorteados[i]);
    }
}

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

void calcular_premios(int n, int num_acertos[], double premio_total) {
    int i;
    int seis_acertos = 0, cinco_acertos = 0, quatro_acertos = 0;

    for (i = 0; i < n; i++) {
        if (num_acertos[i] == 6) {
            seis_acertos += 1;
        } else if (num_acertos[i] == 5) {
            cinco_acertos += 1;
        } else if (num_acertos[i] == 4) {
            quatro_acertos += 1;
        }
    }

    for (i = 0; i < n; i++) {
        if (num_acertos[i] == 6) {
            printf("%.2lf\n", ((0.62 * premio_total) / seis_acertos));
        } else if (num_acertos[i] == 5) {
            printf("%.2lf\n", ((0.19 * premio_total) / cinco_acertos));
        } else if (num_acertos[i] == 4) {
            printf("%.2lf\n", ((0.19 * premio_total) / quatro_acertos));
        } else {
            printf("0.00\n");
        }
    }
}

int main() {
    int num_jogadores;
    double premio_total;
    int apostas[NUM_LINHAS * MAX_PESSOAS][NUM_COLUNAS];
    int sorteados[MAX_SORTEADOS], num_acertos[MAX_PESSOAS];

    scanf("%d %lf ", &num_jogadores, &premio_total);

    ler_apostas(num_jogadores, apostas);
    ler_numeros_sorteados(6, sorteados);

    calcular_numero_acertos(num_jogadores, apostas, 6, sorteados, num_acertos);
    calcular_premios(num_jogadores, num_acertos, premio_total);

    return 0;
}
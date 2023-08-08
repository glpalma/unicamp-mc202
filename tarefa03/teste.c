#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct termo {
    char *titulo;
    double *dados_brutos;
    double max, min, med, des_pad;

} Termo;

typedef struct info_categorias {
    int bot_qtd, surpreendente_qtd, normal_qtd, local_qtd, irrelevante_qtd; // Número de termos dentro da categoria
    char **bot_titulos, **surpreendente_titulos, **normal_titulos, **local_titulos, **irrelevante_titulos; // Matriz contendo os nomes dos termos correspondentes à categoria

} Classificao;

double obter_max(double *vetor, int n_dados) {
    double maximo;
    printf("Chegou aqui1\n");
    maximo = vetor[0];
    printf("Chegou aqui1\n");

    for (int i = 0; i < n_dados; i++) {
        if (vetor[i] > maximo) {
            maximo = vetor[i];
        }
    }
    return maximo;
}

double obter_min(double *vetor, int n_dados) {
    double minimo;
    minimo = vetor[0];

    for (int i = 0; i < n_dados; i++) {
        if (vetor[i] < minimo) {
            minimo = vetor[i];
        }
    }
    return minimo;
}

double calcular_media(double *vetor, int n_dados) {
    double soma, media;
    soma = 0;

    for (int i = 0; i < n_dados; i++) {
        soma += vetor[i];
    }
    media = soma / n_dados;
    return media;    
}

double calcular_des_pad(double *vetor, int n_dados, double media) {
    double diferenca, auxiliar, raiz, soma = 0;
    
    for (int i = 0; i < n_dados; i++) {
        diferenca = vetor[i] - media;
        auxiliar = pow(diferenca, 2);
        soma += auxiliar / n_dados;
    }
    raiz = sqrt(soma);
    return raiz;
}

void calcular_parametros(Termo *termos, int num_dias, int num_termos) {

    for (int i = 0; i < num_termos; i++) {
        termos[i].max = obter_max(termos[i].dados_brutos, num_dias);
        termos[i].min = obter_min(termos[i].dados_brutos, num_dias);
        termos[i].med = calcular_media(termos[i].dados_brutos, num_dias);
        termos[i].des_pad = calcular_des_pad(termos[i].dados_brutos, num_dias, termos[i].med);
    }
}

void categorizar_engajamento();

void imprimir_dados_termos(Termo *termos, int num_termos) {

    for (int i = 0; i < num_termos; i++) {
        printf("%s ", termos[i].titulo);
        printf("%.2lf %.2lf ", termos[i].max, termos[i].min);
        printf("%.2lf %.2lf\n", termos[i].med, termos[i].des_pad);
    }
    printf("\n");
}

void imprimir_resultado(Termo *termo);

void erro_memoria() {
    printf("Não há memória suficiente!\n");
    exit(1);
}

void liberar_memoria_termos(Termo *termos, int num_termos, int num_dias) {

   for (int i = 0; i < num_termos; i++) {
       free(termos[i].titulo);
       free(termos[i].dados_brutos);
    }
   free(termos);
}

int main() {
    int num_termos, num_dias;
    int i, j;
    Termo *termos;

    scanf("%d %d", &num_termos, &num_dias);

    termos = malloc(num_termos * sizeof(Termo));
    if (termos == NULL) {
        erro_memoria();
    }

    for (i = 0; i < num_termos; i++) { // Para cada termo
        termos[i].titulo = malloc(25 * sizeof(char));
        if (termos[i].titulo == NULL) {
            erro_memoria();
        }           
        scanf("%s", termos[i].titulo);
        printf("%s\n", termos[i].titulo);

        termos[i].dados_brutos = malloc(num_dias * sizeof(double)); // fazer alocação de dados brutos
        if (termos[i].dados_brutos == NULL) {
            erro_memoria();
        }
        for (j = 0; j < num_dias; j++) { // Para cada dia
            scanf("%lf", &termos[i].dados_brutos[j]);
            printf("%lf\n", termos[i].dados_brutos[j]);
        }
    }
    calcular_parametros(termos, num_dias, num_termos);
    printf("Chegou aqui!!!\n");
    imprimir_dados_termos(termos, num_termos);

    return 0;
}
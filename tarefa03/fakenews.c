#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_STRING 25

typedef struct termo {
    char *titulo;
    double *dados_brutos;
    double max, min, med, des_pad;

} Termo;

typedef struct info_categorias {
    int bot_qtd, surpreendente_qtd, normal_qtd, local_qtd, irrelevante_qtd; // Número de termos dentro da categoria
    int bot_idx, surpreendente_idx, normal_idx, local_idx, irrelevante_idx;
    int *bot_titulos, *surpreendente_titulos, *normal_titulos, *local_titulos, *irrelevante_titulos; // Vetor com os índices dos títulos associados à categoria

} Categoria;

void erro_memoria() {
    printf("Não há memória suficiente!\n");
    exit(1);
}

double obter_max(double *vetor, int n_dados) {
    double maximo;
    maximo = vetor[0];

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

void contar_categorias(Termo *termos, Categoria *categorias, int num_termos) {
    categorias->bot_qtd = 0; // Inicializa os valores
    categorias->surpreendente_qtd = 0;
    categorias->normal_qtd = 0;
    categorias->local_qtd = 0;
    categorias->irrelevante_qtd = 0;

    for (int i = 0; i < num_termos; i++) {
        if ((termos[i].med >= 60) && (termos[i].des_pad > 15)) {
            categorias->bot_qtd += 1;        
        } else if ((termos[i].med >= 60) && (termos[i].des_pad <= 15)) {
            categorias->surpreendente_qtd += 1;
        } else if (((termos[i].med < 60) && (termos[i].max >= 80)) && (termos[i].min > 20)) {
            categorias->normal_qtd += 1;
        } else if (((termos[i].med < 60) && (termos[i].max >= 80)) && (termos[i].min <= 20)) {
            categorias->local_qtd += 1;
        } else if ((termos[i].med < 60) && (termos[i].max <= 80)) {
            categorias->irrelevante_qtd += 1;
        }
    }
}

void verif_mem_int(int *vetor_int) {
    if (vetor_int == NULL) {
        erro_memoria();
    }
}

Categoria * aloca_categorias(Termo *termos, int num_termos) {
    Categoria *classe;
    classe = malloc(sizeof(Categoria));
    contar_categorias(termos, classe, num_termos); // Conta quantos termos irão em cada categoria
    // para fazer uma alocação do tamanho certo

    classe->bot_titulos = calloc(classe->bot_qtd, sizeof(int));
    verif_mem_int(classe->bot_titulos); // Verifica se houve memória o suficiente

    classe->surpreendente_titulos = calloc(classe->surpreendente_qtd, sizeof(int));
    verif_mem_int(classe->surpreendente_titulos);

    classe->normal_titulos = calloc(classe->normal_qtd, sizeof(int));
    verif_mem_int(classe->normal_titulos);

    classe->local_titulos = calloc(classe->local_qtd, sizeof(int));
    verif_mem_int(classe->local_titulos);

    classe->irrelevante_titulos = calloc(classe->irrelevante_qtd, sizeof(int));
    verif_mem_int(classe->irrelevante_titulos);

    return classe;
}

void categorizar_engajamento(Termo *termos, Categoria *categorias, int num_termos) {
    categorias->bot_idx = 0; // Inicializa os valores
    categorias->surpreendente_idx = 0;
    categorias->normal_idx = 0;
    categorias->local_idx = 0;
    categorias->irrelevante_idx = 0;

    for (int i = 0; i < num_termos; i++) { // Para cada termo i
        if ((termos[i].med >= 60) && (termos[i].des_pad > 15)) {
            categorias->bot_titulos[categorias->bot_idx] = i; // Cópia do índice do termo para o vetor apropriado
            categorias->bot_idx += 1;
        } else if ((termos[i].med >= 60) && (termos[i].des_pad <= 15)) {
            categorias->surpreendente_titulos[categorias->surpreendente_idx] = i;
            categorias->surpreendente_idx += 1;
        } else if (((termos[i].med < 60) && (termos[i].max >= 80)) && (termos[i].min > 20)) {
            categorias->normal_titulos[categorias->normal_idx] = i;
            categorias->normal_idx += 1;
        } else if (((termos[i].med < 60) && (termos[i].max >= 80)) && (termos[i].min <= 20)) {
            categorias->local_titulos[categorias->local_idx] = i;
            categorias->local_idx += 1;
        } else if ((termos[i].med < 60) && (termos[i].max <= 80)) {
            categorias->irrelevante_titulos[categorias->irrelevante_idx] = i;
            categorias->irrelevante_idx += 1;
        }
    }
}

void imprimir_dados_termos(Termo *termos, int num_termos) {
    for (int i = 0; i < num_termos; i++) {
        printf("%s ", termos[i].titulo);
        printf("%.2lf %.2lf ", termos[i].max, termos[i].min);
        printf("%.2lf %.2lf\n", termos[i].med, termos[i].des_pad);
    }
    printf("\n");
}

void imprimir_categoria(Termo *termos, int *lista_idx, int qtd_idx) {
    int idx_termo;

    for (int i = 0; i < qtd_idx; i++) {
        idx_termo = lista_idx[i];
        printf("%s ", termos[idx_termo].titulo);
    }
    printf("\n");
}

void imprimir_categorizacao(Termo *termos, Categoria *categorias) {
    printf("RESULTADO:\n");
    printf("Bot (%d): ", categorias->bot_qtd);
    imprimir_categoria(termos, categorias->bot_titulos, categorias->bot_qtd);

    printf("Surpreendente (%d): ", categorias->surpreendente_qtd);
    imprimir_categoria(termos, categorias->surpreendente_titulos, categorias->surpreendente_qtd);

    printf("Normal (%d): ", categorias->normal_qtd);
    imprimir_categoria(termos, categorias->normal_titulos, categorias->normal_qtd);

    printf("Local (%d): ", categorias->local_qtd);
    imprimir_categoria(termos, categorias->local_titulos, categorias->local_qtd); 

    printf("Irrelevante (%d): ", categorias->irrelevante_qtd);
    imprimir_categoria(termos, categorias->irrelevante_titulos, categorias->irrelevante_qtd);
}

void liberar_memoria_termos(Termo *termos, int num_termos) {

   for (int i = 0; i < num_termos; i++) {
       free(termos[i].titulo);
       free(termos[i].dados_brutos);
    }
    free(termos);
}

Termo * aloca_e_le_termos(int num_termos, int num_dias) {
    Termo *termos;
    int i, j;
    termos = malloc(num_termos * sizeof(Termo));
    if (termos == NULL) {
        erro_memoria();
    }

    for (i = 0; i < num_termos; i++) { // Para cada termo
        termos[i].titulo = malloc(MAX_STRING * sizeof(char));
        if (termos[i].titulo == NULL) {
            erro_memoria();
        }           
        scanf("%s", termos[i].titulo);

        termos[i].dados_brutos = malloc(num_dias * sizeof(double));
        if (termos[i].dados_brutos == NULL) {
            erro_memoria();
        }
        for (j = 0; j < num_dias; j++) { // Para cada dia
            scanf("%lf", &termos[i].dados_brutos[j]);
        }
    }
    return termos;
}

void liberar_memoria_classe(Categoria *categorias) {
    free(categorias->bot_titulos); // Liberar matriz de int
    free(categorias->surpreendente_titulos);
    free(categorias->normal_titulos);
    free(categorias->local_titulos);
    free(categorias->irrelevante_titulos);
    free(categorias); // Liberar infos das categorias
}

int main() {
    int num_termos, num_dias;
    Termo *termos;
    Categoria *categorias;

    scanf("%d %d", &num_termos, &num_dias);
    termos = aloca_e_le_termos(num_termos, num_dias);
    calcular_parametros(termos, num_dias, num_termos);
    categorias = aloca_categorias(termos, num_termos);
    categorizar_engajamento(termos, categorias, num_termos);
    
    imprimir_dados_termos(termos, num_termos);
    imprimir_categorizacao(termos, categorias);

    liberar_memoria_termos(termos, num_termos);
    liberar_memoria_classe(categorias);
    return 0;
}
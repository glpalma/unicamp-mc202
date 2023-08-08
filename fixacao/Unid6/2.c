#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct ponto {
    // ponto com n dimensões
    double *eixos;
} Pt;

Pt * alocar_matriz_Pt(int dim, int qtd) {
    Pt *pontos; // matriz que representa os pontos
    int i;

    pontos = malloc(sizeof(Pt) * qtd);
    if (pontos == NULL) {
        printf("Falta de memória!\n");
        exit(1);
    } 

    for (i = 0; i < qtd; i++) {
        pontos[i].eixos = calloc(sizeof(double), dim); // alocando cada vetor de eixos do ponto
        if (pontos[i].eixos == NULL) {
            printf("Falta de memória!\n");
            exit(1);
        } 
    }

    return pontos;
}

void ler_pontos(Pt *pontos, int dim, int qtd) {
    int i_ponto, i_dim;
    double eixo;

    for (i_ponto = 0; i_ponto < qtd; i_ponto++) {
        for (i_dim = 0; i_dim < dim; i_dim++) {
            scanf("%lf", &eixo);
            pontos[i_ponto].eixos[i_dim] = eixo;
        }
    }    
}

Pt * alocar_ponto(int dim) {
    Pt * ponto;

    ponto = malloc(sizeof(Pt));
    ponto->eixos = calloc(dim, sizeof(double));

    return ponto;
}

Pt * achar_centroide(Pt *centroide, Pt *pontos, int dim, int qtd) {
    int eixo, pt;
    double soma;

    for (eixo = 0; eixo < dim; eixo++) {
        soma = 0;
        for (pt = 0; pt < qtd; pt++) {
            soma += pontos[pt].eixos[eixo];
        }
        centroide->eixos[eixo] = (soma / qtd);
    }
    return centroide;
}

double soma_dist_centroide(Pt *centroide, Pt *pontos, int dim, int qtd) {
    double soma = 0, soma_dist = 0;
    int eixo, pt;
    double diferenca = 0;

    for (pt = 0; pt < qtd; pt++) {
        for (eixo = 0; eixo < dim; eixo++) {
            diferenca = fabs(pontos[pt].eixos[eixo] - centroide->eixos[eixo]);
            soma += pow(diferenca, 2);
        }
        printf("%lf\n", sqrt(soma));
        soma_dist += sqrt(soma);
        soma = 0;
    }
    return soma_dist;
}

void imprimir_ponto(Pt *ponto, int dim) {
    int i, coord_eixo;

    for (i = 0; i < dim; i++) {
        coord_eixo = ponto->eixos[i];
        printf("%d ", coord_eixo);
    }
    printf("\n");
}

void limpar_matriz_Pt(Pt *pontos, int dim, int qtd) {
    int i;

    for (i = 0; i < qtd; i++) { // para cada ponto
        free(pontos[i].eixos); //  liberar o vetor de coordenadas
    }
    free(pontos); // liberar matriz de pontos
}

int main() {
    int dim, qtd;
    Pt *centroide;
    Pt *pontos;
    double soma_dists;

    printf("Digite o número de dimensões e a quantidade de pontos: ");
    scanf("%d %d", &dim, &qtd);
    pontos = alocar_matriz_Pt(dim, qtd);
    ler_pontos(pontos, dim, qtd);

    centroide = alocar_ponto(dim);
    centroide = achar_centroide(centroide, pontos, dim, qtd);
    soma_dists = soma_dist_centroide(centroide, pontos, dim, qtd);
    imprimir_ponto(centroide, dim);
    printf("%lf\n", soma_dists);

    limpar_matriz_Pt(pontos, dim, qtd);
    return 0;
} 
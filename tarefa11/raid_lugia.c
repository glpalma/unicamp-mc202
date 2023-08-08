#include "raid_lugia.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void checar_alocacao(void* ponteiro) {
    if (ponteiro == NULL) {
        printf("Falta de memória! Encerrando o programa...\n");
        exit(1);
    }
}

// lista ligada de vertices
struct no_vert {
    p_vtc vertice;
    struct no_vert* prox;
};

typedef struct no_vert* p_no;

p_no criar_lista_vert() {
    return NULL;
}

p_no insere_vert_lista(p_no lista, p_vtc vertice) {
    // insere no início da lista
    p_no novo;
    novo = malloc(sizeof(*novo));
    checar_alocacao(novo);

    novo->vertice = vertice;
    novo->prox = lista;

    return novo;
}

void destruir_lista_vert(p_no lista) {
    // somente destroi a lista, mas não seu conteúdo
    if (lista != NULL) {
        destruir_lista_vert(lista->prox);
        free(lista->vertice);
        free(lista);
    }
}

p_vtc criar_vertice() {
    p_vtc vertice = malloc(sizeof(*vertice));
    checar_alocacao(vertice);

    p_pt pos = malloc(sizeof(*pos));
    checar_alocacao(pos);
    vertice->pos = pos;
    vertice->pos->x = 0;
    vertice->pos->y = 0;

    return vertice;
}

p_grafo criar_jogo() {
    p_grafo jogo = malloc(sizeof(*jogo));
    checar_alocacao(jogo);
    jogo->n_vtc = 0;
    // ponteiros são inicializados separadamente
    jogo->dist = NULL;
    jogo->vertices = NULL;

    return jogo;
}

void destruir_jogo(p_grafo jogo) {
    // libera o vetor de vértices
    for (int i = 0; i < jogo->n_vtc; i++) {
        free(jogo->vertices[i].pos);
    }
    free(jogo->vertices);

    // libera a matriz de distâncias
    for (int i = 0; i < jogo->n_vtc; i++) {
        free(jogo->dist[i]);
    }
    free(jogo->dist);
    free(jogo);
}

void troca_vertices(p_vtc vert1, p_vtc vert2) {
    struct vertice vert;
    vert = *(vert1);
    *(vert1) = *(vert2);
    *(vert2) = vert;
}

double distancia_euclidiana(p_pt p1, p_pt p2) {
    double distancia = 0;
    distancia = sqrt(pow(p2->x - p1->x, 2) + pow(p2->y - p1->y, 2));

    return distancia;
}

void inicializar_dados(p_grafo jogo, p_no lista, int n) {
    jogo->n_vtc = n;
    double distancia = 0;
    // aloca o vetor de vértices
    p_vtc vertices = malloc(n * sizeof(*vertices));
    checar_alocacao(vertices);

    // transfere os dados para o vetor
    p_no t = lista;
    int i = 0;
    while (i < n && t != NULL) {
        vertices[i] = *(t->vertice);
        // garante que o jogador fique no início do vetor
        if (vertices[i].tipo == JOGADOR && i != 0) {
            troca_vertices(&(vertices[0]), &(vertices[i]));
        }
        i++;
        t = t->prox;
    }
    jogo->vertices = vertices;

    // aloca a matriz
    double** distancias = calloc(n, sizeof(double*));
    checar_alocacao(distancias);
    for (int i = 0; i < n; i++) {
        distancias[i] = calloc(n, sizeof(double));
        checar_alocacao(distancias[i]);
    }

    // inicializa a matriz
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            distancias[i][j] = 0;
        }
    }
    jogo->dist = distancias;

    // calcula as distâncias e coloca na matriz
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j && jogo->dist[i][j] == 0) {
                distancia = distancia_euclidiana(vertices[i].pos, vertices[j].pos);
                jogo->dist[i][j] = distancia;
                jogo->dist[j][i] = distancia;
            }
        }
    }
}

void ler_posicoes(p_grafo jogo) {
    // inicialização dos dados
    int ivtc = 0;
    char tipo[15];
    double x = 0, y = 0;
    p_no lista = criar_lista_vert();

    // leitura dos dados do jogador
    p_vtc vertice = criar_vertice();
    checar_alocacao(vertice);
    scanf(" %lf %lf", &x, &y);
    vertice->pos->x = x;
    vertice->pos->y = y;
    vertice->tipo = JOGADOR;
    ivtc += 1;
    lista = insere_vert_lista(lista, vertice);

    // leitura dos dados dos outros vértices
    while (scanf("%lf %lf %s", &x, &y, tipo) != EOF) {
        vertice = criar_vertice();
        checar_alocacao(vertice);
        vertice->pos->x = x;
        vertice->pos->y = y;
        if (strcmp(tipo, "Lugia") == 0) {
            vertice->tipo = LUGIA;
        }
        else {
            vertice->tipo = POKESTOP;
        }
        ivtc += 1;
        lista = insere_vert_lista(lista, vertice);
    }

    inicializar_dados(jogo, lista, ivtc); // transfere os dados para o grafo
    destruir_lista_vert(lista);
}

int existe_caminho_lugia(p_grafo jogo, int* visitados, double limite, int atual) {
    if (jogo->vertices[atual].tipo == LUGIA) {
        return 1;
    }
    else {
        visitados[atual] = 1;
        // para cada vizinho
        for (int v = 0; v < jogo->n_vtc; v++) {
            if (jogo->dist[atual][v] <= limite && !(visitados[v]) &&
                existe_caminho_lugia(jogo, visitados, limite, v)) {
                return 1;
            }
        }
        return 0;
    }
}

double achar_maior_matriz_simetrica(double** matriz, int n) {
    double maior = matriz[0][0];
    for (int i = 0; i < n; i++) {
        for (int j = n - 1; j >= i; j--) {
            if (matriz[i][j] > maior) {
                maior = matriz[i][j];
            }
        }
    }
    return maior;
}

void resetar_visitados(int* visitados, int n) {
    for (int i = 0; i < n; i++) {
        visitados[i] = 0;
    }
}

int calcular_menor_dist_maxima(p_grafo jogo) {
    int piso = 0;
    int teto = (int) ceil(achar_maior_matriz_simetrica(jogo->dist, jogo->n_vtc));
    int limite = 0;
    int* visitados = calloc(jogo->n_vtc, sizeof(int));
    checar_alocacao(visitados);

    while (1) {
        limite = (piso + teto) / 2;
        if (existe_caminho_lugia(jogo, visitados, (double) limite, 0)) {
            teto = limite;
        }
        else {
            piso = limite;
        }
        if (piso + 1 == teto) {
            break;
        }
        resetar_visitados(visitados, jogo->n_vtc);
    }
    free(visitados);

    return teto;
}

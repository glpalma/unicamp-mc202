#ifndef RAID_LUGIA
#define RAID_LUGIA

struct ponto {
    double x, y;
};

typedef struct ponto* p_pt;

enum tipo { JOGADOR, LUGIA, POKESTOP };

struct vertice {
    p_pt pos;
    enum tipo tipo;
};

typedef struct vertice* p_vtc;

struct grafo {
    p_vtc vertices;
    double** dist;
    int n_vtc;
};

typedef struct grafo* p_grafo;

/**
 * Lê os vértices (até EOF) e os insere no grafo
 * que representa o jogo.
 * */
void ler_posicoes(p_grafo jogo);

/**
 * Aloca e devolve a estrutura que representa
 * o jogo.
 * */
p_grafo criar_jogo();

/**
 * Libera a memória utilizada pelo jogo.
 * */
void destruir_jogo(p_grafo grafo);

/**
 * Calcula a menor distância máxima entre vértices
 * para todas as possibilidades de caminho.
 * */
int calcular_menor_dist_maxima(p_grafo jogo);

#endif // !RAID_LUGIA
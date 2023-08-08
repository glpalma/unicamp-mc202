#include "raid_lugia.h"
#include <stdio.h>

void imprimir_int(int x) {
    printf("%d\n", x);
}

int main() {
    int limite = 0;
    p_grafo jogo = criar_jogo();

    ler_posicoes(jogo);
    
    limite = calcular_menor_dist_maxima(jogo);
    imprimir_int(limite);

    destruir_jogo(jogo);

    return 0;
}

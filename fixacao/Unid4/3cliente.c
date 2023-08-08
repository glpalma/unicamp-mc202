#include <stdio.h>
#include <assert.h>

// c

typedef struct cor {
    int az, am, vm;
    int branco, preto; // valores booleanos
} Cor;

// d
Cor inicializar_cor(int azul, int amarelo, int vermelho) {
    if (azul + amarelo + vermelho != 100) {
        printf("Combinação de cores inválida!\n");
        exit(1);
    }

    Cor cor;
    cor.az = azul;
    cor.am = amarelo;
    cor.vm = vermelho;

    return cor;
}

Cor misturar_cores(Cor cor1, Cor cor2) {
    Cor nova;

    if ((cor1.preto) || (cor2.branco)){
        return cor1;
    } else if ((cor2.preto) || (cor1.branco)) {
        return cor2;
    }

    nova.az = (cor1.az + cor2.az) / 2;
    nova.am = (cor1.am + cor2.am) / 2;
    nova.vm = (cor1.vm + cor2.vm) / 2;

    return nova;    
}

void imprimir_composicao(Cor cor) {
    printf("Vermelho: %d\n", cor.vm);
    printf("Amarelo: %d\n", cor.am);
    printf("Azul: %d\n", cor.az);
}

// Imprime a cor predominante na composição da cor.
void predominante(Cor cor) {
    if ((cor.am > cor.vm) && (cor.am > cor.az)) {
        printf("Amarelo!\n");
    } else if ((cor.az > cor.vm) && (cor.az > cor.vm)) {
        printf("Azul!\n");
    } else if ((cor.vm > cor.am) && (cor.vm > cor.az)) {
        printf("Vermelho!\n");
    }
}

// b

int main() {
    Cor cor1, cor2, vermelho;

    cor1 = inicializar_cor(50, 25, 25);
    vermelho = inicializar_cor(100, 0, 0);
    cor2 = misturar_cores(cor1, vermelho);
    cor_predominante(cor2);
}
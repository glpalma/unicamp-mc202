#include "arvore_tokens.h"

int main() {
    p_no arvore;
    int autoridades = 0;

    while (1) {
        arvore = criar_arvore();
        arvore = ler_tokens(arvore, &autoridades);
        if (autoridades == 0) {
            destruir_arvore(arvore);
            break;
        }
        arvore = visitar_autoridades(arvore, autoridades);
        imprimir_arvore(arvore);
        destruir_arvore(arvore);
    }
    return 0;
}
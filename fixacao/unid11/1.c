#include <stdlib.h>

typedef struct no { // isso representa um nó da lista ligada
    struct no* ant;
    int chave;
    struct no* prox;
} No;

// lista não é circular
typedef No* p_no;


// alternativa a
// insere no início da lista
p_no inserir_elemento(p_no lista, int chave) {
    p_no novo = malloc(sizeof(*novo));
    if (novo == NULL) {
        exit(1);
    }
    novo->chave = chave;
    if (lista == NULL) {
        novo->ant = NULL;
        novo->prox = NULL;
    }
    else {
        novo->prox = lista;
        lista->ant = novo;
        novo->ant = NULL;
    }
    return novo;
}
/*
b
aloca o elemento a ser inserido
a lista é passada por ponteiro, enquanto
o valor a ser inserido é passado por cópia
*/

p_no remover_elemento(p_no lista, int chave) {
    p_no no;

    if (lista != NULL) {
        if (lista->chave = chave) {
            no = lista->prox;
            free(lista);
            return no;
        }
        else {
            lista->prox = remover_elemento(lista->prox, chave);
            if (lista->prox != NULL)
                lista->prox->ant = lista;
            return lista;
        }
    }
}

/*
recebe lista por ponteiro e chave por valor
percorre a lista "por recursão" até achar o elemento
buscado
religa a lista ao devolver o nó que vinha
em seguida do removido
*/

// alternativa c
/*
Para inserir um item no final de uma lista encadeada simples,
gasta-se um tempo da ordem de O(n).
Essa falta de eficiência pode ser contornada (inserção em O(1)) se
também houver um ponteiro apontando para o final da lista. Assim,
não fica necessário percorrer a lista inteira para que seu final
seja alterado. 
*/
#ifndef ARVORE_TOKENS
#define MAX_MENSAGEM 5

typedef struct token {
    int num;
    char* msg;
} Token;

typedef Token* p_tk;

typedef struct no {
    p_tk token;
    struct no* esq;
    struct no* dir;
} No;

typedef No* p_no;

typedef struct trio {
    p_tk pri, seg, ter;
} Trio;

typedef Trio * p_trio;


/**
 * Devolve um ponteiro de nó
 * */
p_no criar_arvore();

/**
 * Libera a memória utilizada por uma árvore
 * */
void destruir_arvore(p_no raiz);

/**
 * Imprime as strings de uma árvore de tokens em inordem
 * */
void imprimir_arvore(p_no raiz);

/**
 * Insere um token em uma árvore
 * */
p_no inserir_token(p_no raiz, p_tk token);

/**
 * Remove um token e seu respectivo nó de uma árvore
 * */
p_no remover_token(p_no raiz, int num_tk);

/**
 * Lê do teclado o número de tokens, o número de autoridades e os tokens
 * */
p_no ler_tokens(p_no raiz, int* n_autoridades);

/**
 * Devolve um trio cuja soma dos números é igual ao número da autoridade
 * */
p_trio buscar_trio(p_no raiz, int autoridade, p_trio trio);

/**
 * lê do teclado n_autoridades autoridades e busca os respectivos trios de token
 * */
p_no visitar_autoridades(p_no raiz, int n_autoridades);

#endif // !ARVORE_TOKENS
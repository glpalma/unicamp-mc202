#ifndef DICIONARIO
#define DICIONARIO
#define MAX_PALAVRA 25

typedef struct no {
    char* palavra;
    struct no* prox;
} No;

typedef No* p_no;

typedef struct hash {
    p_no* v;
    int tam;
    int qtd;
} Hash; // representa o dicionário

typedef Hash* p_hash;

int hash(char* palavra);

/**
 * Aloca e devolve o dicionário
 * e as estruturas anexas.
*/
p_hash criar_dicionario();

/**
 * Libera a memória utilizada pelo
 * dicionário e estruturas anexas.
*/
void destruir_dicionario();

/**
 * Insere uma palavra no dicionário.
*/
void inserir_palavra(p_hash dicio, char* palavra);

/**
 * Verifica a correção de uma palavra de acordo com
 * o dicionário fornecido.
 * Se a palavra estiver correta,
 * devolve 0; se possuir apenas um erro, devolve 1; se
 * possuir dois erros ou mais, devolve um número maior que 1.
*/
int verificar_correcao(p_hash dicio, char* palavra);

/**
 * Imprime o nível de correção de uma palavra.
 * Se o número de erros for 0, imprime "verde";
 * se for 1, imprime "amarelo"; se for um número
 * maior, imprime "vermelho".
*/
void imprimir_correcao(int nerr);

#endif // !DICIONARIO

#ifndef PLANILHA
#define PLANILHA

struct no_cel {
    struct celula* cel;
    struct no_cel* prox;
};

typedef struct no_cel* p_lcel;

struct no_str {
    char* str;
    struct no_str* prox;
};

typedef struct no_str* p_lstr;

enum tipo { VALOR, EXPRESSAO };

struct celula {
    enum tipo tipo;
    p_lstr exp;
    p_lcel ref; // lista de células dependentes
    int valor;
    int contem_erro;
    char coluna;
    int linha;
};

typedef struct celula* p_cel;

struct planilha {
    struct celula** celulas;
    int nlin, ncol;
};

typedef struct planilha* p_pln;

/**
 * Aloca a memória necessária para uma planilha com
 * tamanho n_linhas x n_colunas e devolve o ponteiro.
*/
p_pln alocar_planilha(int n_linhas, int n_colunas);

/**
 * Libera a memória utilizada por uma planilha e por
 * suas células.
*/
void destruir_planilha(p_pln planilha);

/**
 * Lê uma planilha (já alocada na memória) do disco
 * do arquivo com nome nome_arquivo.
*/
void ler_planilha_disco(p_pln planilha, char* nome_arquivo);

/**
 * Executa uma operação sobre a planilha de acordo
 * com o char operacao. Se for "G", lê uma célula
 * imprime o valor presente nela; se for "S", lê uma
 * célula e o novo valor a ser inserido nela e depois
 * imprime a alteração feita.
*/
void operacao_planilha(p_pln planilha, char operacao);

#endif // !PLANILHA
#ifndef ARVORE_LISTAS_LEGAIS
#define ARVORE_LISTAS_LEGAIS

enum Cor { PRETO, VERMELHO };

typedef long int numLegal;

typedef struct no {
    numLegal num;
    short int ocorrencias; // número de vezes que o número aparece na lista
    struct no* esq;
    struct no* dir;
    enum Cor cor;
} No;

typedef No* p_no;

/**
 * Devolve NULL
 * */
p_no criar_arvore();

/**
 * Libera a memória utilizada pela árvore que representa a lista legal
 * */
void destruir_arvore();

/**
 * Lê as quantidades de números presentes na lista e de operações
 * a serem executadas.
 * */
void ler_dados(int* qtd_num, int* qtd_op);

/**
 * Lê qtd_num números, adicionando cada um à árvore. 
 * */
p_no ler_numeros(p_no raiz, int qtd_num);

/**
 * Se o número não estiver na árvore, o insere;
 * se estiver, conta uma ocorrência.
 * */
p_no contar_ocorrencia(p_no raiz, numLegal num);

/**
 * Devolve o número de ocorrências de um número.
 * */
int numero_ocorrencias(p_no raiz, numLegal num);

/**
 * Devolve a quantidade de números que não atendem
 * aos requisitos de listas legais.
 * */
int contar_ilegais(p_no raiz);

/**
 * Lê o número operação e o número correspondente.
 * */
void ler_operacao(int* operacao, numLegal* num);

/**
 * Escolhe a operação a ser executada e devolve o resultado.
 * */
p_no executar_operacao(p_no raiz, int operacao, numLegal num, int* resultado);

/**
 * Imprime o resultado fornecido pela operação.
 * */
void imprimir_resultado(int resultado);

#endif // !ARVORE_LISTAS_LEGAIS
// Este arquivo contém os stubs das funções permitidas sobre as listas
#ifndef INTEIROS_GRANDES
#define INTEIROS_GRANDES

typedef struct algarismo { // isso representa um nó da lista ligada
    struct algarismo * ant;
    int alg;
    struct algarismo * prox;
} Algarismo;

typedef Algarismo * p_alg; // Ponteiro para um algarismo (nó da lista ligada).

typedef struct int_grande { // "cabeça" da lista ligada
    p_alg ini;
    p_alg fim;
    int tam;
} intG;

typedef intG * p_num;

/**
 * Cria, aloca e devolve o ponteiro de um novo número.
 * */
p_num criar_numero();

/**
 * Lê um grande inteiro e devolve o ponteiro correspondente.
 * */
p_num ler_numero(p_num numero);

/**
 * Adiciona um algarismo no início do número.
 * */
p_num adiciona_inicio(p_num numero, int dado);

/**
 * Adiciona um algarismo no fim do número.
 * */
p_num adiciona_fim(p_num numero, int dado);

/**
 * Escolhe a operação a ser executada sobre os números e devolve o resultado.
 * */
p_num executar_operacao(p_num num1, p_num num2, char operacao, p_num resultado);

/**
 * Devolve 1 se os números forem iguais; 0, se não forem.
 * */
int numeros_iguais(p_num num1,p_num num2);

/**
 * Devolve 1 se o número for igual a 0; 0, se não for.
 * */
int eh_nulo(p_num numero);

/**
 * Soma dois números e resolve o resultado.
 * */
p_num somar_numeros(p_num num1, p_num num2, p_num resultado);

/**
 * Subtrai dois números e resolve o resultado.
 * */
p_num subtrair_numeros(p_num num1, p_num num2, p_num resultado);

/**
 * Multiplica dois números e resolve o resultado.
 * */
p_num multiplicar_numeros(p_num num1, p_num num2, p_num resultado);

/**
 * Imprime um grande inteiro.
 * */
void imprimir_numero(p_num numero);

/**
 * Libera a memória usada por um número, enquanto mantém a cabeça.
 * */
void reciclar_numero(p_num numero);

/**
 * Libera a memória usada por um número.
 * */
void destruir_numero(p_num numero);

#endif

// arquivo das structs e dos stubs 
#ifndef ADM_HOSPITALAR
#define ADM_HOSPITALAR
#define NUM_SETORES 9
#define MAX_NOME 50
#define HORA_ABERTURA 8
#define MINUTOS_ABERTURA 0
#include "lista_ligada.h"

enum Prioridade { NORMAL, PREFERENCIAL };

typedef struct paciente { // Informações do paciente
    char* nome;
    p_lista consultas;
    enum Prioridade carteirinha;
    int hora_saida; // número de consultas por quais o paciente passou
    int senha_entrada; // número de entrada
} Paciente;

typedef Paciente* p_pac;

typedef struct posicao { // Uma posição na fila
    struct posicao* prox;
    p_pac paciente;
} Posicao;

typedef Posicao* p_pos;

typedef struct fila { // Cabeça com os dados da fila
    p_pos ini, fim;
    int qtd;
} Fila;

typedef Fila* p_fila;

typedef struct especialidade { // Representa um setor
    int qtd_prof;
    int prof_disp;
    p_fila atendimento;
    p_fila aux;
} Especialidade;

typedef Especialidade* p_esp;

/**
 * Lê as informações dos pacientes.
 * Insere os pacientes na fila normal ou prioritária, dependendo de sua carteirinha.
 * */
void ler_info_pacientes(p_fila entrada);

/**
 * Cria e aloca um paciente.
 * */
p_pac criar_paciente();

/**
 * Cria e aloca uma fila.
 * */
p_fila criar_fila();

/**
 * Cria e aloca os setores de atendimento, incluindo a fila e o número de profissionais de cada um.
 * Retorna um vetor com os setores.
 * */
p_esp criar_setores_atendimento();

/**
 * Libera a memórua utilizada pelos setores de atendimento.
 * */
void destruir_setores(p_esp setores);

/**
 * Devolve 1 se houver pacientes nas filas de espera dos setores médicos; 0, caso contrário.
 * */
int ha_pacientes(p_esp setores);

/**
 * Devolve 1 se a fila for vazia; 0, se não.
 * */
int fila_eh_vazia(p_fila fila);

/**
 * Insere o paciente no início da fila.
 * */
p_fila enfileirar_pref(p_pac paciente, p_fila fila);

/**
 * Insere o paciente no final da fila.
 * */
p_fila enfileirar(p_pac paciente, p_fila fila);

/**
 * Remove o paciente do início da fila e o devolve.
 * */
p_pac desenfileirar(p_fila fila);

/**
 * Direciona os pacientes para o primeiro atendimento deles.
 * Os que estão na fila de prioridade entram no começo da fila de atendimento.
 * */
void direcionar_pacientes(p_fila entrada, p_esp setores);

/**
 * Atende os pacientes presentes nas filas de espera de cada setor.
 * Se tiver passado por todos seus atendimentos, vai pra fila de saída.
 * */
void atender_pacientes(p_esp setores, p_fila saida);

/**
 * Imprime o horário de saída dos pacientes, junto aos seus respectivos nomes.
 * */
void imprimir_saida(p_fila saida);

/**
 * Libera a memória utilizada por uma fila.
 * */
void destruir_fila(p_fila fila);

#endif
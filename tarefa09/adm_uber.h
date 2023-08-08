#ifndef ADM_UBER
#define ADM_UBER
#define MAX_ESPERA 500
#define MAX_NOME 15
#define TAXA_CANCELAMENTO 7
#define ALUGUEL 57
#define CONSUMO 10
#define PRECO_GASOLINA 4.104
#define RECEBIDO_UBER 0.75 // taxa recebida pelo motorista
#define PAGAMENTO_UBER 1.40 // R$ / km

typedef struct ponto {
    int x, y;
} Ponto;

typedef Ponto* p_pt;

typedef struct cliente {
    char* prim_nome;
    double nota;
    p_pt partida; // posição de partida
    p_pt destino; // posição de destino
} Cliente;

typedef Cliente* p_clt;

typedef struct fila { // max heap de clientes
    p_clt fila;
    int tam, esperando;
} FP;

typedef FP* p_fp;

typedef struct motorista {
    int dist_percorrida;
    double rend_bruto;
    double despesas;
    unsigned short int esta_atendendo;
    Cliente em_atendimento;
    p_pt posicao; // posição atual do motorista
    p_fp espera; // fila de espera dos clientes
    // baseada nas notas de cada um 
} Motorista;

typedef Motorista* p_mt;

/**
 * Aloca o motorista e as estruturas auxiliares,
 * inicializa suas variáveis e o devolve.
 * */
p_mt criar_motorista(int tam_espera);

/**
 * Libera a memória utilizada pelo motorista.
 * */
void destruir_motorista(p_mt motorista);

/**
 * Lê e devolve o caractere representante
 * da operação.
 * */
char ler_operacao();

/**
 * Executa a operação escolhida baseado na variável
 * operacao e devolve o motorista.
 * */
p_mt executar_operacao(char operacao, p_mt motorista);

#endif // ADM_UBER

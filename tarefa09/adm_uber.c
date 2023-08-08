#include "adm_uber.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define PAI(i) ((i - 1) / 2) // pai de i
#define F_ESQ(i) (2 * i + 1) // filho esquerdo de i
#define F_DIR(i) (2 * i + 2) // filho direito de i

void checar_alocacao(void* ponteiro) {
    if (ponteiro == NULL) {
        printf("Falta de memória! Encerrando o programa...\n");
        exit(1);
    }
}

p_mt criar_motorista(int tam_espera) { // recebe o número máximo de clientes
    p_mt motorista;
    // aloca espaço para o motorista
    motorista = malloc(sizeof(Motorista));
    checar_alocacao(motorista);

    //inicializa os dados
    motorista->dist_percorrida = 0;
    motorista->rend_bruto = 0;
    motorista->despesas = 0;
    motorista->esta_atendendo = 0;

    // aloca espaço para estrutura a fila de espera
    motorista->espera = malloc(sizeof(FP));
    checar_alocacao(motorista->espera);
    motorista->espera->tam = tam_espera;
    motorista->espera->esperando = 0;

    // aloca espaço para a fila em si
    motorista->espera->fila = calloc(tam_espera, sizeof(Cliente));
    checar_alocacao(motorista->espera->fila);

    // aloca espaço para o ponto de partida
    motorista->posicao = malloc(sizeof(Ponto));
    checar_alocacao(motorista->posicao);
    motorista->posicao->x = 0;
    motorista->posicao->y = 0;

    return motorista;
}

void destruir_info_cliente(p_clt cliente) {
    if (cliente != NULL) {
        free(cliente->prim_nome);
        free(cliente->partida);
        free(cliente->destino);
    }
}

void destruir_motorista(p_mt motorista) {
    if (motorista != NULL) {
        free(motorista->espera->fila);
        free(motorista->espera);
        free(motorista->posicao);
        free(motorista);
    }
}

p_clt criar_cliente() {
    // nome é alocado separadamente
    p_clt cliente = malloc(sizeof(Cliente));
    checar_alocacao(cliente);
    // alocação e inicialização do ponto de partida
    cliente->partida = malloc(sizeof(Ponto));
    checar_alocacao(cliente->partida);
    cliente->partida->x = 0;
    cliente->partida->y = 0;
    // alocação e inicialização do ponto de destino
    cliente->destino = malloc(sizeof(Ponto));
    checar_alocacao(cliente->destino);
    cliente->destino->x = 0;
    cliente->destino->y = 0;

    return cliente;
}

char ler_operacao() {
    char operacao;
    scanf(" %c", &operacao);

    return operacao;
}

p_clt ler_info_cliente(p_clt cliente) {
    // nome
    cliente->prim_nome = malloc((MAX_NOME + 1) * sizeof(char));
    checar_alocacao(cliente->prim_nome);
    scanf(" %s", cliente->prim_nome);
    // nota
    scanf("%lf", &cliente->nota);
    // posição de partida
    scanf(" %d", &(cliente->partida->x));
    scanf(" %d", &(cliente->partida->y));
    // posição de destino
    scanf(" %d", &(cliente->destino->x));
    scanf(" %d", &(cliente->destino->y));

    return cliente;
}

void imprimir_resultados(p_mt motorista) {
    printf("\n");
    printf("Jornada finalizada. Aqui esta o seu rendimento de hoje\n");
    printf("Km total: %d\n", motorista->dist_percorrida);
    printf("Rendimento bruto: %.2lf\n", motorista->rend_bruto);
    printf("Despesas: %.2lf\n", motorista->despesas);
    printf("Rendimento liquido: %.2lf\n", ((RECEBIDO_UBER * motorista->rend_bruto) - motorista->despesas));
}

int distancia_manhattan(p_pt ponto1, p_pt ponto2) {
    int distancia = 0;
    distancia += abs(ponto1->x - ponto2->x);
    distancia += abs(ponto1->y - ponto2->y);

    return distancia;
}

double gasto_combustivel(int distancia, double consumo, double preco) {
    return (preco / consumo) * distancia;
}

p_mt computar_corrida(p_mt motorista, p_clt cliente) {
    int deslocamento = 0, corrida = 0;
    double combustivel = 0, ganho = 0;

    // cálculo das despesas de deslocamento
    deslocamento = distancia_manhattan(motorista->posicao, cliente->partida);
    motorista->dist_percorrida += deslocamento;
    combustivel = gasto_combustivel(deslocamento, CONSUMO, PRECO_GASOLINA);
    motorista->despesas += combustivel;

    // cálculo da corrida
    corrida = distancia_manhattan(cliente->partida, cliente->destino);
    combustivel = gasto_combustivel(corrida, CONSUMO, PRECO_GASOLINA);
    motorista->dist_percorrida += corrida;
    motorista->despesas += combustivel;
    ganho = corrida * PAGAMENTO_UBER;
    motorista->rend_bruto += ganho;
    motorista->posicao->x = cliente->destino->x; // atualiza a posição atual do motorista
    motorista->posicao->y = cliente->destino->y;

    return motorista;
}

void troca_clientes(p_clt cliente1, p_clt cliente2) {
    Cliente aux;
    aux = *cliente1;
    *cliente1 = *cliente2;
    *cliente2 = aux;
}

void desce_no_heap(p_fp fprio, int k) {
    int maior_nota; // índice do cliente com maior nota
    if (F_ESQ(k) < fprio->esperando) {
        maior_nota = F_ESQ(k);
        if (F_DIR(k) < fprio->esperando &&
            fprio->fila[F_ESQ(k)].nota < fprio->fila[F_DIR(k)].nota) {
            maior_nota = F_DIR(k);
        }
        if (fprio->fila[k].nota < fprio->fila[maior_nota].nota) {
            troca_clientes(&fprio->fila[k], &fprio->fila[maior_nota]);
            desce_no_heap(fprio, maior_nota);
        }
    }
}

Cliente atender_cliente(p_mt motorista) {
    Cliente cliente = motorista->espera->fila[0];
    int n = motorista->espera->esperando;
    troca_clientes(&motorista->espera->fila[0], &motorista->espera->fila[n - 1]);
    motorista->espera->esperando--;
    desce_no_heap(motorista->espera, 0);

    return cliente;
}

void sobe_no_heap(p_fp fprio, int k) {
    if (k > 0 && fprio->fila[PAI(k)].nota < fprio->fila[k].nota) {
        troca_clientes(&fprio->fila[k], &fprio->fila[PAI(k)]);
        sobe_no_heap(fprio, PAI(k));
    }
}

int buscar_cliente(p_fp fprio, char* nome) {
    int i;
    for (i = 0; i < fprio->esperando; i++) {
        if (strcmp(nome, fprio->fila[i].prim_nome) == 0) { // se achar o nome
            return i;
        }
    }
    return -1; // se não achar
}

Cliente retirar_cliente_espera(p_mt motorista, char* nome) {
    int idx = buscar_cliente(motorista->espera, nome);
    Cliente cliente = motorista->espera->fila[idx]; // salva em uma variável auxiliar
    troca_clientes(&motorista->espera->fila[idx], &motorista->espera->fila[motorista->espera->esperando - 1]);
    motorista->espera->esperando--;

    if (motorista->espera->fila[idx].nota > motorista->espera->fila[PAI(idx)].nota) {
        sobe_no_heap(motorista->espera, idx);
    }
    else if (motorista->espera->fila[idx].nota < motorista->espera->fila[F_DIR(idx)].nota ||
        motorista->espera->fila[idx].nota < motorista->espera->fila[F_ESQ(idx)].nota)
        desce_no_heap(motorista->espera, idx);

    return cliente;
}

p_mt insere_cliente_espera(p_mt motorista, p_clt cliente) {
    p_fp fprio = motorista->espera;
    fprio->fila[fprio->esperando] = *cliente;
    fprio->esperando++;
    sobe_no_heap(fprio, fprio->esperando - 1);

    return motorista;
}

p_mt executar_operacao(char operacao, p_mt motorista) {
    p_clt aux;
    Cliente cli;
    char nome[MAX_NOME];
    switch (operacao) {
    case ('A'): // adiciona um cliente à espera
        aux = criar_cliente();
        aux = ler_info_cliente(aux);

        if (motorista->esta_atendendo) {
            motorista = insere_cliente_espera(motorista, aux);
        }
        else { // atende o cliente diretamente
            motorista->em_atendimento = *aux;
            motorista->esta_atendendo = 1;
        }
        printf("Cliente %s foi adicionado(a)\n", aux->prim_nome);
        free(aux);

        break;

    case ('F'): // finaliza a corrida do cliente atual e atende o próximo cliente
        motorista = computar_corrida(motorista, &(motorista->em_atendimento));
        printf("A corrida de %s foi finalizada\n", motorista->em_atendimento.prim_nome);
        destruir_info_cliente(&motorista->em_atendimento); // libera dados do cliente

        if (motorista->espera->esperando > 0) {
            cli = atender_cliente(motorista);
            motorista->em_atendimento = cli;
            motorista->esta_atendendo = 1;
        }
        else { // se não houver ninguém na fila de espera
            motorista->esta_atendendo = 0;
        }
        break;

    case ('C'): // cancela a corrida de um cliente  
        scanf("%s", nome);
        cli = retirar_cliente_espera(motorista, nome);
        motorista->rend_bruto += TAXA_CANCELAMENTO;
        printf("%s cancelou a corrida\n", nome);
        destruir_info_cliente(&cli); // libera os dados do cliente
        break;

    case ('T'): // exibe os resultados da jornada de trabalho do motorista
        motorista->despesas += ALUGUEL;
        imprimir_resultados(motorista);
        break;

    default:
        printf("Operação ainda não implementada.\n");
        break;
    }

    return motorista;
}

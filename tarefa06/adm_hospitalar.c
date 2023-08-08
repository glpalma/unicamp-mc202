#include "adm_hospitalar.h"
#include "lista_ligada.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

p_fila criar_fila() {
    p_fila nova = malloc(sizeof(Fila));
    if (nova == NULL) {
        erro_memoria();
    }
    nova->ini = NULL;
    nova->fim = NULL;
    nova->qtd = 0;

    return nova;
}

p_pac criar_paciente() {
    p_pac paciente;
    paciente = malloc(sizeof(Paciente));
    if (paciente == NULL) {
        erro_memoria();
    }
    paciente->consultas = criar_lista();
    paciente->hora_saida = 0;
    paciente->senha_entrada = 0;

    return paciente;
}

p_esp criar_setores_atendimento() {
    short int disp_setores[NUM_SETORES + 1] = { -1, 10, 2, 5, 3, 4, 7, 2, 1, 4 }; // idx 0 é dummy
    p_esp setores;

    setores = malloc(sizeof(Especialidade) * (NUM_SETORES + 1));
    if (setores == NULL) {
        erro_memoria();
    }
    for (int i = 1; i <= NUM_SETORES; i++) {
        setores[i].qtd_prof = disp_setores[i];
        (&setores[i])->atendimento = criar_fila();
        (&setores[i])->aux = criar_fila();
    }
    return setores;
}

p_pos alocar_posicao() {
    p_pos nova;
    nova = malloc(sizeof(Posicao));
    if (nova == NULL) {
        erro_memoria();
    }
    return nova;
}

int eh_preferencial(p_pac paciente) {
    if (paciente->carteirinha == PREFERENCIAL) {
        return 1;
    }
    else {
        return 0;
    }
}

int fila_eh_vazia(p_fila fila) {
    if (fila->ini == NULL && fila->fim == NULL) {
        return 1;
    }
    else {
        return 0;
    }
}

int ha_pacientes(p_esp setores) {
    int pacientes_esp = 0;
    if (setores != NULL) {
        for (int i = 1; i <= NUM_SETORES; i++) {
            if (!fila_eh_vazia(setores[i].atendimento)) {
                pacientes_esp = 1;
                break;
            }
        }
    }
    return pacientes_esp;
}

char* criar_nome(int tam) {
    char* nome;
    nome = malloc(sizeof(char) * (tam));
    if (nome == NULL) {
        erro_memoria();
    }
    return nome;
}

p_fila enfileirar_pref(p_pac paciente, p_fila fila) {
    p_pos posicao = alocar_posicao();
    posicao->paciente = paciente;

    if (fila_eh_vazia(fila)) {
        fila->ini = posicao;
        fila->fim = posicao;
        posicao->prox = NULL;
    }
    else {
        posicao->prox = fila->ini;
        fila->ini = posicao;
    }
    fila->qtd += 1;
    return fila;
}

p_fila enfileirar(p_pac paciente, p_fila fila) {
    p_pos posicao;
    posicao = alocar_posicao();
    posicao->paciente = paciente;

    if (fila_eh_vazia(fila)) {
        fila->ini = posicao;
        fila->fim = posicao;
        posicao->prox = NULL;
    }
    else {
        fila->fim->prox = posicao;
        posicao->prox = NULL;
        fila->fim = posicao;
    }
    fila->qtd += 1;
    return fila;
}

p_pac desenfileirar(p_fila fila) {
    p_pos posicao;
    p_pac paciente = NULL;

    if (!fila_eh_vazia(fila)) {
        posicao = fila->ini;
        paciente = posicao->paciente;
        fila->ini = posicao->prox;
        free(posicao); // apaga a caixinha que guardava o paciente na fila
        if (fila->qtd == 1) {
            fila->ini = NULL;
            fila->fim = NULL;
        }
        fila->qtd -= 1;
    }
    return paciente;
}

void destruir_paciente(p_pac paciente) {
    if (paciente != NULL) {
        free(paciente->nome);
        destruir_lista(paciente->consultas);
        free(paciente);
    }
}

void destruir_fila(p_fila fila) {
    if (fila != NULL) {
        p_pos atual = fila->ini;
        p_pos prox;
        while (atual != NULL) {
            prox = atual->prox;
            destruir_paciente(atual->paciente);
            free(atual);
            atual = prox;
        }
        free(fila);
    }
}

void destruir_setores(p_esp setores) {
    if (setores != NULL) {
        for (int i = 1; i <= NUM_SETORES; i++) {
            destruir_fila(setores[i].atendimento);
            destruir_fila(setores[i].aux);
        }
        free(setores);
    }
}

void ler_info_pacientes(p_fila entrada) {
    char nome_aux[MAX_NOME];
    char prioridade[15];
    p_pac paciente;
    int setor, len;
    int saida1 = 0, saida2 = 0;
    int senha = 1;

    while (1) { // enquanto não for EOF, lê um paciente
        saida1 = scanf("\"%[^\"]\"%s", nome_aux, prioridade);
        if (saida1 != 2) {
            break;
        }
        len = strlen(nome_aux);
        paciente = criar_paciente(); // aloca o paciente
        paciente->nome = criar_nome(len + 1); // aloca o nome 
        memcpy(paciente->nome, nome_aux, len + 1); // transfere o nome pro novo endereço
        paciente->senha_entrada = senha;
        if (strcmp(prioridade, "preferencial") == 0) {
            paciente->carteirinha = PREFERENCIAL;
        }
        else {
            paciente->carteirinha = NORMAL;
        }
        while (1) { // lê os números das consultas até dar EOF
            saida2 = scanf("%d", &setor);
            if (saida2 != 1) {
                break;
            }
            paciente->consultas = adiciona_fim(paciente->consultas, setor);
        }
        enfileirar(paciente, entrada);
        senha++; // senha do próximo paciente
    }
}

int atualizar_consulta(p_lista consultas) {
    int setor = 0;
    if (consultas != NULL) {
        if (consultas->ini != NULL) {
            setor = consultas->ini->dado;
            consultas = remove_inicio(consultas);
        }
    }

    return setor;
}

void direcionar_pacientes(p_fila entrada, p_esp setores) {
    p_pac paciente;
    int setor = 0;
    if (entrada != NULL) {
        while (!fila_eh_vazia(entrada)) {
            paciente = desenfileirar(entrada);
            setor = atualizar_consulta(paciente->consultas);
            if (eh_preferencial(paciente)) {
                enfileirar_pref(paciente, setores[setor].atendimento);
            }
            else {
                enfileirar(paciente, setores[setor].atendimento);
            }
        }
    }
}

void adicionar_espera(p_fila fila) {
    if (fila != NULL && (!fila_eh_vazia(fila))) {
        p_pos posicao = fila->ini;
        while (posicao != NULL) {
            posicao->paciente->hora_saida += 1;
            posicao = posicao->prox;
        }
    }
}

p_pac retirar_menor_senha(p_fila fila) {
    p_pos atual = fila->ini;
    p_pos menor = atual;
    p_pac paciente;
    while (atual != NULL) {
        if (atual->paciente->senha_entrada < menor->paciente->senha_entrada) {
            menor = atual;
        }
        atual = atual->prox;
    }
    paciente = menor->paciente;
    if (fila->qtd == 1) { // se a lista tiver apenas um paciente
        fila->ini = NULL;
        fila->fim = NULL;
    }
    else if (menor == fila->ini && menor != fila->fim) { //se o paciente estiver no início da fila
        fila->ini = menor->prox;
    }
    else { // se tiver no meio da fila ou no fim
        atual = fila->ini;
        while (atual->prox != menor) {
            atual = atual->prox;
        }
        atual->prox = menor->prox;
        if (menor == fila->fim) {
            fila->fim = atual;
        }
    }
    fila->qtd -= 1;
    free(menor);

    return paciente;
}

void transferir_pacientes(p_esp setores) {
    p_pac paciente;
    for (int i = 1; i <= NUM_SETORES; i++) {
        while (!fila_eh_vazia(setores[i].aux)) {
            paciente = retirar_menor_senha(setores[i].aux); // encontra o paciente com menor senha e o devolve
            if (eh_preferencial(paciente)) {
                setores[i].atendimento = enfileirar_pref(paciente, setores[i].atendimento);
            }
            else {
                setores[i].atendimento = enfileirar(paciente, setores[i].atendimento);
            }
        }
    }
}

void atender_pacientes(p_esp setores, p_fila saida) {
    if (setores != NULL) {
        p_pac paciente;
        int setor;
        for (int i = 1; i <= NUM_SETORES; i++) { // para cada setor
            setores[i].prof_disp = setores[i].qtd_prof;
            while (!fila_eh_vazia(setores[i].atendimento) && setores[i].prof_disp > 0) { // para cada paciente
                paciente = desenfileirar(setores[i].atendimento);
                setores[i].prof_disp -= 1; // paciente é atendido
                paciente->hora_saida += 1;
                setor = atualizar_consulta(paciente->consultas); // devolve 0 se a prox consulta for NULL
                if (setor == 0) { // se as consultas do paciente tiverem acabado
                    saida = enfileirar(paciente, saida);
                }
                else {
                    setores[setor].aux = enfileirar(paciente, setores[setor].aux);
                }
            }
            if (!fila_eh_vazia(setores[i].atendimento)) { // se restaram pacientes na fila
                adicionar_espera(setores[i].atendimento);
            }
        }
        transferir_pacientes(setores); // transfere os pacientes das filas aux para as definitivas
    }
}

void imprimir_horario(int hora, int minutos) {
    if (hora < 10) {
        if (minutos == 0) {
            printf("0%d:00", hora);
        }
        else {
            printf("0%d:%d", hora, minutos);
        }
    }
    else {
        if (minutos == 0) {
            printf("%d:00", hora);
        }
        else {
            printf("%d:%d", hora, minutos);
        }
    }
}

void imprimir_saida(p_fila saida) {
    if (saida != NULL) {
        p_pos atual = saida->ini;
        int hora = 0, minutos = 0;
        while (atual != NULL) {
            hora = (((10 * atual->paciente->hora_saida) / 60 + HORA_ABERTURA) % 24);
            minutos = ((10 * atual->paciente->hora_saida + MINUTOS_ABERTURA) % 60);
            imprimir_horario(hora, minutos);
            printf(" %s\n", atual->paciente->nome);
            atual = atual->prox;
        }
    }
}

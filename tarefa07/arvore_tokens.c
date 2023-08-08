#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore_tokens.h"

void checar_alocacao(void* ponteiro) {
    if (ponteiro == NULL) {
        printf("Falta de memória! Encerrando o programa...\n");
        exit(1);
    }
}

p_no criar_arvore() {
    return NULL;
}

void imprimir_numR(p_no raiz) {
    if (raiz != NULL) {
        imprimir_numR(raiz->esq);
        printf("%d ", raiz->token->num);
        imprimir_numR(raiz->dir);
    }
}

void imprimir_num(p_no raiz) {
    imprimir_numR(raiz);
    printf("\n");
}
void imprimir_arvoreR(p_no raiz) {
    if (raiz != NULL) {
        imprimir_arvoreR(raiz->esq);
        printf("%s", raiz->token->msg);
        imprimir_arvoreR(raiz->dir);
    }
}

void imprimir_arvore(p_no raiz) {
    imprimir_arvoreR(raiz);
    printf("\n");
}

void destruir_token(p_tk token) {
    if (token != NULL) {
        free(token->msg);
        free(token);
    }
}

void destruir_arvore(p_no raiz) {
    if (raiz != NULL) {
        destruir_arvore(raiz->esq);
        destruir_arvore(raiz->dir);
        destruir_token(raiz->token);
        free(raiz);
    }
}

p_no inserir_token(p_no raiz, p_tk token) {
    p_no novo;
    if (raiz == NULL) {
        novo = malloc(sizeof(No));
        checar_alocacao(novo);
        novo->esq = NULL;
        novo->dir = NULL;
        novo->token = token;
        return novo;
    }
    if (token->num < raiz->token->num) {
        raiz->esq = inserir_token(raiz->esq, token);
    }
    else {
        raiz->dir = inserir_token(raiz->dir, token);
    }
    return raiz;
}

void substituir_por_sucessor(p_no raiz) {
    p_no min = raiz->dir;
    p_no pai = raiz;
    while (min->esq != NULL) { // chega ao token com menor número
        pai = min;
        min = min->esq;
    }
    if (pai->esq == min) {
        pai->esq = min->dir;
    }
    else {
        pai->dir = min->dir;
    }
    destruir_token(raiz->token);
    raiz->token = min->token;
    free(min);
}

p_no remover_token(p_no raiz, int num_tk) {
    p_no no;
    if (raiz == NULL) {
        return raiz;
    }
    if (num_tk < raiz->token->num) {
        raiz->esq = remover_token(raiz->esq, num_tk);
    }
    else if (num_tk > raiz->token->num) {
        raiz->dir = remover_token(raiz->dir, num_tk);
    }
    else if (raiz->esq == NULL) {
        no = raiz->dir;
        destruir_token(raiz->token);
        free(raiz);
        return no;
    }
    else if (raiz->dir == NULL) {
        no = raiz->esq;
        destruir_token(raiz->token);
        free(raiz);
        return no;
    }
    else {
        substituir_por_sucessor(raiz);
    }
    return raiz;
}

p_tk criar_token() {
    p_tk novo = malloc(sizeof(Token));
    checar_alocacao(novo);

    return novo;
}

p_no ler_tokens(p_no raiz, int* n_autoridades) {
    int entrada = 0;
    int n_cartoes = 0;
    int i = 0;
    char msg_aux[MAX_MENSAGEM + 1];
    p_tk token;

    entrada = scanf(" %d %d", &n_cartoes, n_autoridades);
    if (entrada != 2) { // verifica se a entrada chegou ao fim
        *n_autoridades = 0;
        return NULL; // indica à main que a entrada acabou
    }
    int num_cartao = 0;
    for (i = 0; i < n_cartoes; i++) {
        scanf("%d \"%[^\"]\"", &num_cartao, msg_aux);
        token = criar_token();
        token->num = num_cartao;
        token->msg = malloc(MAX_MENSAGEM);
        checar_alocacao(token);
        memcpy(token->msg, msg_aux, MAX_MENSAGEM); // transfere a mensagem para o token
        raiz = inserir_token(raiz, token);
    }

    return raiz;
}

p_no buscar_no(p_no raiz, int valor) {
    if (raiz == NULL || raiz->token->num == valor) {
        return raiz;
    }
    else if (raiz->token->num < valor) {
        return buscar_no(raiz->dir, valor);
    }
    else {
        return buscar_no(raiz->esq, valor);
    }
}

p_trio achar_par(p_no raiz, p_no atual, p_no pri, p_trio trio, int valor_par, int* achou) {
    if (raiz != NULL && atual != NULL && !(*achou)) {
        p_no procurado;
        trio = achar_par(raiz, atual->esq, pri, trio, valor_par, achou);
        if (atual->token->num < valor_par && !(*achou)) {
            procurado = buscar_no(raiz, valor_par - atual->token->num); // se não achar devolve NULL
            if (procurado != NULL && atual != pri && atual != procurado && procurado != pri) {
                trio->pri = pri->token;
                trio->seg = atual->token;
                trio->ter = procurado->token;
                *achou = 1;
                return trio;
            }
            if (!(*achou))
                trio = achar_par(raiz, atual->dir, pri, trio, valor_par, achou);
        }
    }
    return trio;
}

p_trio buscar_trioR(p_no raiz, p_no atual, p_trio trio, int autoridade, int* achou) {
    if (raiz != NULL && atual != NULL && autoridade != 0 && !(*achou)) {
        trio = buscar_trioR(raiz, atual->esq, trio, autoridade, achou);
        if (atual->token->num < autoridade && !(*achou)) { // evita que nós maiores que a autoridade sejam acessados
            trio = achar_par(raiz, raiz, atual, trio, autoridade - atual->token->num, achou);
            if (!(*achou))
                trio = buscar_trioR(raiz, atual->dir, trio, autoridade, achou);
            else
                return trio;
        }
    }
    return trio;
}

p_trio buscar_trio(p_no raiz, int autoridade, p_trio trio) {
    int achou = 0;
    return buscar_trioR(raiz, raiz, trio, autoridade, &achou);
}

p_trio criar_trio() {
    p_trio trio = malloc(sizeof(Trio));
    checar_alocacao(trio);
    trio->pri = trio->seg = trio->ter = NULL;
    return trio;
}

void destruir_trio(p_trio trio) {
    if (trio != NULL) {
        free(trio);
    }
}

void achar_ordem(p_trio trio, p_tk* menor, p_tk* meio, p_tk* maior) {
    if ((trio->pri->num > trio->seg->num) && (trio->pri->num > trio->ter->num)) {
        *maior = trio->pri;
        if (trio->seg->num > trio->ter->num) {
            *meio = trio->seg;
            *menor = trio->ter;
        }
        else {
            *meio = trio->ter;
            *menor = trio->seg;
        }
    }
    else if ((trio->seg->num > trio->pri->num) && (trio->seg->num > trio->ter->num)) {
        *maior = trio->seg;
        if (trio->pri->num > trio->ter->num) {
            *meio = trio->pri;
            *menor = trio->ter;
        }
        else {
            *meio = trio->ter;
            *menor = trio->pri;
        }
    }
    else if ((trio->ter->num > trio->pri->num) && (trio->ter->num > trio->seg->num)) {
        *maior = trio->ter;
        if (trio->seg->num > trio->pri->num) {
            *meio = trio->seg;
            *menor = trio->pri;
        }
        else {
            *meio = trio->pri;
            *menor = trio->seg;
        }
    }
}

char* concatenar_msg_trio(p_trio trio) {
    p_tk menor, meio, maior;
    int n = strlen(trio->pri->msg) + strlen(trio->seg->msg) + strlen(trio->ter->msg) + 1;
    char* msg_nova = malloc(n * sizeof(char));
    checar_alocacao(msg_nova);
    achar_ordem(trio, &menor, &meio, &maior);

    msg_nova = strcpy(msg_nova, menor->msg);
    msg_nova = strcat(msg_nova, meio->msg);
    msg_nova = strcat(msg_nova, maior->msg);

    return msg_nova;
}

p_no manipular_trio(p_no raiz, p_trio trio) {
    p_tk novo = malloc(sizeof(Token));
    checar_alocacao(novo);
    novo->num = trio->pri->num + trio->seg->num + trio->ter->num;
    novo->msg = concatenar_msg_trio(trio);
    raiz = remover_token(raiz, trio->pri->num);
    raiz = remover_token(raiz, trio->seg->num);
    raiz = remover_token(raiz, trio->ter->num);
    raiz = inserir_token(raiz, novo);
    return raiz;
}

int trio_valido(p_trio trio) {
    return trio->pri != NULL && trio->seg != NULL && trio->ter != NULL;
}

p_no visitar_autoridades(p_no raiz, int n_autoridades) {
    int i, autoridade = 0;
    p_trio trio;

    for (i = 0; i < n_autoridades; i++) { // para cada autoridade
        scanf(" %d", &autoridade);
        trio = criar_trio();
        trio = buscar_trio(raiz, autoridade, trio);
        if (trio_valido(trio))
            raiz = manipular_trio(raiz, trio);
        destruir_trio(trio);
    }
    return raiz;
}

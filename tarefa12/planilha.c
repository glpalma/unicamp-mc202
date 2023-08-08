#include "planilha.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_EXPRESSAO 1024
#define TAM_BUFFER 16

void checar_alocacao(void* ponteiro) {
    if (ponteiro == NULL) {
        printf("Falta de memória! Encerrando o programa...\n");
        exit(1);
    }
}

// início da lista ligada de células
p_lcel criar_lista_cel() {
    return NULL;
}

p_lcel adiciona_cel_inicio(p_lcel lista, p_cel celula) {
    p_lcel novo = malloc(sizeof(*novo));
    checar_alocacao(novo);

    novo->cel = celula;
    novo->prox = lista;

    return novo;
}

void destruir_lista_cel(p_lcel lista) {
    if (lista != NULL) {
        destruir_lista_cel(lista->prox);
        free(lista);
    }
}
// final da lista ligada de células

// início da lista ligada de strings
p_lstr criar_lista_str() {
    return NULL;
}

p_cel buscar_celula(p_pln planilha, char coluna, int linha) {
    int i = linha - 1;
    int j = coluna - 'A';
    p_cel celula = &(planilha->celulas[i][j]);

    return celula;
}

p_lstr adiciona_str_fim(p_lstr lista, char* str) {
    p_lstr atual;
    p_lstr novo = malloc(sizeof(*novo));
    checar_alocacao(novo);
    novo->prox = NULL;
    novo->str = str;

    if (lista == NULL) {
        return novo;
    }
    else {
        atual = lista;
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = novo;
        return lista;
    }
}

void imprime_lista_str(p_lstr lista) {
    if (lista != NULL) {
        printf("%s", lista->str);
        imprime_lista_str(lista->prox);
    }
}

void destruir_lista_str(p_lstr lista) {
    if (lista != NULL) {
        destruir_lista_str(lista->prox);
        free(lista->str);
        free(lista);
    }
}
// final da lista ligada de strings

void inicializar_celula(p_cel celula, int i, int j) {
    celula->tipo = VALOR;
    celula->valor = 0;
    celula->exp = criar_lista_str();
    celula->ref = criar_lista_cel();
    celula->contem_erro = 0;
    celula->linha = i + 1;
    celula->coluna = j + 'A';
}

p_pln alocar_planilha(int n_linhas, int n_colunas) {
    // aloca a estrutura da planilha
    p_pln planilha = malloc(sizeof(*planilha));
    checar_alocacao(planilha);

    // inicializa os dados
    planilha->ncol = n_colunas;
    planilha->nlin = n_linhas;

    //  aloca a matriz de células
    planilha->celulas = malloc(n_linhas * sizeof(struct celula*));
    checar_alocacao(planilha->celulas);
    for (int i = 0; i < n_linhas; i++) {
        planilha->celulas[i] = malloc(n_colunas * sizeof(struct celula));
        checar_alocacao(planilha->celulas[i]);
        for (int j = 0; j < n_colunas; j++) {
            inicializar_celula(&(planilha->celulas[i][j]), i, j);
        }
    }

    return planilha;
}

void associar_valor_celula(char* expressao, p_cel celula) {
    int valor = -1;
    char buffer[TAM_BUFFER];
    char* str_carac;
    int len = strlen(expressao);
    int i, k = 0;

    if (expressao[0] == '=') {
        celula->tipo = EXPRESSAO;
        // para cada caractere além do '='
        for (i = 1; i < len; i++) {
            if (!isspace(expressao[i])) {
                buffer[k] = expressao[i];
                k++;
            }
            else {
                // se o caractere atual for espaço, salva a string anterior na célula atual
                buffer[k] = '\0';
                if (strlen(buffer) != 0) {
                    str_carac = malloc((strlen(buffer) + 1) * sizeof(char));
                    strcpy(str_carac, buffer);
                    celula->exp = adiciona_str_fim(celula->exp, str_carac);
                }
                k = 0;
            }
        }
    }
    else { // é valor
        // extrai o valor da string de expressão e salva na célula
        sscanf(expressao, "%d", &valor);
        celula->valor = valor;
        celula->tipo = VALOR;
    }
}

int eh_celula_valida(p_pln planilha, char* str) {
    p_cel extrema = &(planilha->celulas[planilha->nlin - 1][planilha->ncol - 1]);

    char coluna = str[0];
    int linha = str[1] - '0';

    if (coluna >= 'A' && coluna <= extrema->coluna && linha <= planilha->nlin) {
        return 1;
    }
    else {
        return 0;
    }
}

void adicionar_referencia(p_cel dependente, p_cel dependida) {
    int na_lista = 0;
    p_lcel atual;

    // verifica a presença da dependente na lista da dependida
    for (atual = dependida->ref; atual != NULL; atual = atual->prox) {
        if (atual->cel == dependente) {
            na_lista = 1;
            break;
        }
    }

    // adiciona somente se a célula dependente não está na lista da dependida
    if (!na_lista) {
        dependida->ref = adiciona_cel_inicio(dependida->ref, dependente);
    }
}

int calcular_expressao(p_pln planilha, p_cel origem, p_lstr expressao) {
    int parenteses_inicial = 1;
    int pri_op = 1; // se está buscando o primeiro operando
    char operador = '.';
    int op1 = 0, op2 = 0;
    int resultado;
    char* str;
    p_lstr atual;
    p_cel celula;
    int par_abertos = 0, par_fechados = 0;
    int exps_abertas = 0;
    int valor;
    char coluna;
    int linha;

    // verifica quantos parenteses abertos há na expressão dada
    for (atual = expressao; atual != NULL; atual = atual->prox) {
        str = atual->str;
        if (str[0] == '(') {
            par_abertos += 1;
        }
    }

    // percorre cada string
    for (atual = expressao; atual != NULL; atual = atual->prox) {
        str = atual->str;

        // caso seja um operando
        if (exps_abertas <= 0 && (str[0] == '+' || str[0] == '-')) {
            operador = str[0];
            pri_op = 0;
        }
        // caso seja uma célula
        else if (exps_abertas <= 0 && eh_celula_valida(planilha, str)) {
            sscanf(str, "%c%d", &coluna, &linha);
            celula = buscar_celula(planilha, coluna, linha);

            // caso a célula seja uma expressão e ainda não tenha sido calculada
            if (celula->valor == 0 && celula->tipo == EXPRESSAO) {
                valor = calcular_expressao(planilha, celula, celula->exp);
                celula->valor = valor;
            }
            else {
                valor = celula->valor;
            }
            if (pri_op) {
                op1 = valor;
            }
            else {
                op2 = valor;
            }

            adicionar_referencia(origem, celula);
        }
        // caso seja um abre parenteses que não o primeiro
        else if (str[0] == '(') {
            if (!parenteses_inicial && exps_abertas <= 0) {
                if (pri_op) {
                    op1 = calcular_expressao(planilha, origem, atual);
                }
                else {
                    op2 = calcular_expressao(planilha, origem, atual);
                }
            }
            if (!parenteses_inicial) {
                exps_abertas += 1;
            }
        }
        else if (str[0] == ')') {
            par_fechados += 1;
            exps_abertas -= 1;
        }
        parenteses_inicial = 0;
        if (par_abertos == par_fechados) {
            break;
        }
    }

    if (operador == '+') {
        resultado = op1 + op2;
    }
    else if (operador == '-') {
        resultado = op1 - op2;
    }
    else { // caso seja uma célula única
        resultado = op1;
    }

    return resultado;
}

void calcular_valor_expressoes(p_pln planilha) {
    int i, j;
    p_cel celula;

    // percorre todas as células
    for (i = 0; i < planilha->nlin; i++) {
        for (j = 0; j < planilha->ncol; j++) {
            celula = &(planilha->celulas[i][j]);
            // só faz o cálculo se não tiver erro e se não tiver sido calculada
            if (celula->tipo == EXPRESSAO && celula->valor == 0 && !celula->contem_erro) {
                celula->valor = calcular_expressao(planilha, celula, celula->exp);
            }
        }
    }
}

void ler_planilha_disco(p_pln planilha, char* nome_arquivo) {
    int i, j;
    int contador = 0;
    char expressao[MAX_EXPRESSAO];
    char aux;

    // abre o arquivo
    FILE* arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro na abertura do arquivo. Encerrando o programa...\n");
        exit(1);
    }

    // lê as células no arquivo
    while (fscanf(arquivo, "%c", &aux) != EOF && contador < planilha->nlin * planilha->ncol) {
        fscanf(arquivo, " %[^,\n]", expressao);
        i = contador / planilha->ncol; // divisão inteira
        j = contador % planilha->ncol;
        associar_valor_celula(expressao, &(planilha->celulas[i][j]));
        contador += 1;
    }
    calcular_valor_expressoes(planilha);

    fclose(arquivo);
}

void destruir_planilha(p_pln planilha) {
    p_cel celula;

    // para cada célula
    for (int i = 0; i < planilha->nlin; i++) {
        for (int j = 0; j < planilha->ncol; j++) {
            celula = &(planilha->celulas[i][j]);
            destruir_lista_str(celula->exp);
            destruir_lista_cel(celula->ref);
        }
        // libera a linha da matriz de células
        free(planilha->celulas[i]);
    }
    free(planilha->celulas);
    free(planilha);
}

void atualizar_valor_dependentes(p_pln planilha, p_cel dependida) {
    p_lcel atual;

    for (atual = dependida->ref; atual != NULL; atual = atual->prox) {
        if (!atual->cel->contem_erro) {
            atual->cel->valor = calcular_expressao(planilha, atual->cel, atual->cel->exp);
            atualizar_valor_dependentes(planilha, atual->cel);
        }
    }
}

void atualizar_celula(p_pln planilha, int valor_novo, int coluna, int linha) {
    p_cel celula = buscar_celula(planilha, coluna, linha);
    celula->valor = valor_novo;

    atualizar_valor_dependentes(planilha, celula);
}

int celula_errada(p_pln planilha, char coluna, int linha) {
    p_cel celula = buscar_celula(planilha, coluna, linha);

    return celula->contem_erro;
}

int obter_valor_celula(p_pln planilha, char coluna, int linha) {
    p_cel celula = buscar_celula(planilha, coluna, linha);

    return celula->valor;
}

void operacao_planilha(p_pln planilha, char operacao) {
    char coluna;
    int linha;
    int valor;
    int valor_novo;

    scanf(" %c%d", &coluna, &linha);

    switch (operacao) {
    case 'S': // altera o valor e mostra a mudança
        scanf(" %d", &valor_novo);
        valor = obter_valor_celula(planilha, coluna, linha);
        atualizar_celula(planilha, valor_novo, coluna, linha);
        printf("%c%d: %d -> %d\n", coluna, linha, valor, valor_novo);
        break;

    case 'G': // imprime o valor da célula
        if (celula_errada(planilha, coluna, linha)) {
            printf("%c%d: #ERRO#\n", coluna, linha);
        }
        else {
            valor = obter_valor_celula(planilha, coluna, linha);
            printf("%c%d: %d\n", coluna, linha, valor);
        }
        break;

    default:
        printf("Operação ainda não implementada.\n");
        break;
    }
}

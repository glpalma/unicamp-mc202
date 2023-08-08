// Implementação das possiveis funções sobre os inteiros grandes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inteiros_grandes.h"
#define MAX_NUMERO 25 // máximo comprimento que um número pode ter

void erro_memoria() {
    printf("Não há memória suficiente!\n");
    exit(1);
}

p_num criar_numero() {
    p_num numero;
    numero = malloc(sizeof(intG));
    if (numero == NULL) {
        erro_memoria();
    }
    numero->tam = 0;
    numero->ini = NULL;
    numero->fim = NULL;

    return numero;
}

void destruir_lista_ligada(p_alg lista) {
    if (lista != NULL) {
        destruir_lista_ligada(lista->prox);
        free(lista);
    }
}

void reciclar_numero(p_num numero) {
    destruir_lista_ligada(numero->ini);
    numero->tam = 0;
    numero->ini = NULL;
    numero->fim = NULL;
}

void destruir_numero(p_num numero) {
    destruir_lista_ligada(numero->ini); // limpa a lista ligada do número
    free(numero); // limpa a cabeça do numero
}

int eh_nulo(p_num numero) {
    if (numero->tam == 1 && numero->ini->alg == 0) {
        return 1;
    } else {
        return 0;
    }
}

p_num adiciona_inicio(p_num numero, int dado) {
    p_alg novo;
    novo = malloc(sizeof(Algarismo));
    if (novo == NULL) { // checa se a alocação dinâmica deu certo
        erro_memoria();
    }
    novo->alg = dado;
    if (numero->ini == NULL || numero->fim == NULL) { // caso o número não possua nenhum algarismo
        numero->ini = novo;
        numero->fim = novo;
        novo->ant = NULL;
        novo->prox = NULL;
    } else { // define o novo como o primeiro elemento da lista
        numero->ini->ant = novo;
        novo->prox = numero->ini;
        numero->ini = novo;
        novo->ant = NULL;
    }
    numero->tam += 1;
    return numero;
}

p_num adiciona_fim(p_num numero, int dado) {
    p_alg novo;
    novo = malloc(sizeof(Algarismo));
    if (novo == NULL) { // checa se a alocação dinâmica deu certo
        erro_memoria();
    }
    novo->alg = dado;
    if (numero->ini == NULL || numero->fim == NULL) { // caso o número não possua nenhum algarismo
        numero->ini = novo;
        numero->fim = novo;
        novo->ant = NULL;
        novo->prox = NULL;
    } else { // define o novo como o último elemento da lista
        numero->fim->prox = novo;
        novo->ant = numero->fim;
        numero->fim = novo;
        novo->prox = NULL;
    }
    numero->tam += 1;
    return numero;
}

p_num ler_numero(p_num numero) {
    char *num_str;
    char carac;
    int alg, n;

    num_str = malloc(MAX_NUMERO * (sizeof(char)));
    if (num_str == NULL) {
        erro_memoria();
    }

    scanf("%s", num_str); // lê uma string que representa o número
    n = strlen(num_str);
    for (int i = 0; i < n; i++) { // para cada caractere da string
        carac = num_str[i];
        alg = carac - '0'; // converte de char para int
        adiciona_fim(numero, alg); // adiciona o int ao final da lista
    }
    free(num_str); // libera a memória utilizada pela string, já não mais necessária
    return numero;
}

void copiar_numeros(p_num fonte, p_num destino) {
    p_alg aux;
    for (aux = fonte->ini; aux != NULL; aux = aux->prox) {
        adiciona_fim(destino, aux->alg);
    }
}

p_num somar_numeros(p_num num1, p_num num2, p_num resultado) {
    p_alg atual1 = num1->fim;
    p_alg atual2 = num2->fim;
    int resto = 0, soma_alg = 0, prox_casa = 0;

    while (atual1 != NULL && atual2 != NULL) { // adiciona os n últimos elementos
        soma_alg += (atual1->alg + atual2->alg + prox_casa);
        resto = soma_alg % 10;
        prox_casa = soma_alg / 10; // divisão inteira
        adiciona_inicio(resultado, resto);
        atual1 = atual1->ant;
        atual2 = atual2->ant;
        resto = 0;
        soma_alg = 0;
    }

    if (atual1 != NULL && atual2 == NULL) { // caso em que o num 2 acabou e 1 não
        while (atual1 != NULL) {
            soma_alg += (atual1->alg + prox_casa);
            resto = soma_alg % 10;
            prox_casa = soma_alg / 10; // divisão inteira
            adiciona_inicio(resultado, resto);
            atual1 = atual1->ant;
            resto = 0;
            soma_alg = 0;
        }
    } else if (atual1 == NULL && atual2 != NULL) { // caso em que o num 1 acabou e o 2 não
        while (atual2 != NULL) {
            soma_alg += (atual2->alg + prox_casa);
            resto = soma_alg % 10;
            prox_casa = soma_alg / 10; // divisão inteira
            adiciona_inicio(resultado, resto);
            atual2 = atual2->ant;
            resto = 0;
            soma_alg = 0;
        }
    }
    if (prox_casa) { // se tiver sobrado algum número que iria para a próxima casa decimal
        adiciona_inicio(resultado, prox_casa);
    }
    return resultado;
}

void achar_maior_menor(p_num num1, p_num num2, p_num *maior, p_num *menor) {
    p_alg alg1, alg2;
    int achou = 0;

    if (num1->tam > num2->tam) {
        *maior = num1;
        *menor = num2;
    } else if (num1->tam < num2->tam) {
        *maior = num2;
        *menor = num1;        
    } else { // numeros com o mesmo tamanho
        alg1 = num1->ini;
        alg2 = num2->ini;
        while (!achou) {
            if (alg1->alg > alg2->alg) {
                *maior = num1;
                *menor = num2;
                achou = 1;
            } else if (alg1->alg < alg2->alg) {
                *maior = num2;
                *menor = num1;
                achou = 1;
            } else {
                if ((alg1 == NULL) || (alg2 == NULL)) { // evita que a função faça acesso inválido de memória
                    achou = 1;
                    *maior = num1;
                    *menor = num2;
                    break;
                }
                alg1 = alg1->prox;
                alg2 = alg2->prox;
            }
        }
    }
}

int numeros_iguais(p_num num1,p_num num2) {
    p_alg alg1 = num1->ini;
    p_alg alg2 = num2->ini;

    if (num1->tam != num2->tam) { // se os números forem de tamanhos diferentes
        return 0;
    } else { // se os números tiverem o mesmo tamanho
        while (alg1 != NULL && alg2 != NULL) {
            if (alg1->alg != alg2->alg) {
                return 0;
            }
            alg1 = alg1->prox;
            alg2 = alg2->prox;
        }
    }
    return 1;
}

p_num subtrair_numeros(p_num num1, p_num num2, p_num resultado) {
    // p_num resultado;
    int dif = 0;
    p_num maior, menor;
    p_alg alg_maior, alg_menor, aux;
    // resultado = criar_numero();

    if (numeros_iguais(num1, num2)) { // se os números forem iguais, já retorna com 0
        adiciona_inicio(resultado, 0); // e evita gastar processamento
        return resultado;
    }
    achar_maior_menor(num1, num2, &maior, &menor);
    alg_maior = maior->fim;
    alg_menor = menor->fim;

    while (alg_maior != NULL && alg_menor != NULL) {
        dif = alg_maior->alg - alg_menor->alg;
        if (dif >= 0) {
            adiciona_inicio(resultado, dif);
        } else { // caso o algarismo do maior seja menor do que do número menor
            for (aux = alg_maior->ant; aux->alg == 0 && aux->ant != NULL; aux = aux->ant); // volta nas casas até achar um algarismo não nulo
            aux->alg -= 1;
            do {
                aux = aux->prox;
                aux->alg += 9;
            } while (aux != alg_maior);
            dif = alg_maior->alg + 1 - alg_menor->alg;
            adiciona_inicio(resultado, dif);
        }
        alg_maior = alg_maior->ant;
        alg_menor = alg_menor->ant;
    }

    while (alg_maior != NULL) {
        adiciona_inicio(resultado, alg_maior->alg);
        alg_maior = alg_maior->ant;
    }
    
    return resultado;
}

p_num multiplicar_numeros(p_num num1, p_num num2, p_num resultado) {
    p_num prod_res, aux;
    if (eh_nulo(num1) || eh_nulo(num2)) { // caso um dos números for 0, a função não executará em sua integridade
        adiciona_inicio(resultado, 0);
        return resultado;
    }
    prod_res = criar_numero();
    aux = criar_numero();
    adiciona_fim(resultado, 0); // evita que resultado chegue à primeira chamada da função de soma como NULL
    int prod = 1, prox_casa = 0, prim_dig = 0;
    int casa_inf = 0;
    int resto;
    p_alg atual1, atual2 = num2->fim;

    while (atual2 != NULL) { // percorre os algarismos do número inferior
        atual1 = num1->fim;
        while (atual1 != NULL) { // percorre os algarismos do número superior
            prod = atual1->alg * atual2->alg + prox_casa; // produto entre as casas decimais atuais
            resto = prod % 10;                            // mais o que sobrou da casa decimal anterior
            adiciona_inicio(prod_res, resto);
            prox_casa = prod / 10; // divisão inteira
            atual1 = atual1->ant;
        }
        adiciona_inicio(prod_res, prox_casa);
        for (int i = 0; i < casa_inf; i++) {
            adiciona_fim(prod_res, 0);
        }

        aux = somar_numeros(prod_res, resultado, aux);

        reciclar_numero(resultado);
        copiar_numeros(aux, resultado); // salva o valor de aux em resultado
        reciclar_numero(aux);
        reciclar_numero(prod_res); // reseta a cabeça do número e libera a parte da lista ligada

        prim_dig = prox_casa;
        prox_casa = 0;
        casa_inf += 1;
        atual2 = atual2->ant;
    }
    if (prim_dig) { // adiciona sobras ao primeiro dígito do número, caso tenha alguma
        adiciona_inicio(resultado, prox_casa);
    }
    destruir_numero(prod_res); // apaga o auxiliar de vez, pois não é mais necessário
    destruir_numero(aux); // idem
    return resultado;
}

p_num executar_operacao(p_num num1, p_num num2, char operador, p_num resultado) {

    switch (operador) {
    case ('+'):
        resultado = somar_numeros(num1, num2, resultado);
        break;
    case ('-'):
        resultado = subtrair_numeros(num1, num2, resultado);
        break;
    case ('*'):
        resultado = multiplicar_numeros(num1, num2, resultado);
        break;
    default:
        printf("Operação ainda não implementada.\n");
        resultado = NULL;
        break;
    }
    return resultado;
}

void imprimir_numero(p_num numero) {
    int n;
    int eh_zero_inicial = 1;

    if (numero == NULL) {
        return;
    }
    for (p_alg atual = numero->ini; atual != NULL; atual = atual->prox) {
        n = atual->alg;
        if (n == 0 && eh_zero_inicial && numero->tam != 1){
            continue;
        } else {
            printf("%d", n);
            eh_zero_inicial = 0;
        }
    }
    printf("\n");
}

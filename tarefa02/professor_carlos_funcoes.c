#include <string.h>
#include "professor_carlos.h"

// arquivo de implementação

// Devolve o aluno mais novo entre os dois alunos fornecidos
Aluno aluno_mais_novo(Aluno aluno1, Aluno aluno2) {
    Aluno aluno_escolhido;
    int ano_nasc, mes_nasc, dia_nasc;
    aluno_escolhido = aluno2;

    ano_nasc = aluno1.nascimento.ano;

    if (ano_nasc > aluno_escolhido.nascimento.ano) {
            aluno_escolhido = aluno1;

        } else if (ano_nasc == aluno_escolhido.nascimento.ano) {
            mes_nasc = aluno1.nascimento.mes;
            if (mes_nasc > aluno_escolhido.nascimento.mes) {
                aluno_escolhido = aluno1;
            } else if (mes_nasc == aluno_escolhido.nascimento.mes) {
                dia_nasc = aluno1.nascimento.dia;
                if (dia_nasc > aluno_escolhido.nascimento.dia) {
                    aluno_escolhido = aluno1;
                } else if (dia_nasc == aluno_escolhido.nascimento.dia) {
                    if (strcmp(aluno1.nome, aluno_escolhido.nome) < 0) {
                        aluno_escolhido = aluno1;
                    } else if (strcmp(aluno1.nome, aluno_escolhido.nome) == 0) {
                        if (strcmp(aluno1.sobrenome, aluno_escolhido.sobrenome) < 0) {
                            aluno_escolhido = aluno1;
                        }
                    }
                }
            }
        }
    return aluno_escolhido;
}

Aluno procura_novo_na_turma(Turma t[], int qtd_turmas, int j) { 
    Aluno aluno_atual, aluno_escolhido;
    int num_alunos, i;

    num_alunos = t[j].qtd;

    aluno_escolhido = t[j].alunos[0];

    for (i = 0; i < num_alunos; i++) {
        aluno_atual = t[j].alunos[i];

        aluno_escolhido = aluno_mais_novo(aluno_atual, aluno_escolhido);
    }
    return aluno_escolhido;
}

Aluno procura_novo_todas_turmas(Turma t[], int qtd_turmas) { 
    Aluno aluno_atual, aluno_escolhido;
    int i;

    aluno_escolhido = procura_novo_na_turma(t, qtd_turmas, 0);

    for (i = 0; i < qtd_turmas; i++) {
        aluno_atual = procura_novo_na_turma(t, qtd_turmas, i);

        aluno_escolhido = aluno_mais_novo(aluno_atual, aluno_escolhido);
    }
    return aluno_escolhido;
}

// Devolve o aluno mais velho entre os dois alunos fornecidos
Aluno aluno_mais_velho(Aluno aluno1, Aluno aluno2) { 
    Aluno aluno_escolhido;
    int ano_nasc, mes_nasc, dia_nasc;
    aluno_escolhido = aluno2;

    ano_nasc = aluno1.nascimento.ano;

    if (ano_nasc < aluno_escolhido.nascimento.ano) {
            aluno_escolhido = aluno1;

        } else if (ano_nasc == aluno_escolhido.nascimento.ano) {
            mes_nasc = aluno1.nascimento.mes;
            if (mes_nasc < aluno_escolhido.nascimento.mes) {
                aluno_escolhido = aluno1;
            } else if (mes_nasc == aluno_escolhido.nascimento.mes) {
                dia_nasc = aluno1.nascimento.dia;
                if (dia_nasc < aluno_escolhido.nascimento.dia) {
                    aluno_escolhido = aluno1;
                } else if (dia_nasc == aluno_escolhido.nascimento.dia) {
                    if (strcmp(aluno1.nome, aluno_escolhido.nome) < 0) {
                        aluno_escolhido = aluno1;
                    } else if (strcmp(aluno1.nome, aluno_escolhido.nome) == 0) {
                        if (strcmp(aluno1.sobrenome, aluno_escolhido.sobrenome) < 0) {
                            aluno_escolhido = aluno1;
                        }
                    }
                }
            }
        }
    return aluno_escolhido;
}

Aluno procura_velho_na_turma(Turma t[], int qtd_turmas, int j) { 
    Aluno aluno_atual, aluno_escolhido;
    int num_alunos, i;

    num_alunos = t[j].qtd;

    aluno_escolhido = t[j].alunos[0];

    for (i = 0; i < num_alunos; i++) {
        aluno_atual = t[j].alunos[i];

        aluno_escolhido = aluno_mais_velho(aluno_atual, aluno_escolhido);
    }
    return aluno_escolhido;
}

Aluno procura_velho_todas_turmas(Turma t[], int qtd_turmas) {
    Aluno aluno_atual, aluno_escolhido;
    int i;

    aluno_escolhido = procura_velho_na_turma(t, qtd_turmas, 0);

    for (i = 0; i < qtd_turmas; i++) {
        aluno_atual = procura_velho_na_turma(t, qtd_turmas, i);

        aluno_escolhido = aluno_mais_velho(aluno_atual, aluno_escolhido);
    }
    return aluno_escolhido;
}

// Devolve 1 caso o padrão esteja presente na palavra
int achou_padrao(char palavra[], char padrao[]) {
    int i, j;
    int achou;
    achou = 0;
    i = 0;
    j = 0;
    
    while ((padrao[j] != '\0') && (palavra[i] != '\0')) {
        if (padrao[j] == palavra[i]) {
            j += 1;
            i += 1;
            continue;
        }
        i += 1;
        j = 0;
    }

    if (j == strlen(padrao)) {
        achou = 1;
    }

    return achou;
}

int conta_substrings(Turma t[], int qtd_turmas, char *padrao) {
    int i, j, n;
    int num_alunos;
    Aluno aluno;
    n = 0;

    for (i = 0; i < qtd_turmas; i++) {
        num_alunos = t[i].qtd;
        for (j = 0; j < num_alunos; j++) {
            aluno = t[i].alunos[j];
            if (achou_padrao(aluno.nome, padrao)) {
                n += 1;
            }
        }
    }
    return n;
}

int add_aluno(Turma t[], Aluno A, int j) { 
    int n;
    n = t[j].qtd; // número de alunos em uma turma

    t[j].alunos[n] = A;
    n += 1;

    return n;
}

int remove_aluno(Turma t[], int j) {
    int n;

    n = t[j].qtd;
    n -= 1;

    return n;
}

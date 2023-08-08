#include <stdio.h>
#include <string.h>

typedef struct data {
    int dia;
    int mes;
    int ano;
} Data;

typedef struct aluno {
    Data nascimento;
    char nome[15];
    char sobrenome[15];
} Aluno;

typedef struct turma {
    Aluno alunos[50];
    int qtd;
} Turma;

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

int main() {
    int n;
    Turma t[50];
    Aluno aluno;
    char palavra[10], padrao[5];

    scanf("%s %s", palavra, padrao);

    n = achou_padrao(palavra, padrao);
    printf("%d\n", n);

    return 0;
}
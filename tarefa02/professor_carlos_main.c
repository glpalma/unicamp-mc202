#include <stdio.h>
#include "professor_carlos.h"
#define MAX_PADRAO 5
#define MAX_TURMAS 50

Aluno ler_info_aluno() {
    Aluno aluno;
    scanf("%s ", aluno.nome);
    scanf("%s ", aluno.sobrenome);

    scanf("%d ", &aluno.nascimento.dia);
    scanf("%d ", &aluno.nascimento.mes);
    scanf("%d", &aluno.nascimento.ano);

    return aluno;
}

int main() {
    int qtd_turmas, num_operacoes, num_alunos;
    int operacao, id_turma, idx_aluno;
    int i, n;
    char padrao[MAX_PADRAO];
    Aluno aluno;
    Turma t[MAX_TURMAS]; // VETOR DE TURMAS --> VÁRIAS TURMAS

    scanf("%d ", &qtd_turmas);
    scanf("%d", &num_operacoes);

    for (i = 0; i < qtd_turmas; i++) {
        scanf("%d", &num_alunos); 
        t[i].qtd = 0; // Inicializa a quantidade de alunos em uma turma
        for (idx_aluno = 0; idx_aluno < num_alunos; idx_aluno++) {
            aluno = ler_info_aluno();
            n = add_aluno(t, aluno, i);
            t[i].qtd += 1; // Soma 1 a cada aluno adcicionado
        }
    }

    for (i = 0; i < num_operacoes; i++) {
        scanf("%d ", &operacao);

        switch (operacao) {
        case (1):
            scanf("%d", &id_turma);
            aluno = procura_novo_na_turma(t, qtd_turmas, id_turma);
            printf("%s\n", aluno.nome);
            break;
        case (2):
            scanf("%d", &id_turma);
            aluno = procura_velho_na_turma(t, qtd_turmas, id_turma);
            printf("%s\n", aluno.sobrenome);
            break;
        case (3):
            aluno = procura_velho_todas_turmas(t, qtd_turmas);
            printf("%s\n", aluno.nome);
            break;
        case (4):
            aluno = procura_novo_todas_turmas(t, qtd_turmas);
            printf("%s\n", aluno.sobrenome);
            break;
        case (5):
            scanf("%s", padrao);
            n = conta_substrings(t, qtd_turmas, padrao);
            printf("%d\n", n);
            break;
        case (6):
            scanf("%d", &id_turma);
            aluno = ler_info_aluno();
            n = add_aluno(t, aluno, id_turma);
            t[id_turma].qtd = n;
            printf("%d\n", n);
            break;
        case (7):
            scanf("%d", &id_turma);
            n = remove_aluno(t, id_turma);
            t[id_turma].qtd = n;
            printf("%d\n", n);
            break;
        default:
            break;
        }
    }
    return 0;
}

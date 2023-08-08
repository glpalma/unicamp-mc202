número de pacientes não é definido
número de consultas tb não

structs a serem utilizadas

struct paciente {
    string de nome
    tipo de atendimento (1 para normal e 2 para preferencial)
    lista ligada que guarda os setores a serem visitados 
        guardar dado de próxima consulta
    número de consultas pelas quais passou
} guardar os pacientes com uma ll ? (não é dado o num de pacientes)

struct especialidade {
    int id // usar isso ou índices de um vetor?
    total de profissionais
    int profissionais disponíveis (qtd ou booleano)
    pont fila de atendimento
}

estrutura da fila do atendimento {
    struct cabeça da fila de atendimento {
        p_no ini, fim
    }
    struct do nó { (antes da struct de especialidade)
        pont prox
        pont paciente
    }
}

-----
PROTOTIPO DA MAIN
    relogio = 0
    jogar os pacientes em duas listas de espera (normal e preferencial)
    criar filas de atendimento
    coloca esses pacientes no primeiro atendimento que eles têm (preferencial na frente etc)
    limpa filas de entrada

enquanto todos os pacientes não tiverem sido atendidos
    relogio ++
    passa por cada fila de atendimento
        atende n pacientes (sendo n o número de profissionais disponíveis)
            para cada paciente atendido
                atualiza a fila de consultas dele
                se as consultas tiverem acabado
                    coloca na fila de saída
                coloca ele na fila do próximo atendimento
                tira ele do atendimento anterior

apagar filas de atendimento

imprimir saidas
apagar fila de saída
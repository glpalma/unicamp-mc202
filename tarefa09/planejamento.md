planejamento da main

enquanto a entrada não tiver sido finalizada
    receber operação
    executar operação
    se a operação for T
        finalizar programa

destruir motorista
// quando recebe um F, atende o cliente com prioridade

ESTRUTURAS
ponto cartesiano {
    int x, y
}

cliente {
    char nome
    double nota
    ponto inicio
    ponto final
}

motorista {
    km rodados
    rendimento bruto
    despesas
    heap de espera
}

OPERAÇÕES
A:
aloca o cliente
lê as informações do cliente 
insere no heap de acordo com sua nota
mostra mensagem de compleção

F:
cliente com maior prioridade do heap é atendido
calcular os ganhos e gastos do cliente
atualizar o motorista
mensagem de finalização

C:
recebe o nome do cliente
remove o cliente do heap
soma 7 reais ao rend bruto do motorista
mensagem de cancelamento

T: 
finalizar entrada
mostrar resultados

REFAZENDO A LÓGICA DO PROGRAMA
na hora de atender um, eu já vejo quem vai ser o próximo


FINALIZANDO ATENDIMENTO

se for NULL
    retira da fila e atende

atende o atual se não for NULL (calcula tudo bonitinho)
libera o espaço do cliente atual

atualiza o cliente atual (a partir da fila)
e é salvo em uma variável no motorista de cliente atual

// case ('F'): // finaliza a corrida do cliente com maior nota
        //     clt = atender_cliente(motorista); // supostamente OK
        //     motorista = computar_corrida(motorista, &clt); // OK
        //     printf("A corrida de %s foi finalizada\n", (&clt)->prim_nome);
        //     // destruir_cliente(clt);
        //     break; // caso anterior/ o abaixo será uma nova tentativa
    case ('F'): // finaliza a corrida do cliente com maior nota
        if (motorista->atendido == NULL) {
            motorista->atendido = atender_cliente(motorista);
        }
        motorista = computar_corrida(motorista, motorista->atendido);
        printf("A corrida de %s foi finalizada\n", motorista->atendido->prim_nome);
        // destruir_cliente(motorista->atendido); // precisa destruir o cliente aqui?
        motorista->atendido = NULL;
        
        motorista->atendido = atender_cliente(motorista); // atualiza o cliente a ser atendido
        break;

      
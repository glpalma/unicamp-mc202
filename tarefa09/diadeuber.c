#include "adm_uber.h"

int main() {
    p_mt motorista = criar_motorista(MAX_ESPERA);
    int finalizou = 0;
    char operacao;

    while (!finalizou) {
        operacao = ler_operacao(); // lê o char da operação
        motorista = executar_operacao(operacao, motorista);
        if (operacao == 'T') {
            finalizou = 1;
        }
    }
    destruir_motorista(motorista);

    return 0;
}
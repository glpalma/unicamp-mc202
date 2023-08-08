#include "adm_hospitalar.h"
#define NUM_SETORES 9

int main() {
    p_fila entrada = criar_fila();
    p_fila saida = criar_fila();
    p_esp setores = criar_setores_atendimento();

    ler_info_pacientes(entrada);
    direcionar_pacientes(entrada, setores);
    destruir_fila(entrada);

    while (ha_pacientes(setores)) {
        atender_pacientes(setores, saida); // atende os pacientes de cada setor de acordo com o número de profissionais disponíveis
    }
    destruir_setores(setores);
    imprimir_saida(saida);
    destruir_fila(saida);
    return 0;
}
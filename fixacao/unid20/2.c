/*
As tabelas que utilizam endereçamento aberto apresentam complicações
na hora de remoção. Isso porque não se pode simplesmente remover um item
de sua posição atual, pois isso pode causar problemas posteriores com operações
de inserção e busca.
Para contornar isso, a posição do item removido deve contar com um registro de
item removido, por exemplo, para que uma futura inserção seja feita com sucesso.
*/

struct dado {
    int chave;
    int removido;
};

struct tabela_espalhamento {
    struct dado* v;
    int n;
};

typedef struct tabela_espalhamento p_tabes;

void hash(p_tabes tabela, int chave);

p_tabes criar_tabela();

void destruir_tabela();

void inserir_chave(p_tabes tabela, int chave);

void remover_chave(p_tabes tabela, int chave);

struct dado* buscar_chave(p_tabes tabela, int chave);

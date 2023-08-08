planej {
    ler número de palavras no dicionario
    ler palavras a serem checadas

    ler palavras do dicionário
    inserir na hash table

    para cada palavra
    ler a palavra
    verificar nível de correção
    imprimir resultado

    destruir hash table
    destruir outras alocações feitas
    return 0
}

VERIFICAÇÃO DO NÍVEL DE CORREÇÃO
primeiro, verifica se a palavra corresponde ao hash
acessa o hash
percorrer a lista ligada da posição escolhida
    comparar com a palavra de cada nó
    se achar, para o loop e devolve verde

    se não achar
    alocar vetor com tam = dicio->qtd
    idx = 0
    para cada posicao no vetor
        para cada no até null
            calcular erros com a palavra do no
            salvar no vetor no idx i
            idx ++

    obtem o menor numero de erros no vetor
    libera o vetor
    retorna o numero de erros

# NOTAS
palavra com duas letras trocadas de posição conta como dois erros
    duas letras trocadas
se a palavra não estiver no dicionário, conta como errada

um erro -> amarela
dois ou mais-> vermelho



ESTRUTURAS A SEREM UTILIZADAS

tabela hash
cada i do vetor é um p_no de lista ligada

p_no
palavra
prox

FUNÇÃO DE HASH
preciso devolver um índice em que a palavra será inserida
0 <= idx < M

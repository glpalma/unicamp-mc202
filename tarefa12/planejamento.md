ler nome do arquivo
ler colunas
ler linhas

alocar planilha
ler arquivo e colocar na planilha

ler operações até dar EOF
    ler operação
    ler célula
        se operação for S
            ler nova expressão/número
            salvar valor antigo da célula
            salvar valor novo na célula
            imprimir mudança
        se não for
            acessar célula 
            imprimir valor

destruir planilha da memória

ED

célula
    tipo (valor, expressao)
    bool contem_erro
    char coluna
    int linha
    char* expressao
    referencias (lista ligada de células que se referem a essa celula atual)

planilha vai ser constituida de matriz de células (tamanho fornecido na entrada)
    têm no máximo 26 colunas, então dá pra fazer conversão int -> char e vice versa

a struct tb vai ter o número de linhas e colunas junto

leitura do arquivo
fopen 
tentar ler cada célula com regex do fscanf
se começar com '=' é expressão
se não, é número

preciso testar a leitura da planilha (só com números)
    depois imprimir planilha só pra ter certeza

para calcular a expressão

chamar a função com o ponteiro do inicio da expressao
parenteses inicial = 1

para cada string da lista
    se a string atual for um operando
        salvar operando
        procurando segundo operando = true
    
    se a string atual for uma célula
        se estiver procurando o primeiro operando
            salva o valor da célula no primeiro operando
        senao
            salva no segundo
    se for um parenteses (inicio de uma expressao) e nao for o do inicio
        se estiver procurando o primeiro operando
            salva o valor da exp no primeiro operando
        senao
            salva no segundo
    parenteses inicial = 0;

se operando for +
    resultado = op1 + op2
senao 
    resultado = op1 - op2

retorna resultado
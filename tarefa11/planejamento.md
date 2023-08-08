não se importa com a distância total que caminhará

maior distância entre duas paradas tem que ser mínima.

para cada adjacencia do jogador
buscar_menor_maior_caminho do jogador até um lugia
colocar em uma lista
obter o menor valor

Talvez calcular uma vez só (e ter uma matriz de adjacência) seja mais interessante
fazer isso (vai facilitar muito a busca)

para cada vizinho do jogador
buscar um caminho até o lugia (com a maior distância sendo jogador - vizinho)

se o atual for o lugia
    salvar o maior em uma lista ligada
se não for
    atual = visitado
    visitar vizinhos recursivamente
    se a distancia for maior do que a anterior, atualize-a

retorna a lista de maiores caminhos

pegar o menor número da lista ligada
libera a lista
retorna o número

projeto da main {
    ler jogador, pokestops e lugia (todos vertices) em lista ligada
        contar quantos vertices
    com essa lista ligada
    criar um vetor com todos os vertices
    criar matriz de adjacencia (distancias)
    liberar lista ligada do inicio

    procurar distancia la de cima
    imprimir resultado

    liberar matriz e vetor (ou struct idk)    
}

# Primeiro, definimos o grafo usando um dicionario onde cada chave representa um no
# e correspondemos o valor dos nos adjascentes a uma lista de vizinhos
graph = {
    "a" : ["b", "d"],
    "b" : [],
    "c" : [],
    "d" : ["e", "g"],
    "e" : ["c"],
    "f" : [],
    "g" : ["f"]
}

def dfs(graph, source):
    # Criamos uma lista vazia para rastrear os nos
    stack = []
    stack.append(source) #comecamos com o no fonte

    while stack:
        node = stack.pop(-1) # Retiramos o ultimo no
        print(node) # Printo o no atual
        
        # Adiciono os nos vizinhos, ainda nao visitados, para a pilha
        for neighbour in graph[node]:
            stack.append(neighbour)

# Logica basica de DFS -> Pilha, visito o no, ele sai da pilha, vou para os adjascentes, e assim 
# ate o fim do grafo

dfs(graph, "a")
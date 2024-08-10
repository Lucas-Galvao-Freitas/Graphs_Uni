# Definimos o grafo usando um dicionário onde cada chave representa um nó,
# e o valor correspondente é uma lista de seus nós adjacentes.
graph = {
    "a": ["b", "d"],
    "b": [],
    "c": [],
    "d": ["e", "g"],
    "e": ["c"],
    "f": [],
    "g": ["f"]
}

def bfs(graph, source):
    # Criamos uma fila vazia para rastrear os nós.
    queue = []
    queue.append(source)  # Começamos com o nó de origem.

    while queue:
        node = queue.pop(0)  # Removemos o primeiro nó da fila.
        print(node)  # Imprimimos o nó atual.

        # Adicionamos todos os nós vizinhos (ainda não visitados) à fila.
        for neighbour in graph[node]:
            queue.append(neighbour)

# Lógica básica do BFS -> Fila, visitamos o nó, ele sai da fila, vamos para os adjacentes e assim por diante.

# Chamamos a função BFS começando pelo nó "a".
bfs(graph, "a")

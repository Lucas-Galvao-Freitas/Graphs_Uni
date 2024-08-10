import sys

INF = sys.maxsize            # infinito
N = 9                        # vertices
dist = [INF] * N             # vetor de distancias
pred = [-1] * N              # predecessores
adj = [[] for _ in range(N)] # vetor de adjascencia

def bellmanFord(s):
    # inicializando a distancia do vertice de partida como 0
    dist[s] = 0

    # atualizacao das distancias das arestas repetidamente (relaxamento)
    for i in range(N-1):
        alterado = False # flag que verifica o relaxamento
        for u in range(N):
            #se o vertice u ainda esta no menor caminho
            if dist[u] != INF:
                for v, w in adj[u]:
                    # relaxa a aresta
                    if dist[u] + w < dist[v]:
                        dist[v] = dist[u] + w
                        pred[v] = u
                        alterado = True

        # se nenhum vertice foi alterado, entao temos o fim do bellmanFord
        if not alterado:
            break

    # verificando a existencia de ciclos negativos
    for u in range(N):
        if dist[u] != INF:
            for v, w in dist[u]:
                if dist[u] + w < dist[v]:
                    return 1 # presenca de ciclo negativo
                
    return 0


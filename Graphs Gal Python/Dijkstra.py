import heapq
INF = float('inf')
N = 9

dist = [INF] * N                # distancias
pred = [-1] * N                 # predecessores
visited = [0] * N               # visitados
adj = [[] for _ in range(N)]    # adjascentes

def dijkstra(s):
    """
        Dijkstra's algorithm implementation. S = starting vertex
    """

    dist[s] = 0
    # Create a min-hep with the 1st elem as the distance to the second as the vertex
    q = [(0, s)]

    while q:
        a, u = heapq.heappop(q)

        if visited[u]:
            continue

        visited[u] = 1 # Mark as visited

        for v, w in adj[u]:
            if dist[u] + w < dist[v]:
                dist[v] = dist[u] + w           # update the distance
                pred[v] = u                     # update the predecessor
                heapq.heappush(q, (dist[v], v)) # add the vertex to min-heap

def main():
    # Define the graph
    adj[0].append((1, 4))
    adj[0].append((7, 8))
    adj[1].append((0, 4))
    adj[1].append((2, 8))
    adj[1].append((7, 11))
    adj[2].append((1, 8))
    adj[2].append((3, 7))
    adj[2].append((8, 2))
    adj[2].append((5, 4))
    adj[3].append((2, 7))
    adj[3].append((4, 9))
    adj[3].append((5, 14))
    adj[4].append((3, 9))
    adj[4].append((5, 10))
    adj[5].append((2, 4))
    adj[5].append((3, 14))
    adj[5].append((4, 10))
    adj[5].append((6, 2))
    adj[6].append((5, 2))
    adj[6].append((7, 1))
    adj[6].append((8, 6))
    adj[7].append((0, 8))
    adj[7].append((1, 11))
    adj[7].append((6, 1))
    adj[7].append((8, 7))
    adj[8].append((2, 2))
    adj[8].append((6, 6))
    adj[8].append((7, 7))

    # Run Dijkstra's algorithm
    dijkstra(0)

    # Print the shortest distances
    print("Vertex\tDistance\tPredecessor")
    for i in range(N):
        print(f"{i}\t{dist[i]}\t{pred[i]}")

if __name__ == "__main__":
    main()
#include <bits/stdc++.h>

using namespace std;

#define INF 0x3f3f3f3f    // infinito
#define N 9// numero de vertices do grafo
vector<int> dist(N, INF); // vetor de distancias
vector<int> pred(N, -1);  // vetor de predecessores
vector<pair<int, int>> adj[N]; //vetor de adj
// prototipos de funcoes
int bellmanFord(int); // a funcao recebe o vertice de origem

int main()
{

}

int bellmanFord(int s)
{
    dist[s] = 0;
    for (int i = 0; i < N - 1; i++)
    {
        int alterado = 0;
        for (int u = 0; u < N; u++)
        {
            if (dist[u] != INF)
                for (auto p : adj[u])
                {
                    int v = p.first, w = p.second;
                    if (dist[u] + w >= dist[v])
                        continue;
                    dist[v] = dist[u] + w;
                    pred[v] = u;
                    alterado = 1;
                } // for auto
        }
        if (!alterado)
            break;
    } // for i

    // verifica ciclo negativo:
    // se possuir, retorna 1.
    // senao, retorna 0.
    for (int u = 0; u < N; u++)
        if (dist[u] != INF)
            for (auto p : adj[u])
            {
                int v = p.first, w = p.second;
                if (dist[v] > dist[u] + w)
                    return 1;
            } // for auto
    return 0;
} // belmannFord
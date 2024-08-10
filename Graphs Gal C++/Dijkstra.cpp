#include <bits/stdc++.h>

using namespace std;

// Definicoes gerais
#define INF 0x3f3f3f3f            // infinito
#define N 9                       // numero de vertices do grafo
vector<int> dist(N, INF);         // vetor de distancias
vector<int> pred(N, -1);          // vetor de predecessores
vector<int> visitado(N, 0);       // marca se o vertice foi visitado
priority_queue<pair<int, int>> q; // fila: (distancia, vertice)

vector<pair<int, int>> adj[N]; //vetor de adj

// prototipo da funcao
void dijkstra(int s); // a funcao recebe o vertice de origem

int main()
{
    
}

void dijkstra(int s)
{
    dist[s] = 0;
    q.push({0, s});

    while (!q.empty())
    {
        int a = q.top().second;
        q.pop();

        if (visitado[a])
            continue;

        visitado[a] = 1;

        for (auto u : adj[a])
        {
            int b = u.first;
            int w = u.second;

            if (dist[a] + w < dist[b])
            {
                dist[b] = dist[a] + w;
                pred[b] = a;
                q.push({-dist[b], b});
            }
        } // for
    } // while
} // dijkstra
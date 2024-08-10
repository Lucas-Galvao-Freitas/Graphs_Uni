#include <bits/stdc++.h>

using namespace std;


// Definicoes gerais
#define INF -1
#define N 4     // qtd de vertices
int m[N][N];     // a matriz de adjacencia
int dist[N];     // Distancias a partir do inicio. Inicializar com infinito.
queue<int> fila; // estrutura de fila para percorrer os niveis.

void bfs(int s);

int main()
{
    memset(m, 0, sizeof(m));
    memset(dist, INF, sizeof(dist));

    m[0][1] = 1;
    m[1][0] = 1;
    m[0][2] = 1;
    m[2][3] = 1;

    for(int i = 0; i < N; i++)
    {
        bfs(i);
        cout << dist[3] << endl;
        memset(dist, INF, sizeof(dist));
        
        cout << endl;
    }

}

void bfs(int s)
{
    int i, u;

    dist[s] = 0;
    fila.push(s);

    while (!fila.empty())
    {
        u = fila.front();
        fila.pop();
        printf("% d ", u);

        for (i = 0; i < N; i++)
        {
            if (dist[i] == INF && m[u][i])
            {
                dist[i] = dist[u] + 1;
                fila.push(i);
            }
        }
    }
}
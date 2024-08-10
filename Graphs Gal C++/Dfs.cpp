#include <bits/stdc++.h>

using namespace std;

// Definicoes gerais
#define N 4         // qtd de vertices
int m[N][N];         // a matriz de adjacencia
int visitado_rec[N]; // marca os nos visitados, inicializar com 0
int anterior_rec[N]; // marca o no anterior na busca, inicializar com -1
int cont = 0;
int total = 0;

// Definicoes gerais
int visitado[N];  // marca os nos visitados, inicializar com 0
int anterior[N];  // marca o no anterior na busca, inicializar com -1
stack<int> pilha; // pilha para marcar o caminho de volta

void dfs_rec(int u);

int main()
{
    memset(m, 0, sizeof(m));
    memset(visitado_rec, 0, sizeof(visitado_rec));
    memset(anterior_rec, -1, sizeof(anterior_rec));

    m[0][1] = 1;
    m[1][0] = 1;
    m[0][2] = 1;
    m[2][0] = 1;
    m[2][3] = 1;
    m[3][2] = 1;

    for(int i = 0; i < N; i++)
    {
        dfs_rec(i);
        if(cont == N)
        {
            cout << i << " eh um componente fortemente conectado." << endl;
            total ++;
        }
        memset(visitado_rec, 0, sizeof(visitado_rec));
        memset(anterior_rec, -1, sizeof(anterior_rec));
        cont = 0;
        cout << endl;
    }

    if(total == N)
        cout << "Grafo fortemente conectado.";
}

//do the predecessors of a vertex
//run dfs on its children and check if they can reach the predecessor through any path that doesn't go through the vertex

// u: no inicio
void dfs_rec(int u)
{
    int i;
    if (!visitado_rec[u])
    {
        visitado_rec[u] = 1;
        cont++;
        printf("% d ", u);
    }
    for (i = 0; i < N; i++)
    {
        if (m[u][i] && !visitado_rec[i])
        {
            anterior_rec[i] = u;
            dfs_rec(i);
        }
    }
}

// s: no inicial.
void dfs(int s)
{
    int u, i;

    pilha.push(s);

    while (!pilha.empty())
    {
        u = pilha.top();
        pilha.pop();
        if (!visitado[u])
        {
            visitado[u] = 1;
            printf("% d ", u);
        }

        for (i = 0; i < N; i++)
        {
            if (m[u][i] && !visitado[i])
            {
                pilha.push(i);
                anterior[i] = u;
            }
        }
    }
}

vector<int> adj[N]; // lista de adjacencia
int visitado_list[N];    // marca os nos visitados. Inicializar com 0.


// u: no inicial
void dfs_list(int u)
{
    if (!visitado_list[u])
    {
        visitado_list[u] = 1;
        printf("% d ", u);

        for (auto i : adj[u])
            dfs_list(i);
    }
}
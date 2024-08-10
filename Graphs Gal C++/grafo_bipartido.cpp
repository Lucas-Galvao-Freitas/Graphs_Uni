#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm> // precisei usar a funcao reverse (dessa biblioteca)
#include <climits> // int_max
using namespace std;

class Aresta
{
    int vertice1, vertice2, peso;

public:
    Aresta(int v1, int v2, int peso)
    {
        vertice1 = v1;
        vertice2 = v2;
        this->peso = peso;
    }

    int obterVertice1() const
    {
        return vertice1;
    }

    int obterVertice2() const
    {
        return vertice2;
    }

    int obterPeso() const
    {
        return peso;
    }
};

class Grafo
{
    int V;                          // número de vértices
    vector<Aresta> arestas;         // vetor de arestas
    vector<vector<int>> adj;        // lista de adjacência
    vector<vector<int>> capacidade; // matriz de capacidades

public:
    Grafo(int V)
    {
        this->V = V;
        adj.resize(V);
        capacidade.resize(V, vector<int>(V, 0));
    }

    int obterNumVertices() const
    {
        return this->V;
    }

    const vector<Aresta> &obterArestas() const
    {
        return arestas;
    }

    void adicionarAresta(int v1, int v2, int peso)
    {
        Aresta aresta(v1, v2, peso);
        arestas.push_back(aresta);
        adj[v1].push_back(v2);
        adj[v2].push_back(v1);
        capacidade[v1][v2] = peso;
    }

    bool bfs(const vector<vector<int>> &rGraph, int s, int t, vector<int> &parent) const
    {
        vector<bool> visited(V, false);
        queue<int> q;
        q.push(s);
        visited[s] = true;
        parent[s] = -1;

        while (!q.empty())
        {
            int u = q.front();
            q.pop();

            for (int v : adj[u])
            {
                if (!visited[v] && rGraph[u][v] > 0)
                {
                    if (v == t)
                    {
                        parent[v] = u;
                        return true;
                    }
                    q.push(v);
                    parent[v] = u;
                    visited[v] = true;
                }
            }
        }

        return false;
    }

    Grafo ford_fulkerson(int s, int t) const
    {
        Grafo rGrafo = *this;


        vector<int> fluxo(this->arestas.size(), 0);

        vector<vector<int>> rGraph = capacidade;
        vector<int> parent(V);

        while (bfs(rGraph, s, t, parent))
        {
            int path_flow = INT_MAX;


            for (int v = t; v != s; v = parent[v])
            {
                int u = parent[v];
                path_flow = min(path_flow, rGraph[u][v]);
            }


            for (int v = t; v != s; v = parent[v])
            {
                int u = parent[v];
                rGraph[u][v] -= path_flow;
                rGraph[v][u] += path_flow;
            }
        }

        Grafo fluxoMaximo(V);
        for (int u = 0; u < V; u++)
        {
            for (int v : adj[u])
            {
                if (capacidade[u][v] > 0 && rGraph[u][v] < capacidade[u][v])
                {
                    fluxoMaximo.adicionarAresta(u, v, capacidade[u][v] - rGraph[u][v]);
                }
            }
        }

        return fluxoMaximo;
    }

    bool isBipartite(vector<int> &color, int src) const
    {
        queue<int> q;
        q.push(src);
        color[src] = 1;

        while (!q.empty())
        {
            int u = q.front();
            q.pop();

            for (int v : adj[u])
            {
                if (color[v] == -1)
                {
                    color[v] = 1 - color[u];
                    q.push(v);
                }
                else if (color[v] == color[u])
                {
                    return false;
                }
            }
        }
        return true;
    }

    bool obterGrafoBipartido(vector<int> &part1, vector<int> &part2) const
    {
        vector<int> color(V, -1);

        for (int i = 0; i < V; ++i)
        {
            if (color[i] == -1)
            {
                if (!isBipartite(color, i))
                {
                    return false;
                }
            }
        }

        for (int i = 0; i < V; ++i)
        {
            if (color[i] == 1)
            {
                part1.push_back(i);
            }
            else
            {
                part2.push_back(i);
            }
        }

        return true;
    }

    Grafo emparelhamentoMaximo() const
    {
        vector<int> part1, part2;
        this->obterGrafoBipartido(part1, part2);
        Grafo g1(part1.size() + part2.size() + 2);
        for (Aresta aresta : this->obterArestas())
        {
            g1.adicionarAresta(aresta.obterVertice1() + 1, aresta.obterVertice2() + 1, aresta.obterPeso());
        }
        for (int v : part1)
        {
            g1.adicionarAresta(0, v, 1);
        }
        for (int u : part2)
        {
            g1.adicionarAresta(u, g1.V - 1, 1);
        }
        return g1.ford_fulkerson(0, g1.V - 1);
    }

    void imprimir_adjacencias(void)
    {
        int matriz_adj[this->V][this->V];
        for (int i = 0 ; i < this->V; i++)
        {
            for (int j = 0; j < this->V; j++)
            {
                matriz_adj[i][j] = 0;
            }
        }

        for (Aresta aresta : arestas)
        {
            matriz_adj[aresta.obterVertice1()][aresta.obterVertice2()] = aresta.obterPeso();
            matriz_adj[aresta.obterVertice2()][aresta.obterVertice1()] = aresta.obterPeso();
        }

        cout << "   ";
        for (int i = 0; i < this->V; i++)
        {
            cout << i << " ";
        }
        cout << endl;

        for (int i = 0; i < this->V;i++)
        {
            cout << i << ": ";
            for(int j=0; j < this->V; j++)
            {
                cout << matriz_adj[i][j] << " ";
            }
            cout << endl;
        }
    }

    vector<int> dijkstra(int origem, int destino) const {
        vector<int> distancia(V, INT_MAX);
        vector<int> predecessor(V, -1);

        distancia[origem] = 0;

        // fila de prioridade          elementos                comparador que define a ordem de prioridade 
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> fila_p;
        fila_p.push({0, origem});

        while(!fila_p.empty()) {
            int u = fila_p.top().second;
            fila_p.pop();

            for(int v : adj[u]) {
                int peso = capacidade[u][v];

                if(distancia[u] + peso < distancia[v]) {
                    distancia[v] = distancia[u] + peso;
                    predecessor[v] = u;
                    fila_p.push({distancia[v], v});
                }
            }
        }

        vector<int> caminho_das_pedras;
        int atual = destino;

        while(atual != -1) {
            caminho_das_pedras.push_back(atual);
            atual = predecessor[atual];
        }
        reverse(caminho_das_pedras.begin(), caminho_das_pedras.end());

        return caminho_das_pedras;
    }

    vector<Aresta> kruskal() const{
        
        vector<Aresta> arestas = this->obterArestas();
        sort(arestas.begin(), arestas.end(), [](const Aresta &a, const Aresta &b) {
            return a.obterPeso() < b.obterPeso();
        });

        vector <Aresta> mst;
        vector<int> parent(this->V);
        for(int i = 0; i < this->V; i++){
            parent[i] = i;
        }

        for(const Aresta &aresta : arestas)
        {   
            int x = aresta.obterVertice1();
            int y = aresta.obterVertice2();
            
            if(find(parent, x) != find(parent, y)){
                mst.push_back(aresta);
                unionSets(parent, x, y);
            }    
        }

        return mst;
    }

    int find(vector<int> &parent, int u) const {
        if(parent[u] != u){
            parent[u] = find(parent, parent[u]);
        }
        
        return parent[u];
    }

    void unionSets(vector<int> &parent, int u, int v) const {
        int uRoot = find(parent, u);
        int vRoot = find(parent, v);
        parent[uRoot] = vRoot;
    }

    void dfs(int vertice) const {
        vector<bool> visited(this->V, false);
        dfs_logic(vertice, visited);
    }

    void dfs_logic(int vertice, vector<bool> &visited) const {
        visited[vertice] = true;
        cout << vertice << " ";

        for(int v : adj[vertice]) {
            if(!visited[v]){
                dfs_logic(v, visited);
            }
        }
    }

};


void menu(Grafo g)
{
    int escolha;

    cout << "1. Matriz de adjacencia" << endl
         << "2. Arvore Geradora Minima" << endl
         << "3. Busca pelos vertices do grafo." << endl
         << "4. Algoritmo de Dijkstra." << endl
         << "5. Algoritmo de Ford-Fulkerson" << endl
         << "6. Algoritmo de Emparelhamento Maximo" << endl;
    cin >> escolha;

    switch (escolha)
    {
    case 1:
        g.imprimir_adjacencias();
        cout << endl
             << endl;
        break;

    case 2:
    {
        vector<Aresta> mst = g.kruskal();
        cout << "Arestas da arvore geradora minima:" << endl;
        for (const Aresta &aresta : mst)
        {
            cout << aresta.obterVertice1() << " -> " << aresta.obterVertice2() << " com peso " << aresta.obterPeso() << endl;
        }
        break;
    }

    case 3:
    {   
        int vertice;
        cout << "Digite o vertice para realizar a busca em profundidade (DFS): ";
        cin >> vertice;
        g.dfs(vertice);
        cout << endl 
             << endl;
        break;
    }

    case 4:
    {
        int a, b;
        cout << "Determine os vertices para os quais sera calculado o menor caminho: " << endl;
        cin >> a >> b;

        vector<int> caminho_min = g.dijkstra(a, b);

        cout << "Caminho minimo: " << endl;
        for (auto node : caminho_min)
        {
            cout << node << " -> ";
        }
        cout << endl 
             << endl;

        break;

    }

    case 5:
    {
        int a, b;
        cout << "Determine os vertices para os quais sera calculado o fluxo maximo" << endl;
        cin >> a >> b;

        Grafo fluxoMaximo = g.ford_fulkerson(a, b);

        cout << "Arestas com fluxo maximo:\n";
        for (const Aresta &aresta : fluxoMaximo.obterArestas())
        {
            cout << aresta.obterVertice1() << " -> " << aresta.obterVertice2() << " com fluxo " << aresta.obterPeso() << endl;
        }
        break;
    }

    case 6:
    {
        vector<int> part1, part2;

        if (g.obterGrafoBipartido(part1, part2))
        {
            cout << endl
                 << endl
                 << "O grafo e bipartido.\n";
            cout << "Particao 1: ";
            for (int v : part1)
            {
                cout << v + 1 << " ";
            }
            cout << "\nParticao 2: ";
            for (int v : part2)
            {
                cout << v + 1 << " ";
            }
            cout << endl;
        }

        cout << "Arestas com emparelhamento maximo:\n";
        Grafo emparelhamentoMax = g.emparelhamentoMaximo();
        for (const Aresta &aresta : emparelhamentoMax.obterArestas())
        {
            if (aresta.obterVertice1() != 0 && aresta.obterVertice2() != emparelhamentoMax.obterNumVertices())
            {
                cout << aresta.obterVertice1() << " -> " << aresta.obterVertice2() << endl;
            }
        }
        break;
    }

    default:
        cout << "Digite um valor de 1 a 6!" << endl
             << endl;
        break;
    }
}

int main()
{
    Grafo g(9);
    g.adicionarAresta(0, 5, 1);
    g.adicionarAresta(1, 5, 1);
    g.adicionarAresta(2, 6, 1);
    g.adicionarAresta(1, 7, 1);
    g.adicionarAresta(2, 7, 1);
    g.adicionarAresta(3, 7, 1);
    g.adicionarAresta(4, 7, 1);
    g.adicionarAresta(2, 8, 1);

    while (1)
    {
        menu(g);
    }

    return 0;
}
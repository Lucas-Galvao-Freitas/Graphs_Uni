class Aresta:
    def __init__(self, v1, v2, weight):
        self.vertice1 = v1
        self.vertice2 = v2
        self.weight = weight

    def getV1(self):
        return self.vertice1

    def getV2(self):
        return self.vertice2
    
    def getWeight(self):
        return self.weight
    
    # funcao responsavel por auxiliar a ordenacao de arestas em ordem crescente
    def __lt__(self, aresta2):
        return self.weight < aresta2.weight
    
class Graph:
    def __init__(self, V):
        self.V = V
        self.arestas = []

    def addAresta(self, v1, v2, weight):
        aresta = Aresta(v1, v2, weight)
        self.arestas.append(aresta)

    # Basicamente, a funcao de busca esta buscando vertices que estao em seu
    # proprio subconjunto, vulgo vertices de menor grau
    def search(self, subset, i):
        if subset[i] == -1:
            return i 
        return self.search(subset, subset[i])
        
    def unir(self, subset, v1, v2):
        v1_set = self.search(subset, v1)
        v2_set = self.search(subset, v2)

        subset[v1_set] = v2_set

    def kruskal(self):
        arvore = []
        arestas = self.arestas

        #ordenando as arestas pelo menor peso
        arestas.sort()

        #alocando memoria para criar "V" subconjuntos
        subset = [-1] * self.V

        for aresta in arestas:
            v1 = self.search(subset, aresta.getV1())
            v2 = self.search(subset, aresta.getV2())

            if v1 != v2:
            # se forem diferentes, nao formam ciclo, insere no vetor
                arvore.append(aresta)
                self.unir(subset, v1, v2) # realiza a uniao

        for aresta in arvore:
        # mostra as arestas selecionadas com seus respectivos pesos
            v1 = chr(aresta.getV1() + ord('A'))
            v2 = chr(aresta.getV2() + ord('A'))
            print(f"Vertices: ({v1}, {v2}); Peso = {aresta.getWeight()}")

g = Graph(7)

g.addAresta(0, 1, 0)
g.addAresta(1, 2, 1)
g.addAresta(2, 3, 7)
g.addAresta(3, 4, 1)
g.addAresta(4, 5, 1)
g.addAresta(3, 5, 9)
g.addAresta(5, 2, 8)
g.addAresta(6, 3, 4)
g.addAresta(6, 0, 2)

g.kruskal()
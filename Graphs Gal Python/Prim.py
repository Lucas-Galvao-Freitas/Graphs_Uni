import math
import unittest
from math import inf
from heapdict import heapdict

class Vertex:
    def __init__(self, value):
        self.value = value
        self.edges = []
        self.in_tree = False
        self.parent = self

    def addEdges(self, vertex, weight):
        self.edges.append(Edge(vertex, weight))

class Edge:
    def __init__(self, vertex, weight):
        self.vertex = vertex
        self.weight = weight

class Graph:
    def __init__(self):
        self.vertices = []

    def addVert(self, vertices):
        for vertex in vertices:
            self.vertices.append(vertex)

def prim(graph, start):
    distance = {}
    remaining = heapdict() # dicionario de prioridade:
                           # escolhe o menor valor ao inves do maior (similar a P.Q)
    weight = 0

    for vertex in graph.vertices:
        distance[vertex] = remaining[vertex] = inf
    
    distance[start] = remaining[start] = 0

    while len(remaining) > 0:
        v = remaining.popitem()[0]
        v.in_tree = True
        print(f'{v.parent.value} -> {v.value} = {distance[v]}')
        if v != start:
            weight += distance[v]
        
        for edge in v.edges:
            w = edge.vertex
            if distance[w] > edge.weight and w.in_tree == False:
                distance[w] = remaining[w] = edge.weight
                w.parent = v

    return weight

class Test(unittest.TestCase):
    def test_prim(self):
        vertices = {"A": Vertex("A"), "B": Vertex("B"), "C": Vertex("C"), "D": Vertex("D"),
                 "E": Vertex("E"), "F": Vertex("F"),  "G": Vertex("G")}

        edges = [("A", "B", 2), ("A", "C", 3), ("A", "D", 3), ("B", "C", 4), ("B", "E", 3),
                 ("C", "E", 1), ("C", "F", 6), ("E", "F", 8), ("F", "G", 9)]

        for e in edges:
            vertices[e[0]].addEdges(vertices[e[1]], e[2])
            vertices[e[1]].addEdges(vertices[e[0]], e[2])

        g = Graph()
        g.addVert(vertices.values())

        weight = prim(g, vertices["A"])

# def test_prim_disconnected(self):
#         vertices = {"A": Vertex("A"), "B": Vertex("B"), "C": Vertex("C"), "D": Vertex("D"),
#                     "E": Vertex("E"), "F": Vertex("F"),  "G": Vertex("G")}

#         edges = [("A", "C", 35), ("A", "D", 89), ("B", "A", 11), ("C", "B", 28),
#                  ("C", "D", 62), ("E", "A", 8)]

#         for e in edges:
#             vertices[e[0]].add_edge(vertices[e[1]], e[2])

#         g = Graph()
#         g.add_vertices(vertices.values())

#         self.assertEqual(prim(g, vertices["A"]), math.inf)


if __name__ == "__main__":
    unittest.main()







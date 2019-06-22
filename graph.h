// graph.h
#ifndef GRAPH_H 
#define GRAPH_H

#include "edge.h"
#include <iostream>
#include <vector>
#include <queue>
#include <stack>

#define INF 99999999
#define UNDEF -1
#define EDGE_LENGTH 1

using namespace std;

class Graph{
    private:
        int num_v;
        int num_e;
        int *adj_matrix;
    public:
        Graph(const int);                               // (a) construtor
        ~Graph();                                       // (b) destrutor
        void print(); 
        bool insert(const Edge&);                       // (c) adiciona aresta
        bool remove(const Edge&);                       // (d) remove aresta
        int numVertex();                                // (e) número de vértices
        int numEdges();                                 // (e) número de arestas
        bool edge(const Edge&) const;                   // (f) verifica aresta
        bool isComplete();                              // (g) verifica se é completo
        void complete();                                // (h) completa grafo
        vector<int> BFSearch(const int);                // (i) busca em largura
        vector<int> DFSearch(const int);                // (j) busca em profundidade
        int numCC();                                    // (k) número de componentes conectadas
        vector<int> dijkstra(const int, const int);     // (l) menor caminho (Algoritmo de Dijkstra)
        vector<int> tsp(const int, int*);               // (m) menor caminho (Caixeiro viajante), passando por todas on vértices
        void primMST();                                 // (n) Árvore geradora mínima.
};

int pop_min_dist(vector<int>&, const int *);
int minKey(int[], bool[], int);
void printMST(int parent[], int **graph, int numv);


#endif /* GRAPH_H */

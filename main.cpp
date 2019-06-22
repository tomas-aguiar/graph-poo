#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

#include "graph.h"

using namespace std;

int main(int argc, char *argv[]){

    string file_path = argv[1];
    ifstream infile(file_path);
    
    int num_v;
    infile >> num_v;    
    Graph graph(num_v);
    
    int v1, v2, w;    
    while (infile >> v1 >> v2 >> w){   
        Edge edge(v1,v2,w);
        graph.insert(edge);
    }
    
    graph.print(); 
    
    if(argc > 2){
        string arg = argv[2];
        if(arg == "-insert"){
            int v1 = atoi(argv[3]);
            int v2 = atoi(argv[4]);
            
            Edge edge;
            if(argc > 5){
                int w = atoi(argv[5]);
                Edge edg(v1,v2,w);
                edge = edg;
            }else{
                Edge edg(v1,v2);
                edge = edg;
            }
            
            bool ins = graph.insert(edge);
            
            if(ins){
                cout << endl;
                cout << ">> Inserida aresta (" << v1 << ", " << v2 << ")";
                cout << endl << endl;
            } else{
                cout << endl;
                cout << ">> Falha ao inserir aresta (" << v1 << ", " << v2 << ")";
                cout << endl << endl;
            }
            graph.print();
        } else if(arg == "-remove"){
            int v1 = atoi(argv[3]);
            int v2 = atoi(argv[4]);
            Edge edge(v1,v2);
            bool ins = graph.remove(edge);
            if(ins){
                cout << endl;
                cout << ">> Removida aresta (" << v1 << ", " << v2 << ")";
                cout << endl << endl;
            } else{
                cout << endl;
                cout << ">> Falha ao remover aresta (" << v1 << ", " << v2 << ")";
                cout << endl << endl;
            }
            graph.print();
        } else if(arg == "-iscomplete"){
            bool ins = graph.isComplete();
            if(ins){
                cout << endl;
                cout << ">> Grafo é completo";
                cout << endl << endl;
            } else{
                cout << endl;
                cout << ">> Grafo não é completo";
                cout << endl << endl;
            }
        } else if(arg == "-complete"){
            cout << endl;
            cout << ">> Grafo completado" << endl;
            cout << endl;            
            graph.complete();
            graph.print();
        } else if(arg == "-bfsearch"){
            int vertex = atoi(argv[3]);
            cout << endl;
            cout << ">> Busca em largura partindo do vértice " << vertex; 
            cout << endl;
            vector<int> bfs_array = graph.BFSearch(vertex);            
            cout << ">> ";
            for(int i=0; i<graph.numVertex(); i++){
                cout << bfs_array[i] << " ";
            }
            cout << endl;
        } else if(arg == "-dfsearch"){
            int vertex = atoi(argv[3]);
            cout << endl;
            cout << ">> Busca em profundidade partindo do vértice " << vertex; 
            cout << endl;
            vector<int> dfs_array = graph.DFSearch(vertex);            
            cout << ">> ";
            for(int i=0; i<graph.numVertex(); i++){
                cout << dfs_array[i] << " ";
            }
            cout << endl;
        } else if(arg == "-numcc"){
            int numcc = graph.numCC();
            cout << endl;
            cout << ">> Número de componentes conectadas: " << numcc; 
            cout << endl;
        } else if(arg == "-dijkstra"){
            int src = atoi(argv[3]);
            int dst = atoi(argv[4]);
            vector<int> dijkstra = graph.dijkstra(src,dst);
            cout << endl;
            cout << ">> Menor caminho entre os vértices " << src << " e " << dst; 
            cout << endl << ">> ";
            for(unsigned int i=1; i<dijkstra.size(); i++)
                cout << dijkstra[i] << " ";
            cout << "(comprimento = " << dijkstra[0] << ")";
            cout << endl;
        } else if(arg == "-tsp"){
            int src = atoi(argv[3]);
            int lentsp = 0;
            vector<int> tsp = graph.tsp((src - 1), &lentsp);
            cout << endl;
            cout << ">> Solução do problema do caixeiro viajante ";
            cout << endl << ">> " << src << " ";
            for(unsigned int i=1; i<tsp.size(); i++)
                cout << (tsp[i] + 1) << " ";
            cout << "(comprimento = " << lentsp << ")";
            cout << endl;
        } else if(arg == "-mst"){
            //int src = atoi(argv[3]);
            //int lentsp = 0;
            //vector<int> tsp = graph.tsp(src, &lentsp);
            cout << endl;
            cout << ">> Solução do problema de geração de árvore mínima ";
            cout << endl << ">> ";
            graph.primMST();
            cout << endl;
        }
    }

    return 0;
}

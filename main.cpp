#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>

#include "graph.h"

using namespace std;

int main(int argc, char *argv[])
{

    string file_path = argv[1];
    ifstream infile(file_path);
    
    int num_v;
    infile >> num_v;    
    Graph graph(num_v);
    
    int v1, v2, w;    
    while (infile >> v1 >> v2 >> w)
    {
        Edge edge(v1,v2,w);
        graph.insert(edge);
    }
    
    graph.print(); 
    
    if (argc <= 2) return EXIT_FAILURE;

    string arg = argv[2];
    if (arg == "-insert")
    {
        insert(argc, argv, graph);
    }
    else if(arg == "-remove")
    {
        remove(argv, graph);
    }
    else if(arg == "-iscomplete")
    {
        is_complete(graph);
    }
    else if(arg == "-complete")
    {
        complete(graph);
    }
    else if(arg == "-bfsearch")
    {
        bfsearch(argv, graph);
    }
    else if(arg == "-dfsearch")
    {
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
    }
    else if(arg == "-numcc")
    {
        int numcc = graph.numCC();
        cout << endl;
        cout << ">> Número de componentes conectadas: " << numcc;
        cout << endl;
    }
    else if(arg == "-dijkstra")
    {
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
    }
    else if(arg == "-tsp")
    {
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
    }
    else if(arg == "-mst")
    {
        cout << endl;
        cout << ">> Solução do problema de geração de árvore mínima ";
        cout << endl << ">> ";
        graph.primMST();
        cout << endl;
    }

    return 0;
}

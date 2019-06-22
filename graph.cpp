#include "graph.h"
#include <algorithm>

Graph::Graph(const int size){
    num_v = size;
    num_e = 0;
    adj_matrix = new int[size*size];
    for(int i = 0; i < size*size; i++)
        adj_matrix[i] = 0;
}

Graph::~Graph(){
    delete [] adj_matrix;
}

void Graph::print(){

    cout << "num_v: " << num_v;
    cout << '\n';
    cout << "num_e: " << num_e;
    cout << '\n';
    
    for(int row = 0; row < num_v; row++){
        for(int collum = 0; collum < num_v; collum++){
            cout << adj_matrix[row+num_v*collum];
            cout << " ";
            }
            cout << "\n";
    }   
}

bool Graph::insert(const Edge& edge){
    
    if(Graph::edge(edge))
        return false;
    
    int v1 = edge.v1; 
    int v2 = edge.v2;
    adj_matrix[(v1-1)+num_v*(v2-1)] = edge.w;
    adj_matrix[(v2-1)+num_v*(v1-1)] = edge.w;
    num_e++;   
    return true;    
}

bool Graph::remove(const Edge& edge){

    if(!Graph::edge(edge))
        return false;
    
    int v1 = edge.v1; 
    int v2 = edge.v2;
    adj_matrix[(v1-1)+num_v*(v2-1)] = 0;
    adj_matrix[(v2-1)+num_v*(v1-1)] = 0;
    num_e--;   
    return true; 
}

int Graph::numVertex(){
    return num_v;
}

int Graph::numEdges(){
    return num_e;
}

bool Graph::edge(const Edge& edge) const{
    if(adj_matrix[(edge.v1-1)+num_v*(edge.v2-1)] != 0){
        return true;
    } else{
        return false;
    }
}

bool Graph::isComplete(){
    for(int row = 0; row < num_v; row++){
        for(int collum = 0; collum < row; collum++){
            if(adj_matrix[row+num_v*collum] == 0)
                return false;
        }
    }
    return true;
}

void Graph::complete(){
    for(int i = 0; i < num_v*num_v; i++)
        if(adj_matrix[i]==0)
            adj_matrix[i] = 1;
    for(int i = 0; i < num_v; i++)
        adj_matrix[i+num_v*i] = 0;
    num_e = num_v*(num_v-1)/2;
}

vector<int> Graph::BFSearch(const int vertex){

    vector<int> output;
     
    bool *visited = new bool[num_v];
    for(int i = 0; i < num_v; i++)
		visited[i] = false;
    visited[vertex-1] = true; 
    
    queue<int> Q;
    Q.push(vertex);
    
    while(!Q.empty()){
        int v = Q.front();         
        output.push_back(v);
        Q.pop();        
        for(int w = 1; w <= num_v; w++){
            if(adj_matrix[(v-1)+num_v*(w-1)] != 0){
                if(visited[w-1] == false){
                    visited[w-1] = true;
                    Q.push(w);
                }
            }
        }        
    }
    return output;            
}

vector<int> Graph::DFSearch(const int vertex){

    vector<int> output;
     
    bool *visited = new bool[num_v];
    for(int i = 0; i < num_v; i++)
		visited[i] = false;
    visited[vertex-1] = true; 
    
    stack<int> S;
    S.push(vertex);
    
    while(!S.empty()){
        int v = S.top();         
        output.push_back(v);
        S.pop();        
        for(int w = 1; w <= num_v; w++){
            if(adj_matrix[(v-1)+num_v*(w-1)] != 0){
                if(visited[w-1] == false){
                    visited[w-1] = true;
                    S.push(w);
                }
            }
        }        
    }
    return output;            
}

int Graph::numCC(){
    int num_cc = 0;    
    bool *visited = new bool[num_v];
    for(int i = 0; i < num_v; i++)
		visited[i] = false;  
    
    for(int i = 0; i < num_v; i++){
        if(!visited[i]){    
            vector<int> dfs_array = Graph::DFSearch(i+1);
            num_cc++;
            
            for(int i = 0; i < num_v; i++)
                visited[dfs_array[i]-1] = true;
        }
    }    
    return num_cc;  
}

int pop_min_dist(vector<int>& set, const int * dist){
    int min_i = UNDEF;
    int min_idx = UNDEF;
    int min_value = INF;
    for(unsigned int i=0; i < set.size(); i++){
        if(dist[set[i]-1] < min_value){
            min_i = i;
            min_idx = set[i];
            min_value = dist[set[i]-1];
        }        
    }
    if(min_i!=UNDEF)
        set.erase(set.begin()+min_i);
    return min_idx;
}

vector<int> Graph::dijkstra(const int source, const int dest){
   
    int *dist = new int[num_v];
    int *prev = new int[num_v];
    
    vector<int> vertex_set; // vertex set   
    
    for(int v = 1; v <= num_v; v++){
        dist[v-1] = INF;
        prev[v-1] = UNDEF;
        vertex_set.push_back(v);      
    }    
        
    dist[source-1] = 0;
                   
    while(!vertex_set.empty()){
               
        int u = pop_min_dist(vertex_set, dist); 
 
        if(u == dest || u == UNDEF)
            break;
            
        for(unsigned int i=0; i < vertex_set.size(); i++){
            int v = vertex_set[i];
            int edge = adj_matrix[(u-1)+num_v*(v-1)];            
            if(edge != 0){
                int alt = dist[u-1] + EDGE_LENGTH*edge;
                if(alt < dist[v-1]){
                    dist[v-1] = alt;
                    prev[v-1] = u;
                }
            }
        }    
    }  
           
    vector<int> output;
    vector<int>::iterator it;
    it = output.begin();

    int u = dest;
    
    if(prev[u-1] != UNDEF || u == source){
        while(u != UNDEF){
            it = output.insert(it, u); // stack path
            u = prev[u-1];
        }
    }   
    output.insert(it, dist[dest-1]); // stack path length
    
    return output;
}

vector<int> Graph::tsp(const int src, int *len)
{
    //  Completa o Grafo //
    if(!isComplete())
        complete();

    //  Cria a matriz de adjacencia //
    int **matAdj = new int *[num_v];
    for(int i = 0; i < num_v; i++)
        matAdj[i] = new int[num_v];

    //  Popula matriz completa  //   
    for(int i = 0; i < num_v; i++)
    {
        for(int j = 0; j < num_v; j++)
            (i != j) ? matAdj[i][j] = 1 : matAdj[i][j] = 0;
    }

    //  Guarda todos os vertices menos o remetente  //
    vector<int> vertex;
    vector<int> pathV;
    for(int i = 0; i < num_v; i++)
        if(i != src)
            vertex.push_back(i);

    //  Guarda o menor peso //
    int min_path = INF;
    do
    {
        //  Guarda o caminho atual  //
        int curr_pathw = 0;
        vector<int> auxV;
        auxV.push_back(src);

        //  Calcula o peso do caminho atual //
        int k = src;
        for(unsigned int i = 0; i < vertex.size(); i++)
        {
            curr_pathw += matAdj[k][vertex[i]];
            k = vertex[i];
            auxV.push_back(k);
        }
        curr_pathw += matAdj[k][src];

        //  Atualiza o menor caminho    //
        int aux = min(min_path, curr_pathw);
        if(aux < min_path)
        {
            min_path = aux;
            pathV = auxV;
        }
    } while (next_permutation(vertex.begin(), vertex.end()));

    *len = min_path;

    return pathV;
}

int minKey(int key[], bool mstSet[], int numv)
{
    //  Inicializa o menor valor    //
    int min = INF;
    int min_ind;

    for(int i = 0; i < numv; i++)
    {
        if((mstSet[i] == false) && (key[i] < min))
        {
            min = key[i];
            min_ind = i;
        }
    }
    
    return min_ind;
}

void printMST(int parent[], int **graph, int numv)
{   
    for (int i = 1; i < numv; i++)  
        cout<<(parent[i]+1)<<" - "<<(i+1)<<" \t"<<graph[i][parent[i]]+1<<" \n";
}  

void Graph::primMST()
{
    //  Vetor que guarda o mst  //
    //vector<int> parent = new int[num_v];
    int *parent = new int[num_v];

    int *key = new int[num_v];

    //  Vetor que guarda os vertices ainda nao presentes na arvore  //
    bool *mstSet = new bool[num_v];

    //  Inicializa todas as chaves como infinito    //
    for(int i = 0; i < num_v; i++)
    {
        key[i] = INF;
        mstSet[i] = false;
    }

    //  Coloca o primeiro vertice no MST    //
    key[0] = 0;
    parent[0] = -1;

    //  Cria a matriz de adjacencia //
    int **matAdj = new int *[num_v];
    for(int i = 0; i < num_v; i++)
        matAdj[i] = new int[num_v];

    //  Popula matriz completa  //   
    for(int i = 0; i < num_v; i++)
    {
        for(int j = 0; j < num_v; j++)
        {
            Edge aux(i,j);
            if(edge(aux) && (i != j))
                matAdj[i][j] = 1;
            else
                matAdj[i][j] = 0;            
        }       
    }

    //  MST terá num_v vertices //
    for(int count = 0; count < (num_v - 1); count++)
    {
        int u = minKey(key, mstSet, num_v);                 // Recebe a menor chave.
        mstSet[u] = true;                                   // Adiciona o vertice ao grupo.

        //  Atualiza o grupo    //
        for(int v = 0; v < num_v; v++)
        {
            if(matAdj[u][v] && (mstSet[v] == false) && (matAdj[u][v] < key[v]))
            {
                parent[v] = u;
                key[v] = matAdj[u][v];
            }
        }
    }

    printMST(parent, matAdj, num_v);
}

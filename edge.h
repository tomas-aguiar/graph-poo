// edge.h
#ifndef EDGE_H 
#define EDGE_H

# define UNDEF -1

class Edge{
	public:
        int v1;
		int v2;
		int w;
		Edge();
		Edge(const int vertex1, const int vertex2);
		Edge(const int vertex1, const int vertex2, const int weigth); 
};


#endif /* EDGE_H */

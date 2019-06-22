#include "edge.h"

Edge::Edge()
{
	v1 = UNDEF;
	v2 = UNDEF;
	w = UNDEF;
}

Edge::Edge(const int vertex1, const int vertex2)
{
	v1 = vertex1;
	v2 = vertex2;
	w = 1;
}

Edge::Edge(const int vertex1, const int vertex2, const int weigth)
{
	v1 = vertex1;
	v2 = vertex2;
	w = weigth;
}

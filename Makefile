all: edge graph main clean 

edge: edge.h edge.cpp
	g++ -Wall -Werror -c edge.cpp

graph: graph.h graph.cpp
	g++ -Wall -Werror -c graph.cpp

main: graph main.cpp
	g++ -Wall -Werror -o tp-poo edge.o graph.o main.cpp

clean: edge graph
	rm edge.o graph.o

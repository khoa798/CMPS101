#ifndef LOADGRAPH
#define LOADGRAPH

#include "edgeVec.h"

// Loads the graph and builds it.

typedef struct {
	int from;
	int to;
	double weight;
} Edge;

FILE* open_file(char *); // for opening file
EdgeVec* initEdges(int); // parses the edges and creates IntVec constructs
Edge parseEdges(char*, int); // parses the edges
int parseN(char*); // Finds the total number of vertices
void loadEdges(char*, EdgeVec[], int, int); // load up edges
void printEdge(EdgeInfo); // prints out edges
void printGraph(EdgeVec[], int); // prints out the graph
void printOutput(int, int[], double[], int[]); // prints the arrays
#endif
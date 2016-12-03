#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include "loadWgtGraph.h"


// Creates and builds the graph for the algorithm



FILE* open_file(char* infile){
	// opens a file
	FILE* fp;
	fp = fopen(infile, "r");
	if (fp== NULL){
		fprintf(stderr, "No file by that name found.\n");
		exit(1);
	}
	printf("Opened %s for input\n", infile);
	return fp;
}

EdgeVec* initEdges(int n){
	EdgeVec* adjInfos = calloc(n+1, sizeof(EdgeVec));
	assert (adjInfos != NULL);
	adjInfos[0] = edgeMakeEmptyVec();
	for(int i = 1; i<=n; i++){
		adjInfos[i] = edgeMakeEmptyVec(); // create intVec constructs to each table index here
	}
	return adjInfos;

}
Edge parseEdges(char* line_parseEdge, int n){
	Edge newE;
	char* lineTemp = strdup(line_parseEdge);
	char* w0 = strtok(lineTemp, " \t\n");
	char* w1 = strtok(NULL, " \t\n");
	char* w2 = strtok(NULL, " \t\n");
	char* w3 = strtok(NULL, " \t\n");

	if (w0 == NULL || w1 == NULL || w3 != NULL){
		fprintf(stderr, "Bad edge: %s\n", line_parseEdge);
		exit(1);
	}

	newE.from = atoi(w0);
	newE.to = atoi(w1);

	// check that all edges are inside the range of values

	if (newE.from <= 0 || newE.from > n \
		|| newE.to <= 0 || newE.to > n){
		fprintf(stderr, "Edge (%d, %d) is out of range\n", newE.from, newE.to);
		newE.from = 0;
		newE.to = 0;
	}

	if(w2 != NULL){
		newE.weight = atof(w2);
	}else{
		newE.weight = 0.0;
	}
	//free (lineTemp);
	return newE;
}

int parseN(char* line){
	int num;
	char* lineTemp = strdup(line);
	char* w0 = strtok(lineTemp, " \t\n");
	char* w1 = strtok(NULL, " \t\n");

	if (w0 == NULL || w1 != NULL){
		fprintf(stderr, "Bad line: %s", line);
		exit(1);
	}
	num = atoi(w0);
	free(lineTemp);

	return num;

}

void loadEdges(char* line, EdgeVec* adjInfos, int num, int task){
	// Uses parseEdges to find edges
	Edge E = parseEdges(line, num);

	// use the edges found to get adjacency vectors
	if(E.from != 0 && E.to != 0){
		EdgeInfo newE;
		newE.to = E.to;
		newE.wgt = E.weight;
		edgeVecPush(adjInfos[E.from], newE);
		// If using graph as undirected, treat as two directed edges.
		if( task == 'P'){
			EdgeInfo newE0;
			newE0.to = E.from;
			newE0.wgt = E.weight;
			edgeVecPush(adjInfos[E.to], newE0);
		}
	}
}

void printEdge(EdgeInfo Edge){
	printf( "(%d, %.2f)",Edge.to, Edge.wgt);

}
void printGraph(EdgeVec* adjInfos, int l){
	int j;

	printf("The graph has %d nodes.\n", l);
	for (j =1; j<= l; ++j){
		EdgeVec pnode = adjInfos[j];
		int it=1;
		printf("%d\t", j);

		while(edgeSize(pnode) > 0){
			if(it){
				printf("[");
			}else{
				printf(", ");
			}
			printEdge(edgeTop(pnode));
			edgeVecPop(pnode);
			it=0;	



		}
		if(it){
			printf("[]");
		}else{
			printf("]");
		}
		printf("\n");
	}
	puts(" ");

}

void printOutput(int n, int * status, double * fringeWgt, int * parent) {
	puts("vertex\tstatus\tparent\tpriority\t");
	int j;
	for(j = 1; j <= n; ++j) {
		printf("%d\t  %c\t  %d\t   %.2f\n",\
		       j, status[j], parent[j], fringeWgt[j]);
	} 
}

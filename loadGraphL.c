#ifndef C101IntVec
#define C101IntVec
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<assert.h>
#include "loadGraphL.h"
#include "intList.h"

typedef struct Edge{
	int from;
	int to;
	double weight;
} Edge;



IntList* initEdges(int n){
	IntList* adjVertices_init = calloc(n+1,sizeof(int));
	assert (adjVertices_init != NULL);
	for(int i = 1; i<=n; i++){
		adjVertices_init[i] = NULL;
	}
	return adjVertices_init;
}

Edge parseEdge(char line_parseEdge[]){
	Edge newE;
	int numFields;
	numFields = sscanf(line_parseEdge, "%d %d %lf %*s", &newE.from, &newE.to, &newE.weight);
	if(numFields < 2 || numFields > 3){
		printf("Bad edge: %s\n", line_parseEdge);
		exit(EXIT_FAILURE);
	}
	
	if(numFields == 2){
		newE.weight = 0.0;
	}
	return newE;
}



#endif
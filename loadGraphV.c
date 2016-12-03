
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<assert.h>
#include "loadGraphV.h"

IntVec* initEdgesV(int n){
	IntVec* adjVertices_initE = calloc(n+1, sizeof(IntVec));
	assert (adjVertices_initE != NULL);
	adjVertices_initE[0] = intMakeEmptyVec();
	for(int i = 1; i<=n; i++){
		adjVertices_initE[i] = intMakeEmptyVec(); // create intVec constructs to each table index here
	}
	return adjVertices_initE;
}
		
EdgeV parseEdgeV(char line_parseEdge[]){
	EdgeV newE;
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



void printGraphV(IntVec* adjVertices_Vec, int l){
	for(int j = 1; j<=l; j++){
		printf("%d \t ",j); // print out which vertex you are at with tab
		printf("[");
		if(adjVertices_Vec[j] != NULL){
			int size = intSize(adjVertices_Vec[j]); // how many elements the vertex is pointing to
			int printSize = size-1;
			for(int f = printSize; f>=0; f--){
				int temp = intData(adjVertices_Vec[j], f);
				printf("%d ", temp);
			}
		}
		printf("]\n");
	}
}


void printStack(IntVec* tempStack){
	int size = intSize(tempStack);
	int printSize = size-1;
	for(int f = printSize; f>=0; f--){
		int temp = intData(tempStack, f);
		printf("%d ", temp);
	}
}
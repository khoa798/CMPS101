//-----------------------------------------------------------------------------
// graph01.c
// 
//-----------------------------------------------------------------------------


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include "intList.h"
typedef char* Cstring;

int main(int argc, Cstring argv[]){
	FILE* in; // handle for input file
	int m; // represents edges
	int n; // represents vertices
	char line[1024];
	char* fgetsRetn;
	//struct IntListNode* IntList;
	IntList *adjVertices;

	
	typedef struct Edge{
		int from;
		int to;
		double weight;
	} Edge;
	
	// assigns each value of adjVertices table to be NULL
	IntList* initEdges(int n){
		IntList* adjVertices_init = calloc(n+1,sizeof(int));
		assert (adjVertices_init != NULL);
		for(int i = 1; i<=n; i++){
			adjVertices_init[i] = intNil;
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
	
	if (argc != 2){
		printf("Usage: %s input.data\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	in=fopen(argv[1], "r");// opens file name for reading
	printf("Opened %s for input\n", argv[1]);
	fgetsRetn = fgets(line, 1024, in);
	n = atoi(line); //parses the line for int value for vertices
	printf("n = %d\n", n);
	adjVertices = initEdges(n);
	fgetsRetn = fgets(line, 1024, in);
	while( fgetsRetn == line ){
		Edge e = parseEdge(line);
		adjVertices[e.from] = intCons(e.to, adjVertices[e.from]);
		m++;
		fgetsRetn = fgets(line, 1024, in);
	}
	
	if ( ! feof(in)) { /* Some error occured */ }
	
	
	//print Function
	printf("m = %d\n",m);
	IntList temp;
	for(int k = 1; k<=n; k++){
		temp = adjVertices[k];
		printf("%d \t [%d ", k, intFirst(temp));
		IntList temp2 = adjVertices[k];
		for(IntList temp2 = adjVertices[k]; temp2 != NULL; temp2.next){
			printf(", %d ",intFirst(temp2));
		}
		
		
	}

	//fclose(in);
	return(EXIT_SUCCESS);
	

	
}
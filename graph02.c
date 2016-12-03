//-----------------------------------------------------------------------------
// graph02.c
//  Uses the IntList ADT or IntVec ADT based on the command line arguments
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<assert.h>
#include "intList.h"
#include "intVec.h"
//#include "loadGraphL.h"
//#include "loadGraph"
typedef char* Cstring;

int main(int argc, Cstring argv[]){
	FILE* in; // handle for input file
	int m; // represents edges
	int n; // represents vertices
	char line[1024];
	char* fgetsRetn;
	IntList* adjVertices;
	IntVec* adjVertices_Vec;
	
	typedef struct Edge{
		int from;
		int to;
		double weight;
	} Edge;
	
	if (argc != 3){ // if command line arguments are not exactly 3, remember a[0] in C is the input file's name.
		fprintf(stderr, "Usage: %s '-L' or '-V' input.data\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	
	if(strcmp(argv[1], "-L") == 0 ){ // uses IntList ADT
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
	
	

		in=fopen(argv[2], "r");// opens file name for reading
		printf("Opened %s for input\n", argv[2]);
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
		
		printf("m = %d\n",m);
		
		
		// Print function - incomplete, only prints first item in list.
		for(int o = 1; o<=n; o++){ 
			printf("%d \t ",o); // print out which vertex you are at with tab
			printf("[");
			if (adjVertices[o] != intNil){
				int temp2 = intFirst(adjVertices[o]);
				IntList temp=intRest(adjVertices[o]);
				while(temp2 != -1){
					printf("%d ",temp2);
					temp = intRest(temp);
					temp2 = intFirst(temp);
				}
			}
			printf("]\n");
			
		}
		
	}else if(strcmp(argv[1], "-V")== 0){ //uses IntVec ADT
		IntVec* initEdgesV(int n){
			IntVec* adjVertices_initE = calloc(n+1, sizeof(IntVec));
			assert (adjVertices_initE != NULL);
			adjVertices_initE[0] = intMakeEmptyVec();
			for(int i = 1; i<=n; i++){
				adjVertices_initE[i] = intMakeEmptyVec(); // create intVec constructs to each table index here
			}
			return adjVertices_initE;
		}
		
		Edge parseEdgeV(char line_parseEdge[]){
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
		
		in=fopen(argv[2], "r"); // opens file name for reading
		printf("Opened %s for input\n", argv[2]);
		fgetsRetn = fgets(line, 1024, in);
		n = atoi(line); // parses the line for int value for vertices
		printf("n = %d\n", n);
		adjVertices_Vec = initEdgesV(n);
		fgetsRetn = fgets(line, 1024, in);
		while( fgetsRetn == line){
			Edge eV = parseEdgeV(line);
			intVecPush(adjVertices_Vec[eV.from], eV.to);
			m++;
			fgetsRetn = fgets(line, 1024, in);
		}
		
		if (! feof (in)) { /* some error occurred */ }
		printf("m = %d\n",m);
		
		
		for(int j = 1; j<=n; j++){
			printf("%d \t ",j); // print out which vertex you are at with tab
			printf("[");
			if(adjVertices_Vec[j] != NULL){
				int size = intSize(adjVertices_Vec[j]); // how many elements the vertex is pointing to
				for(int k=0; k<size; k++){ // start from 0 but actually print out from end of array
					//int temp = intData(adjVertices_Vec[j], k);
					int temp = intTop(adjVertices_Vec[j]); // print out in order based on LIFO
					if(temp != -1){ // safety measure
						printf("%d ",temp);
					}
					intVecPop(adjVertices_Vec[j]); // set to -1, removing the element
				}
			}
			printf("]\n");
		}
		
		
	}
	
	


	//fclose(in);
	return(EXIT_SUCCESS);
	

	
}
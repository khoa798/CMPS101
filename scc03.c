//-----------------------------------------------------------------------------
// scc03.c
//  Performs DFS on a tree using IntVec ADT, also finds strongly connect components
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<assert.h>
#include "intList.h"
#include "intVec.h"
#include "loadGraphL.h"
#include "loadGraphV.h"
#include "dfsTrace1.h"
#include "dfsPhase2.h"
typedef char* Cstring;

int main(int argc, Cstring argv[]){
	FILE* in; // handle for input file
	int m = 0; // represents edges
	int n = 0; // represents vertices
	char line[1024];
	char* fgetsRetn;
	int undirectedOn = 0;
	//IntList* adjVertices;
	IntVec* adjVertices_Vec;
	IntVec* copiedVec;
	IntVec* copiedTransGraph;
	
	int numberOfArgs = argc;
	if (numberOfArgs == 3 ){
		if (strcmp(argv[1], "-V") != 0){
			fprintf(stderr, "Usage: %s '-u'(optional) '-V' input.data\n", argv[0]);
			exit(EXIT_FAILURE);
		}else{
			if(strcmp(argv[2], "-") == 0){
				in = stdin;
				printf("Using stdin for input\n");
			}else{
				in=fopen(argv[2], "r"); // opens file name for reading
				printf("Opened %s for input\n", argv[2]);
			}
			fgetsRetn = fgets(line, 1024, in);
			n = atoi(line); // parses the line for int value for vertices
			printf("n = %d\n", n);
			adjVertices_Vec = initEdgesV(n);
			fgetsRetn = fgets(line, 1024, in);
			while( fgetsRetn == line){
				EdgeV eV = parseEdgeV(line);
				intVecPush(adjVertices_Vec[eV.from], eV.to);
				m++;
				fgetsRetn = fgets(line, 1024, in);
			}
				
			if (! feof (in)) { /* some error occurred */ }
			printf("m = %d\n",m);
			puts("----------ORIGINAL GRAPH---------------");
			printGraphV(adjVertices_Vec, n); // print original graph

			// PHASE 1

			// Helper function
			IntVec* copyVec(IntVec* origVec, int num){
				IntVec* copyOfVec = initEdgesV(num);
				for(int index = 1; index<=num; index++){
					if(origVec[index] != NULL){
						int size = intSize(origVec[index]); // how many elements the vertex is pointing to
						int realSize = size-1;
						for(int f = realSize; f>=0; f--){
							int temp = intData(origVec[index], f);
							intVecPush(copyOfVec[index],temp);
						}
					}
				}
				return copyOfVec;
			}

			copiedVec = copyVec(adjVertices_Vec,n);
			puts("-----------TABLES--------------");
			IntVec* FinishStack1 = dfsSweep1(adjVertices_Vec, n, undirectedOn);
			// prints out stack
			//puts("------------STACK-----------");
			printf("FSTK: ");
			printStack(FinishStack1);
			printf("\n");

			// TRANSPOSE
			IntVec* transposeGraph(IntVec* origGraph, int num){
				IntVec* transGraph = initEdgesV(num);
				int size;
				int movingElement;
				for(int index = 1 ; index<= num; index++){
					if(origGraph[index] != NULL){
						size = intSize(origGraph[index]);
						int realSize = size-1;
						for(int f = realSize; f>=0; f-- ){
							movingElement = intData(origGraph[index],f);
							intVecPush(transGraph[movingElement],index);
						}
					}
				}
				return transGraph;
			}
			IntVec* transposedGraph = transposeGraph(copiedVec, n);
			puts("---------TRANSPOSED GRAPH--------------");
			printGraphV(transposedGraph,n);
			// PHASE 2

			copiedTransGraph = copyVec(transposedGraph,n);
			puts("----------SECOND TABLES----------------");
			dfsSweep2(copiedTransGraph, n, FinishStack1, undirectedOn);

			free(adjVertices_Vec);
			free(transposedGraph);
			free(FinishStack1);
			free(copiedVec);
			free(copiedTransGraph);
			return(EXIT_SUCCESS);
			}
// ------------------------------------------------------------------------------
		}else if(numberOfArgs == 4){ // if user wants undirected
			if(strcmp(argv[1], "-u") == 0){ // first case: if -u is like: scc03 -u
				undirectedOn = 1; // used for readability
				if(strcmp(argv[2], "-V") == 0){ // then check for -V
					if(strcmp(argv[3], "-") == 0){
						in = stdin;
						printf("Using stdin for input\n");
					}else{
						in=fopen(argv[3], "r"); // opens file name for reading
						printf("Opened %s for input\n", argv[3]);
					}
					fgetsRetn = fgets(line, 1024, in);
					n = atoi(line); // parses the line for int value for vertices
					printf("n = %d\n", n);
					adjVertices_Vec = initEdgesV(n);
					fgetsRetn = fgets(line, 1024, in);
					while( fgetsRetn == line){
						EdgeV eV = parseEdgeV(line);
						intVecPush(adjVertices_Vec[eV.from], eV.to);
						intVecPush(adjVertices_Vec[eV.to], eV.from);
						m++;
						fgetsRetn = fgets(line, 1024, in);
					}
						
					if (! feof (in)) { /* some error occurred */ }
					printf("m = %d\n",m);
					puts("----------ORIGINAL GRAPH---------------");
					printGraphV(adjVertices_Vec, n); // print original graph

					// PHASE 1

					// Helper function
					IntVec* copyVec(IntVec* origVec, int num){
						IntVec* copyOfVec = initEdgesV(num);
						for(int index = 1; index<=num; index++){
							if(origVec[index] != NULL){
								int size = intSize(origVec[index]); // how many elements the vertex is pointing to
								int realSize = size-1;
								for(int f = realSize; f>=0; f--){
									int temp = intData(origVec[index], f);
									intVecPush(copyOfVec[index],temp);
								}
							}
						}
						return copyOfVec;
					}

					copiedVec = copyVec(adjVertices_Vec,n);
					puts("-----------TABLES--------------");
					IntVec* FinishStack1 = dfsSweep1(adjVertices_Vec, n, undirectedOn);
					// prints out stack
					//puts("------------STACK-----------");
					printf("FSTK: ");
					printStack(FinishStack1);
					printf("\n");

					// TRANSPOSE
					IntVec* transposeGraph(IntVec* origGraph, int num){
						IntVec* transGraph = initEdgesV(num);
						int size;
						int movingElement;
						for(int index = 1 ; index<= num; index++){
							if(origGraph[index] != NULL){
								size = intSize(origGraph[index]);
								int realSize = size-1;
								for(int f = realSize; f>=0; f-- ){
									movingElement = intData(origGraph[index],f);
									intVecPush(transGraph[movingElement],index);
								}
							}
						}
						return transGraph;
					}
					IntVec* transposedGraph = transposeGraph(copiedVec, n);
					puts("---------TRANSPOSED GRAPH--------------");
					printGraphV(transposedGraph,n);
					// PHASE 2

					copiedTransGraph = copyVec(transposedGraph,n);
					puts("----------SECOND TABLES----------------");
					dfsSweep2(copiedTransGraph, n, FinishStack1, undirectedOn);

					free(adjVertices_Vec);
					free(transposedGraph);
					free(FinishStack1);
					free(copiedVec);
					free(copiedTransGraph);
					return(EXIT_SUCCESS);
				}else{
					fprintf(stderr, "Usage: %s '-u'(optional) '-V' input.data\n", argv[0]);
					exit(EXIT_FAILURE);
				}
			//---------------------------------------------------------------------------------
			}else if(strcmp(argv[2], "-u")== 0){ // second case: if -u is like scc03 -V -u
				undirectedOn = 1;
				if(strcmp(argv[1], "-V")==0){ // then check previous for -V
					// do all that
					if(strcmp(argv[3], "-") == 0){
						in = stdin;
						printf("Using stdin for input\n");
					}else{
						in=fopen(argv[3], "r"); // opens file name for reading
						printf("Opened %s for input\n", argv[3]);
					}
					fgetsRetn = fgets(line, 1024, in);
					n = atoi(line); // parses the line for int value for vertices
					printf("n = %d\n", n);
					adjVertices_Vec = initEdgesV(n);
					fgetsRetn = fgets(line, 1024, in);
					while( fgetsRetn == line){
						EdgeV eV = parseEdgeV(line);
						intVecPush(adjVertices_Vec[eV.from], eV.to);
						intVecPush(adjVertices_Vec[eV.to], eV.from);
						m++;
						fgetsRetn = fgets(line, 1024, in);
					}
						
					if (! feof (in)) { /* some error occurred */ }
					printf("m = %d\n",m);
					puts("----------ORIGINAL GRAPH---------------");
					printGraphV(adjVertices_Vec, n); // print original graph

					// PHASE 1

					// Helper function
					IntVec* copyVec(IntVec* origVec, int num){
						IntVec* copyOfVec = initEdgesV(num);
						for(int index = 1; index<=num; index++){
							if(origVec[index] != NULL){
								int size = intSize(origVec[index]); // how many elements the vertex is pointing to
								int realSize = size-1;
								for(int f = realSize; f>=0; f--){
									int temp = intData(origVec[index], f);
									intVecPush(copyOfVec[index],temp);
								}
							}
						}
						return copyOfVec;
					}

					copiedVec = copyVec(adjVertices_Vec,n);
					puts("-----------TABLES--------------");
					IntVec* FinishStack1 = dfsSweep1(adjVertices_Vec, n, undirectedOn);
					// prints out stack
					//puts("------------STACK-----------");
					printf("FSTK: ");
					printStack(FinishStack1);
					printf("\n");

					// TRANSPOSE
					IntVec* transposeGraph(IntVec* origGraph, int num){
						IntVec* transGraph = initEdgesV(num);
						int size;
						int movingElement;
						for(int index = 1 ; index<= num; index++){
							if(origGraph[index] != NULL){
								size = intSize(origGraph[index]);
								int realSize = size-1;
								for(int f = realSize; f>=0; f-- ){
									movingElement = intData(origGraph[index],f);
									intVecPush(transGraph[movingElement],index);
								}
							}
						}
						return transGraph;
					}
					IntVec* transposedGraph = transposeGraph(copiedVec, n);
					puts("---------TRANSPOSED GRAPH--------------");
					printGraphV(transposedGraph,n);
					// PHASE 2

					copiedTransGraph = copyVec(transposedGraph,n);
					puts("----------SECOND TABLES----------------");
					dfsSweep2(copiedTransGraph, n, FinishStack1, undirectedOn);

					free(adjVertices_Vec);
					free(transposedGraph);
					free(FinishStack1);
					free(copiedVec);
					free(copiedTransGraph);
					return(EXIT_SUCCESS);
//---------------------------------------------------------------------------------------
				}else{
					fprintf(stderr, "Usage: %s '-u'(optional) '-V' input.data\n", argv[0]);
					exit(EXIT_FAILURE);
				}
			}else{
				fprintf(stderr, "Usage: %s '-u'(optional) '-V' input.data\n", argv[0]);
				exit(EXIT_FAILURE);
			}
		}else{ // no other option
			fprintf(stderr, "Usage: %s '-u'(optional) '-V' input.data\n", argv[0]);
			exit(EXIT_FAILURE);
		}





}


	

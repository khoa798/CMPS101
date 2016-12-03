#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include "edgeVec.h"
#include "loadWgtGraph.h"
#include "minPQ.h"



int main(int argc, char* argv[]){

double calcPriority(int taskCP, MinPQ pqCP, int v, double wgtCP){
	if (taskCP == 'P'){
		return wgtCP;
	}else{
		double myDist = getPriority(pqCP, v);
		return (myDist + wgtCP);
	}
}


void updateFringe(int taskUF, MinPQ pqUF, EdgeVec* adjInfoOfV, int v){
	// See if a better connection is found to any vertex in the list adjInfoOfV, and decreaseKey if so.
	// For a new connection. insert the vertex. -As quoted from page 399 from Textbook

	EdgeVec remAdj;
	remAdj = (EdgeVec) adjInfoOfV;

	while (edgeSize(remAdj) > 0){
		EdgeInfo wInfo = edgeTop(remAdj);
		int w = wInfo.to;
		double newWgt = wInfo.wgt;
		double newPriority = calcPriority(taskUF, pqUF, v, newWgt);
		if(getStatus(pqUF, w) == UNSEEN){
			insertPQ(pqUF, w, newPriority, v);
		}else if(getStatus(pqUF,w) == FRINGE){
			if(newPriority < getPriority(pqUF, w)){
				decreaseKey(pqUF, w, newPriority, v);
			}
		}
		edgeVecPop(remAdj);

	}


}
void greedyTree(int taskGT, EdgeVec* adjInfo , int numberOfVerticesGT, int startVertexGT, int* statusGT, double* fringeWgtGT, int* parentGT){
	MinPQ pqGT = createPQ(numberOfVerticesGT, statusGT, fringeWgtGT, parentGT);
	insertPQ(pqGT, startVertexGT, 0.0, -1);
	while(isEmptyPQ(pqGT)==0){
		int b = getMin(pqGT);
		delMin(pqGT);
		updateFringe(taskGT, pqGT, (EdgeVec*)adjInfo[b], b);
	}
	//free(pqGT);
}
	

	if (argc != 4){
		fprintf(stderr, "Usage: greedy04 -task starting(vertex) input.in\n");
		exit(0);
	}

	int task;
	if (strcmp(argv[1], "-P") == 0){
		task = 'P';
		
		puts("Implementing Prim's Algorithm.");
		puts("--------------------------------");
	}else if(strcmp(argv[1], "-D") == 0){
		task = 'D';
		puts("Implementing Dijkstra's Algorithm.");
		puts("--------------------------------");

	}else{
		fprintf(stderr, "Invalid task. (Use -P or -D)\n");
		exit(1);
	}

	FILE* in;
	//int m = 0; // represents edges
	int numberOfVertices = 0; // represents vertices
	char line[1024];
	char* fgetsRetn;

	if(strcmp(argv[3], "-") == 0){
		in = stdin;
	}else{
		in = open_file(argv[3]);
	}

	fgetsRetn = fgets(line, 1024, in);
	if (!fgetsRetn){
		fprintf(stderr, "File is empty\n");
	}

	numberOfVertices = parseN(line); // parses the line for int value for vertices

	// gets the start vertex
	int startVertex = atoi(argv[2]);

	if (startVertex>numberOfVertices || startVertex<=0){
		fprintf(stderr, "Invalid start vertex.\n");
		exit(1);
	}

	// Create the adjacency lists
	EdgeVec* adjInfos;
	EdgeVec* adjInfosCopy;
	adjInfos = initEdges(numberOfVertices);
	adjInfosCopy = initEdges(numberOfVertices);

	while(fgets(line, 1024, in)){
		loadEdges(line,adjInfos, numberOfVertices,task);
		loadEdges(line,adjInfosCopy, numberOfVertices,task);
	}
	
	

	puts("-----------------------ORIGINAL GRAPH------------------");
	printGraph(adjInfosCopy, numberOfVertices);

	// Initialize all the arrays
	int* status = (int*)malloc((numberOfVertices+1)*sizeof(int));
	int* parent = (int*)malloc((numberOfVertices+1)*sizeof(int));
	double* fringeWgt = (double*)malloc((numberOfVertices+1)*sizeof(double));

	// Use Prim's Algorithm or Dijkstra's algorithm based on task.
	greedyTree(task, adjInfos, numberOfVertices, startVertex, status, fringeWgt, parent);


	// print out the result
	printOutput(numberOfVertices, status, fringeWgt, parent);



	return 0;



}


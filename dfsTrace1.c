#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include<unistd.h>
#include "dfsTrace1.h"
int time = 0;


// Depth First Search

int *dfsColor(int p){
	int * color =(int*)malloc((p+1)*sizeof(int));

	// set all vertices to be initially white
	int b;
	for (b = 1; b<= p; b++){
		color[b] = white;
	}
	return color;
}

int *dfsDiscoverTime(int p){
	int* discoveredTime = (int*) malloc ((p+1)*sizeof(int));
	// set all discover times to be initially 0
	int b;
	for (b = 1; b <= p; b++){
		discoveredTime[b] = 0;
	}
	return discoveredTime;
}

int *dfsFinishTime(int p){
	int* finishedTime = (int*)malloc((p+1)*sizeof(int));
	// set all finish times to be initially 0
	int b;
	for (b = 1; b <= p; b++){
		finishedTime[b] = 0;
	}
	return finishedTime;
}

int *dfsParent(int p){
	int* parents = (int*)malloc((p+1)*sizeof(int));
	// set all parents to be no parents, initially -1
	int b;
	for (b = 1; b <= p; b++){
		parents[b] = -1;
	}
	return parents;
}


void printTables(int p, int* color, int* discoveredTime, int* finishedTime, int* parents, int tableIndex){
	int b;

	printf("V\t color%d\t dTime%d\t fTime%d\t parent%d\t \n", tableIndex, tableIndex, tableIndex, tableIndex);
	for(b = 1; b <= p; b++){
		printf("%d \t ",b); // print out vertex
		int i = color[b];
		char* printColor;
		if(i == white){
			printColor = "W";
			printf("%s \t ", printColor);
		}else if(i == gray){
			printColor = "G";
			printf("%s \t ", printColor);
		}else{ 
			printColor = "B";
			printf("%s \t ", printColor);
		}


		printf("%d \t ", discoveredTime[b]); // print out discoveredTime
		printf("%d \t ", finishedTime[b]); // print out finishedTime
		printf("%d \t ", parents[b]); // print out parents
		printf("\n");
	}

}

void printTables2(int p, int* color, int* discoveredTime, int* finishedTime, int* parents, int tableIndex, int* roots){
	int b;

	printf("V\t color%d\t dTime%d\t fTime%d\t parent%d dfstRoot2\t \n", tableIndex, tableIndex, tableIndex, tableIndex);
	for(b = 1; b <= p; b++){
		printf("%d \t ",b); // print out vertex
		int i = color[b];
		char* printColor;
		if(i == white){
			printColor = "W";
			printf("%s \t ", printColor);
		}else if(i == gray){
			printColor = "G";
			printf("%s \t ", printColor);
		}else{ 
			printColor = "B";
			printf("%s \t ", printColor);
		}


		printf("%d \t ", discoveredTime[b]); // print out discoveredTime
		printf("%d \t ", finishedTime[b]); // print out finishedTime
		printf("%d \t ", parents[b]); // print out parents
		printf("%d \t ", roots[b]); // print out roots for phase 2
		printf("\n");
	}

}


IntVec* dfsSweep1(IntVec* adjVertices, int b, int undirectedOn){
	int* color, *discoveryTime1, *finishTime1, *parent1;
	color = dfsColor(b);
	finishTime1 = dfsFinishTime(b);;
	discoveryTime1 = dfsDiscoverTime(b);
	parent1 = dfsParent(b);
	IntVec* stack1 = (IntVec*)calloc(1,sizeof(IntVec));
	stack1[0] = intMakeEmptyVec();
	IntVec* returnedStack =(IntVec*)stack1[0];

	int p;
	for(p = 1; p<= b; p++){
		if (color[p] == white){
			dfsTrace1(adjVertices, p, color, discoveryTime1, finishTime1, parent1, returnedStack, undirectedOn, p);
		}
	}
	printTables(b, color, discoveryTime1, finishTime1, parent1, 1);

	free(color);
	free(discoveryTime1);
	free(finishTime1);
	free(parent1);
	return returnedStack;

}

void dfsTrace1(IntVec* adjVertices, int v, int* color, int* discoverTime, int* finishTime,\
				int* parent, IntVec* finishStk1, int undirectedOn, int h){
	int w;
	IntVec* remAdj;
	color[v] = gray;
	++time;
	int nextEdge = 1;
	discoverTime[v] = time;
	remAdj = (IntVec*)adjVertices[v];
	int temp = intSize(remAdj);
	if( (temp) > 0){
		while(remAdj != NULL && nextEdge != -1 ){
			if( undirectedOn == 0){
				w = intData(remAdj, temp-1);
				if (color[w] == white){
					parent[w] = v;
					dfsTrace1(adjVertices, w, color, discoverTime, finishTime,\
										parent, finishStk1, undirectedOn, h);
				}
				intVecPop(remAdj);
				temp = intSize(remAdj);
				nextEdge = intData(remAdj, temp-1);
				remAdj = adjVertices[nextEdge];
			}else{ //undirectedOn = 1(true)
				w = intData(remAdj, temp-1);
				if (color[w] == white){
					parent[w] = v;
					dfsTrace1(adjVertices, w, color, discoverTime, finishTime,\
										parent, finishStk1, undirectedOn, h);
				}else if(color[w] == gray && w != h){
					dfsTrace1(adjVertices, w, color, discoverTime, finishTime,\
									parent, finishStk1, undirectedOn, h);
				}
				intVecPop(remAdj);
				temp = intSize(remAdj);
				nextEdge = intData(remAdj, temp-1);
				remAdj = adjVertices[nextEdge];
			}

		} // while loop ends here
	}
	time++;
	finishTime[v] = time;
	color[v] = black;
	intVecPush(finishStk1, v);
	
}


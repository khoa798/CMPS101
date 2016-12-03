
#include<stdlib.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include "dfsPhase2.h"
int time2 = 0;
int leader;

int* dfsRoots(int n){
	int* dfsRoot = (int*)malloc((n+1)*sizeof(int));

	int p;

	for(p = 0; p<= n; p++ ){
		dfsRoot[p] = 0;
	}
	return dfsRoot;
}

void dfsTrace2(IntVec* adjacentTransGraph, int* color2, int v, int leader, int* scc, int* discoverTime2, int* finishTime2
	, int* parent2, int undirectedOn, int h){
	int w; 
	IntVec* remAdj;
	color2[v] = gray;
	scc[v] = leader;
	time2++;
	int nextEdge = 1;
	discoverTime2[v] = time2;
	remAdj = (IntVec*)adjacentTransGraph[v];
	int temp = intSize(remAdj);
	if( temp > 0){
		while(remAdj != NULL && nextEdge != -1 ){
			if( undirectedOn == 0){
				w = intData(remAdj, temp-1);
				if (color2[w] == white){
					parent2[w] = v;
					dfsTrace2(adjacentTransGraph, color2, w, leader, scc, discoverTime2, finishTime2
						, parent2, undirectedOn, h);
				}
				intVecPop(remAdj);
				temp = intSize(remAdj);
				nextEdge = intData(remAdj, temp-1);
				remAdj = adjacentTransGraph[nextEdge];
			}else{
				w = intData(remAdj, temp-1);
				if (color2[w] == white){
					parent2[w] = v;
					dfsTrace2(adjacentTransGraph, color2, w, leader, scc, discoverTime2, finishTime2
						, parent2, undirectedOn, h);
				}else if(color2[w] == gray && w!= h){
					dfsTrace2(adjacentTransGraph, color2, w, leader, scc, discoverTime2, finishTime2
						, parent2, undirectedOn, h);
				}
				intVecPop(remAdj);
				temp = intSize(remAdj);
				nextEdge = intData(remAdj, temp-1);
				remAdj = adjacentTransGraph[nextEdge];
			}
		}
	}
	time2++;
	finishTime2[v] = time2;
	color2[v] = black;

}

void dfsSweep2(IntVec* adjacentTransGraph, int n, IntVec* finishStack, int undirectedOn){
	int* color2, * discoverTime2, *finishTime2, *parent2;
	int * Root2;
	color2 = dfsColor(n);
	discoverTime2 = dfsDiscoverTime(n);
	finishTime2 = dfsFinishTime(n);
	parent2 = dfsParent(n);
	Root2 = dfsRoots(n);

	
	for (int k = n; k>0; k--){
		int a = intTop(finishStack);
		intVecPop(finishStack);
		if(a != -1){
			if(color2[a] == white){
				dfsTrace2(adjacentTransGraph, color2, a, a, Root2, discoverTime2,\
					finishTime2, parent2, undirectedOn,a);
			}
		}
	}

	printTables2(n, color2, discoverTime2, finishTime2, parent2, 2, Root2);

	free(color2);
	free(discoverTime2);
	free(finishTime2);
	free(parent2);
	free(Root2);


}







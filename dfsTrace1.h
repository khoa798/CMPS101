#ifndef DFS1
#define DFS1
#include "intVec.h"

# define white 1
# define gray 2
# define black 3


// Depth First Search

int *dfsColor(int);
int *dfsDiscoverTime(int);
int *dfsFinishTime(int);
int *dfsParent(int);
extern int nextInArray;

void printTables(int, int[], int[], int[], int[], int);
void printTables2(int, int[], int[], int[], int[], int, int[]);
IntVec* dfsSweep1(IntVec*, int, int);
void dfsTrace1(IntVec*, int, int[], int[], int[], int[], IntVec*, int, int);

#endif
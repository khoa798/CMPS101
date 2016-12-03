#ifndef loadGraphV
#define loadGraphV


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<assert.h>
#include "intVec.h"

typedef struct {
	int from;
	int to;
	double weight;
} EdgeV;


IntVec* initEdgesV(int);
EdgeV parseEdgeV(char*);
void printGraphV(IntVec[], int);
void printStack(IntVec*);



#endif
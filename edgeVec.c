// edgeVec.c

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include "edgeVec.h"



struct EdgeVecNode{
	EdgeInfo* data; // pointer to the data
	int sz; // how many elements are in the array
	int capacity; // length of the maximum array size
}EdgeVecNode;


const EdgeVec edgeNil = NULL;

// Returns the top element of the stack
EdgeInfo edgeTop(EdgeVec myVec){
	int printTop = (myVec->sz)-1;
	return (myVec->data[printTop]);
}

// Returns the EdgeInfo structure specified at the index, i
EdgeInfo edgeData(EdgeVec myVec, int i){
	return myVec->data[i];
}

// Returns the size of myVec construct
int edgeSize(EdgeVec myVec){
	return (myVec->sz);
}

// Returns the total amount that myVec can store
int edgeCapacity(EdgeVec myVec){
	return myVec->capacity;
}

// This function creates a new edgeVec in each table index for the program file
EdgeVec edgeMakeEmptyVec(void){
	EdgeVec newVec = calloc(1, sizeof(EdgeVecNode));
	assert(newVec != NULL);
	newVec->capacity = edgeInitCap;
	newVec->sz = 0;
	newVec->data = calloc(edgeInitCap, sizeof(EdgeVecNode)); // can change when array size is doubled
	return newVec;
}


// This function pushes a new element on top of the stack for the specified myVec
void edgeVecPush(EdgeVec myVec, EdgeInfo newE){
	int newCap;
	int* newData;
	int size;
	size = myVec->sz;

	if (size>=myVec->capacity){
		newCap = 2 * myVec->capacity;
		newData = realloc(myVec->data, newCap * sizeof(int));
		assert (newData != NULL);
		if (newData != myVec->data) { myVec->data = newData; }
		myVec->capacity = newCap;
	}
	myVec->data[size] = newE; // add in new element to end of the list
	myVec->sz++; // increment size	
}


void edgeVecPop(EdgeVec myVec){
	if (myVec->sz == 0){
		// do nothing
	}else{

		myVec->sz--;

	}
}




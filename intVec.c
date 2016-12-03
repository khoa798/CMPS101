/* intVec.c
 * Implementation of the header file for intVec ADT
 */

#ifndef C101IntVec
#define C101IntVec
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include "intVec.h"

/* Multiple typedefs for the same type are an error in C. */
 /* The above ifndef and define prevent multiple copies of code below.
 */

 
typedef struct IntVecNode{
	int* data; // pointer to the data
	int sz; // how many elements are in the array
	int capacity; // length of the maximum array size
} IntVecNode;
	
 
typedef IntVecNode * IntVec;


/** intInitCap: initial capacity after intMakeEmptyVec() */
static const int intInitCap = 4;

/* Access functions */

/** intTop()
 * precondition: myVec != NULL and myVec->sz != 0
 * peeks and returns the top element of the stack
 */
int intTop(IntVec myVec){
	if( myVec==NULL ){
		fprintf(stderr, 
			"IntVec Error: calling intTop() on NULL IntVec reference\n");
		exit(EXIT_FAILURE);
	}
	
	if(myVec->sz == 0){
		fprintf(stderr,
			"IntVec Error: calling intTop() on empty list\n");
		exit(EXIT_FAILURE);
	}
	int printTop = (myVec->sz)-1;
	return(myVec->data[printTop]);
}

/** intData()
 * precondition: 0 <= i < intSize(myVec).
 * returns data value of the index
 */
int intData(IntVec myVec, int i){
	int size = myVec->sz;
	if( i < 0 || i >= size ){
		fprintf(stderr,
			"IntVec Error: calling intData() on invalid index");
		exit(EXIT_FAILURE);
	}
	return myVec->data[i];
}

/** intSize()
 * precondition: myVec has been constructed.
 * returns how many elements are inside the stack.
 */
int intSize(IntVec myVec){
	if( myVec==NULL ){
		fprintf(stderr, 
			"IntVec Error: calling intSize() on NULL IntVec reference\n");
		exit(EXIT_FAILURE);
   }
	return(myVec->sz);
}

/** intCapacity()
 * precondition: myVec has been constructed.
 * returns the maximum size or length of the array / stack
 */
int intCapacity(IntVec myVec){
	if( myVec==NULL ){
		fprintf(stderr, 
		"IntVec Error: calling intCapacity() on NULL IntVec reference\n");
		exit(EXIT_FAILURE);
   }
	return(myVec->capacity);
}

/* Constructors */

/** intMakeEmptyVec()
 * preconditions: none.
 * postconditions: Let /return be the value returned by intMakeEmptyVec().
 *    Then intCapacity(/return) == 4, intSize(/return) == 0).
 */
IntVec intMakeEmptyVec(void){

	IntVec newVec = calloc(1, sizeof(IntVecNode));
	assert(newVec != NULL);
	newVec->capacity = intInitCap;
	newVec->sz = 0;
	newVec->data = calloc(intInitCap, sizeof(IntVecNode)); // can change when array size is doubled
	return newVec;
}


/* Manipulation Procedures */

/** intVecPush()
 * precondition: myVec has been constructed.
 * postconditions: Let /sz/ = intSize(myVec) before the call.
 *                 Let /cap/ = intCapacity(myVec) before the call.
 *    Then after the call, intSize(myVec) == /sz/+1,
 *        and intTop(myVec) == newE and intData(myVec, /sz/) == newE.
 *    Also, for all 0 <= i < /sz/: intData(myVec, i) is unchanged.
 *    Also, if (/sz/+1) > /cap/, then after the call,
 *        intCapacity(myVec) = 2 * /cap/.
 *    otherwise, intCapacity(myVec) is unchanged.
 */
void intVecPush(IntVec myVec, int newE){
	int newCap;
	int* newData;
	int size;
	if (myVec == NULL){
		fprintf(stderr,
			"IntVec Error: calling intVecPush() on NULL IntVec reference\n");
		exit(EXIT_FAILURE);
	}
	//adjVertices[e.from] = intCons(e.to, adjVertices[e.from]);
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

/** intVecPop()
 * precondition: myVec has been constructed and intSize(myVec) > 0.
 * postconditions: Let /sz/ = intSize(myVec) before the call.
 *                 Let /cap/ = intCapacity(myVec) before the call.
 *    Then after the call, intSize(myVec) == /sz/-1,
 *        intTop(myVec) == intData(/sz/-2).
 *    Also, for all 0 <= i < /sz/-1: intData(myVec, i) is unchanged.
 *    Also, intCapacity(myVec) is unchanged.
 */
void intVecPop(IntVec myVec){
	int size;
	if (myVec == NULL){
		fprintf(stderr,
			"IntVec Error: calling intVecPop() on NULL IntVec reference\n");
		exit(EXIT_FAILURE);
	}
	
	if (myVec->sz == 0){
		fprintf(stderr, 
			"IntVec Error: calling intVecPop() on empty IntVec list\n");
		exit(EXIT_FAILURE);
	}
	size = myVec->sz;
	
	myVec->data[size-1] = -1;
	myVec->sz--; // decrement size
	
	
}




#endif

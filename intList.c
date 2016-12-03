//INTLIST.C

/* intList.h
 *
 Implements the functions specified in the header file for intList ADT
 */

#ifndef C101IntList
#define C101IntList
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include "intList.h"
typedef char * Cstring;

/* Multiple typedefs for the same type are an error in C. */
 
typedef struct IntListNode{
	int element;
	struct IntListNode* next;
	
}IntListNode;

typedef IntListNode* IntList;

/** intNil denotes the empty IntList */
const IntList intNil = NULL;

/* Access functions
 * PRE: intList != NULL
 */

/** first
 PRE: oldL != NULL
  returns the first element in the intList
 */
int intFirst(IntList oldL){
	if(oldL != NULL){
		return oldL->element;
	}
	return -1;
}

/** rest
 * PRE: oldL != NULL
 returns the list containing all elements excluding the first element.
 */
IntList intRest(IntList oldL){
	if(oldL != NULL){
		return oldL->next;
	}
	
}

/* Constructors
 */

/** cons
Adds a new element to the front of the list 
and reconstructs the old list behind new element
PRE: none
POST: intList->element = newE and intList->rest = oldL
*/
IntList intCons(int newE, IntList oldL){
	IntList newList = calloc(1, sizeof(IntListNode));
	assert (newList != NULL);
	newList->element = newE;
	newList->next = oldL;
	return newList;
}

#endif


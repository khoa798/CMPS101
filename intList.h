//intlist .H

/* intList.h
 * Header file for the intList ADT
 */
 

#ifndef C101IntList
#define C101IntList
/* Multiple typedefs for the same type are an error in C. */

typedef struct IntListNode * IntList;

/** intNil denotes the empty IntList */
extern const IntList intNil;

/* Access functions
 * PRE: intList != NULLL
 */

/** first
 PRE: oldL != NULL
  returns the first element in the intList
 */
int intFirst(IntList oldL);

/** rest
 * PRE: oldL != NULL
 returns the list containing all elements excluding the first element.
 */
IntList intRest(IntList oldL);

/* Constructors
 */

/** cons
Adds a new element to the front of the list 
and reconstructs the old list behind new element
PRE: none
POST: intList->element = newE and intList->rest = oldL
 */
IntList intCons(int newE, IntList oldL);

#endif


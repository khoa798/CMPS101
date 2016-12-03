/* minPQ.h (what is the purpose of this file? Replace this question with your comment.)
*/
#include <stdlib.h>
#include <float.h> // for DBL_MAX
#include "minPQ.h"

/* Multiple typedefs for the same type are an error in C. */

struct MinPQNode{
	int numVertices; // total number of vertices
	int numPQ; // current number of vertices in priority queue
	int minVertex; // minVertex = -1 by default
	double oo; // infinity
	int* status;
	int* parent;
	double* fringeWgt;
};


/* ***************** Access functions */

/** , PRE: pq != NULL && 0<id<numVertices
*/

/** isEmpty
*/
int isEmptyPQ(MinPQ pq){
	if(pq->numPQ == 0){
		return 1;
	}
	return 0;
}

/** getMin
// returns fringe vertex with minimum weight
// returns -1 if there are no fringe vertex remaining
, PRE: pq != NULL && 0<id<numVertices
*/
int getMin(MinPQ pq){
	if(pq->minVertex == -1){
		int w;
		double minWgt = pq->oo;
		for (w = 1; w <= pq->numVertices; ++w){
			if(pq->status[w] == FRINGE){
				if(pq->fringeWgt[w] < minWgt){
					pq->minVertex = w;
					minWgt = pq->fringeWgt[w];
				}
			}
		}
	}
	return pq->minVertex;
}

/** getStatus
, PRE: pq != NULL && 0<id<numVertices
*/
int getStatus(MinPQ pq, int id){
	return pq->status[id];
}

/** getParent
, PRE: pq != NULL && 0<id<numVertices
*/
int getParent(MinPQ pq, int id){
	return pq->parent[id];
}

/** getPriority
, PRE: pq != NULL && 0<id<numVertices
*/
double getPriority(MinPQ pq, int id){
	return pq->fringeWgt[id];
}


/* ***************** Manipulation procedures */

/** delMin 
PRE: pq != NULL
POST: pq->numPQ  = -1
// Delete fringe vertex with min wgt from pq
*/
void delMin(MinPQ pq){
	int oldMin = getMin(pq);
	pq->status[oldMin] = INTREE;
	pq->minVertex = -1;
	pq->numPQ--;
}

/** insertPQ
PRE: pq != NULL
POST: pq->numPQ = +- 1
// Record newPar, par as parent, priority of id, and make status[id] = FRINGE
*/
void insertPQ(MinPQ pq, int id, double newW, int newPar){
	pq->parent[id] = newPar;
	pq->fringeWgt[id] = newW;
	pq->status[id] = FRINGE;
	pq->minVertex = -1;
	pq->numPQ++;
}

/** decreaseKey
PRE: pq != NULL
POST: pq->numPQ - 1
// Record newPar, newW as the parent, newW of id
*/
void decreaseKey(MinPQ pq, int id, double newW, int newPar){
	pq->parent[id] = newPar;
	pq->fringeWgt[id] = newW;
	pq->minVertex = -1;
}


/* ***************** Constructors */

/** createPQ
PRE: pq != NULL
POST: returns pointer to new PQ
*/
MinPQ createPQ(int n, int* status, double* priority, int* parent){
	MinPQ pq = (MinPQ) malloc(sizeof(struct MinPQNode));
	pq->parent = parent;
	pq->fringeWgt = priority;
	pq->status = status;
	pq->oo = DBL_MAX;
	pq->numVertices = n;
	pq->minVertex = -1;


	int i;
	for(i=1; i<=n; ++i){
		pq->status[i] = UNSEEN;
		pq->fringeWgt[i] = pq->oo;
		pq->parent[i] = -1;
	}
	return pq;
}





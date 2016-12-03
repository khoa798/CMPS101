/* minPQ.h (what is the purpose of this file? Replace this question with your comment.)
*/

#ifndef C101MinPQ
#define C101MinPQ
/* Multiple typedefs for the same type are an error in C. */

typedef struct MinPQNode * MinPQ;

#define UNSEEN ('u')
#define FRINGE ('f')
#define INTREE ('t')

/* ***************** Access functions */

/** Preconditions: pq has been constructed and != NULL
*/

/** isEmpty
*/ // Preconditions: pq has been constructed and != NULL
int isEmptyPQ(MinPQ pq);

/** getMin
*/ // Preconditions: pq has been constructed and != NULL
int getMin(MinPQ pq);

/** getStatus
*/ // Preconditions: pq has been constructed and != NULL && id is between 0 and numberOfVertices
int getStatus(MinPQ pq, int id);

/** getParent
*/// Preconditions: pq has been constructed and != NULL && id is between 0 and numberOfVertices
int getParent(MinPQ pq, int id);

/** getPriority
*/// Preconditions: pq has been constructed and != NULL && id is between 0 and numberOfVertices
double getPriority(MinPQ pq, int id);


/* ***************** Manipulation procedures */

/** delMin 
*/// Preconditions: pq has been constructed and != NULL && id is between 0 and numberOfVertices 
void delMin(MinPQ pq);

/** insertPQ 
*/ // Preconditions: pq has been constructed and != NULL && id is between 0 and numberOfVertices
void insertPQ(MinPQ pq, int id, double priority, int par);

/** decreaseKey
*/ // Preconditions: pq has been constructed and != NULL && id is between 0 and numberOfVertices
// pq's priority and par of ID has been changed
void decreaseKey(MinPQ pq, int id, double priority, int par);


/* ***************** Constructors */

/** createPQ
*/ // Preconditions: pq has been constructed and != NULL && id is between 0 and numberOfVertices
// Post: returns a pointer to pq
MinPQ createPQ(int n, int status[], double priority[], int parent[]);


#endif


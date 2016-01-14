#ifndef BIOINF_SUFFIKS_TREE_UKKONEN_CONSTANTS_H
#define BIOINF_SUFFIKS_TREE_UKKONEN_CONSTANTS_H

/**
 * The maximum input string length this program
 * will handle is defined here.  A suffix tree
 * can have as many as 2N edges/nodes.  The edges
 * are stored in a hash table, whose size is also
 * defined here.
*/
#define MAX_LENGTH 1000000
#define HASH_TABLE_SIZE 1300000

#include "Edge.h"
#include "Node.h"

/**
 * This is the hash table where all the currently
 * defined edges are stored. Edges whose start_node
 * is not -1 are printable.
*/
extern Edge Edges[HASH_TABLE_SIZE];

/* Input sequence read from file. */
extern char Sequence[MAX_LENGTH];

/* Length of input sequence. */
extern int Length;


/* The array of defined nodes. */
extern Node Nodes[MAX_LENGTH * 2];

#endif //BIOINF_SUFFIKS_TREE_UKKONEN_CONSTANTS_H

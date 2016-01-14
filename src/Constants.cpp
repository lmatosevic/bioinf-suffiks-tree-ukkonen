#include "../include/Constants.h"

Edge Edges[HASH_TABLE_SIZE];

char Sequence[MAX_LENGTH];

int Length;

Node Nodes[MAX_LENGTH * 2];

/* The count is 1 at the start because the initial tree has the root node
 * defined, with no children. */
int Node::Count = 1;
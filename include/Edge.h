#ifndef BIOINF_SUFFIKS_TREE_UKKONEN_EDGE_H
#define BIOINF_SUFFIKS_TREE_UKKONEN_EDGE_H

#include "Suffix.h"

/**
 * The suffix tree is made up of edges connecting nodes. Each edge
 * represents a string of characters starting at first_char_index and
 * ending at last_char_index. Edges can be inserted and removed from a hash table,
 * based on the Hash() function defined here.  The hash table indicates
 * an unused slot by setting the start_node value to -1.
 */
class Edge {
public :
    int first_char_index;
    int last_char_index;
    int end_node;
    int start_node;

    void Insert();

    void Remove();

    Edge();

    Edge(int init_first_char_index,
         int init_last_char_index,
         int parent_node);

    int SplitEdge(Suffix &s);

    static Edge Find(int node, int c);

    static int Hash(int node, int c);
};


#endif //BIOINF_SUFFIKS_TREE_UKKONEN_EDGE_H

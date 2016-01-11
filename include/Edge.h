//
// Created by luka on 11.01.16..
//

#ifndef BIOINF_SUFFIKS_TREE_UKKONEN_EDGE_H
#define BIOINF_SUFFIKS_TREE_UKKONEN_EDGE_H

#include "Suffix.h"

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

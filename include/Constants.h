//
// Created by luka on 11.01.16..
//

#ifndef BIOINF_SUFFIKS_TREE_UKKONEN_CONSTANTS_H
#define BIOINF_SUFFIKS_TREE_UKKONEN_CONSTANTS_H

#define MAX_LENGTH 1000000
#define HASH_TABLE_SIZE 4096

#include "Edge.h"
#include "Node.h"

extern Edge Edges[HASH_TABLE_SIZE];

extern char T[MAX_LENGTH];

extern int N;

extern Node Nodes[MAX_LENGTH * 2];

#endif //BIOINF_SUFFIKS_TREE_UKKONEN_CONSTANTS_H

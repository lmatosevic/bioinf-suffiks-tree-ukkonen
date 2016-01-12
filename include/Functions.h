//
// Created by luka on 12.01.16..
//

#ifndef BIOINF_SUFFIKS_TREE_UKKONEN_FUNCTIONS_H
#define BIOINF_SUFFIKS_TREE_UKKONEN_FUNCTIONS_H

#include "Suffix.h"

void dump_edges(int current_n);

void AddPrefix(Suffix &active, int last_char_index);

int walk_tree(int start_node, int last_char_so_far);

void validate();

#endif //BIOINF_SUFFIKS_TREE_UKKONEN_FUNCTIONS_H

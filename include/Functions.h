#ifndef BIOINF_SUFFIKS_TREE_UKKONEN_FUNCTIONS_H
#define BIOINF_SUFFIKS_TREE_UKKONEN_FUNCTIONS_H

#include <string.h>
#include "Suffix.h"

using std::string;
using std::ofstream;

void print_edges(int current_n, ofstream& file);

void AddPrefix(Suffix &active, int last_char_index);

int walk_tree(int start_node, int last_char_so_far, ofstream& file);

void validate(ofstream& file);

#endif //BIOINF_SUFFIKS_TREE_UKKONEN_FUNCTIONS_H

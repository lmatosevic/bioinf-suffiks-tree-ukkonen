#include "../include/Suffix.h"
#include "../include/Edge.h"
#include "../include/Constants.h"


Suffix::Suffix(int node, int start, int stop) {
    origin_node = node;
    first_char_index = start;
    last_char_index = stop;
}

// Check if suffix is explicit
int Suffix::Explicit() {
    return first_char_index > last_char_index;
}

// Check if suffix is implicit
int Suffix::Implicit() {
    return last_char_index >= first_char_index;
}

/**
 * A suffix in the tree is marked by a Suffix structure that marks
 * its last character. The cannonical representation of a suffix for this algorithm requires
 * that the origin_node by the closest noode to the end of the tree.
 * To force this to be true needs to slide down every edge in the current path until
 * last node.
 */
void Suffix::Canonize() {
    if (!Explicit()) {
        Edge edge = Edge::Find(origin_node, Sequence[first_char_index]);
        int edge_span = edge.last_char_index - edge.first_char_index;
        while (edge_span <= (last_char_index - first_char_index)) {
            first_char_index = first_char_index + edge_span + 1;
            origin_node = edge.end_node;
            if (first_char_index <= last_char_index) {
                edge = Edge::Find(edge.end_node, Sequence[first_char_index]);
                edge_span = edge.last_char_index - edge.first_char_index;
            };
        }
    }
}
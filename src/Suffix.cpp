#include "../include/Suffix.h"
#include "../include/Edge.h"
#include "../include/Constants.h"

Suffix::Suffix(int node, int start, int stop) {
    origin_node = node;
    first_char_index = start;
    last_char_index = stop;
}

int Suffix::Explicit() {
    return first_char_index > last_char_index;
}

int Suffix::Implicit() {
    return last_char_index >= first_char_index;
}

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
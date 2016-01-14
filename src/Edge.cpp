#include "../include/Edge.h"
#include "../include/Node.h"
#include "../include/Constants.h"

Edge::Edge() {
    start_node = -1;
}

Edge::Edge(int init_first, int init_last, int parent_node) {
    first_char_index = init_first;
    last_char_index = init_last;
    start_node = parent_node;
    end_node = Node::Count++;
}

int Edge::Hash(int node, int c) {
    return ((node << 8) + c) % HASH_TABLE_SIZE;
}

void Edge::Insert() {
    int i = Hash(start_node, Sequence[first_char_index]);
    while (Edges[i].start_node != -1)
        i = ++i % HASH_TABLE_SIZE;
    Edges[i] = *this;
}

void Edge::Remove() {
    int i = Hash(start_node, Sequence[first_char_index]);
    while (Edges[i].start_node != start_node ||
           Edges[i].first_char_index != first_char_index)
        i = ++i % HASH_TABLE_SIZE;
    for (; ;) {
        Edges[i].start_node = -1;
        int j = i;
        for (; ;) {
            i = ++i % HASH_TABLE_SIZE;
            if (Edges[i].start_node == -1)
                return;
            int r = Hash(Edges[i].start_node, Sequence[Edges[i].first_char_index]);
            if (i >= r && r > j)
                continue;
            if (r > j && j > i)
                continue;
            if (j > i && i >= r)
                continue;
            break;
        }
        Edges[j] = Edges[i];
    }
}

Edge Edge::Find(int node, int c) {
    int i = Hash(node, c);
    for (; ;) {
        if (Edges[i].start_node == node) if (c == Sequence[Edges[i].first_char_index])
            return Edges[i];
        if (Edges[i].start_node == -1)
            return Edges[i];
        i = ++i % HASH_TABLE_SIZE;
    }
}

int Edge::SplitEdge(Suffix &s) {
    Remove();
    Edge *new_edge =
            new Edge(first_char_index,
                     first_char_index + s.last_char_index - s.first_char_index,
                     s.origin_node);
    new_edge->Insert();
    Nodes[new_edge->end_node].suffix_node = s.origin_node;
    first_char_index += s.last_char_index - s.first_char_index + 1;
    start_node = new_edge->end_node;
    Insert();
    return new_edge->end_node;
}

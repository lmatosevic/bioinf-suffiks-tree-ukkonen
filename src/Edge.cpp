#include "../include/Edge.h"
#include "../include/Node.h"
#include "../include/Constants.h"

/**
 * The default constructor for class Edge sets start_node to the invalid value.
 * This  guarantees that the hash table is initially filled with unused edges.
*/
Edge::Edge() {
    start_node = -1;
}

/**
 * Construct new edges in the program while walking up
 * the set of suffixes from the active point to the
 * endpoint. Each time a new edge is created, add a new node for its end point.
 * The node entry is already present in the Nodes[] array, and its
 * suffix node is set to -1 by the default constructor.
*/
Edge::Edge(int init_first, int init_last, int parent_node) {
    first_char_index = init_first;
    last_char_index = init_last;
    start_node = parent_node;
    end_node = Node::Count++;
}

// Method for calculating hash code which is used for storing edges.
int Edge::Hash(int node, int c) {
    return ((node << 8) + c) % HASH_TABLE_SIZE;
}

// Insert new edge in hashtable using Hash function.
void Edge::Insert() {
    int i = Hash(start_node, Sequence[first_char_index]);
    while (Edges[i].start_node != -1)
        i = ++i % HASH_TABLE_SIZE;
    Edges[i] = *this;
}

/* *
 * Removes edge from hashtable(Eges). When edge is removed, all gaps need to be
 * translated forward so other edges can be found using Find method.
 */
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

/**
 * The whole reason for storing edges in a hash table is that it
 * makes this function fairly efficient.  When I want to find a
 * particular edge leading out of a particular node, I call this
 * function.  It locates the edge in the hash table, and returns
 * a copy of it.  If the edge is not found, the edge that is returned
 * to the caller will have start_node set to -1, which is the value
 * used in the hash table to flag an unused entry.
*/
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

/**
 * When a suffix ends on an implicit node, adding a new character
 * means spliting existing edge. This function is called
 * to split an edge at the point defnied by the suffix argument.
 * The existing edge loses its parent, as well as some of its leading
 * characters. New edge descends from the original parent,
 * and now has the existing edge as a child.
 * Since the existing edge is getting a new parent and starting
 * character, its hash table entry will no longer be valid. SO it must be
 * removed at the start of the function.  After the parent and start character
 * have been recalculated, it is inserted again.
 * The number of characters stolen from the original node and givn
 * to the new node is equal to the number of characters in the suffix
 * argument and it is (last - first + 1);
 */
int Edge::SplitEdge(Suffix &s) {
    Remove();
    Edge *new_edge = new Edge(first_char_index,
                              first_char_index + s.last_char_index - s.first_char_index,
                              s.origin_node);
    new_edge->Insert();
    Nodes[new_edge->end_node].suffix_node = s.origin_node;
    first_char_index += s.last_char_index - s.first_char_index + 1;
    start_node = new_edge->end_node;
    Insert();
    return new_edge->end_node;
}

#ifndef BIOINF_SUFFIKS_TREE_UKKONEN_NODE_H
#define BIOINF_SUFFIKS_TREE_UKKONEN_NODE_H

/**
 * Only information contained in a node is the suffix link.
 * Each suffix in the tree that ends at a particular node can find
 * the next smaller suffix by following the suffix_node link to a new node.
 * Nodes are stored in a simple one dimensional array.
 */
class Node {
public :
    int suffix_node;
    static int Count;

    Node();
};


#endif //BIOINF_SUFFIKS_TREE_UKKONEN_NODE_H

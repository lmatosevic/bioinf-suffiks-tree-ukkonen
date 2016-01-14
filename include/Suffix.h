#ifndef BIOINF_SUFFIKS_TREE_UKKONEN_SUFFIX_H
#define BIOINF_SUFFIKS_TREE_UKKONEN_SUFFIX_H

/**
 * This structure defines a Suffix by its final character.
 * In the canonical representation is defined that las tcharacter
 * by starting at a node in the tree, and following a string of characters,
 * represented by first_char_index and last_char_index.
 * If suffix ends at a node, there are no additional characters
 * needed to characterize its last character position then node is Explicit,
 * and set first_char_index > last_char_index to mark that.
 */
class Suffix {
public :
    int origin_node;
    int first_char_index;
    int last_char_index;

    Suffix(int node, int start, int stop);

    int Explicit();

    int Implicit();

    void Canonize();
};


#endif //BIOINF_SUFFIKS_TREE_UKKONEN_SUFFIX_H

#ifndef BIOINF_SUFFIKS_TREE_UKKONEN_SUFFIX_H
#define BIOINF_SUFFIKS_TREE_UKKONEN_SUFFIX_H


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

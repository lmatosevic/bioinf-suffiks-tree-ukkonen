//
// Created by luka on 11.01.16..
//

#ifndef BIOINF_SUFFIKS_TREE_UKKONEN_SUFFIX_H
#define BIOINF_SUFFIKS_TREE_UKKONEN_SUFFIX_H


class Suffix {
public :
    int origin_node;
    int first_char_index;
    int last_char_index;
    Suffix( int node, int start, int stop )
            : origin_node( node ),
              first_char_index( start ),
              last_char_index( stop ){};
    int Explicit(){ return first_char_index > last_char_index; }
    int Implicit(){ return last_char_index >= first_char_index; }
    void Canonize();
};


#endif //BIOINF_SUFFIKS_TREE_UKKONEN_SUFFIX_H

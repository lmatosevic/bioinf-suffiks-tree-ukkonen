#include <iostream>
#include <iomanip>
#include <string.h>
#include <cstdlib>
#include <fstream>

#include "../include/Functions.h"
#include "../include/Edge.h"
#include "../include/Node.h"
#include "../include/Constants.h"

using std::cout;
using std::setw;
using std::cerr;
using std::endl;
using std::ofstream;

/**
 * This function prints out the contents of the suffix tree by walking through the
 * hash table and printing out all used edges. It provides next infomration:
 * Start - starting node index
 * End - ending node index
 * Suf - suffix node index
 * First - index of first char in sequence
 * Last - index of last char in sequence
 * String - content of suffix
 */
void print_edges(int current_n, ofstream &file) {
    cout << " Start  End  Suf  First  Last  String\n";
    file << " Start  End  Suf  First  Last  String\n";
    for (int j = 0; j < HASH_TABLE_SIZE; j++) {
        Edge *s = Edges + j;
        if (s->start_node == -1)
            continue;
        cout << setw(5) << s->start_node << " "
        << setw(5) << s->end_node << " "
        << setw(3) << Nodes[s->end_node].suffix_node << " "
        << setw(5) << s->first_char_index << " "
        << setw(6) << s->last_char_index << "  ";
        file << setw(5) << s->start_node << " "
        << setw(5) << s->end_node << " "
        << setw(3) << Nodes[s->end_node].suffix_node << " "
        << setw(5) << s->first_char_index << " "
        << setw(6) << s->last_char_index << "  ";
        int top;
        if (current_n > s->last_char_index)
            top = s->last_char_index;
        else
            top = current_n;
        for (int l = s->first_char_index; l <= top; l++) {
            cout << Sequence[l];
            file << Sequence[l];
        }
        cout << "\n";
        file << "\n";
    }
}


/**
 * This function is basicly the Ukkonnens algorithm implementation.
 * It is called repetitively in for loop, once for each of the prefixes
 * of the input string. The prefix in question is marked with the index
 * of its last character.
 * At each prefix, start is at active point, add
 * a new edge marking the new last character, until is
 * reached a point where the new edge is not needed because to
 * the presence of an existing edge starting with the new
 * last character. This point is the end point.
 * end point is active point for the next pass through the tree.
 * It is required to update it is last_char_index to indicate
 * that it has grown by a single character, and then this
 * method can do all its work repeatevly.
 */
void AddPrefix(Suffix &active, int last_char_index) {
    int parent_node;
    int last_parent_node = -1;

    while (true) {
        Edge edge;
        parent_node = active.origin_node;
        // Step 1 is to try and find a matching edge for the given node.
        // If a matching edge exists, work is done with adding edges->breake.
        if (active.Explicit()) {
            edge = Edge::Find(active.origin_node, Sequence[last_char_index]);
            if (edge.start_node != -1)
                break;
        } else { //implicit node
            edge = Edge::Find(active.origin_node, Sequence[active.first_char_index]);
            int span = active.last_char_index - active.first_char_index;
            if (Sequence[edge.first_char_index + span + 1] == Sequence[last_char_index])
                break;
            parent_node = edge.SplitEdge(active);
        }

        // Matching edge is not found -> create a new one, add
        // it to the tree at the parent node position, and insert it
        // into the hash table.
        // WHen new node is created then also create a suffix link to the new node from
        // the last node visited.
        Edge *new_edge = new Edge(last_char_index, Length, parent_node);
        new_edge->Insert();
        if (last_parent_node > 0)
            Nodes[last_parent_node].suffix_node = parent_node;
        last_parent_node = parent_node;

        // This final step isto move on the next smaller suffix..
        if (active.origin_node == 0)
            active.first_char_index++;
        else
            active.origin_node = Nodes[active.origin_node].suffix_node;
        active.Canonize();
    }
    if (last_parent_node > 0)
        Nodes[last_parent_node].suffix_node = parent_node;
    active.last_char_index++; // Eendpoint is the next active point
    active.Canonize();
}

/** Validation code belowe **/

char CurrentString[MAX_LENGTH];
char GoodSuffixes[MAX_LENGTH];
char BranchCount[MAX_LENGTH * 2] = {0};

/**
 * The validation code consists of two functions. All it does
 * is traverse the entire tree. walk_tree() calls itself
 * recursively, building suffix strings up as it goes. When
 * walk_tree() reaches a leaf node, it checks to see if the
 * suffix derived from the tree matches the suffix starting
 * at the same point in the input text. If so, it tags that
 * suffix as correct in the GoodSuffixes[] array. When the tree
 * has been traversed, every entry in the GoodSuffixes array should
 * have a value of 1.
 * In addition, the BranchCount[] array is updated while the tree is
 * walked as well. Every count in the array has the number of child edges
 * emanating from that node.  If the node is a leaf node, the value is set to -1.
 *  When the routine finishes, every node should be a branch or a leaf.
 * The number of leaf nodes should match the number of suffixes (the length)
 * of the input string. The total number of branches from all
 * nodes should match the node count. */
void validate(ofstream &file) {
    for (int i = 0; i < Length; i++)
        GoodSuffixes[i] = 0;
    walk_tree(0, 0, file);
    int error = 0;
    for (int i = 0; i < Length; i++)
        if (GoodSuffixes[i] != 1) {
            cout << "Suffix " << i << " count wrong!\n";
            file << "Suffix " << i << " count wrong!\n";
            error++;
        }
    if (error == 0) {
        cout << "All Suffixes are present!\n";
        file << "All Suffixes are present!\n";
    }
    int leaf_count = 0;
    int branch_count = 0;
    for (int i = 0; i < Node::Count; i++) {
        if (BranchCount[i] == 0) {
            cout << "Logic error on node " << i << ", not a leaf or internal node!\n";
            file << "Logic error on node " << i << ", not a leaf or internal node!\n";
        } else if (BranchCount[i] == -1) {
            leaf_count++;
        } else {
            branch_count += BranchCount[i];
        }
    }
    cout << "Leaf count : " << leaf_count
    << (leaf_count == (Length + 1) ? " OK" : " Error!") << "\n";
    file << "Leaf count : " << leaf_count
    << (leaf_count == (Length + 1) ? " OK" : " Error!") << "\n";
    cout << "Branch count : " << branch_count
    << (branch_count == (Node::Count - 1) ? " OK" : " Error!") << endl;
    file << "Branch count : " << branch_count
    << (branch_count == (Node::Count - 1) ? " OK" : " Error!") << endl;
}

int walk_tree(int start_node, int last_char_so_far, ofstream &file) {
    int edges = 0;
    for (int i = 0; i < 256; i++) {
        Edge edge = Edge::Find(start_node, i);
        if (edge.start_node != -1) {
            if (BranchCount[edge.start_node] < 0)
                cerr << "Logic error on node "
                << edge.start_node
                << '\n';
            BranchCount[edge.start_node]++;
            edges++;
            int l = last_char_so_far;
            for (int j = edge.first_char_index; j <= edge.last_char_index; j++)
                CurrentString[l++] = Sequence[j];
            CurrentString[l] = '\0';
            if (walk_tree(edge.end_node, l, file)) {
                if (BranchCount[edge.end_node] > 0)
                    cerr << "Logic error on node "
                    << edge.end_node
                    << "\n";
                BranchCount[edge.end_node]--;
            }
        }
    }
    // If this node dont have any child edges it means that
    // current location is at a leaf node, and can check on this suffix.
    // Check to see if it matches the input string then turn off their
    // entry in the GoodSuffixes list.
    if (edges == 0) {
        cout << "Suffix : ";
        file << "Suffix : ";
        for (int m = 0; m < last_char_so_far; m++) {
            cout << CurrentString[m];
            file << CurrentString[m];
        }
        cout << "\n";
        file << "\n";
        GoodSuffixes[strlen(CurrentString) - 1]++;
        cout << "comparation: " << (Sequence + Length - strlen(CurrentString) + 1)
        << " with " << CurrentString << endl;
        file << "comparation: " << (Sequence + Length - strlen(CurrentString) + 1)
        << " with " << CurrentString << endl;
        if (strcmp(Sequence + Length - strlen(CurrentString) + 1, CurrentString) != 0) {
            cout << "Comparison failure!\n";
            file << "Comparison failure!\n";
        }
        return 1;
    } else {
        return 0;
    }
}
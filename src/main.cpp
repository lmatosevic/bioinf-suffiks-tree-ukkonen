#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string.h>
#include <cassert>
#include <string>

#include "../include/Suffix.h"
#include "../include/Edge.h"
#include "../include/Node.h"
#include "../include/Constants.h"

using std::cout;
using std::cin;
using std::cerr;
using std::setw;
using std::flush;
using std::endl;

void dump_edges(int current_n) {
    cout << " Start  End  Suf  First Last  String\n";
    for (int j = 0; j < HASH_TABLE_SIZE; j++) {
        Edge *s = Edges + j;
        if (s->start_node == -1)
            continue;
        cout << setw(5) << s->start_node << " "
        << setw(5) << s->end_node << " "
        << setw(3) << Nodes[s->end_node].suffix_node << " "
        << setw(5) << s->first_char_index << " "
        << setw(6) << s->last_char_index << "  ";
        int top;
        if (current_n > s->last_char_index)
            top = s->last_char_index;
        else
            top = current_n;
        for (int l = s->first_char_index;
             l <= top;
             l++)
            cout << T[l];
        cout << "\n";
    }
}

void AddPrefix(Suffix &active, int last_char_index) {
    int parent_node;
    int last_parent_node = -1;

    while (true) {
        Edge edge;
        parent_node = active.origin_node;
        //
        // Step 1 is to try and find a matching edge for the given node.
        // If a matching edge exists, we are done adding edges, so we break
        // out of this big loop.
        //
        if (active.Explicit()) {
            edge = Edge::Find(active.origin_node, T[last_char_index]);
            if (edge.start_node != -1)
                break;
        } else { //implicit node, a little more complicated
            edge = Edge::Find(active.origin_node, T[active.first_char_index]);
            int span = active.last_char_index - active.first_char_index;
            if (T[edge.first_char_index + span + 1] == T[last_char_index])
                break;
            parent_node = edge.SplitEdge(active);
        }
        //
        // We didn't find a matching edge, so we create a new one, add
        // it to the tree at the parent node position, and insert it
        // into the hash table.  When we create a new node, it also
        // means we need to create a suffix link to the new node from
        // the last node we visited.
        //
        Edge *new_edge = new Edge(last_char_index, N, parent_node);
        new_edge->Insert();
        if (last_parent_node > 0)
            Nodes[last_parent_node].suffix_node = parent_node;
        last_parent_node = parent_node;
        //
        // This final step is where we move to the next smaller suffix
        //
        if (active.origin_node == 0)
            active.first_char_index++;
        else
            active.origin_node = Nodes[active.origin_node].suffix_node;
        active.Canonize();
    }
    if (last_parent_node > 0)
        Nodes[last_parent_node].suffix_node = parent_node;
    active.last_char_index++;  //Now the endpoint is the next active point
    active.Canonize();
}

int main() {
    cout << "Enter sample string: " << flush;
    cin.getline(T, MAX_LENGTH - 1);
    N = strlen(T) - 1;
//
// The active point is the first non-leaf suffix in the
// tree.  We start by setting this to be the empty string
// at node 0.  The AddPrefix() function will update this
// value after every new prefix is added.
//
    Suffix active(0, 0, -1);  // The initial active prefix
    for (int i = 0; i <= N; i++)
        AddPrefix(active, i);
//
// Once all N prefixes have been added, the resulting table
// of edges is printed out, and a validation step is
// optionally performed.
//
    dump_edges(N);
    cout << "Would you like to validate the tree?"
    << flush;
    std::string s;
    getline(cin, s);
    if (s.size() > 0 && s[0] == 'Y' || s[0] == 'y')
        //validate();
        return 1;
}
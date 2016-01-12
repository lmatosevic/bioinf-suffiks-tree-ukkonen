//
// Created by luka on 12.01.16..
//
#include <iostream>
#include <iomanip>
#include <string.h>

#include "../include/Functions.h"
#include "../include/Edge.h"
#include "../include/Node.h"
#include "../include/Constants.h"

using std::cout;
using std::setw;
using std::cerr;
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
        if (active.Explicit()) {
            edge = Edge::Find(active.origin_node, T[last_char_index]);
            if (edge.start_node != -1)
                break;
        } else {
            edge = Edge::Find(active.origin_node, T[active.first_char_index]);
            int span = active.last_char_index - active.first_char_index;
            if (T[edge.first_char_index + span + 1] == T[last_char_index])
                break;
            parent_node = edge.SplitEdge(active);
        }

        Edge *new_edge = new Edge(last_char_index, N, parent_node);
        new_edge->Insert();
        if (last_parent_node > 0)
            Nodes[last_parent_node].suffix_node = parent_node;
        last_parent_node = parent_node;

        if (active.origin_node == 0)
            active.first_char_index++;
        else
            active.origin_node = Nodes[active.origin_node].suffix_node;
        active.Canonize();
    }
    if (last_parent_node > 0)
        Nodes[last_parent_node].suffix_node = parent_node;
    active.last_char_index++;
    active.Canonize();
}

char CurrentString[MAX_LENGTH];
char GoodSuffixes[MAX_LENGTH];
char BranchCount[MAX_LENGTH * 2] = {0};

void validate() {
    for (int i = 0; i < N; i++)
        GoodSuffixes[i] = 0;
    walk_tree(0, 0);
    int error = 0;
    for (int i = 0; i < N; i++)
        if (GoodSuffixes[i] != 1) {
            cout << "Suffix " << i << " count wrong!\n";
            error++;
        }
    if (error == 0)
        cout << "All Suffixes present!\n";
    int leaf_count = 0;
    int branch_count = 0;
    for (int i = 0; i < Node::Count; i++) {
        if (BranchCount[i] == 0)
            cout << "Logic error on node "
            << i
            << ", not a leaf or internal node!\n";
        else if (BranchCount[i] == -1)
            leaf_count++;
        else
            branch_count += BranchCount[i];
    }
    cout << "Leaf count : "
    << leaf_count
    << (leaf_count == (N + 1) ? " OK" : " Error!")
    << "\n";
    cout << "Branch count : "
    << branch_count
    << (branch_count == (Node::Count - 1) ? " OK" : " Error!")
    << endl;
}

int walk_tree(int start_node, int last_char_so_far) {
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
                CurrentString[l++] = T[j];
            CurrentString[l] = '\0';
            if (walk_tree(edge.end_node, l)) {
                if (BranchCount[edge.end_node] > 0)
                    cerr << "Logic error on node "
                    << edge.end_node
                    << "\n";
                BranchCount[edge.end_node]--;
            }
        }
    }
    if (edges == 0) {
        cout << "Suffix : ";
        for (int m = 0; m < last_char_so_far; m++)
            cout << CurrentString[m];
        cout << "\n";
        GoodSuffixes[strlen(CurrentString) - 1]++;
        cout << "comparing: " << (T + N - strlen(CurrentString) + 1)
        << " to " << CurrentString << endl;
        if (strcmp(T + N - strlen(CurrentString) + 1, CurrentString) != 0)
            cout << "Comparison failure!\n";
        return 1;
    } else {
        return 0;
    }
}
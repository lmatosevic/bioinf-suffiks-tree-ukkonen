#include <iostream>
#include <iomanip>
#include <string.h>

#include "../include/Suffix.h"
#include "../include/Constants.h"
#include "../include/Functions.h"
#include "../include/FASTAFormat.h"

using std::cout;
using std::cin;
using std::flush;
using std::cerr;
using std::string;
using std::endl;

int main(int argc, char *argv[]) {
    if (argc != 2 && argc != 3) {
        cerr << "Invalid number of arguments! Please provide test file path "
                        "and validation option(optional)." << flush;
        cout << "Usage: bioinf_suffiks_tree_ukkonen test/sample.txt validate";
        return 1;
    }
    FASTAFormat *reader = new FASTAFormat();
    string path = string(argv[1]);
    reader->readFASTAFile(path);
    const char *sequence = reader->sequenceToCharArray();
    strncpy(T, sequence, strlen(sequence));
    N = (int) (strlen(T) - 1);

    cout << "Building suffix tree..." << endl << flush;
    Suffix active(0, 0, -1);
    for (int i = 0; i <= N; i++) {
        AddPrefix(active, i);
    }
    dump_edges(N);
    string valid = "no";
    if(argc == 3) {
        valid = string(argv[2]);
    }
    if (valid.compare("validate") == 0) {
        validate();
    } else {
        cout << "Tree validation has been skipped!" << flush;
    }
    return 0;
}
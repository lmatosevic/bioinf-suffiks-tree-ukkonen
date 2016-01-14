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
    if (argc != 3 && argc != 4) {
        cerr << "Invalid number of arguments! Please provide test file path, output file "
                "and validation option(optional)." << flush;
        cout << "Usage: bioinf_suffiks_tree_ukkonen test/sample.txt output/out.txt [-validate]";
        return 1;
    }
    FASTAFormat *reader = new FASTAFormat();
    string path = string(argv[1]);
    reader->readFASTAFile(path);
    const char *sequence = reader->sequenceToCharArray();
    strncpy(Sequence, sequence, strlen(sequence));
    Length = (int) (strlen(Sequence) - 1);

    cout << "Building suffix tree..." << endl << flush;
    Suffix active(0, 0, -1);
    for (int i = 0; i <= Length; i++) {
        AddPrefix(active, i);
    }
    print_edges(Length);
    string valid = "no";
    if (argc == 4) {
        valid = string(argv[3]);
    }
    if (valid.compare("-validate") == 0) {
        cout << "Validation has been started!" << flush;
        validate();
    } else {
        cout << "Tree validation has been skipped!" << flush;
    }
    return 0;
}
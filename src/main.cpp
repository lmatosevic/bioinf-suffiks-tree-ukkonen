#include <iostream>
#include <fstream>
#include <iomanip>
#include <string.h>
#include <chrono>

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
using std::ofstream;
using std::chrono::steady_clock;

int main(int argc, char *argv[]) {
    if (argc != 3 && argc != 4) {
        cerr << "Invalid number of arguments! Please provide test file path, output file "
                "and validation option(optional)." << flush;
        cout << "Usage: bioinf_suffiks_tree_ukkonen test/sample.txt output/out.txt [-validate]" << endl;
        return 1;
    }
    FASTAFormat *reader = new FASTAFormat();
    string path = string(argv[1]);
    reader->readFASTAFile(path);
    const char *sequence = reader->sequenceToCharArray();
    strncpy(Sequence, sequence, strlen(sequence));
    Length = (int) (strlen(Sequence) - 1);

    cout << "Building suffix tree..." << endl << flush;
    steady_clock::time_point begin_build = steady_clock::now();
    Suffix active(0, 0, -1);
    for (int i = 0; i <= Length; i++) {
        AddPrefix(active, i);
    }
    steady_clock::time_point end_build = steady_clock::now();
    string filePath = argv[2];
    ofstream file(filePath, ofstream::out);
    if (!file) {
        cerr << "Invalid output file provided!" << flush;
        return 2;
    }
    print_edges(Length, file);
    string valid = "no";
    if (argc == 4) {
        valid = string(argv[3]);
    }
    steady_clock::time_point begin_validate = steady_clock::now();
    if (valid.compare("-validate") == 0) {
        cout << "Validation has been started!" << flush;
        validate(file);
    } else {
        cout << "Tree validation has been skipped!" << flush;
    }
    steady_clock::time_point end_validate = steady_clock::now();

    cout << "Building duration = " <<
    std::chrono::duration_cast<std::chrono::microseconds>(end_build - begin_build).count() << " us" << endl;
    file << "Building duration = " <<
    std::chrono::duration_cast<std::chrono::microseconds>(end_build - begin_build).count() << " us" << endl;
    if (valid.compare("-validate") == 0) {
        cout << "Validation duration = " <<
        std::chrono::duration_cast<std::chrono::microseconds>(end_validate - begin_validate).count() << " us" << endl;
        file << "Validation duration = " <<
        std::chrono::duration_cast<std::chrono::microseconds>(end_validate - begin_validate).count() << " us" << endl;
    }
    file.close();
    return 0;
}
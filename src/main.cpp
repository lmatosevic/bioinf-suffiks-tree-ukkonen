#include <iostream>
#include <iomanip>
#include <string.h>

#include "../include/Suffix.h"
#include "../include/Constants.h"
#include "../include/Functions.h"

using std::cout;
using std::cin;
using std::flush;
using std::cerr;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Invalid number of arguments! Please provide test file path." << flush;
        return 1;
    }
    cout << "Enter sample string: " << flush;
    cin.getline(T, MAX_LENGTH - 1);
    N = (int) (strlen(T) - 1);

    Suffix active(0, 0, -1);
    for (int i = 0; i <= N; i++) {
        AddPrefix(active, i);
    }
    dump_edges(N);
    cout << "Do you want to validate generated suffix tree?(y/n)" << flush;
    std::string s;
    getline(cin, s);
    if (s.size() > 0 && s[0] == 'Y' || s[0] == 'y') {
        validate();
    }
    return 0;
}
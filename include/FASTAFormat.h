#pragma once

#include<string>

using namespace std;

class FASTAFormat {
private:
    string sequenceID;
    string description;
    string sequence;
public:
    FASTAFormat(void);

    ~FASTAFormat(void);

    void addHeader(string);

    string getSequenceID();

    void addSequence(string);

    string getSequence();

    void readFASTAFile(string);

    const char *sequenceToCharArray();
};


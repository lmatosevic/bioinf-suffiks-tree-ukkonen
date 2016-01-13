#include<cstdlib>
#include<iostream>
#include<fstream>
#include<string>
#include "../include/FASTAFormat.h"

FASTAFormat::FASTAFormat(void) {
    this->sequenceID = "";
    this->description = "";
    this->sequence = "";
}


FASTAFormat::~FASTAFormat(void) {
    this->sequenceID.clear();
    this->description.clear();
    this->sequence.clear();
}

void FASTAFormat::addHeader(string header) {
    string id = header.substr(0, header.find_first_of(' '));
    string desc = header.substr(header.find_first_of(' '), header.npos);
    this->sequenceID = id;
    this->description = desc;
}

string FASTAFormat::getSequenceID() {
    return this->sequenceID;
}

void FASTAFormat::addSequence(string seq) {
    this->sequence = seq;
}

string FASTAFormat::getSequence() {
    return this->sequence;
}

const char *FASTAFormat::sequenceToCharArray() {
    return this->sequence.c_str();
}

void FASTAFormat::readFASTAFile(string filePath) {
    ifstream file(filePath, ifstream::in);
    string str;
    if (!file) {
        cerr << "Error during file opening!" << endl;
        exit(-1);
    }
    while (getline(file, str)) {
        char firstChar = str.at(0);
        if (firstChar == '>') {
            this->addHeader(str.substr(1, str.npos));
        }
        else {
            this->sequence.append(str);
        }
    }
    file.close();
}

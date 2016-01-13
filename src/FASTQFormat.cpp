#include<cstdlib>
#include<iostream>
#include<fstream>
#include<string>
#include "../include/FASTQFormat.h"

FASTQFormat::FASTQFormat(void) {
}


FASTQFormat::~FASTQFormat(void) {
}


void FASTQFormat::setSequenceID(string id) {
    this->sequenceID = id;
}

void FASTQFormat::setSequence(string seq) {
    this->sequence = seq;
}

void FASTQFormat::setDescription(string desc) {
    this->description = desc;
}

void FASTQFormat::setQualityOfSequence(string qos) {
    this->qualityOfSequence = qos;
}

string FASTQFormat::getSequenceID(void) {
    return this->sequenceID;
}

string FASTQFormat::getSequence(void) {
    return this->sequence;
}

string FASTQFormat::getDescription(void) {
    return this->description;
}

string FASTQFormat::getQualityOfSequence(void) {
    return this->qualityOfSequence;
}

const char *FASTQFormat::sequneceToCharArray(void) {
    return this->sequence.c_str();
}

void FASTQFormat::readFASTQFile(string path) {
    ifstream file(path);
    string str;
    if (!file) {
        cerr << "Error during file opening!" << endl;
        exit(-1);
    }
    bool seq = false;
    while (getline(file, str)) {
        char firstChar = str.at(0);
        if (firstChar == '@') {
            this->setSequenceID(str.substr(1, str.find_first_of(' ')));
        }
        else if (firstChar == '+') {
            this->setDescription(str.substr(1, str.npos));
        }
        else {
            if (seq) {
                if (str.length() != this->getSequence().length()) {
                    cerr << "Quality of sequence (4th line) doesnt have enough characters!" << endl;
                    exit(-1);
                }
                this->setQualityOfSequence(str);
            }
            else {
                this->setSequence(str);
                seq = true;
            }
        }
    }
    file.close();
}